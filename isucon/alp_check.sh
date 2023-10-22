alp json --sort sum -r -m "/posts/[0-9]+,/@\w+" -o count,method,uri,min,avg,max,sum < /var/log/nginx/access.log
