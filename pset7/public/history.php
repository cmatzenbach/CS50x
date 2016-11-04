<?php

    // configuration
    require("../includes/config.php"); 
    
    $history = CS50::query("SELECT * FROM `history` WHERE `user_id` = ?", $_SESSION["id"]);

    // render portfolio
    render("history_form.php", ["title" => "History", "history" => $history]);

?>