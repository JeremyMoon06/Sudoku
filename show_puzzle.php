<?php
  function setPuzzle($a){
    echo'
      <form method="POST">
        <table>
          <tr>
    ';
    for($i = 0; $i < 81; $i++){
      if($i != 0 && $i % 9 == 0){
        echo'
          </tr>
          <tr>
        ';
      }
      if($a[$i] == 0){
        echo'
          <td>
            <input type="text" name="'.$i.'" value="">
          </td>
        ';
      }
      else{
        echo'
          <td>
            <input type="text" name="'.$i.'" value="'.$a[$i].'" readonly>
          </td>
        ';
      }
    }
    echo'
          </tr>
        <table>
        <button class="solve-button" type="submit" name="solve" value="solve">Solve</button>
      <form>
    ';
  }
?>