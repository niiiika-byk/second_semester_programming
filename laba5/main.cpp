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

    std::vector<std::vector<int>> preyCount(line, std::vector<int>(count, 0));
    std::vector<std::vector<int>> predatorCount(line, std::vector<int>(count, 0));

    //симуляция
    for (int i = 0; i < step; i++){
       // Move each animal
        for (auto& animal : animals) {
            animal->move(line, count);
        }

        // Age and check for reproduction
        std::vector<Animal*> newAnimals; // To store new animals from reproduction
        for (auto& animal : animals) {
            animal->ageAnimal(); // Age the animal
            if (animal->isAlive()) {
                animal->reproduce(newAnimals); // Handle reproduction
            }
        }

        // Handle predator-prey interactions
        for (auto predator : animals) {
            if (dynamic_cast<Predator*>(predator)) {
                for (auto prey : animals) {
                    if (dynamic_cast<Prey*>(prey) && predator->getX() == prey->getX() && predator->getY() == prey->getY()) {
                        // Predator eats prey
                        dynamic_cast<Predator*>(predator)->eatPrey();
                        // Remove prey from the simulation
                        prey = nullptr; // Mark for deletion
                        break; // Exit inner loop
                    }
                }
            }
        }

        // Remove dead animals (those that are not alive)
        animals.erase(std::remove_if(animals.begin(), animals.end(), [](Animal* animal) {
            return !animal->isAlive();
        }), animals.end());

        // Add new animals to the main list
        for (auto newAnimal : newAnimals) {
            animals.push_back(newAnimal);
        }

        // Update the grid counts
        for (const auto& animal : animals) {
            int x = animal->getX();
            int y = animal->getY();
            if (dynamic_cast<Prey*>(animal)) {
                preyCount[y][x]++;
            } else if (dynamic_cast<Predator*>(animal)) {
                predatorCount[y][x]++;
            }
        }
    }

    for (int i = 0; i < line; i++) {
        for (int j = 0; j < count; j++) {
            if (preyCount[i][j] > 0) {
                std::cout << "+" << preyCount[i][j]; // Prey count
            } else if (predatorCount[i][j] > 0) {
                std::cout << "-" << predatorCount[i][j]; // Predator count
            } else {
                std::cout << "*"; // No animals
            }
        }
        std::cout << std::endl; // New line for the next row
    }

    // Освобождение памяти
    for (auto& animal : animals) {
        delete animal; // Удаляем объект
    }

    return 0;
}