#include <iostream>
#include <vector>

class Animal {
public:
    virtual void move() = 0; // Чисто виртуальный метод для движения
    virtual void changeDirection() = 0;
    virtual void reproduce() = 0;
    virtual bool isAlive() const = 0;
    virtual ~Animal() = default; // Виртуальный деструктор

};

class Prey : public Animal {
private:
    int x, y;
    int orientation, step_change_direction;
    int age, satiety;

public:
    Prey(int _x, int _y, int _orientation, int k) : 
        x(_x), y(_y), orientation(_orientation), step_change_direction(k), age(0), satiety(10) {}

    void move() override { 
        //движение
    }
    void changeDirection() override { 
        //измена направления
    }
    void reproduce() override { 
        //размножение 
    }
    bool isAlive() const override { 
        //живой 
    }
};

class Predator : public Animal {
private:
    int x, y;
    int orientation, step_change_direction;
    int age, satiety;

public:
    Predator(int _x, int _y, int _orientation, int k) : 
        x(_x), y(_y), orientation(_orientation), step_change_direction(k), age(0), satiety(10) {}

    void move() override { 
        //движение
    }
    void changeDirection() override { 
        //измена направления
    }
    void reproduce() override { 
        //размножение 
    }
    bool isAlive() const override { 
        //живой 
    }
};

// Фабрика для создания животных
class AnimalFactory {
public:
    static Animal* createPrey(int x, int y, int orientation, int step_change_direction) {
        return new Prey(x, y, orientation, step_change_direction);
    }
    static Animal* createPredator(int x, int y, int orientation, int step_change_direction) {
        return new Predator(x, y, orientation, step_change_direction);
    }
};