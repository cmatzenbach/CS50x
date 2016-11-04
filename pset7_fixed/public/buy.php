<?php 

    // configuration
    require("../includes/config.php");
    
    $portfolio = CS50::query("SELECT * FROM `Portfolio` WHERE `user_id` = ?", $_SESSION["id"]);
    for($a = 0; $a < sizeof($portfolio); $a++) {
        $price = lookup($portfolio[$a]["stock"]);
        if($price) $portfolio[$a]["price"] = $price["price"];
    }
     // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("buy_form.php", ["title" => "Buy", "portfolio" => $portfolio]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        // make sure quantity is positive
        if (!preg_match("/^\d+$/", $_POST["shares"])) {
            apologize("Purchase quantity must be a positive number");
        }
        
        // make sure quantity is a whole number
        $str_check = strpos($_POST["shares"], '.');
        if ($str_check !== false) {
            apologize("Purchase quantity must be a whole number");
        }

        // lookup stock via yahoo, then get symbol in uppercase
        $getstock = lookup($_POST["stock"]);
        if(!$getstock) apologize("Invalid symbol.  Please re-submit");
        $buystock = strtoupper($getstock["symbol"]);
        
        // get purchase price
        $price = $getstock["price"] * $_POST["shares"];
        
        $buyit = cs50::query("INSERT INTO Portfolio (user_id, stock, shares) VALUES(?, ?, ?) ON DUPLICATE KEY UPDATE shares = shares + VALUES(shares)", $_SESSION["id"], $buystock, $_POST["shares"]);
        $update = cs50::query("UPDATE users SET cash = cash - ? WHERE id = ?", $price, $_SESSION["id"]);
        $history = cs50::query("INSERT INTO history (stock, shares, action, user_id, price) VALUES(?, ?, ?, ?, ?)", $buystock, $_POST["shares"], "BUY", $_SESSION["id"], $price);
        if ($buyit === 0 || $update === 0) {
            apologize("Stock could not be purchased");
        }
        else {
            render("buy_confirm.php", ["title" => "Stock Purchased"]);
        }
    }

?>