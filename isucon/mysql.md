- スロークエリの有効化
 - mysqld.cnfの編集
  ```
  sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf

  ...
  slow_query_log          = 1
  slow_query_log_file     = /var/log/mysql/mysql-slow.log
  long_query_time = 0
  ...
  ```
 - mysqlからの設定: 永続化はmy.cof or set presist を使用
  ```
  set global slow_query_log = 1;
  set global   slow_query_log_file = "/var/log/mysql/mysql-slow.log";
  set global long_query_time = 0;
  ```

|  やりたいこと  |     コマンド      | 備考 |
| --- | ----------- | ------- |
| 設定編集    | sudo nano /etc/mysql/mysql.conf.d/mysqld.cnf |       |
| 再起動    | sudo systemctl restart mysql |       |
|  ログ解析   | sudo mysqldumpslow /var/log/mysql/mysql-slow.log |       |
| ログイン    | sudo mysql -u root |      |
| ログ再生成 | sudo mysqladmin flush-logs |  comments は対象テーブル |

---
|  やりたいこと  |     コマンド      | 備考 |
| --- | ----------- | ------- |
| データベース確認    | SHOW DATABASES; |   python |
| テーブル指定    | USE isuconp |     ruby |
| 対象テーブルの確認 | SHOW CREATE TABLE comments\G |  comments は対象テーブル |
| 対象テーブルの動作検証 | explain select * from `comments` WHERE `post_id` = 9995 order by `created_at` desc limit 3\G |  comments は対象テーブル |
| インデックスの挿入 | alter table comments add index post_id_idx(post_id); |  comments は対象テーブル |
| MySQLのスレッド処理内容確認 | show full processlist; |  |
