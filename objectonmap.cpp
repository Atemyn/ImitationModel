#include "objectonmap.h"
#include "map.h"
/* Конструктор. */
ObjectOnMap::ObjectOnMap(int xCoord, int yCoord, Map* map)
{
    srand(time(NULL));
    this->map = map;
    set_xCoord(xCoord);
    set_yCoord(yCoord);
}
/* Геттер для xCoord. */
int ObjectOnMap::get_xCoord()
{
    return xCoord;
}
/* Геттер для yCoord. */
int ObjectOnMap::get_yCoord()
{
    return yCoord;
}
/* Сеттер для xCoord. */
void ObjectOnMap::set_xCoord(int xCoord)
{
    // Проверка, чтобы значение xCoord не превышало ширины карты.
    if (xCoord >= map->getWidth())
        this->xCoord = map->getWidth() - 1;
    // Проверка, чтобы значение xCoord было неотрицательным.
    else if (xCoord < 0)
        this->xCoord = 0;
    else
        this->xCoord = xCoord;
}
/* Сеттер для yCoord. */
void ObjectOnMap::set_yCoord(int yCoord)
{
    // Проверка, чтобы значение yCoord не превышало высоты карты.
    if (yCoord >= map->getHeight())
        this->yCoord = map->getHeight() - 1;
    // Проверка, чтобы значение yCoord было неотрицательным.
    else if (yCoord < 0)
        this->yCoord = 0;
    else
        this->yCoord = yCoord;
}
/* Геттер для map. */
Map* ObjectOnMap::getMap()
{
    return map;
}
