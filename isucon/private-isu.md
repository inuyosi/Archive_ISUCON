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
