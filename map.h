#ifndef MAP_H
#define MAP_H
#include <list>
// Заявление класса Объект на карте.
class ObjectOnMap;
/* Класс Карта. */
class Map
{
private:
    // Ширина и высота карты.
    int width;
    int height;
    // Список объектов на карте.
    std::list<ObjectOnMap*> objectsOnMap;
    // Метод, возвращающий квадрат расстояния от объекта obj1 до объекта obj2.
    int squaredDistance(ObjectOnMap* obj1, ObjectOnMap* obj2);
public:
    // Конструктор.
    Map(int width, int height);
    // Геттер для width.
    int getWidth();
    // Геттер для height.
    int getHeight();
    // Метод для определения видимых для объекта obj с радиусом зрения r объектов на карте.
    std::list<ObjectOnMap*> getVisibleObjects(ObjectOnMap* obj, int r);
    // Метод для получения списка всех объектов на карте.
    std::list<ObjectOnMap*> getAllObjects();
    // Метод для случайной генерации заданного числа растений и видов животных.
    void randomGenerate(int plantCount, int mouseCount, int snakeCount, int lynxCount, int cheetahCount, int vultureCount);
    // Метод для выполнения одного жизненного шага всех объектов на карте.
    void liveStep();
};

#endif // MAP_H
