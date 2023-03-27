from typing import Dict


class Stock:
    def __init__(self, symbol: str, price: float, quantity: int):
        self.symbol = symbol
        self.price = price
        self.quantity = quantity


class User:
    def __init__(self, id: str):
        self.id = id
        self.balance = 0
        self.portfolio: Dict[str, int] = {}

    def add_funds(self, amount: float):
        self.balance += amount

    def buy_shares(self, stock: Stock, quantity: int):
        cost = stock.price * quantity
        self.balance -= cost
        if stock.symbol in self.portfolio:
            self.portfolio[stock.symbol] += quantity
        else:
            self.portfolio[stock.symbol] = quantity
        stock.quantity -= quantity

    def sell_shares(self, stock: Stock, quantity: int):
        revenue = stock.price * quantity
        self.balance += revenue
        self.portfolio[stock.symbol] -= quantity
        stock.quantity += quantity


class Exchange:
    def __init__(self, stocks: Dict[str, Stock]):
        self.stocks = stocks
        self.users: Dict[str, User] = {}

    def add_user(self, id: str) -> User:
        user = User(id)
        self.users[id] = user
        return user

    def get_user(self, id: str) -> User:
        return self.users.get(id)

    def add_stock(self, stock: Stock):
        self.stocks[stock.symbol] = stock

    def get_stock(self, symbol: str) -> Stock:
        return self.stocks.get(symbol)

    def get_stock_price(self, symbol: str) -> float:
        stock = self.stocks.get(symbol)
        if stock:
            return stock.price
        else:
            return 0.0
