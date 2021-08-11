#ifndef OBJECTONMAP_H
#define OBJECTONMAP_H

#include <cstdlib>
#include <time.h>
// Заявление класса Карта.
class Map;
/* Класс Объект на карте. */
class ObjectOnMap
{
private:
    // Текущие x и y координаты объекта на карте.
    int xCoord;
    int yCoord;
public:
    // Конструктор.
    ObjectOnMap(int xCoord, int yCoord, Map* map);
    // Виртуальный геттер для sightRadius для наследуемых классов.
    virtual int getSightRadius() = 0;
    // Виртуальный геттер для satietyPoints для наследуемых классов.
    virtual int getSatietyPoints() = 0;
    // Виртуальный метод жизненного шага для наследуемых классов.
    virtual void liveStep() = 0;
    // Виртуальный геттер для volume или meatVolume для наследуемых классов.
    virtual int getVolume() = 0;
    // Виртуальный метод для передачи мяса для наследуемых классов.
    virtual int giveFood(int foodVolume) = 0;
    // Виртуальный геттер для alive для наследуемых классов.
    virtual bool isAlive() = 0;
    // Виртуальный метод, изменяющий поле alive на false для наследуемых классов.
    virtual void die() = 0;
    // Виртуальный геттер для meatVolume для наследуемых классов.
    virtual bool hasMeat() = 0;
    // Геттер для xCoord.
    int get_xCoord();
    // Геттер для yCoord.
    int get_yCoord();
protected:
    // Указатель на карту, на которой объект находится.
    Map* map;
    // Сеттер для xCoord.
    void set_xCoord(int xCoord);
    // Сеттер для yCoord.
    void set_yCoord(int yCoord);
    // Геттер для map.
    Map* getMap();
};

#endif // OBJECTONMAP_H
