from flask import Flask, jsonify, request
from exchange import Exchange, User

app = Flask(__name__)
exchange = Exchange()
users = {}

@app.route('/register_user', methods=['POST'])
def register_user():
    user_id = request.json['user_id']
    users[user_id] = User(user_id)
    return jsonify({'status': 'success'})

@app.route('/add_funds', methods=['POST'])
def add_funds():
    user_id = request.json['user_id']
    amount = request.json['amount']
    users[user_id].add_funds(amount)
    return jsonify({'status': 'success'})

@app.route('/view_portfolio', methods=['POST'])
def view_portfolio():
    user_id = request.json['user_id']
    user = users[user_id]
    portfolio = {}
    for name, quantity in user.shares.items():
        price = exchange.get_price(name)
        portfolio[name] = {
            'quantity': quantity,
            'value': price * quantity
        }
    total_value = user.total_value(exchange)
    return jsonify({
        'portfolio': portfolio,
        'total_value': total_value
    })

@app.route('/buy_shares', methods=['POST'])
def buy_shares():
    user_id = request.json['user_id']
    company = request.json['company']
    quantity = request.json['quantity']
    user = users[user_id]
    user.buy_shares(exchange, company, quantity)
    return jsonify({'status': 'success'})

@app.route('/sell_shares', methods=['POST'])
def sell_shares():
    user_id = request.json['user_id']
    company = request.json['company']
    quantity = request.json['quantity']
    user = users[user_id]
    user.sell_shares(exchange, company, quantity)
    return jsonify({'status': 'success'})

if __name__ == '__main__':
    app.run(debug=False, host='0.0.0.0')
