確認コマンド
---
- mamcached: stats
  - evictions, get_hits, get_misses
- Redis: INFO
  - evicted_keys, keyspace_hits, keyspace_misses
