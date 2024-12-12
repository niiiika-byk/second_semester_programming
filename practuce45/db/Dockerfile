FROM ubuntu:latest

# Установка необходимых пакетов
RUN apt-get update && apt-get install -y build-essential libssl-dev libboost-all-dev

# Копирование кода сервера в контейнер
COPY . /app
COPY *.cpp /app
COPY *.hpp /app
COPY *.h /app
COPY *.json /app
COPY *.csv /app

# Установка рабочей директории
WORKDIR /app

# Сборка сервера
RUN g++ -std=c++11 -o server server.cpp tablejson.cpp insert.cpp delete.cpp select.cpp -lpthread -lssl -lcrypto

# Запуск сервера
CMD ["./server"]