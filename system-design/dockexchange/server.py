from flask import Flask, jsonify, request
from typing import Dict
from exchange import Exchange, User, Stock

app = Flask(__name__)

# Example data
stocks: Dict[str, Stock] = {
    'AAPL': Stock('AAPL', 100, 0),
    'GOOG': Stock('GOOG', 200, 0),
    'AMZN': Stock('AMZN', 300, 0),
}

exchange = Exchange(stocks)


@app.route('/register_user', methods=['POST'])
def register_user():
    user_id = request.json.get('user_id')
    user = exchange.add_user(user_id)
    return jsonify({'status': 'success', 'user_id': user.id})


@app.route('/add_funds', methods=['POST'])
def add_funds():
    user_id = request.json.get('user_id')
    amount = request.json.get('amount')
    user = exchange.get_user(user_id)
    user.add_funds(amount)
    return jsonify({'status': 'success', 'user_id': user.id, 'amount': amount})


@app.route('/view_portfolio', methods=['POST'])
def view_portfolio():
    user_id = request.json.get('user_id')
    user = exchange.get_user(user_id)
    portfolio = {}
    total_value = 0
    for stock, quantity in user.portfolio.items():
        price = exchange.get_stock_price(stock)
        value = quantity * price
        if quantity > 0:
            portfolio[stock] = {'quantity': quantity, 'value': value}
            total_value += value
    return jsonify({'portfolio': portfolio, 'total_value': total_value})


@app.route('/buy_shares', methods=['POST'])
def buy_shares():
    user_id = request.json.get('user_id')
    stock_symbol = request.json.get('stock')
    quantity = request.json.get('quantity')
    user = exchange.get_user(user_id)
    stock = exchange.get_stock(stock_symbol)
    if not stock:
        return jsonify({'status': 'error', 'message': f'Stock {stock_symbol} does not exist'})
    price = stock.price
    cost = price * quantity
    # Check if user has enough funds
    if cost > user.balance:
        return jsonify({'status': 'error', 'message': f'Insufficient funds'})
    # Buy shares
    user.buy_shares(stock, quantity)
    return jsonify({'status': 'success', 'user_id': user.id, 'stock': stock_symbol, 'quantity': quantity, 'cost': cost})


@app.route('/sell_shares', methods=['POST'])
def sell_shares():
    user_id = request.json.get('user_id')
    stock_symbol = request.json.get('stock')
    quantity = request.json.get('quantity')
    user = exchange.get_user(user_id)
    stock = exchange.get_stock(stock_symbol)
    if not stock:
        return jsonify({'status': 'error', 'message': f'Stock {stock_symbol} does not exist'})
    if stock.quantity < quantity:
        return jsonify({'status': 'error', 'message': f'Insufficient shares of {stock_symbol}'})
    price = stock.price
    revenue = price * quantity
    # Sell shares
    user.sell_shares(stock, quantity)
    return jsonify({'status': 'success', 'user_id': user.id, 'stock': stock_symbol, 'quantity': quantity, 'revenue': revenue})


@app.route('/add_stock', methods=['POST'])
def add_stock():
    stock_symbol = request.json.get('stock')
    price = request.json.get('price')
    quantity = request
    if exchange.get_stock(stock_symbol):
        return jsonify({'status': 'error', 'message': f'Stock {stock_symbol} already exists'})
    stock = Stock(stock_symbol, price, quantity)
    exchange.add_stock(stock)
    return jsonify({'status': 'success', 'stock': stock_symbol, 'price': price, 'quantity': quantity})


@app.route('/change_price', methods=['POST'])
def change_price():
    stock_symbol = request.json.get('stock')
    price = request.json.get('price')
    stock = exchange.get_stock(stock_symbol)
    if not stock:
        return jsonify({'status': 'error', 'message': f'Stock {stock_symbol} does not exist'})
    stock.price = price
    return jsonify({'status': 'success', 'stock': stock_symbol, 'price': price})


if __name__ == '__main__':
    app.run(debug=True)
