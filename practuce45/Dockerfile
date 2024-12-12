FROM gcc:12

# Копирование кода сервера в контейнер
COPY . /app/
COPY *.cpp /app/
COPY *.hpp /app/
COPY *.h /app/
COPY *.json /app/

# Установка рабочей директории
WORKDIR /app

# Сборка сервера
RUN g++ -std=c++17 -o server main.cpp tablejson.cpp insert.cpp delete.cpp select.cpp -lpthread -lssl -lcrypto

# Запуск сервера
CMD ["./server"]