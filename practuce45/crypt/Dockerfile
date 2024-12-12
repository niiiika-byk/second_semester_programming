# Используем образ с Python и Flask
FROM tiangolo/uwsgi-nginx-flask:python3.9

# Копирование исходного кода в контейнер
COPY ./crypt /app

# Установка переменных окружения
ENV PYTHONUNBUFFERED 1

# Установка рабочей директории
WORKDIR /app

# Запуск приложения
CMD ["python3", "user.py"]