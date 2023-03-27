import requests
import pytest
import time
from testcontainers import GenericContainer


@pytest.fixture(scope='module')
def exchange_container():
    # Start Docker container
    container = GenericContainer('exchange').with_exposed_ports(5000)\
        .with_env('FLASK_APP', 'app.py')\
        .with_command('flask run --host 0.0.0.0 --port 5000')\
        .start()
    time.sleep(2)  # Wait for container to start up

    yield

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
