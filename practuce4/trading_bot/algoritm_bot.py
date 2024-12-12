#запуск python3 algoritm_bot.py your_user_key

import requests
import random
import time
import sys

API_URL = "http://localhost:5000"  # URL вашего API

def get_price(pair_id):
    # Здесь вы должны реализовать логику получения текущей цены для валютной пары
    # Например, можно использовать API для получения последней цены
    # Для примера, просто вернем случайное значение
    return random.uniform(0.001, 0.01)

def place_order(user_key, order_type, pair_id, quantity, price):
    order_data = {
        "pair_id": pair_id,
        "quantity": quantity,
        "price": price,
        "type": order_type
    }
    headers = {
        "X-USER-KEY": user_key
    }
    response = requests.post(f"{API_URL}/order", json=order_data, headers=headers)
    return response.json()

def moving_average(prices, window):
    return sum(prices[-window:]) / window

def algorithmic_trading_bot(user_key):
    prices = []
    window_size = 5  # Размер окна для скользящей средней
    pair_id = 1  # Замените на реальный ID валютной пары

    while True:
        price = get_price(pair_id)
        prices.append(price)
        print(f"Current price: {price}")

        if len(prices) > window_size:
            ma = moving_average(prices, window_size)
            print(f"Moving Average: {ma}")

            if price > ma:
                result = place_order(user_key, "buy", pair_id, 1, price)  # Покупаем 1 единицу
                print(f"Placed buy order: {result}")
            elif price < ma:
                result = place_order(user_key, "sell", pair_id, 1, price)  # Продаем 1 единицу
                print(f"Placed sell order: {result}")

        time.sleep(10)  # Пауза между запросами

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage: python3 algoritm_bot.py <USER_KEY>")
        sys.exit(1)

    user_key = sys.argv[1]
    algorithmic_trading_bot(user_key)