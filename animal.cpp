#include "animal.h"
/* Конструктор. */
Animal::Animal(int x, int y, Map* map) : ObjectOnMap(x, y, map)
{
    previousX = x;
    previousY = y;
    sightRadius = rand() % 10 + 1;
    healthPoints = rand() % 71 + 30;
    satietyPoints = healthPoints - 15;
    maxSatiety = satietyPoints;
    alive = true;
    meatVolume = healthPoints + 40;
}
/* Геттер для sightRadius. */
int Animal::getSightRadius()
{
    return sightRadius;
}
/* Геттер для healthPoints. */
int Animal::getHealthPoints()
{
    return healthPoints;
}
/* Геттер для satietyPoints. */
int Animal::getSatietyPoints()
{
    return satietyPoints;
}
/* Геттер для maxSatiety. */
int Animal::getMaxSatiety()
{
    return maxSatiety;
}
/* Метод, позволяющий животному переместиться на одну клетку по направлению к еде. */
void Animal::goToFood(ObjectOnMap* food)
{
    // Определение направления перемещения.
    int dx = food->get_xCoord() - get_xCoord();
    int dy = food->get_yCoord() - get_yCoord();
    dx = dx > 0 ? 1 : dx < 0 ? -1 : 0;
    dy = dy > 0 ? 1 : dy < 0 ? -1 : 0;
    previousX = get_xCoord();
    previousY = get_yCoord();
    set_xCoord(get_xCoord() + dx);
    set_yCoord(get_yCoord() + dy);
}
/* Метод, позволяющий животному пойти в случайном направлении. */
void Animal::goRandomDirection()
{
    int dx = 0, dy = 0;
    // Проверка, чтобы животное не стояло на месте и не возвращалось туда, где уже было.
    while ((!dx && !dy) || ((previousX == (get_xCoord() + dx)) && (previousY == (get_yCoord() + dy))))
    {
        dx = rand() % 3 - 1;
        dy = rand() % 3 - 1;
    }
    previousX = get_xCoord();
    previousY = get_yCoord();
    set_xCoord(get_xCoord() + dx);
    set_yCoord(get_yCoord() + dy);
}
/* Геттер для alive. */
bool Animal::isAlive()
{
    return alive;
}
/* Метод, изменяющий поле alive на false. */
void Animal::die()
{
    alive = false;
}
/* Метод, возвращающий true, если мясо в животном есть и false, если его нет. */
bool Animal::hasMeat()
{
    return meatVolume > 0;
}
/* Метод, позволяющий другим животным получить мясо от этого животного. */
int Animal::giveFood(int foodRequired)
{
    if (isAlive())
        return 0;
    // Если имеющийся объем мяса больше объема запрашиваемого мяса.
    if (meatVolume > foodRequired)
    {
        meatVolume -= foodRequired;
        return foodRequired;
    }
    // инача - отдать все, что есть.
    else
    {
        int realVolume = meatVolume;
        meatVolume = 0;
        return realVolume;
    }
}
/* Геттер для meatVolume. */
int Animal::getVolume()
{
    return meatVolume;
}
