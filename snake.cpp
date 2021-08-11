#include "snake.h"
#include "mouse.h"
#include "plant.h"

Snake::Snake(int x, int y, Map* map) : Animal(x, y, map)
{
    healthPoints = rand() % 41 + 10;
    meatVolume = healthPoints + 10;
}

void Snake::liveStep()
{
    if (!isAlive())
    {
        // Разложение трупа.
        if (meatVolume > 0)
            meatVolume--;
        return;
    }
    // Механизм голода.
    if (satietyPoints > 0)
        satietyPoints--;
    else
        if (healthPoints - 2 >= 0)
            healthPoints -= 2;
        else
            healthPoints = 0;
    // Проверка, остались ли жизни.
    if (!healthPoints)
    {
        alive = false;
        return;
    }
    std::list<ObjectOnMap*> visibleObjects = this->getMap()->getVisibleObjects(this, sightRadius);
    // Проверка, не находится ли змея уже на клетке с мышью.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (dynamic_cast<Mouse*>(*obj) || (!dynamic_cast<Plant*>(*obj) && !(*obj)->isAlive() && !satietyPoints))
        {
            // Если змея уже на клетке с мышью - откусить от нее, сколько необходимо или возможно.
            if ((*obj)->get_xCoord() == get_xCoord() && (*obj)->get_yCoord() == get_yCoord())
            {
                if (satietyPoints > 0 && !(*obj)->isAlive())
                {
                    continue;
                }
                if ((*obj)->isAlive())
                {
                    (*obj)->die();
                }
                if ((*obj)->hasMeat())
                {
                    satietyPoints += (*obj)->giveFood(getMaxSatiety() - getSatietyPoints());
                    return;
                }
            }
        }
    }
    // Если змея не на клетке с мышью - подойти к мыши в поле зрения.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if ((dynamic_cast<Mouse*>(*obj) && (*obj)->isAlive()) || (!(*obj)->isAlive() && satietyPoints == 0 && (*obj)->hasMeat()))
        {
            goToFood(*obj);
            if ((*obj)->get_xCoord() == get_xCoord() && (*obj)->get_yCoord() == get_yCoord())
            {
                if ((*obj)->isAlive())
                {
                    (*obj)->die();
                }
                satietyPoints += (*obj)->giveFood(getMaxSatiety() - getSatietyPoints());
            }
            return;
        }
    }
    // Если мышей в поле зрения нет - пойти в случайном направлении.
    goRandomDirection();
}
