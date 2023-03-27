FROM python:3.8-slim-buster

COPY exchange.py /app/exchange.py
COPY server.py /app/server.py
COPY requirements.txt /app/requirements.txt

WORKDIR /app

RUN pip install -r requirements.txt

CMD ["python", "server.py"]
