# apk token: pk_4d0f8c0d0a234c5fa00d9161b0797fb3
# export API_KEY=pk_4d0f8c0d0a234c5fa00d9161b0797fb3

import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

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

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # config variable with request sql
    current_user = session["user_id"]
    user_cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
    cash = user_cash[0]["cash"]
    cash_balance = user_cash[0]["cash"]
    history = db.execute("SELECT symbol, price, shares FROM history WHERE user_id = ?", current_user)

    # add total values each rows in array
    for rows in history:
        lookedup = lookup(rows["symbol"])
        current_price = lookedup["price"]
        rows["current_price"] = current_price
        rows["total_value"] = (current_price * int(rows["shares"]))
        cash = cash + rows["total_value"]

    return render_template("index.html", cash=cash, history=history, cash_balance=cash_balance)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "GET":
        return render_template("buy.html")
    else:
        symbol = lookup(request.form.get("symbol"))
        try:
            shares = int(request.form.get("shares"))
        except:
            return apology("Make sure the shares is positive integers")

        if not symbol or not shares:
            return apology("Verify input", 400)

        shares = int(request.form.get("shares"))
        if shares <= 0:
            return apology("Make sure the shares is positive integers", 400)

        # check balance cash
        current_price = symbol["price"]
        current_user = session["user_id"]
        cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
        if (float(current_price) * int(shares)) > float(cash[0]["cash"]):
            return apology("not enough cash in your balance")
        else:
            date = datetime.now()
            available_cash = float(cash[0]["cash"]) - (float(current_price) * int(shares))
            db.execute("UPDATE users SET cash = ? WHERE id = ?", available_cash, current_user)
            current_history = db.execute("SELECT * FROM history WHERE user_id = ? AND symbol = ?", current_user, symbol["symbol"])
            if not current_history:
                db.execute("INSERT INTO history(user_id, symbol, price, shares, date) VALUES (?, ?, ?, ?, ?)",
                           current_user, symbol["symbol"], symbol["price"], shares, date)
                db.execute("INSERT INTO all_history (user_id, symbol, buysell, price, shares, date) VALUES (?, ?, ?, ?, ?, ?)",
                           current_user, symbol["symbol"], "Buy", symbol["price"], shares, date)
            else:
                all_shares = int(shares) + int(current_history[0]["shares"])
                db.execute("UPDATE history SET shares = ? WHERE user_id = ? AND symbol = ?",
                           all_shares, current_user, symbol["symbol"])
                db.execute("INSERT INTO all_history (user_id, symbol, buysell, price, shares, date) VALUES (?, ?, ?, ?, ?, ?)",
                           current_id, symbol["symbol"], "Buy", symbol["price"], shares, date)
            return redirect("/")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    current_user = session["user_id"]
    your_history = db.execute("SELECT * FROM all_history WHERE user_id = ?", current_user)
    return render_template("history.html", your_history=your_history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # check form get username
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # check form get password
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
    # verify method used
    if request.method == "GET":
        return render_template("quote.html")
    else:
        symbol = request.form.get("symbol")
        if not symbol:
            return apology("Make sure Symbol")
        quote = lookup(symbol)
        if not quote:
            return apology("Incorrect symbol")
        company = quote["name"]
        symbol = quote["symbol"]
        price = quote["price"]
        return render_template("quoted.html", company=company, symbol=symbol, price=price)


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "GET":
        return render_template("register.html")
    else:
        name = request.form.get("username")
        password = request.form.get("password")
        confirmation = request.form.get("confirmation")

        users = db.execute("SELECT * FROM users WHERE username = ?", name)
        # check username in db
        if len(users) != 0:
            return apology("Username already used")
        if not name:
            return apology("Enter a username", 400)
        if not password:
            return apology("Enter a password", 400)
        if password != confirmation:
            return apology("Password is wrong")

        hash_password = generate_password_hash(password)
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", name, hash_password)

        return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    current_user = session["user_id"]
    if request.method == "GET":
        symbol = db.execute("SELECT symbol FROM history WHERE user_id = ?", current_user)
        return render_template("sell.html", symbol=symbol)
    else:
        symbol = request.form.get("symbol")
        shares_sell = int(request.form.get("shares"))
        stock = db.execute("SELECT symbol FROM history WHERE user_id = ?", current_user)

        STOCK_LIST = []
        for rows in stock:
            STOCK_LIST.append(rows["symbol"])
        if not symbol or symbol not in STOCK_LIST:
            return apology("Stock not enough")

        shares_owned = db.execute("SELECT shares FROM history WHERE user_id = ? AND symbol = ?", current_user, symbol)
        shares_owd_number = int(shares_owned[0]["shares"])
        if shares_sell > shares_owd_number:
            return apology("Not enough shares")
        if shares_sell <= 0:
            return apology("Please, enter a positive number")

        date = datetime.now()
        total_shares = shares_owd_number - shares_sell
        if (total_shares == 0):
            db.execute("DELETE FROM history WHERE user_id = ? AND symbol = ?", current_user, symbol)
        else:
            db.execute("UPDATE history SET shares = ? WHERE user_id = ? AND symbol = ?", total_shares, current_user, symbol)

        lookedup = lookup(symbol)
        sell_price = lookedup["price"]
        cash_deposit = sell_price * shares_sell
        cash = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
        cash_deposit += cash[0]["cash"]
        db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_deposit, current_user)
        db.execute("INSERT INTO all_history (user_id, symbol, buysell, price, shares, date) VALUES (?, ?, ?, ?, ?, ?)",
                   current_user, symbol, "Sell", sell_price, shares_sell, date)

        return redirect("/")


@app.route("/addcash", methods=["GET", "POST"])
@login_required
def addFunds():
    current_user = session["user_id"]
    if request.method == "GET":
        return render_template("addcash.html")
    else:
        cash_adding = int(request.form.get("addcash"))
        fund = db.execute("SELECT cash FROM users WHERE id = ?", current_user)
        cash = float(fund[0]["cash"])

    cash_total = cash_adding + cash
    # update the users table
    db.execute("UPDATE users SET cash = ? WHERE id = ?", cash_total, current_user)

    return redirect("/")


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
