import requests
import argparse


def add_stock(exchange_url, stock, price, quantity):
    url = f'{exchange_url}/add_stock'
    data = {'stock': stock, 'price': price, 'quantity': quantity}
    response = requests.post(url, json=data)
    print(response.json())


def change_price(exchange_url, stock, price):
    url = f'{exchange_url}/change_price'
    data = {'stock': stock, 'price': price}
    response = requests.post(url, json=data)
    print(response.json())


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('exchange_url', help='URL of the exchange server')
    subparsers = parser.add_subparsers(dest='command')

    add_stock_parser = subparsers.add_parser('add_stock')
    add_stock_parser.add_argument('stock', help='Stock symbol')
    add_stock_parser.add_argument('price', type=float, help='Stock price')
    add_stock_parser.add_argument('quantity', type=int, help='Initial quantity of shares')

    change_price_parser = subparsers.add_parser('change_price')
    change_price_parser.add_argument('stock', help='Stock symbol')
    change_price_parser.add_argument('price', type=float, help='New stock price')

    args = parser.parse_args()

    if args.command == 'add_stock':
        add_stock(args.exchange_url, args.stock, args.price, args.quantity)
    elif args.command == 'change_price':
        change_price(args.exchange_url, args.stock, args.price)
    else:
        print('Invalid command')
