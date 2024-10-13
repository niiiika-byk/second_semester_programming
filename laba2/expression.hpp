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

        if (expression[i] == '0' || expression[i] == '1') {
            values.push(expression[i] - '0'); // Преобразуем символ в число
        } else if (expression[i] == '(') {
            operators.push(expression[i]);
        } else if (expression[i] == ')') {
            while (!operators.isEmpty() && operators.top() != '(') {
                int val2 = values.top(); 
                values.pop();
                int val1 = values.top(); 
                values.pop();
                char op = operators.top(); 
                operators.pop();
                int result = apply_operator(op, val1, val2);
                values.push(result);
            }
            operators.pop(); // Убираем '('
        } else { // Оператор
            while (!operators.isEmpty() && operators.top() != '(') {
                char topOp = operators.top();
                if ((topOp == '&') || (topOp == '|') || (topOp == '^')) {
                    int val2 = values.top(); 
                    values.pop();
                    int val1 = values.top(); 
                    values.pop();
                    operators.pop();
                    int result = apply_operator(topOp, val1, val2);
                    values.push(result);
                }
            }
            operators.push(expression[i]);
        }
    }

    while (!operators.isEmpty()) {
        int val2 = values.top(); 
        values.pop();
        int val1 = values.top(); 
        values.pop();
        char op = operators.top(); 
        operators.pop();
        int result = apply_operator(op, val1, val2);
        values.push(result);
    }

    return values.top();
}
