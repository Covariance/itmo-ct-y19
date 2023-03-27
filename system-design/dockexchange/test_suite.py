import os
import requests
import pytest
import time
from testcontainers.core.container import DockerContainer


@pytest.fixture(scope='module')
def exchange_container():
    # Build and start Docker container
    os.system('docker build -t exchange .')
    container = DockerContainer('exchange')
    container.with_bind_ports(5000, 5000)
    container.with_env('FLASK_APP', 'server.py')
    container.with_command('flask run --host 0.0.0.0 --port 5000')

    container.start()
    time.sleep(2)  # Wait for container to start up

    # Add some initial shares of AAPL
    url = f'http://{container.get_container_host_ip()}:5000/add_stock'
    data = {'stock': 'AAPL', 'price': 100, 'quantity': 100}
    requests.post(url, json=data)

    yield container

    # Clean up Docker container
    container.stop()




def test_register_user(exchange_container):
    with requests.Session() as session:
        url = f'http://{exchange_container.get_container_host_ip()}:5000/register_user'
        data = {'user_id': 1}
        response = session.post(url, json=data)
        assert response.status_code == 200
        assert response.json() == {'status': 'success'}


def test_add_funds(exchange_container):
    with requests.Session() as session:
        url = f'http://{exchange_container.get_container_host_ip()}:5000/add_funds'
        data = {'user_id': 1, 'amount': 1000}
        response = session.post(url, json=data)
        assert response.status_code == 200
        assert response.json() == {'status': 'success'}


def test_view_portfolio(exchange_container):
    with requests.Session() as session:
        # Register user
        url = f'http://{exchange_container.get_container_host_ip()}:5000/register_user'
        data = {'user_id': 1}
        session.post(url, json=data)

        # Add funds to user account
        url = f'http://{exchange_container.get_container_host_ip()}:5000/add_funds'
        data = {'user_id': 1, 'amount': 1000}
        session.post(url, json=data)

        # Buy shares
        url = f'http://{exchange_container.get_container_host_ip()}:5000/buy_shares'
        data = {'user_id': 1, 'company': 'AAPL', 'quantity': 10}
        session.post(url, json=data)

        # View portfolio
        url = f'http://{exchange_container.get_container_host_ip()}:5000/view_portfolio'
        data = {'user_id': 1}
        response = session.post(url, json=data)
        assert response.status_code == 200
        assert response.json() == {
            'portfolio': {'AAPL': {'quantity': 10, 'value': 15000.0}},
            'total_value': 15000.0
        }


def test_buy_shares(exchange_container):
    with requests.Session() as session:
        # Register user
        url = f'http://{exchange_container.get_container_host_ip()}:5000/register_user'
        data = {'user_id': 1}
        session.post(url, json=data)

        # Add funds to user account
        url = f'http://{exchange_container.get_container_host_ip()}:5000/add_funds'
        data = {'user_id': 1, 'amount': 1000}
        session.post(url, json=data)

        # Buy shares
        url = f'http://{exchange_container.get_container_host_ip()}:5000/buy_shares'
        data = {'user_id': 1, 'company': 'AAPL', 'quantity': 10}
        response = session.post(url, json=data)
        assert response.status_code == 200
        assert response.json() == {'status': 'success'}


def test_sell_shares(exchange_container):
    with requests.Session() as session:
        # Register user
        url = f'http://{exchange_container.get_container_host_ip()}:5000/register_user'
        data = {'user_id': 1}
        session.post(url, json=data)

        # Add funds to user account
        url = f'http://{exchange_container.get_container_host_ip()}:5000/add_funds'
        data = {'user_id': 1, 'amount': 1000}
        session.post(url, json=data)

        # Buy shares
        url = f'http://{exchange_container.get_container_host_ip()}:5000/buy_shares'
        data = {'user_id': 1, 'company': 'AAPL', 'quantity': 10}
        session.post(url, json=data)

        # Sell shares
        url = f'http://{exchange_container.get_container_host_ip()}:5000/sell_shares'
        data = {'user_id': 1, 'company': 'AAPL', 'quantity': 5}
        response = session.post(url, json=data)
        assert response.status_code == 200
        assert response.json() == {'status': 'success'}
