#include <iostream>
#include <vector>
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

// Фабрика для создания животных
class AnimalFactory {
public:
    static Prey* createPrey(int x, int y, Direction direction, int k) {
        return new Prey(x, y, direction, k);
    }

    static Predator* createPredator(int x, int y, Direction direction, int k) {
        return new Predator(x, y, direction, k);
    }
};