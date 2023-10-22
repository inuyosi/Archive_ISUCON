- whttps://github.com/catatsuy/private-isu#ami

#### nginx
- before: `126.208.117.147 - - [14/Oct/2023:20:27:06 +0900] "GET /image/10001.png HTTP/1.1" 200 491313 "http://35.74.241.117/posts/10001" "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60"`

- edit /etc/nginx/nginx.conf
```
sudo nano /etc/nginx/nginx.conf

...
        log_format json escape=json     '{"time":"$time_iso8601",'
                                        '"host":"$remote_addr",'
                                        '"port":$remote_port,'
                                        '"method":"$request_method",'
                                        '"uri":"$request_uri",'
                                        '"status":"$status",'
                                        '"body_bytes":"$body_bytes_sent",'
                                        '"referer":"$http_referer",'
                                        '"ua":"$http_user_agent",'
                                        '"request_time":"$request_time",'
                                        '"response_time":"$upstream_response_time",';

        access_log /var/log/nginx/access.log json;
...
```

- apply(reload):
`sudo systemctl reload nginx`

- after: `{"time":"2023-10-14T20:59:07+09:00","host":"126.208.117.147","port":57417,"method":"GET","uri":"/image/10001.png","status":"200","body_bytes":"491313","referer":"http://35.74.241.117/posts/10001","ua":"Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/117.0.0.0 Safari/537.36 Edg/117.0.2045.60","request_time":"0.019","response_time":"0.000"}`

---
#### alp
- install
  - https://github.com/tkuchiki/alp/
```
wget https://github.com/tkuchiki/alp/releases/download/v1.0.21/alp_linux_amd64.tar.gz
tar -xvzf alp_linux_amd64.tar.gz

sudo install ./alp /usr/local/bin/alp
```

- result
```
 alp json --file /var/log/nginx/access.log
+-------+-----+-----+-----+-----+-----+--------+------------------+-------+-------+-------+-------+-------+-------+-------+--------+------------+------------+------------+------------+
| COUNT | 1XX | 2XX | 3XX | 4XX | 5XX | METHOD |       URI        |  MIN  |  MAX  |  SUM  |  AVG  |  P90  |  P95  |  P99  | STDDEV | MIN(BODY)  | MAX(BODY)  | SUM(BODY)  | AVG(BODY)  |
+-------+-----+-----+-----+-----+-----+--------+------------------+-------+-------+-------+-------+-------+-------+-------+--------+------------+------------+------------+------------+
| 2     | 0   | 2   | 0   | 0   | 0   | GET    | /image/10001.png | 0.000 | 0.000 | 0.000 | 0.000 | 0.000 | 0.000 | 0.000 | 0.000  | 491313.000 | 491313.000 | 982626.000 | 491313.000 |
+-------+-----+-----+-----+-----+-----+--------+------------------+-------+-------+-------+-------+-------+-------+-------+--------+------------+------------+------------+------------+
```

#### ab
- install
```
sudo apt update
sudo apt install apache2-utils
```

- result
```
ab -c 1 -n 10 http://localhost/
This is ApacheBench, Version 2.3 <$Revision: 1879490 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/

Benchmarking localhost (be patient).....done


Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /
Document Length:        34907 bytes

Concurrency Level:      1
Time taken for tests:   12.533 seconds
Complete requests:      10
Failed requests:        0
Total transferred:      352790 bytes
HTML transferred:       349070 bytes
Requests per second:    0.80 [#/sec] (mean)
Time per request:       1253.277 [ms] (mean)
Time per request:       1253.277 [ms] (mean, across all concurrent requests)
Transfer rate:          27.49 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:  1241 1253  14.7   1252    1292
Waiting:     1240 1253  14.7   1252    1292
Total:       1241 1253  14.7   1252    1292

Percentage of the requests served within a certain time (ms)
  50%   1252
  66%   1252
  75%   1254
  80%   1258
  90%   1292
  95%   1292
  98%   1292
  99%   1292
 100%   1292 (longest request)
```

- compare alp, ab
```
 tail -n 10 /var/log/nginx/access.log | alp json -o count,method,uri,min,avg,max
+-------+--------+-----+-------+-------+-------+
| COUNT | METHOD | URI |  MIN  |  AVG  |  MAX  |
+-------+--------+-----+-------+-------+-------+
| 10    | GET    | /   | 1.240 | 1.253 | 1.292 |
+-------+--------+-----+-------+-------+-------+
```

