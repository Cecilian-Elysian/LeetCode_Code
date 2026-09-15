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
from urllib.parse import quote

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
    num: str           # LeetCode problem number ("" if unnumbered)
    slug: str          # camelCase slug, e.g. "twoSum" ("" if absent)
    path: str          # relative path to source file (for jump links)
    category: str      # primary category (Chinese), see CATEGORY_BY_NUM


# Primary category (Chinese) per LeetCode problem number. Add entries here
# when you solve a new problem; otherwise it falls back to "其他".
# Categories: 数组 / 字符串 / 哈希表 / 链表 / 树 / 栈 / 数学 /
#             位运算 / 双指针 / 排序 / 滑动窗口 / 前缀和 / 动态规划 / 模拟
CATEGORY_BY_NUM: dict[int, str] = {
    1: "数组", 2: "链表", 4: "数组", 5: "字符串", 6: "字符串",
    9: "数学", 12: "数学", 13: "哈希表", 14: "字符串", 20: "栈",
    21: "链表", 26: "数组", 27: "数组", 28: "字符串", 34: "数组",
    35: "数组", 49: "哈希表", 58: "字符串", 66: "数组", 67: "位运算",
    69: "数学", 70: "动态规划", 88: "数组", 100: "树", 101: "树",
    104: "树", 108: "树", 167: "数组", 206: "链表", 643: "数组",
    704: "数组", 744: "数组", 867: "数组", 961: "哈希表", 1170: "字符串",
    1343: "数组", 1385: "数组", 1422: "字符串", 1423: "数组", 1456: "字符串",
    1769: "位运算", 1833: "数组", 2090: "数组", 2235: "数学", 2236: "树",
    2379: "字符串", 2413: "数学", 2461: "数组", 2469: "数学", 2529: "数组",
    2586: "字符串", 2841: "数组", 3614: "字符串", 3658: "数学", 3679: "字符串",
}

