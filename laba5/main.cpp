#include "animal.hpp"

int main() {    
    //первая строка: размер(высота, ширина), количество шагов
    int line, count, step; 
    std::cin >> line >> count >> step;

    //вторая строка: начальное количество зайцев и волков
    int count_beast, count_prey;
    std::cin >> count_beast >> count_prey;

    //создаем массив указателей на животных
    std::vector<Animal*> animals;

    Simulation simulation(line, count, step);

    //инициализируем жертв
    for (int i = 0; i < count_beast; i++) {
        int x, y, orientation, step_change_direction;
        std::cin >> x >> y >> orientation >> step_change_direction;
        Direction direction = getDirectionFromInput(orientation);
        animals.push_back(AnimalFactory::createPrey(x, y, direction, step_change_direction));
    }

    //инициализируем хищников
    for (int i = 0; i < count_prey; i++) {
        int x, y, orientation, step_change_direction;
        std::cin >> x >> y >> orientation >> step_change_direction;
        Direction direction = getDirectionFromInput(orientation);
        animals.push_back(AnimalFactory::createPredator(x, y, direction, step_change_direction));
    }

    //запускаем симуляцию
    simulation.run();

    //Выводим финальный результат
    simulation.printResults();

    return 0;
}