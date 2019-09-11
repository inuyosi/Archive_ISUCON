FROM php:7.2.3-apache

RUN apt update &&\
    echo 'date.timezone = Asia/Tokyo' >> /usr/local/etc/php/conf.d/99_myconf.ini
# RUN docker-php-ext-install pdo_mysql
# RUN docker-php-ext-install pdo


CMD ["apache2-foreground"]
