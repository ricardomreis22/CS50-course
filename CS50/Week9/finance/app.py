import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    user_id = session["user_id"]

    transactions_db = db.execute ("SELECT symbol, SUM (shares) AS shares, price FROM transactions WHERE user_id = ? GROUP BY symbol", user_id )
    cash_db = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
    cash = cash_db[0]["cash"]



    total = cash

    for transaction in transactions_db:

        total = total + transaction["price"] * transaction ["shares"]



    return render_template("index.html", transactions_db = transactions_db, cash = cash, total = total, usd=usd)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""

    if request.method =="POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must give symbol")

        stock = lookup(symbol.upper())

        if stock == None:
            return apology("Could not find symbol")

        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Shares must be an integer")

        if shares < 0:
            return apology("Share must be positive")

        transaction_value = shares * stock["price"]

        user_id = session["user_id"]
        user_cash_db = db.execute("SELECT cash FROM users WHERE id = :id", id=user_id)
        user_cash = user_cash_db[0]["cash"]

        if transaction_value > user_cash:
            return apology("Not enough money")

        cash_updated = user_cash-transaction_value

        # Update cash on users table
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_updated, user_id)

        # find the time of buy
        date = datetime.datetime.now()


        # Update the purchase on transactions
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, stock["symbol"], shares, stock["price"], date)

        flash("Bought!")

        return redirect("/")

    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    user_id = session["user_id"]
    transactions = db.execute("SELECT symbol, price, shares, date FROM transactions WHERE user_id = ?", user_id)

    return render_template("history.html", transactions = transactions, usd=usd)


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
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "POST":

        symbol = request.form.get("symbol")

        if not symbol:
            return apology("Must give symbol")

        stock = lookup(symbol.upper())

        if not stock:
            return apology("Invalid symbol")

        return render_template("quoted.html", name = stock["name"], price = stock["price"], symbol = stock ["symbol"], usd = usd)

    else:
        return render_template("quote.html")



@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
        # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        username = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        # Ensure username was submitted
        if not username:
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not password:
            return apology("must provide password", 400)

        # Ensure password and password confirmation are the same
        elif password != confirmation:
            return apology("password and confirmation are not the same", 400)

        # Generate passsword hash
        hash = generate_password_hash(password)

        # Insert new user and hash into SQL table
        try:
            new_user = db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, hash)

        # Ensure the username isnt taken already
        except:
            return apology("Username already exists")

        #Remember which user has logged in

        session["user_id"] = new_user

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")




@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    user_id = session["user_id"]

    if request.method == "POST":
        symbol = request.form.get("symbol")
        shares = int(request.form.get("shares"))

        if shares <= 0:
            return apology("Shares must be positive!")

        stock_price = lookup(symbol)["price"]
        stock_name = lookup(symbol)["name"]
        price = shares * stock_price

        date = datetime.datetime.now()

        current_shares = db.execute("SELECT shares FROM transactions WHERE user_id =? AND symbol = ? GROUP BY symbol", user_id, symbol)[0]["shares"]
        if current_shares < shares:
            return apology ("You dont have enough shares")

        current_cash = db.execute("SELECT cash FROM users WHERE id = ?", user_id)[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", current_cash + price, user_id)
        db.execute("INSERT INTO transactions (user_id, symbol, shares, price, date) VALUES (?, ?, ?, ?, ?)", user_id, symbol, -shares, stock_price, date)

        return redirect("/")
    else:

        symbols = db.execute("SELECT symbol FROM transactions WHERE user_id = ? GROUP BY symbol", user_id)

        return render_template("sell.html", symbols=symbols)