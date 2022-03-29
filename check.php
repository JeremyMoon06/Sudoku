<?php
  function checkInput($solved){
    $input = $_POST;
    unset($input['solve']);
    if($solved == $input){
      echo'<div class="result-text">Correct!</div>';
    }
    else{
      echo'<div class="result-text">Try again.</div>';
    }
  }
?>