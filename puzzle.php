<html>
  <head>
    <link rel="stylesheet" href="style/style.css">
  </head>
  <body>
    <?php
      // Connect database
      require 'connect_db.php';
      $sql = connect();

      // Save session
      include 'show_puzzle.php';
      session_start();
      if(isset($_POST['userName'])) {
        $_SESSION['post'] = $_POST;
      }

      // Get user
      $user_info = $_SESSION['post'];
      if(empty($sql->query('SELECT * FROM account WHERE user_name = "'.$user_info["userName"].'" AND password = "'.$user_info["password"].'";')->fetch_assoc())){
        $sql->query('INSERT INTO account (user_name, password, account_id, puzzle_id) VALUES ("'.$user_info["userName"].'", "'.$user_info["password"].'", NULL, 1)');
      }
      $user = $sql->query('SELECT * FROM account WHERE user_name = "'.$user_info["userName"].'" AND password = "'.$user_info["password"].'";')->fetch_assoc();

      // Get current puzzle
      $puzzle = json_decode($sql->query('SELECT * FROM puzzle WHERE puzzle_id = '.$user['puzzle_id'].'')->fetch_assoc()['unsolved_puzzle']);

      // Show puzzle
      setPuzzle($puzzle);

      // Check input on solve button click
      include 'check.php';
      if(isset($_POST['solve'])){
        $solved = json_decode($sql->query('SELECT * FROM puzzle WHERE puzzle_id = '.$user['puzzle_id'].'')->fetch_assoc()['solved_puzzle']);
        checkInput($solved);
      }

      // Next button
      include 'next.php';
      showNextButton();
      if(isset($_POST['next'])){
        $index = $sql->query('SELECT puzzle_id FROM account WHERE user_name = "'.$user_info["userName"].'" AND password = "'.$user_info["password"].'";')->fetch_assoc()['puzzle_id'];
        $index++;
        if($index > 2){
          $index = 1;
        }
        $sql->query('UPDATE account SET puzzle_id = '.$index.' WHERE account_id = '.$user['account_id'].'');
        $user = $sql->query('SELECT * FROM account WHERE user_name = "'.$user_info["userName"].'" AND password = "'.$user_info["password"].'";')->fetch_assoc();
        $puzzle = json_decode($sql->query('SELECT * FROM puzzle WHERE puzzle_id = '.$user['puzzle_id'].'')->fetch_assoc()['unsolved_puzzle']);
        setPuzzle($puzzle);
      }
    ?>
  </body>
</html>