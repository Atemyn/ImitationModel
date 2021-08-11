#ifndef ANIMAL_H
#define ANIMAL_H

#include "objectonmap.h"
#include "map.h"
#include <list>
/* Класс Животное, наследуемый от Объекта на карте. */
class Animal : public ObjectOnMap
{
protected:
    // Предыдущие координаты для более разумного выполнения метода goRandomDirection().
    int previousX;
    int previousY;
    // Радиус зрения.
    int sightRadius;
    // Очки здоровья.
    int healthPoints;
    // Очки сытости.
    int satietyPoints;
    // Максимальное кол-во очков сытости.
    int maxSatiety;
    // Поле, отбражающее, живо ли животное.
    bool alive;
    // Кол-во мяса в животном.
    int meatVolume;
public:
    // Конструктор.
    Animal(int x, int y, Map* map);
    // Геттер для sightRadius.
    virtual int getSightRadius() override;
    // Геттер для healthPoints.
    int getHealthPoints();
    // Геттер для satietyPoints.
    int getSatietyPoints() override;
    // Геттер для maxSatiety.
    int getMaxSatiety();
    // Метод, позволяющий животному переместиться на одну клетку по направлению к еде.
    void goToFood(ObjectOnMap* food);
    // Метод, позволяющий животному пойти в случайном направлении.
    void goRandomDirection();
    // Геттер для alive.
    virtual bool isAlive() override;
    // Метод, изменяющий поле alive на false.
    virtual void die() override;
    // Метод, возвращающий true, если мясо в животном есть и false, если его нет.
    virtual bool hasMeat() override;
    // Метод, позволяющий другим животным получить мясо от этого животного.
    virtual int giveFood(int foodVolume) override;
    // Геттер для meatVolume.
    virtual int getVolume() override;
};

#endif // ANIMAL_H