- 乖離がある場合: ネットワーク影響を大きく受けている
  - alpはnginxのホスト上, abはネットワーク経由
####  log rotate
- script: log_rotate.sh
```
#!/bin/sh

sudo mv /var/log/nginx/access.log /var/log/nginx/access.log.`date +%Y%m%d-%H%M%S`
sudo nginx -s reopen
```

#### bottle-neck check
<img width="1274" alt="image" src="https://github.com/inuyosi/study/assets/23133280/e16ff3d3-2016-4c73-8870-3eac0eab62d4">

#### MySQL
- edit: `/etc/mysql/mysql.conf.d/mysqld.cnf`
  - remove comment-out + long_query_time value from 2 to 0 
```
sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf

...
slow_query_log          = 1
slow_query_log_file     = /var/log/mysql/mysql-slow.log
long_query_time = 0
...

sudo systemctl restart mysql
```

#### mysqldumpslow
```
sudo mysqldumpslow /var/log/mysql/mysql-slow.log

Reading mysql slow query log from /var/log/mysql/mysql-slow.log
Count: 528  Time=0.04s (22s)  Lock=0.00s (0s)  Rows=2.9 (1512), isuconp[isuconp]@localhost
  SELECT * FROM `comments` WHERE `post_id` = N ORDER BY `created_at` DESC LIMIT N

Count: 24  Time=0.02s (0s)  Lock=0.00s (0s)  Rows=10001.0 (240024), isuconp[isuconp]@localhost
  SELECT `id`, `user_id`, `body`, `created_at`, `mime` FROM `posts` ORDER BY `created_at` DESC

Count: 528  Time=0.01s (6s)  Lock=0.00s (0s)  Rows=1.0 (528), isuconp[isuconp]@localhost
  SELECT COUNT(*) AS `count` FROM `comments` WHERE `post_id` = N

Count: 1  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=1.0 (1), isuconp[isuconp]@localhost
  SELECT * FROM `posts` WHERE `id` = N

Count: 1  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), isuconp[isuconp]@localhost
  SET NAMES utf8mb4

Count: 2040  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=1.0 (2040), isuconp[isuconp]@localhost
  SELECT * FROM `users` WHERE `id` = N

Count: 5936  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=4741.0 (28142839), isuconp[isuconp]@localhost
  #

Count: 3097  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), 0users@0hosts
  administrator command: Prepare

Count: 2839  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), 0users@0hosts
  administrator command: Close stmt

```
- /var/log/mysql/mysql-slow.log
```
# User@Host: isuconp[isuconp] @ localhost []  Id:     8
# Query_time: 0.041236  Lock_time: 0.000001 Rows_sent: 3  Rows_examined: 100003
SET timestamp=1697288837;
SELECT * FROM `comments` WHERE `post_id` = 9980 ORDER BY `created_at` DESC LIMIT 3;
```

#### mysql check
```
sudo mysql -u root

mysql> SHOW DATABASES;
+--------------------+
| Database           |
+--------------------+
| information_schema |
| isuconp            |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
5 rows in set (0.00 sec)

mysql> USE isuconp
Reading table information for completion of table and column names
You can turn off this feature to get a quicker startup with -A

Database changed

mysql> SHOW CREATE TABLE comments\G
*************************** 1. row ***************************
       Table: comments
Create Table: CREATE TABLE `comments` (
  `id` int NOT NULL AUTO_INCREMENT,
  `post_id` int NOT NULL,
  `user_id` int NOT NULL,
  `comment` text NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`)
) ENGINE=InnoDB AUTO_INCREMENT=100001 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
1 row in set (0.00 sec)

mysql> explain select * from `comments` WHERE `post_id` = 9995 order by `created_at` desc limit 3\G
*************************** 1. row ***************************
           id: 1
  select_type: SIMPLE
        table: comments
   partitions: NULL
         type: ALL
possible_keys: NULL
          key: NULL
      key_len: NULL
          ref: NULL
         rows: 96610
     filtered: 10.00
        Extra: Using where; Using filesort
1 row in set, 1 warning (0.00 sec)

```
#### add index to post_id
```
mysql> alter table comments add index post_id_idx(post_id);
Query OK, 0 rows affected (0.63 sec)
Records: 0  Duplicates: 0  Warnings: 0

mysql> explain select * from `comments` WHERE `post_id` = 9995 order by `created_at` desc limit 3\G
*************************** 1. row ***************************
           id: 1
  select_type: SIMPLE
        table: comments
   partitions: NULL
         type: ref
