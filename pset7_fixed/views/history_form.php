<h1><?= $title; ?></h1>
<div>
    <table class="table">
        <tr>
            <th>Date</th>
            <th>Stock</th>
            <th>Shares</th>
            <th>Action</th>
            <th>Price</th>
        </tr>
    
    <?php
        foreach ($history as $a)
        {
            print("<tr>");
            print("<td>" . $a["date"] . "</td>");
            print("<td>" . $a["stock"] . "</td>");
            print("<td>" . $a["shares"] . "</td>");
            print("<td>" . $a["action"] . "</td>");
            print("<td>$" . $a["price"] . "</td>");
            print("</tr>");
        }

    ?>
    </table>
</div>
