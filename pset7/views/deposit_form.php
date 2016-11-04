<h1><?= $title ?></h1>
<p>Deposit money into your account by entering amount below</p>
<form action="deposit.php" method="post">
    <fieldset>
        <div class="form-group">
            <input class="form-control" name="deposit" placeholder="Amount" type="text"/>
        </div>
        <div class="form-group">
            <button class="btn btn-default" type="submit">
                <span aria-hidden="true" class="glyphicon glyphicon-log-in"></span>
                Deposit
            </button>
        </div>
    </fieldset>
</form>