possible_keys: post_id_idx
          key: post_id_idx
      key_len: 4
          ref: const
         rows: 6
     filtered: 100.00
        Extra: Using filesort
1 row in set, 1 warning (0.00 sec)

mysql> SHOW CREATE TABLE comments\G
*************************** 1. row ***************************
       Table: comments
Create Table: CREATE TABLE `comments` (
  `id` int NOT NULL AUTO_INCREMENT,
  `post_id` int NOT NULL,
  `user_id` int NOT NULL,
  `comment` text NOT NULL,
  `created_at` timestamp NOT NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`),
  KEY `post_id_idx` (`post_id`)
) ENGINE=InnoDB AUTO_INCREMENT=100001 DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_0900_ai_ci
1 row in set (0.00 sec)
```

- /var/log/mysql/mysql-slow.log
```
# Query_time: 0.000321  Lock_time: 0.000003 Rows_sent: 3  Rows_examined: 9
SET timestamp=1697290924;
select * from `comments` where `post_id` = 9995 order by `created_at` desc limit 3;
```

```
sudo rm /var/log/mysql/mysql-slow.log
sudo mysqladmin flush-logs
```
<img width="1262" alt="image" src="https://github.com/inuyosi/study/assets/23133280/7183f42c-4a44-4b23-9d4f-35e19da59793">

```
ab -c 1 -t 30 http://localhost/
This is ApacheBench, Version 2.3 <$Revision: 1879490 $>
Copyright 1996 Adam Twiss, Zeus Technology Ltd, http://www.zeustech.net/
Licensed to The Apache Software Foundation, http://www.apache.org/
Benchmarking localhost (be patient)
Finished 432 requests
Server Software:        nginx/1.18.0
Server Hostname:        localhost
Server Port:            80

Document Path:          /
Document Length:        34907 bytes

Concurrency Level:      1
Time taken for tests:   30.009 seconds
Complete requests:      432
Failed requests:        0
Total transferred:      15240528 bytes
HTML transferred:       15079824 bytes
Requests per second:    14.40 [#/sec] (mean)
Time per request:       69.464 [ms] (mean)
Time per request:       69.464 [ms] (mean, across all concurrent requests)
Transfer rate:          495.97 [Kbytes/sec] received

Connection Times (ms)
              min  mean[+/-sd] median   max
Connect:        0    0   0.0      0       0
Processing:    66   69   1.5     70      74
Waiting:       66   69   1.5     69      74
Total:         66   69   1.5     70      74

Percentage of the requests served within a certain time (ms)
  50%     70
  66%     70
  75%     70
  80%     71
  90%     71
  95%     72
  98%     73
  99%     73
 100%     74 (longest request)

 sudo mysqldumpslow /var/log/mysql/mysql-slow.log

Reading mysql slow query log from /var/log/mysql/mysql-slow.log
Count: 432  Time=0.01s (6s)  Lock=0.00s (0s)  Rows=10001.0 (4320432), isuconp[isuconp]@localhost
  SELECT `id`, `user_id`, `body`, `created_at`, `mime` FROM `posts` ORDER BY `created_at` DESC

Count: 1  Time=0.01s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), root[root]@localhost
  FLUSH LOGS

Count: 9504  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=2.9 (27216), isuconp[isuconp]@localhost
  SELECT * FROM `comments` WHERE `post_id` = N ORDER BY `created_at` DESC LIMIT N

Count: 9504  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=1.0 (9504), isuconp[isuconp]@localhost
  SELECT COUNT(*) AS `count` FROM `comments` WHERE `post_id` = N

Count: 36720  Time=0.00s (1s)  Lock=0.00s (0s)  Rows=1.0 (36720), isuconp[isuconp]@localhost
  SELECT * FROM `users` WHERE `id` = N

Count: 111466  Time=0.00s (1s)  Lock=0.00s (0s)  Rows=4617.3 (514675213), 2users@localhost
  #

Count: 1  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), 0users@0hosts
  administrator command: Quit

Count: 55737  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), 0users@0hosts
  administrator command: Close stmt

Count: 55728  Time=0.00s (0s)  Lock=0.00s (0s)  Rows=0.0 (0), 0users@0hosts
  administrator command: Prepare
```

#### dstat
apt update -y && apt install dstat
```
$ dstat --cpu
--total-cpu-usage--
usr sys idl wai stl
  9   2  89   0   0
  0   0 100   0   0
  0   0 100   0   0                                                                                                          0   0 100   0   0
  0   0 100   0   0
  0   0 100   0   0
  0   0 100   0   0
 30   6  64   0   0
 50   6  44   0   0
```

#### top確認
```
top - 20:06:02 up 16 min,  3 users,  load average: 0.55, 0.37, 0.20
Tasks: 113 total,   2 running, 111 sleeping,   0 stopped,   0 zombie
%Cpu(s): 47.8 us,  6.3 sy,  0.0 ni, 45.7 id,  0.0 wa,  0.0 hi,  0.2 si,  0.0 st
MiB Mem :   3827.7 total,   2105.9 free,    659.0 used,   1062.8 buff/cache
MiB Swap:      0.0 total,      0.0 free,      0.0 used.   2927.3 avail Mem

    PID USER      PR  NI    VIRT    RES    SHR S  %CPU  %MEM     TIME+ COMMAND                                                           694 isucon    20   0  221808  74136   9984 R  62.3   1.9   2:24.24 ruby
    595 mysql     20   0 1784712 421888  36224 S  46.0  10.8   1:46.15 mysqld
    376 memcache  20   0  413424   7424   3712 S   0.3   0.2   0:00.57 memcached
    460 www-data  20   0   55844   6004   4096 S   0.3   0.2   0:00.48 nginx
   1624 ubuntu    20   0   10892   3840   3200 R   0.3   0.1   0:00.01 top
      1 root      20   0  100688  11516   8316 S   0.0   0.3   0:02.18 systemd
      2 root      20   0       0      0      0 S   0.0   0.0   0:00.00 kthreadd
      3 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 rcu_gp
      4 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 rcu_par_gp
      5 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 slub_flushwq
      6 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 netns
      8 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 kworker/0:0H-events_highpri
     10 root       0 -20       0      0      0 I   0.0   0.0   0:00.00 mm_percpu_wq
     11 root      20   0       0      0      0 I   0.0   0.0   0:00.00 rcu_tasks_rude_kthread
```

#### unicornの修正(Rubyの場合)
- 普通はCPUの2倍の数値にする。
```
$ sudo cat /home/isucon/private_isu/webapp/ruby/unicorn_config.rb
worker_processes 4 #CPUが2個の場合
preload_app true
listen "0.0.0.0:8080"
```

#### install k6
- https://k6.io/docs/get-started/installation/
```
sudo gpg -k
sudo gpg --no-default-keyring --keyring /usr/share/keyrings/k6-archive-keyring.gpg --keyserver hkp://keyserver.ubuntu.com:80 --recv-keys C5AD17C747E3415A3642D57D77C6C491D6AC1D69
echo "deb [signed-by=/usr/share/keyrings/k6-archive-keyring.gpg] https://dl.k6.io/deb stable main" | sudo tee /etc/apt/sources.list.d/k6.list
sudo apt-get update
sudo apt-get install k6
```
#### create senario for k6
- ab.js
```
import http from "k6/http";

const BASE_URL = "http://localhost";

export default function () {
    http.get(`${BASE_URL}/`);
}
```
- config.js
```
const BASE_URL = "http://localhost";

export function url(path) {
    return `${BASE_URL}${path}`;
}
```
- initialize.js
```
import http from "k6/http";

import { sleep } from "k6";

import { url } from "./config.js";

export default function () {
    http.get(url("/initialize"), {
        timeout: "10s",
    });

    sleep(1);
}
```

- その他コードは別に保存

#### alp check
```
$ alp json \
> --sort sum -r \
> -m "/posts/[0-9]+,/@\w+" \
> -o count,method,uri,min,avg,max,sum \
> < /var/log/nginx/access.log
+-------+--------+---------------+-------+-------+-------+---------+
| COUNT | METHOD |      URI      |  MIN  |  AVG  |  MAX  |   SUM   |
+-------+--------+---------------+-------+-------+-------+---------+
| 426   | GET    | /             | 0.156 | 0.259 | 0.500 | 110.240 |
| 426   | POST   | /login        | 0.004 | 0.075 | 0.228 | 31.852  |
| 149   | GET    | /@\w+         | 0.064 | 0.161 | 0.364 | 24.052  |
| 128   | POST   | /             | 0.008 | 0.062 | 0.200 | 7.884   |
| 128   | GET    | /posts/[0-9]+ | 0.004 | 0.055 | 0.240 | 7.096   |
| 1     | GET    | /initialize   | 0.028 | 0.028 | 0.028 | 0.028   |
+-------+--------+---------------+-------+-------+-------+---------+
```
