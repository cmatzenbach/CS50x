<h1><?= $title ?></h1>
<p>Please enter the stock and amount you would like to buy.</p>
<form action="buy.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="stock" placeholder="Stock Symbol" type="text"/>
        </div>
        <div class="form-group">
            <input class="form-control" name="shares" placeholder="Shares" type="number"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Buy
            </button>
        </div>
    </fieldset>
</form>
