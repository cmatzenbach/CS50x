<?php

    // configuration
    require("../includes/config.php"); 
    
    $portfolio = CS50::query("SELECT * FROM `Portfolio` WHERE `user_id` = ?", $_SESSION["id"]);
    $user = cs50::query("SELECT * from `users` WHERE `id` = ?", $_SESSION["id"]);
    for($a = 0; $a < sizeof($portfolio); $a++) {
        $price = lookup($portfolio[$a]["stock"]);
        if($price) $portfolio[$a]["price"] = $price["price"];
    }

    // render portfolio
    render("portfolio.php", ["title" => "Portfolio", "portfolio" => $portfolio, "user" => $user]);

?>
