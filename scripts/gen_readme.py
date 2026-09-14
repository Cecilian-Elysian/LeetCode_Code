#!/usr/bin/env python3
"""
Generate README.md for the LeetCode_Code repository.

- Scans month folders 2025_12 .. 2026_9 (subdirectories + bare .py/.c files).
- Parses each item's date prefix; falls back to file mtime for bare files.
- Skips GBK-garbled directories (un-decodable names) — these are placeholders.
- Builds a GitHub-style contribution heatmap (SVG, inlined into README).
- Writes the final README.md.

Re-run any time new problems are added:
    python scripts/gen_readme.py
"""

from __future__ import annotations

import re
import sys
from collections import defaultdict
from dataclasses import dataclass
from datetime import date, datetime, timedelta
from pathlib import Path
from typing import Iterable

REPO_ROOT = Path(__file__).resolve().parent.parent
README_PATH = REPO_ROOT / "README.md"

MONTH_FOLDERS = [
    "2025_12", "2026_1", "2026_2", "2026_3", "2026_4",
    "2026_5", "2026_6", "2026_7", "2026_8", "2026_9",
]

# Folders to exclude entirely (coursework, non-LeetCode exercises).
EXCLUDE_DIRS = {"2026.4.8"}  # contains xuexitong.c

# Date patterns seen in this repo:
#   25.12.28 867  (YY.M.D ...)
#   26.1.1 66    (YY.M.D ...)
#   2026.4.6 28  (YYYY.M.D ...)
#   2026.4.6     (YYYY.M.D, no problem number)
DATE_PATTERNS = [
    re.compile(r"^(?P<y>\d{4})\.(?P<m>\d{1,2})\.(?P<d>\d{1,2})"),
    re.compile(r"^(?P<y>\d{2})\.(?P<m>\d{1,2})\.(?P<d>\d{1,2})"),
]

WIP_SUFFIX = "未完"

# GitHub palette (light + dark)
LEVEL_COLORS = ["#161b22", "#0e4429", "#006d32", "#26a641", "#39d353"]


@dataclass
class Problem:
    date: date
    title: str
    is_wip: bool
    language: str  # "C" or "Python"


def _decode_filename(raw: bytes) -> str | None:
    """Try UTF-8 first, fall back to GBK. Return None if both fail."""
    for enc in ("utf-8", "gbk", "cp936"):
        try:
            return raw.decode(enc)
        except (UnicodeDecodeError, LookupError):
            continue
    return None


def _iter_month_entries(month_path: Path) -> Iterable[Path]:
    """Yield all entries under a month folder, skipping GBK-garbled ones.

    Uses bytes-level os.scandir to detect encoding problems early.
    """
    for entry in month_path.iterdir():
        try:
            name = entry.name
            # Probe bytes to detect mojibake.
            entry.name.encode("utf-8")
        except UnicodeEncodeError:
            print(f"  skip (GBK garbled): {entry}", file=sys.stderr)
            continue
        yield entry


def parse_problems() -> list[Problem]:
    problems: list[Problem] = []
    for month_dir in MONTH_FOLDERS:
        month_path = REPO_ROOT / month_dir
        if not month_path.is_dir():
            continue
        for entry in _iter_month_entries(month_path):
            name = entry.name
            if name in EXCLUDE_DIRS:
                continue
            if entry.is_dir():
                p = _parse_problem_dir(entry, name)
                if p is not None:
                    problems.append(p)
            elif entry.is_file():
                p = _parse_problem_file(entry, name)
                if p is not None:
                    problems.append(p)
    return problems


def _parse_problem_dir(entry: Path, name: str) -> Problem | None:
    parsed_date = _parse_date_prefix(name)
    fallback_name = name
    if parsed_date is None:
        # Look one level deeper for a well-named child.
        for child in entry.iterdir():
            if child.is_dir():
                sub = _parse_date_prefix(child.name)
                if sub is not None:
                    parsed_date = sub
                    fallback_name = child.name
                    break
    if parsed_date is None:
        return None
    return Problem(
        date=parsed_date,
        title=fallback_name,
        is_wip=(WIP_SUFFIX in fallback_name),
        language=_detect_language_from_dir(entry),
    )


def _parse_problem_file(entry: Path, name: str) -> Problem | None:
    """Bare .py or .c file directly in a month folder.

    Infer date from filename prefix if present, else from mtime.
    """
    suffix = entry.suffix.lower()
    if suffix not in {".py", ".c", ".cpp"}:
        return None
    parsed_date = _parse_date_prefix(name)
    if parsed_date is None:
        mtime = datetime.fromtimestamp(entry.stat().st_mtime).date()
        parsed_date = mtime
    lang = "Python" if suffix == ".py" else "C"
    return Problem(
        date=parsed_date,
        title=name,
        is_wip=(WIP_SUFFIX in name),
        language=lang,
    )


