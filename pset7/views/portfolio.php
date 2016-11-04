<h1><?= $title; ?></h1>
<p>Your current account balance is: $<?= $user[0]["cash"]; ?></p>
<div>
    <table class="table table-striped">
        <tr>
            <th>Stock</th>
            <th>Shares</th>
            <th>Price</th>
        </tr>
    
    <?php
        foreach ($portfolio as $a)
        {
            print("<tr>");
            print("<td>" . $a["stock"] . "</td>");
            print("<td>" . $a["shares"] . "</td>");
            print("<td>$" . $a["price"] . "</td>");
            print("</tr>");
        }

    ?>
    </table>
</div>
