#### unicornの修正(Rubyの場合)
- 普通はCPUの2倍の数値にする。
```
$ sudo cat /home/isucon/private_isu/webapp/ruby/unicorn_config.rb
worker_processes 4 #CPUが2個の場合
preload_app true
listen "0.0.0.0:8080"
```