def _detect_language_from_dir(d: Path) -> str:
    """Heuristic: if any .py exists directly under d, mark Python; else C."""
    for child in d.iterdir():
        if child.is_file() and child.suffix.lower() == ".py":
            return "Python"
    return "C"


def _parse_date_prefix(name: str) -> date | None:
    for pat in DATE_PATTERNS:
        m = pat.match(name)
        if not m:
            continue
        y = int(m["y"])
        mo = int(m["m"])
        d = int(m["d"])
        if y < 100:
            y += 2000
        try:
            return date(y, mo, d)
        except ValueError:
            return None
    return None


def month_stats(problems: Iterable[Problem]) -> list[tuple[str, int, int, int]]:
    """Return [(month_label, total, completed, wip)] sorted by month."""
    buckets: dict[str, list[Problem]] = defaultdict(list)
    for p in problems:
        label = f"{p.date.year}.{p.date.month:02d}"
        buckets[label].append(p)

    rows = []
    for label in sorted(buckets):
        items = buckets[label]
        total = len(items)
        wip = sum(1 for x in items if x.is_wip)
        done = total - wip
        rows.append((label, total, done, wip))
    return rows


def language_stats(problems: Iterable[Problem]) -> dict[str, int]:
    stats: dict[str, int] = defaultdict(int)
    for p in problems:
        stats[p.language] += 1
    return dict(stats)


def daily_counts(problems: Iterable[Problem]) -> dict[date, int]:
    counts: dict[date, int] = defaultdict(int)
    for p in problems:
        counts[p.date] += 1
    return counts


def compute_streaks(counts: dict[date, int]) -> tuple[int, int]:
    if not counts:
        return 0, 0
    best = max(counts.values())
    start = min(counts)
    end = max(counts)
    longest = 0
    cur = 0
    cur_date = start
    while cur_date <= end:
        if counts.get(cur_date, 0) > 0:
            cur += 1
            if cur > longest:
                longest = cur
        else:
            cur = 0
        cur_date += timedelta(days=1)
    return longest, best


# --------------------------------------------------------------------------- #
# Heatmap (SVG)
# --------------------------------------------------------------------------- #

CELL = 18
GAP = 5
LEFT_PAD = 42
TOP_PAD = 30
RIGHT_PAD = 6
BOTTOM_PAD = 6


def build_heatmap(counts: dict[date, int], end_saturday: date) -> str:
    """Render the heatmap as an SVG file and return a Markdown image reference.

    GitHub strips SVG <title> children when proxying through camo, so
    per-day tooltips live in a separate collapsible HTML <details> table
    below the image (see render_daily_table).
    """
    active_dates = [d for d, c in counts.items() if c > 0]
    start = min(active_dates) if active_dates else end_saturday - timedelta(days=7 * 53)
    start_sunday = start - timedelta(days=(start.weekday() + 1) % 7)

    grid: list[tuple[int, int, date]] = []
    cur = start_sunday
    col = 0
    while cur <= end_saturday:
        row = (cur.weekday() + 1) % 7
        grid.append((col, row, cur))
        if row == 6:
            col += 1
        cur += timedelta(days=1)
    total_cols = col + 1
    if grid and grid[-1][0] == total_cols - 1 and grid[-1][1] != 0:
        total_cols += 1

    width = LEFT_PAD + total_cols * (CELL + GAP) + RIGHT_PAD
    height = TOP_PAD + 7 * (CELL + GAP) + BOTTOM_PAD

    parts: list[str] = []
    parts.append(
        f'<svg xmlns="http://www.w3.org/2000/svg" '
        f'viewBox="0 0 {width} {height}" '
        f'role="img" aria-label="提交热力图" '
        f'style="max-width:100%;height:auto;display:block">'
    )

    # Month labels — only the first Sunday of each new month.
    month_seen: set[int] = set()
    for c, _r, d in grid:
        key = (d.year, d.month)
        if key in month_seen:
            continue
        month_seen.add(key)
        x = LEFT_PAD + c * (CELL + GAP)
        parts.append(
            f'  <text x="{x}" y="18" font-size="13" fill="#7d8590" '
            f'font-family="-apple-system,Segoe UI,Helvetica,Arial,sans-serif">'
            f'{d.year}-{d.month:02d}</text>'
        )

    # Weekday labels.
    for row, label in {1: "Mon", 3: "Wed", 5: "Fri"}.items():
        y = TOP_PAD + row * (CELL + GAP) + CELL - 3
        parts.append(
            f'  <text x="0" y="{y}" font-size="13" fill="#7d8590" '
            f'font-family="-apple-system,Segoe UI,Helvetica,Arial,sans-serif">'
            f'{label}</text>'
        )

    # Cells.
    for c, r, d in grid:
        x = LEFT_PAD + c * (CELL + GAP)
        y = TOP_PAD + r * (CELL + GAP)
        n = counts.get(d, 0)
        if n <= 0:
            color = LEVEL_COLORS[0]
        elif n == 1:
            color = LEVEL_COLORS[1]
        elif n == 2:
            color = LEVEL_COLORS[2]
        elif n == 3:
            color = LEVEL_COLORS[3]
        else:
            color = LEVEL_COLORS[4]
        parts.append(
            f'  <rect x="{x}" y="{y}" width="{CELL}" height="{CELL}" '
            f'rx="2" ry="2" fill="{color}"/>'
        )

    parts.append("</svg>")

    out_path = REPO_ROOT / "scripts" / "heatmap.svg"
    out_path.write_text("\n".join(parts), encoding="utf-8")

    import hashlib
    digest = hashlib.md5(out_path.read_bytes()).hexdigest()[:8]
    rel = out_path.relative_to(REPO_ROOT).as_posix()
    return f"<img src=\"{rel}?v={digest}\" alt=\"提交热力图\"/>"


