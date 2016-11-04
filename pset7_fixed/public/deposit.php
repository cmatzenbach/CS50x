<?php 

    // configuration
    require("../includes/config.php");
    
     // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // render form
        render("deposit_form.php", ["title" => "Deposit Money"]);
    }
    
    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
         // make sure quantity is positive
        if ($_POST["deposit"] < 0) {
            apologize("Purchase quantity must be a positive number");
        }
        $indabank = cs50::query("UPDATE users SET cash = cash + ? WHERE id = ?", $_POST["deposit"], $_SESSION["id"]);
        
        if(!$indabank) apologize("Money could not be deposited.  Please try again");

        render("deposit_confirm.php", ["title" => "Deposit Confirmed"]);
    }

?>