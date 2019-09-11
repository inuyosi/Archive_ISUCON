<?php
 define('DB_HOST', 'localhost');
// define('DB_HOST', 'db');
define('DB_USER', 'root');
define('DB_PASSWORD', 'secret');
define('DB_NAME', 'mysql');
try {
  $dsn = 'mysql:host='.DB_HOST.'; dbname='.DB_NAME.';charset=utf8;';
  $pdo = new PDO($dsn, DB_USER, DB_PASSWORD);
  $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);
  print('接続しました。');
}
catch(PDOException $e){
  print('ERROR:'.$e->getMessage());
  exit;
}
