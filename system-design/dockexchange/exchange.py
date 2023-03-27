class Exchange:
    def __init__(self):
        self.companies = {}
        
    def add_company(self, name, shares, price):
        self.companies[name] = {'shares': shares, 'price': price}
        
    def get_price(self, name):
        return self.companies[name]['price']
    
    def get_shares(self, name):
        return self.companies[name]['shares']
    
    def change_price(self, name, new_price):
        self.companies[name]['price'] = new_price
        
    def sell_shares(self, name, quantity):
        self.companies[name]['shares'] -= quantity
        
        
class User:
    def __init__(self, id):
        self.id = id
        self.shares = {}
        self.funds = 0
        
    def add_funds(self, amount):
        self.funds += amount
        
    def buy_shares(self, exchange, name, quantity):
        price = exchange.get_price(name)
        cost = price * quantity
        if cost > self.funds:
            raise Exception('Insufficient funds')
        exchange.sell_shares(name, quantity)
        if name in self.shares:
            self.shares[name] += quantity
        else:
            self.shares[name] = quantity
        self.funds -= cost
        
    def sell_shares(self, exchange, name, quantity):
        price = exchange.get_price(name)
        if name not in self.shares or self.shares[name] < quantity:
            raise Exception('Insufficient shares')
        exchange.add_shares(name, quantity)
        self.shares[name] -= quantity
        self.funds += price * quantity
        
    def total_value(self, exchange):
        total = self.funds
        for name, quantity in self.shares.items():
            total += exchange.get_price(name) * quantity
        return total
