<html>
  <head>
    <link rel="stylesheet" href="style/signInStyle.css">
  </head>
  <body>
    <?php
      echo '
        <div class="sign-in">
          <form method="post" id="sign-in" action="puzzle.php">
            <label>User Name </label>
            <input type="text" name="userName" form="sign-in"><br>
            <label>Password </label>
            <input type="text" name="password" form="sign-in"><br><br>
            <button type="submit" name="login" value="login">Login</button>
          </form>
        </div>
      ';
    ?>
  </body>
</html>