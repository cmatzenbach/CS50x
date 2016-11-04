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
        render("sell_form.php", ["title" => "Sell", "portfolio" => $portfolio]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        //make sure user has stock they want to sell
        //find amount made, which stock was sold, amount sold, and remaining shares
        $return; 
        $stock_sold;
        $amount_sold;
        $remaining_shares;
        // iterate through stocks, finding the one that was sold
        for ($a = 0; $a < sizeof($portfolio); $a++) {
            // this will match the "name" property of the stock sold
            $checkstr = $portfolio[$a]["stock"] .  "amount";
            // see if amounts of that stock were sold
            if ($_POST[$checkstr] > 0) {
                // if so, calculate return and remaining shares and make note of which stock was sold and how much was sold, then break
                $amount_sold = $_POST[$checkstr];
                $return = $portfolio[$a]["price"] * $_POST[$checkstr];
                $stock_sold = $portfolio[$a];
                $remaining_shares = $portfolio[$a]["shares"] - $amount_sold;
                break;
            }
        }
        
        // remove stock from portfolio and update cash total
        // if all stock is sold
        if ($amount_sold == $stock_sold["shares"]) {
            $delete = CS50::query("DELETE FROM Portfolio WHERE user_id = ? AND stock = ?", $_SESSION["id"], $stock_sold["stock"]);
            if ($delete === 0) {
                apologize("Cannot delete stock from database");
            }
            
            $update = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $return, $_SESSION["id"]);
            if ($update === 0) {
                apologize("Cannot add cash to portfolio");
            }
            
            $history = $history = cs50::query("INSERT INTO history (stock, shares, action, user_id, price) VALUES(?, ?, ?, ?, ?)", $stock_sold["stock"], $stock_sold["shares"], "SELL", $_SESSION["id"], $return);
            render("sell_confirm.php", ["title" => "Stock Sold"]);
        }
        
        // if some stock is sold
        else if ($amount_sold < $stock_sold["shares"]) {
            $subtract = CS50::query("UPDATE Portfolio SET shares = ? WHERE user_id = ? AND stock = ?", $remaining_shares, $_SESSION["id"], $stock_sold["stock"]);
            if ($subtract === 0) {
                apologize("Cannot remove stock quantity from database");
            }
            
            $update = CS50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $return, $_SESSION["id"]);
            if ($update === 0) {
                apologize("Cannot add cash to portfolio");
            }
            
            $history = $history = cs50::query("INSERT INTO history (stock, shares, action, user_id, price) VALUES(?, ?, ?, ?, ?)", $stock_sold["stock"], $stock_sold["shares"], "SELL", $_SESSION["id"], $return);
            render("sell_confirm.php", ["title" => "Stock Sold"]);
        }
        
        // tried to sell more than they had
        else {
            apologize("You cannot sell more shares than you have.  Please try again");
        }

    }

?>