- `cat /etc/nginx/sites-available/isucon.conf`
  ```
  server {
    listen 80;
  
    client_max_body_size 10m;
    root /home/isucon/private_isu/webapp/public/;

    #静的ファイルをnginx経由で実施  
    location /css/ {
      root /home/isucon/private_isu/webapp/public/;
      # HTTPヘッダを活用してクライアント側にキャッシュさせる
      expires 1d;
    }
  
    #静的ファイルをnginx経由で実施  
    location /js/ {
      root /home/isucon/private_isu/webapp/public/;
    }
  
    location / {
      proxy_set_header Host $host;
      proxy_pass http://localhost:8080;
    }
  }
  ```
- hoge
