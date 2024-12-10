import socket

class DatabaseClient:
    def __init__(self, host='localhost', port=7432, timeout=5):
        """
        Класс для взаимодействия с сервером базы данных
        :param host: Хост сервера
        :param port: Порт
        :param timeout: Таймаут для соединения (в секундах)
        """
        self.host = host
        self.port = port
        self.timeout = timeout


    def send_command(self, command):
        """
        Отправляет команду на сервер базы данных и возвращает ответ
        :param command: SQL-команда
        :return: Ответ сервера
        """
        try:
            with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
                s.settimeout(self.timeout)
                print(f"[DEBUG] Connecting to {self.host}:{self.port}")
                s.connect((self.host, self.port))
                print(f"[DEBUG] Sending command: {command}")
                s.sendall(command.encode())

                # Ожидаем ответ от сервера
                response = b""
                while True:
                    part = s.recv(4096)
                    if not part:
                        break
                    response += part

                decoded_response = response.decode()
                print(f"[DEBUG] Response received: {decoded_response}")
                return decoded_response.strip()
        except socket.timeout:
            print("[ERROR] Connection timed out.")
            return "Error: Connection timed out"
        except Exception as e:
            print(f"[ERROR] Unexpected error: {str(e)}")
            return f"Error: {str(e)}"


    def insert(self, table, values):
        """
        Выполняет INSERT
        :param table: таблица
        :param values: значение для вставки
        :return: ответ
        """
        command = f"INSERT INTO {table} VALUES ({values})"
        response = self.send_command(command)
        if "Error" in response:
            raise RuntimeError(f"Insert failed: {response}")
        return response


    def delete(self, table, condition):
        """
    Выполняет DELETE
    :param table: таблица
    :param condition: условие для удаления
    :return: ответ
    """
    # Очистка условия от лишних пробелов
        condition = condition.strip()
        command = f"DELETE FROM {table} WHERE {condition}"
        print(f"[DEBUG] Executing delete command: {command}")
        response = self.send_command(command)
        if "Error" in response:
            raise RuntimeError(f"Delete failed: {response}")
        return response


    def select(self, columns, table, condition=None):
        """
        Выполняет SELECT и возвращает в виде списка словарей
        :param columns: столбцы
        :param table: таблица
        :param condition: WHERE (необязательно).
        :return: ответ список словарей
        """
        command = f"SELECT {columns} FROM {table}"
        if condition:
            command += f" WHERE {condition}"
        response = self.send_command(command)

        if "Error" in response:
            raise RuntimeError(f"Select failed: {response}")

        # Парсим результат в список словарей
        lines = response.strip().split("\n")
        if len(lines) < 2:
            return []  # Если данных нет, возвращаем пустой список
        headers = lines[0].split(",")
        data = [dict(zip(headers, line.split(","))) for line in lines[1:]]
        return data