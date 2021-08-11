#include "map.h"
#include "objectonmap.h"
#include "plant.h"
#include "mouse.h"
#include "snake.h"
#include "lynx.h"
#include "cheetah.h"
#include "vulture.h"
/* Конструктор. */
Map::Map(int width, int height)
{
    this->width = width;
    this->height = height;
}
/* Геттер для width. */
int Map::getWidth()
{
    return width;
}
/* Геттер для height. */
int Map::getHeight()
{
    return height;
}
/* Метод, возвращающий квадрат расстояния от объекта obj1 до объекта obj2. */
int Map::squaredDistance(ObjectOnMap* obj1, ObjectOnMap* obj2)
{
    return (obj1->get_xCoord() - obj2->get_xCoord()) * (obj1->get_xCoord() - obj2->get_xCoord()) +
        (obj1->get_yCoord() - obj2->get_yCoord()) * (obj1->get_yCoord() - obj2->get_yCoord());
}
/* Метод для определения видимых для объекта obj с радиусом зрения r объектов на карте. */
std::list<ObjectOnMap*> Map::getVisibleObjects(ObjectOnMap* obj, int r)
{
    std::list<ObjectOnMap*> visibleObjects;
    // Проход по всем объектам на карте.
    for (std::list <ObjectOnMap*>::iterator objToSee = objectsOnMap.begin(); objToSee != objectsOnMap.end(); ++objToSee)
    {
        // Если объект в радиусе зрения - добавить его в список.
        if (squaredDistance(obj, *objToSee) <= r * r)
            visibleObjects.push_back(*objToSee);
    }
    return visibleObjects;
}
/* Метод для получения списка всех объектов на карте. */
std::list<ObjectOnMap*> Map::getAllObjects()
{
    std::list<ObjectOnMap*>* allObjects = new std::list<ObjectOnMap*>();
    // Проход по всем объектам на карте.
    for (std::list <ObjectOnMap*>::const_iterator obj = objectsOnMap.begin(); obj != objectsOnMap.end(); ++obj)
    {
        allObjects->push_back(*obj);
    }
    return *allObjects;
}
/* Метод для случайной генерации заданного числа растений и видов животных. */
void Map::randomGenerate(int plantCount, int mouseCount, int snakeCount, int lynxCount, int cheetahCount, int vultureCount)
{
    srand(time(NULL));
    // Случайная генерация plantCount числа растений.
    for (int i = 0; i < plantCount; i++)
    {
        Plant* plant = new Plant(rand() % getWidth(), rand() % getHeight(), this);
        objectsOnMap.push_back(plant);
    }
    // Случайная генерация mouseCount числа мышей.
    for (int i = 0; i < mouseCount; i++)
    {
        Mouse* mouse = new Mouse(rand() % width, rand() % height, this);
        objectsOnMap.push_back(mouse);
    }
    // Случайная генерация snakeCount числа змей.
    for (int i = 0; i < snakeCount; i++)
    {
        Snake* snake = new Snake(rand() % width, rand() % height, this);
        objectsOnMap.push_back(snake);
    }
    // Случайная генерация lynxCount числа рысей.
    for (int i = 0; i < lynxCount; i++)
    {
        Lynx* lynx = new Lynx(rand() % width, rand() % height, this);
        objectsOnMap.push_back(lynx);
    }
    // Случайная генерация cheetahCount числа леопардов.
    for (int i = 0; i < cheetahCount; i++)
    {
        Cheetah* cheetah = new Cheetah(rand() % width, rand() % height, this);
        objectsOnMap.push_back(cheetah);
    }
    // Случайная генерация vultureCount числа стервятников.
    for (int i = 0; i < vultureCount; i++)
    {
        Vulture* vulture = new Vulture(rand() % width, rand() % height, this);
        objectsOnMap.push_back(vulture);
    }
}
/* Метод для выполнения одного жизненного шага всех объектов на карте. */
void Map::liveStep()
{
    // Проход по всем объектам на карте.
    for (std::list <ObjectOnMap*>::const_iterator obj = objectsOnMap.begin(); obj != objectsOnMap.end(); ++obj)
    {
        (*obj)->liveStep();
    }
}