CATEGORY_ORDER = [
    "数组", "字符串", "哈希表", "链表", "树", "栈", "数学",
    "位运算", "双指针", "排序", "滑动窗口", "前缀和", "动态规划",
    "模拟", "其他",
]


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
        # Outer folder has no date — try inner folders.
        for child in entry.iterdir():
            if child.is_dir():
                sub = _parse_date_prefix(child.name)
                if sub is not None:
                    parsed_date = sub
                    fallback_name = child.name
                    break
    if parsed_date is None:
        return None

    # Look for a source file: prefer the outer folder, fall back to the inner
    # (date-bearing) subfolder if the outer has none.
    src_rel: str | None = None
    outer_src = _find_source_file(entry)
    if outer_src:
        src_rel = outer_src
    elif fallback_name != name:
        inner = entry / fallback_name
        if inner.is_dir():
            inner_src = _find_source_file(inner)
            if inner_src:
                src_rel = f"{fallback_name}/{inner_src}"

    if src_rel:
        rel_path = (entry / src_rel).relative_to(REPO_ROOT).as_posix()
        slug_base = src_rel.split("/")[-1]
        slug = re.sub(r"\.(c|py|cpp)$", "", slug_base, flags=re.IGNORECASE)
        if slug in {"源", "source"}:
            slug = ""
    else:
        rel_path = entry.relative_to(REPO_ROOT).as_posix()
        slug = ""

    num, _ = _parse_num_and_slug(fallback_name)
    category = CATEGORY_BY_NUM.get(int(num), "其他") if num.isdigit() else "其他"

    return Problem(
        date=parsed_date,
        title=fallback_name,
        is_wip=(WIP_SUFFIX in fallback_name),
        language=_detect_language_from_dir(entry),
        num=num,
        slug=slug,
        path=rel_path,
        category=category,
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
    num, slug = _parse_num_and_slug(name)
    rel_path = entry.relative_to(REPO_ROOT).as_posix()
    category = CATEGORY_BY_NUM.get(int(num), "其他") if num.isdigit() else "其他"
    return Problem(
        date=parsed_date,
        title=name,
        is_wip=(WIP_SUFFIX in name),
        language=lang,
        num=num,
        slug=slug,
        path=rel_path,
        category=category,
    )


def _detect_language_from_dir(d: Path) -> str:
    """Heuristic: if any .py exists directly under d, mark Python; else C."""
    for child in d.iterdir():
        if child.is_file() and child.suffix.lower() == ".py":
            return "Python"
    return "C"


def _parse_num_and_slug(name: str) -> tuple[str, str]:
    """Extract LeetCode problem number and camelCase slug from a name.

    Examples:
        "2026.9.14 1 twoSum.py"        -> ("1",  "twoSum")
        "26.1.13 13"                   -> ("13", "")
        "2026.4.26 2841(未完)"         -> ("2841", "")
        "25.12.28.1422"                -> ("1422", "")
        "26.1.1 Q1"                    -> ("",   "")
    """
    m_num = re.search(r"\s(\d+)\b", name)
    if not m_num:
        # Fallback for the legacy "YY.M.D.N" naming, e.g. "25.12.28.1422" → 1422.
        # Only matches 2-digit-year dates to avoid mistaking "2026.4.6" for #6.
        m_num = re.match(r"^\d{2}\.\d{1,2}\.\d{1,2}\.(\d+)$", name)
    if not m_num:
        return "", ""
    num = m_num.group(1)
    rest = name[m_num.end():].strip()
    rest = re.sub(r"\.(c|py|cpp)$", "", rest, flags=re.IGNORECASE)
    rest = re.sub(r"\(.*?\)$", "", rest).strip()
    return num, rest


_SKIP_SUBDIRS = {"x64", "x86", "debug", "release", "源文件", "ipch", ".vs"}


def _find_source_file(d: Path) -> str | None:
    """Pick the primary source file inside a problem directory.

    Priority: .py > 源.cpp / source.cpp > .c

    Returns a path relative to ``d`` (may contain one ``/`` if the source
    file is inside a subdirectory). Returns None if nothing matches.
    """
    candidates: list[tuple[int, str]] = []
    subdirs: list[Path] = []
    for child in d.iterdir():
        if child.is_dir():
            if child.name.lower() not in _SKIP_SUBDIRS:
                subdirs.append(child)
            continue
        n = child.name
        low = n.lower()
        if low.endswith(".py"):
            candidates.append((0, n))
        elif low in ("源.cpp", "source.cpp"):
            candidates.append((1, n))
        elif low.endswith(".c"):
            candidates.append((2, n))
    if candidates:
        candidates.sort()
        return candidates[0][1]
    # Recurse one level for the nested "outer/inner/源.cpp" pattern.
    for sub in subdirs:
        result = _find_source_file(sub)
        if result:
            return f"{sub.name}/{result}"
    return None


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
# Category index
# --------------------------------------------------------------------------- #


def render_category_section(problems: list[Problem]) -> str:
    """Render the '题目分类' section: jump nav + grouped problem lists."""
    buckets: dict[str, list[Problem]] = defaultdict(list)
    for p in problems:
        buckets[p.category].append(p)

    def sort_key(p: Problem) -> tuple[int, str, str]:
        return (
            int(p.num) if p.num.isdigit() else 999999,
            p.slug,
            p.title,
        )
    for cat in buckets:
        buckets[cat].sort(key=sort_key)

    lines: list[str] = []

    nav_lines = ["| 分类 | 题数 |", "|------|------|"]
    for cat in CATEGORY_ORDER:
        if cat not in buckets:
            continue
        count = len(buckets[cat])
        anchor = f"#{cat}-{count}"
        nav_lines.append(f"| [{cat} ({count})]({anchor}) | {count} |")
    lines.append("\n".join(nav_lines))
    lines.append("")

    for cat in CATEGORY_ORDER:
        if cat not in buckets:
            continue
        items = buckets[cat]
        lines.append(f"### {cat} ({len(items)})")
        lines.append("")
        for p in items:
            if p.num and p.slug:
                label = f"#{p.num} {p.slug}"
            elif p.num:
                label = f"#{p.num}"
            else:
                label = p.title
            link_target = quote(p.path, safe="/-._~")
            lines.append(f"- [{label}]({link_target})")
        lines.append("")

    return "\n".join(lines).rstrip() + "\n"


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
    category_md = render_category_section(problems)

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

## 题目分类

{category_md}

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
