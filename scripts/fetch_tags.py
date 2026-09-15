"""Fetch LeetCode topic tags and cache to scripts/problems_tags.json.

GraphQL endpoint: https://leetcode.com/graphql
Uses problemsetQuestionListV2 with skip/limit pagination (max 100 per batch).
"""
from __future__ import annotations

import json
import sys
import time
import urllib.error
import urllib.request
from pathlib import Path

ENDPOINT = "https://leetcode.com/graphql"
BATCH_SIZE = 100
SLEEP_SECONDS = 1.0  # polite pacing

OUT_PATH = Path(__file__).resolve().parent / "problems_tags.json"

QUERY = """
query problemsetQuestionListV2($limit: Int!, $skip: Int) {
  problemsetQuestionListV2(limit: $limit, skip: $skip) {
    questions {
      questionFrontendId
      titleSlug
      topicTags {
        name
      }
    }
  }
}
"""


def fetch_batch(skip: int, limit: int = BATCH_SIZE) -> list:
    body = json.dumps({
        "query": QUERY,
        "variables": {"limit": limit, "skip": skip},
    }).encode("utf-8")
    req = urllib.request.Request(ENDPOINT, data=body, method="POST")
    req.add_header("Content-Type", "application/json")
    req.add_header("User-Agent", "Mozilla/5.0")
    last_err: Exception | None = None
    for attempt in range(4):
        try:
            with urllib.request.urlopen(req, timeout=30) as resp:
                payload = json.loads(resp.read())
            if "errors" in payload:
                raise RuntimeError(f"GraphQL errors: {payload['errors']}")
            return payload["data"]["problemsetQuestionListV2"]["questions"]
        except (urllib.error.URLError, TimeoutError) as e:
            last_err = e
            wait = 2 ** attempt
            print(f"  attempt {attempt + 1} failed: {e}; sleeping {wait}s", file=sys.stderr)
            time.sleep(wait)
    raise RuntimeError(f"fetch_batch(skip={skip}) failed: {last_err}")


def fetch_all() -> dict[str, list[str]]:
    """Return {questionFrontendId: [tag, ...]} for every LeetCode problem."""
    out: dict[str, list[str]] = {}
    skip = 0
    while True:
        print(f"fetching skip={skip} ...", file=sys.stderr)
        batch = fetch_batch(skip)
        if not batch:
            break
        for q in batch:
            out[q["questionFrontendId"]] = [t["name"] for t in q["topicTags"]]
        if len(batch) < BATCH_SIZE:
            break
        skip += BATCH_SIZE
        time.sleep(SLEEP_SECONDS)
    return out


def main() -> int:
    if OUT_PATH.exists():
        # Per design: skip if cache present. Force-refresh by deleting the file.
        print(f"{OUT_PATH.name} already exists; delete it to re-fetch.")
        return 0
    tags = fetch_all()
    OUT_PATH.write_text(
        json.dumps(tags, ensure_ascii=False, indent=0, sort_keys=True),
        encoding="utf-8",
    )
    print(f"Wrote {OUT_PATH} ({len(tags)} problems)")
    return 0


if __name__ == "__main__":
    sys.exit(main())