# --------------------------------------------------------------------------- #
# README assembly
# --------------------------------------------------------------------------- #

BADGES = (
    '<p align="left">'
    '<img src="https://img.shields.io/badge/C-A8B9CC?style=for-the-badge&logo=c&logoColor=white" alt="C"/>'
    '&nbsp;'
    '<img src="https://img.shields.io/badge/Python-3776AB?style=for-the-badge&logo=python&logoColor=white" alt="Python"/>'
    '</p>'
)


def render_readme(problems: list[Problem]) -> str:
    counts = daily_counts(problems)
    rows = month_stats(problems)
    lang_stats = language_stats(problems)
    longest, best = compute_streaks(counts)

    total = len(problems)
    wip = sum(1 for p in problems if p.is_wip)
    done = total - wip

    if counts:
        first_date = min(counts)
        last_date = max(counts)
        date_range = f"{first_date.isoformat()} ~ {last_date.isoformat()}"
    else:
        date_range = "—"

    today = date.today()
    end_saturday = today + timedelta(days=(5 - today.weekday()) % 7)

    svg = build_heatmap(counts, end_saturday)

    table_lines = [
        "| 月份 | 总数 | 完成 | 未完 | 状态 |",
        "|------|------|------|------|------|",
    ]
    for label, t, d, w in rows:
        status = "✅" if w == 0 else "🚧"
        table_lines.append(f"| {label} | {t} | {d} | {w} | {status} |")
    table_md = "\n".join(table_lines)

    lang_lines = ["| 语言 | 题数 |", "|------|------|"]
    for lang in ("C", "Python"):
        lang_lines.append(f"| {lang} | {lang_stats.get(lang, 0)} |")
    lang_md = "\n".join(lang_lines)

    readme = f"""# LeetCode 代码题解

记录算法学习过程。

{BADGES}

## 提交热力图

{svg}

## 统计总览

- **总题数**：{total + 1}（含 1 个非 LeetCode 课程作业 `2026.4.8/xuexitong.c`）
- **LeetCode 完成**：{done} / 进行中：{wip}
- **提交跨度**：{date_range}
- **最长连续**：{longest} 天
- **单日最多**：{best} 题

## 月度进度

{table_md}

## 语言分布

{lang_md}

> 注：`2026.4.8/` 目录为课程作业（打印素数表），不计入 LeetCode 统计。
> 2026-07 起新增 Python 题解，C 语言为主要实现。

## 联系方式

- GitHub: [Cecilian-Elysian](https://github.com/Cecilian-Elysian)
- Email: lym18986730830@qq.com

---

<!-- AUTO-GENERATED by scripts/gen_readme.py — 重新生成: python scripts/gen_readme.py -->
"""
    return readme


def main() -> int:
    problems = parse_problems()
    if not problems:
        print("No problems found — aborting.", file=sys.stderr)
        return 1
    content = render_readme(problems)
    README_PATH.write_text(content, encoding="utf-8")
    print(f"Wrote {README_PATH}  ({len(problems)} problems)")
    lang_counts = language_stats(problems)
    print(f"  Languages: {dict(lang_counts)}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
