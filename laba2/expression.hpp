#include "Stack.hpp"

int apply_operator(char op, int a, int b) { // Функция применения оператора
    switch (op) {
        case '&': return a & b;
        case '|': return a | b;
        case '^': return a ^ b;
        default: return 0;
    }
}

int evaluate_expression(const std::string& expression) {
    Stack<int> values;   // Стек для хранения чисел
    Stack<char> operators; // Стек для хранения операторов

    for (size_t i = 0; i < expression.length(); i++) {
        if (expression[i] == ' ') {
            continue; // Игнорируем пробелы
        }

        if (expression[i] == '0' || expression[i] == '1') { //если встретилось число
            values.push(expression[i] - '0'); // Преобразуем символ в число
        } else if (expression[i] == '(') { //в оператор
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                int val2 = values.top(); //вытаскиваем два верхних числа
                values.pop();
                int val1 = values.top(); 
                values.pop();
                char op = operators.top(); //вытаскиваем оператор верхний
                operators.pop();
                int result = apply_operator(op, val1, val2); //смотрим на значение
                values.push(result);
            }
            operators.pop(); // Убираем '('
        } else { // Оператор
            while (!operators.isEmpty() && operators.top() != '(') { //пока нет скобок
                char topOp = operators.top();
                if ((topOp == '&') || (topOp == '|') || (topOp == '^')) {
                    int val2 = values.top(); //берем два верхних
                    values.pop();
                    int val1 = values.top(); 
                    values.pop();
                    operators.pop(); //берем верхний оператор
                    int result = apply_operator(topOp, val1, val2);
                    values.push(result);
                }
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.isEmpty()) { //пока есть операторы
        int val2 = values.top(); 
        values.pop();
        int val1 = values.top(); 
        values.pop();
        char op = operators.top(); 
        operators.pop();
        int result = apply_operator(op, val1, val2);
        values.push(result); //ищем результат
    }

    return values.top();
}
