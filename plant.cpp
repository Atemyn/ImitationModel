#include "plant.h"
/* Конструктор. */
Plant::Plant(int x, int y, Map* map):ObjectOnMap(x, y, map)
{
    volume = rand() % 100 + 100;
    maxVolume = volume;
    growSpeed = rand() % 2;
}
/* Геттер для satietyPoints. */
int Plant::getSatietyPoints()
{
    return 0;
}
/* Геттер для sightRadius. */
int Plant::getSightRadius()
{
    return 0;
}
/* Геттер для volume. */
int Plant::getVolume()
{
    return volume;
}
/* Геттер для alive, нужный для того, чтобы класс не был абстрактным. */
bool Plant::isAlive()
{
    if (volume > 0)
        return true;
    return false;
}
/* Метод для роста растения. */
void Plant::grow()
{
    // Если объем растения меньше максимального объема - вырасти на growSpeed.
    if (volume < maxVolume)
        volume += growSpeed;
    volume = maxVolume > volume ? volume : maxVolume;
}
/* Метод для выполнения жизненного шага растением. */
void Plant::liveStep()
{
    if (volume > 0)
        grow();
}
/* Метод для отдачи растением части своих питательных веществ животному. */
int Plant::giveFood(int foodVolume)
{
    // Если текущий объем больше запрашиваемого объема пищи -
    if (volume > foodVolume)
    {
        // - отдать запрашиваемый объем пищи.
        volume -= foodVolume;
        return foodVolume;
    }
    // иначе - отдать все, что имеется.
    else
    {
        int realVolume = volume;
        volume = 0;
        return realVolume;
    }
}
/* Метод для изменения alive, нужный для того, чтобы класс не был абстрактным. */
void Plant::die()
{
    volume = 0;
}
/* Метод, нужный для того, чтобы класс не был абстрактным. */
bool Plant::hasMeat()
{
    return isAlive();
}
