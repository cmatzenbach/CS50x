<?php

    // configuration
    require("../includes/config.php");

    // if user reached page via GET (as by clicking a link or via redirect)
    if ($_SERVER["REQUEST_METHOD"] == "GET")
    {
        // else render form
        render("register_form.php", ["title" => "Register"]);
    }

    // else if user reached page via POST (as by submitting a form via POST)
    else if ($_SERVER["REQUEST_METHOD"] == "POST")
    {
        if(!isset($_POST["username"]) || !isset($_POST["password"])) {
            apologize("Username and password are required");
            //render("register_form.php", ["title" => "Register"]);
        }
        else if($_POST["password"] !== $_POST["confirmation"]) {
            apologize("Password does not match confirmation");
            //render("register_form.php", ["title" => "Register"]);
       } 
        else {
            $add = CS50::query("INSERT IGNORE INTO users (username, hash, cash) VALUES(?, ?, 10000.0000)", $_POST["username"], password_hash($_POST["password"], PASSWORD_DEFAULT));
            if($add === 0) {
                apologize("Username already exists");
            }
            $id = $add[0]["id"];
            $_SESSION["id"] = $id;
            redirect("index.php");
        }
    }

?>

