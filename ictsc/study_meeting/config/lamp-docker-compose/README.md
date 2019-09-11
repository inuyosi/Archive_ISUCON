# lamp-docker-compose
Quick start LAMP environment using docker-compose!

## Requirement
- Docker
- docker-compose

## Usage
### start
```
$ cd lamp-docker-compose
$ docker-compose up -d
```

### stop
```
$ docker-compose stop
```

### connect to MySQL
Use your favorite tool for connect to mysql with below information.

- Host: `localhost`
- Port: `33306`
- UserName: `root`
- Password: `password`

or use below command

```
$ docker-compose exec mysql mysql -u root -p secret
```

### reset MySQL data
Delete `./mysql` dir to initialize db.
