<?php
  function connect(){
    $host = 'localhost';
    $user = 'root';
    $password = '';
    $db = 'sudoku';
    $port = 3307;
    return new mysqli(
      $host,
      $user,
      $password,
      $db,
      $port
    );
  }
?>