<?php

    require(__DIR__ . "/../includes/config.php");

    // numerically indexed array of places
    $places = [];

    // if user enters a 5 digit number (ala zip), use this query
    if (is_numeric($_GET["geo"]) && strlen($_GET["geo"]) >= 4) {
        $places = CS50::query("SELECT * FROM places WHERE postal_code LIKE ?", $_GET["geo"] . "%");
    }
    
    // if user enters a string with a comma in it and no numbers
    else if (strpos($_GET["geo"], ",") !== false && 0 === preg_match('~[0-9]~', $_GET["geo"])) {
        /* assuming "city, state" - clean up string to get city and state */
        
        // first step - remove spaces
        $input = str_replace(' ', '', $_GET["geo"]);
        
        // then separate city and state by comma
        $input = explode(",", $input);

        if (strlen($input[1]) !== 0) {
            // if it's only two letters long, it's probably a state abbreviation, query appropriately
            if (strlen($input[1]) <= 2) {
                $places = CS50::query("SELECT * FROM places WHERE place_name = ? AND admin_code1 LIKE ?", $input[0], $input[1] . "%");
            }
            // if it's longer, it's probably the whole city name, query appropriately
            else {
                $places = CS50::query("SELECT * FROM places WHERE place_name = ? AND admin_name1 LIKE ?", $input[0], $input[1] . "%");
            }
        }
        
    }
    
    else {
        // if none of the above, run all-purpose query
        $places = CS50::query("SELECT * FROM places WHERE MATCH(place_name, admin_code1, postal_code) AGAINST (?) OR MATCH(place_name, admin_code1) AGAINST (?) OR MATCH(place_name, admin_name1) AGAINST (?)", $_GET["geo"], $_GET["geo"], $_GET["geo"]);
    }

    // output places as JSON (pretty-printed for debugging convenience)
    header("Content-type: application/json");
    print(json_encode($places, JSON_PRETTY_PRINT));

?>