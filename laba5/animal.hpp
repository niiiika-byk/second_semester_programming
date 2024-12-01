#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>
#include <ctime>

const int MAX_AGE_PREY = 10;    //макс.возраст жертвы
const int MAX_AGE_PREDATOR = 20; //макс.возраст хищника

enum Direction { UP, RIGHT, DOWN, LEFT };

Direction getDirectionFromInput(int input) {
    if (input < 0 || input > 3) {
        std::cerr << "Неверный ввод. Используйте 0 для UP, 1 для RIGHT, 2 для DOWN, 3 для LEFT." << std::endl;
        throw std::invalid_argument("Неверный ввод направления");
    }
    return static_cast<Direction>(input);
}

class Animal {
protected:
    int x, y;                 // Координаты
    int age;                  // Возраст
    int satiety;              // Насыщение
    Direction direction;      // Направление
    int step_change_direction; // Параметр k
    int steps_since_direction_change; // Счетчик шагов для изменения направления

public:
    Animal(int _x, int _y, Direction _direction, int k)
        : x(_x), y(_y), age(0), satiety(10), direction(_direction), 
          step_change_direction(k), steps_since_direction_change(0) {}

    virtual void move(int field_width, int field_height) = 0; //движение
    virtual void ageAnimal() { age++; }                      //старение
    virtual bool isAlive() const = 0;                        //проверка на жизнь
    virtual void reproduce(std::vector<Animal*>& animals) = 0; //размножение

    int getX() const { return x; } //координаты
    int getY() const { return y; }
    int getAge() const { return age; }
    Direction getDirection() const { return direction; } //напраление

    virtual ~Animal() {} //деструктор для наследников
};

class Prey : public Animal {
public:
    Prey(int _x, int _y, Direction _direction, int k)
        : Animal(_x, _y, _direction, k) {}

    // Движение жертвы
    void move(int field_width, int field_height) override {
        switch (direction) {
            case UP: y = (y - 1 + field_height) % field_height; break;
            case RIGHT: x = (x + 1) % field_width; break;
            case DOWN: y = (y + 1) % field_height; break;
            case LEFT: x = (x - 1 + field_width) % field_width; break;
        }
        steps_since_direction_change++;
        if (steps_since_direction_change >= step_change_direction) {
            direction = static_cast<Direction>((direction + 1) % 4); // Изменение направления
            steps_since_direction_change = 0;
        }
    }

    bool isAlive() const override {
        return age < MAX_AGE_PREY;
    }

    void reproduce(std::vector<Animal*>& animals) override {
        if (age == 5 || age == 10) {
            animals.push_back(new Prey(x, y, direction, step_change_direction));
        }
    }
};

class Predator : public Animal {
private:
    int preyEaten; // Количество съеденных жертв

public:
    Predator(int _x, int _y, Direction _direction, int k)
        : Animal(_x, _y, _direction, k), preyEaten(0) {}

    // Движение хищника
    void move(int field_width, int field_height) override {
        switch (direction) {
            case UP: y = (y - 2 + field_height) % field_height; break;
            case RIGHT: x = (x + 2) % field_width; break;
            case DOWN: y = (y + 2) % field_height; break;
            case LEFT: x = (x - 2 + field_width) % field_width; break;
        }
        steps_since_direction_change++;
        if (steps_since_direction_change >= step_change_direction) {
            direction = static_cast<Direction>((direction + 1) % 4); // Изменение направления
            steps_since_direction_change = 0;
        }
    }

    bool isAlive() const override {
        return age < MAX_AGE_PREDATOR;
    }

    void reproduce(std::vector<Animal*>& animals) override {
        if (preyEaten >= 2) {
            animals.push_back(new Predator(x, y, direction, step_change_direction));
            preyEaten = 0; // Сбрасываем счетчик после размножения
        }
    }

    void eatPrey() {
        preyEaten++;
    }

    int getPreyEaten() const {
        return preyEaten;
    }
};

class Fox : public Predator {
public:
    Fox(int _x, int _y, Direction _direction, int k) 
        : Predator(_x, _y, _direction, k) {}
};

