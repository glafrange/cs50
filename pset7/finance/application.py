import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd, transaction_types

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


@app.route("/")
@login_required
def index():
    if request.method == "GET":
        user_id = session.get("user_id")
        stocks = db.execute("SELECT * FROM owned_stocks "
                          "WHERE user_id = :user_id",
                          user_id = user_id)

        for stock in stocks:
            stock['price'] = lookup(stock['symbol'])['price']

        return render_template("index.html", stocks=stocks)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    if request.method == "GET":
        return render_template("buy.html")
    if request.method == "POST":
        if not request.form.get("symbol") or not request.form.get("shares"):
            return apology("Enter all inputs", 403)

        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))
        user_id = session.get("user_id")
        cash = db.execute("SELECT cash FROM users WHERE id = :user_id",
                          user_id=user_id)[0]['cash']
        quote = lookup(symbol)
        if not quote:
            return apology("Couldn't find symbol", 403)
        price = quote['price']
        purchase_cost = price * shares
        final_cash = cash - purchase_cost

        if final_cash < 0:
            return apology("Not enough cash", 403)

        db.execute("UPDATE users "
                   "SET cash = :final_cash "
                   "WHERE id = :user_id ",
                   final_cash=final_cash,
                   user_id=user_id)

        db.execute("INSERT INTO transactions (user_id, price, shares, transaction_type, symbol) "
                   "values (:user_id, :price, :shares, :transaction_type, :symbol)",
                   user_id=user_id,
                   price=price,
                   shares=shares,
                   transaction_type=transaction_types['buy'],
                   symbol=symbol)

        current_owned = db.execute("SELECT * FROM owned_stocks "
                                   "WHERE user_id = :user_id AND symbol = :symbol",
                                   user_id=user_id,
                                   symbol=symbol)

        if len(current_owned) > 0 :
            db.execute("UPDATE owned_stocks "
                       "SET shares = :new_shares "
                       "WHERE user_id = :user_id AND symbol = :symbol",
                       new_shares=shares + current_owned[0]['shares'],
                       user_id=user_id,
                       symbol=symbol)
        else:
            db.execute("INSERT INTO owned_stocks (user_id, symbol, shares) "
                       "values (:user_id, :symbol, :shares)",
                       user_id=user_id, symbol=symbol, shares=shares)

        data = {
            'symbol': symbol,
            'shares': str(shares),
            'purchase_cost': str(purchase_cost),
            'final_cash': str(final_cash)
        }

        return render_template("buy_success.html", **data)


@app.route("/history")
@login_required
def history():
    user_id = session.get('user_id')
    if request.method == "GET":
        user_id = session.get("user_id")
        transactions = db.execute("SELECT * FROM transactions "
                                  "WHERE user_id = :user_id "
                                  "ORDER BY date DESC",
                                  user_id=user_id)

        return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "GET":
        return render_template("quote.html")
    elif request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide symbol", 403)

        quote = lookup(request.form.get("symbol"))

        return render_template("quoted.html", quote=quote) if quote else apology("Couldn't find symbol", 403)



@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        # Ensure password is valid
        if request.form.get("confirmation") != request.form.get("password") or len(request.form.get("password")) < 1:
            return apology("invalid password", 403)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        hash = generate_password_hash(request.form.get("password"), method="sha256", salt_length=8)
        db.execute("INSERT INTO users (username, hash) values (:username, :hash)",
                    username=request.form.get("username"),
                    hash=hash)

        return redirect("/")
    elif request.method == "GET":
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    user_id = session.get('user_id')

    if request.method == "GET":
        symbols = db.execute("SELECT symbol from owned_stocks "
                             "WHERE user_id = :user_id",
                             user_id=user_id)

        return render_template("sell.html", symbols=symbols)
    if request.method == "POST":
        symbol = request.form.get("symbol")

        if len(symbol) < 1:
            return apology("please select a stock", 400)

        price = lookup(symbol)['price']
        shares = int(request.form.get("shares"))
        owned_shares = db.execute("SELECT shares from owned_stocks "
                                  "WHERE user_id = :user_id AND symbol = :symbol",
                                  user_id=user_id,
                                  symbol=symbol)[0]['shares']

        cash = db.execute("SELECT cash from users "
                          "WHERE id = :user_id",
                          user_id=user_id)[0]['cash']

        if not shares > 0:
            return apology("select number of shares to sell", 400)

        if owned_shares < shares:
            return apology("you dont own that many shares", 400)

        final_cash = shares * price
        final_shares = owned_shares + shares

        db.execute("UPDATE users "
                   "SET cash = :final_cash "
                   "WHERE id = :user_id",
                   final_cash=final_cash, user_id=user_id)

        db.execute("UPDATE owned_stocks "
                   "SET shares = :final_shares "
                   "WHERE user_id = :user_id AND symbol = :symbol",
                   final_shares=final_shares, user_id=user_id, symbol=symbol)

        db.execute("INSERT INTO transactions (user_id, price, shares, transaction_type, symbol) "
                   "values (:user_id, :price, :shares, :transaction_type, :symbol)",
                   user_id=user_id,
                   price=price,
                   shares=shares,
                   transaction_type=transaction_types['sell'],
                   symbol=symbol)

        data = {
            'symbol': symbol,
            'shares': shares,
            'final_shares': final_shares,
            'price': price,
            'final_cash': final_cash
        }

        return render_template("sell_success.html", **data)


def errorhandler(e):
    """Handle error"""
    return apology(e.name, e.code)


# listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
