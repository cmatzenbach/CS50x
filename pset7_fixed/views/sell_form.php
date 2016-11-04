<h1><?= $title ?></h1>
<p>Please enter the amount of stock you would like to sell.</p>
<p><strong>IMPORTANT:</strong> You can only sell shares from one stock at a time.<br />If you try to sell shares of multiple stocks at the same time, only the first stock with a sell quantity entered will be sold.</p>
<form action="sell.php" method="post">
<fieldset>
    <table class="table">
        <tr>
            <th>Stock</th>
            <th>Shares</th>
            <th>Price</th>
            <th>Sell</th>
        </tr>
    
    <?php
        foreach ($portfolio as $a)
        {
            print("<tr>");
            //print("<input type=\"hidden\" name=\"sell_stock\" value=\"" . $a["stock"] . "\" />");
            print("<td>" . $a["stock"] . "</td>");
            print("<td>" . $a["shares"] . "</td>");
            print("<td>$" . $a["price"] . "</td>");
            print("<td><input type=\"text\" name=\"" .  $a["stock"] . "amount\" /></td>");
            print("</tr>");
        }

    ?>
    </table>
    <div class="form-group">
        <button class="btn btn-default" type="submit">
            <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
            Sell
        </button>
    </div>
</fieldset>
</form>