class Bear : public Predator {
public:
    Bear(int _x, int _y, Direction _direction, int k) 
        : Predator(_x, _y, _direction, k) {}
};

class Rabbit : public Prey {
public:
    Rabbit(int _x, int _y, Direction _direction, int k) 
        : Prey(_x, _y, _direction, k) {}
};

class Pig : public Prey {
public:
    Pig(int _x, int _y, Direction _direction, int k) 
        : Prey(_x, _y, _direction, k) {}
};

//фабрика для создания животных
class AnimalFactory {
public:
    static Prey* createPrey(int x, int y, Direction direction, int k) {
        // Случайный выбор между зайцем и поросенком
        if (std::rand() % 2 == 0) {
            return new Rabbit(x, y, direction, k); // Создание случайного зайца
        } else {
            return new Pig(x, y, direction, k); // Создание случайного поросенка
        }
    }

    static Predator* createPredator(int x, int y, Direction direction, int k) {
        // Случайный выбор между лисой и медведем
        if (std::rand() % 2 == 0) {
            return new Fox(x, y, direction, k); // Создание случайной лисы
        } else {
            return new Bear(x, y, direction, k); // Создание случайного медведя
        }
    }
};

struct pair_hash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2>& pair) const {
        auto hash1 = std::hash<T1>{}(pair.first);
        auto hash2 = std::hash<T2>{}(pair.second);
        return hash1 ^ hash2;
    }
};

//симуляция жизни
class Simulation {
private:
    int height;
    int width;
    int steps;
    std::vector<Animal*> animals;
    std::vector<std::vector<int>> preyCount;
    std::vector<std::vector<int>> predatorCount;

public:
    Simulation(int h, int w, int s) : height(h), width(w), steps(s) {
        preyCount.resize(height, std::vector<int>(width, 0));
        predatorCount.resize(height, std::vector<int>(width, 0));
    }

    void addAnimal(Animal* animal) {
        animals.push_back(animal);
    }

    void run() {
        for (int i = 0; i < steps; i++) {
            //движение животного
            for (auto& animal : animals) {
                animal->move(width, height);
            }

            //возраст и размножение
            std::vector<Animal*> newAnimals; //детеныши
            for (auto& animal : animals) {
                animal->ageAnimal();
                if (animal->isAlive()) {
                    animal->reproduce(newAnimals);
                }
            }

            std::unordered_map<std::pair<int, int>, std::vector<Predator*>, pair_hash> predatorMap;

            for (auto predator : animals) {
                if (dynamic_cast<Predator*>(predator)) {
                    int x = predator->getX();
                    int y = predator->getY();
                    predatorMap[{x, y}].push_back(dynamic_cast<Predator*>(predator));
                }
            }

            for (auto prey : animals) {
                if (dynamic_cast<Prey*>(prey)) {
                    int x = prey->getX();
                    int y = prey->getY();

                    //проверка наличия хищника
                    if (predatorMap.find({x, y}) != predatorMap.end()) {
                        auto& predatorsOnCell = predatorMap[{x, y}];

                        if (!predatorsOnCell.empty()) {
                            Predator* youngestPredator = nullptr;
                            for (auto predator : predatorsOnCell) {
                                if (youngestPredator == nullptr || predator->getAge() < youngestPredator->getAge()) {
                                    youngestPredator = predator;
                                }
                            }
                        youngestPredator->eatPrey();
                        prey = nullptr; //маркируем для удаления
                    }
                }
            }
        }

            //удаляем умерших животных
            animals.erase(std::remove_if(animals.begin(), animals.end(), [](Animal* animal) {
                return !animal->isAlive();
            }), animals.end());

            //добавляем родившихся
            for (auto newAnimal : newAnimals) {
                animals.push_back(newAnimal);
            }

            //обновление положения
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
    }

    void printResults() const {
        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                if (preyCount[i][j] > 0) {
                    std::cout << "+" << preyCount[i][j];
                } else if (predatorCount[i][j] > 0) {
                    std::cout << "-" << predatorCount[i][j];
                } else {
                    std::cout << "*";
                }
            }
            std::cout << std::endl;
        }
    }

    ~Simulation() {
        for (auto& animal : animals) {
            delete animal; // Free memory
        }
    }
};