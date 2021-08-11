#include "mouse.h"
#include "plant.h"

Mouse::Mouse(int x, int y, Map* map) : Animal(x, y, map)
{
    meatVolume = healthPoints + 10;
}

void Mouse::liveStep()
{
    if (!isAlive())
    {
        // Разложение трупа.
        if (meatVolume > 0)
            meatVolume--;
        return;
    }
    // Механизм голода.
    if (satietyPoints - 2 >= 0)
        satietyPoints -= 2;
    else if (satietyPoints > 0)
        satietyPoints = 0;
    else if (satietyPoints <= 0)
    {
        if (healthPoints - 2 >= 0)
        {
            healthPoints -= 2;
        }
        else
        {
            healthPoints = 0;
        }
    }
    // Проверка, остались ли жизни.
    if (!healthPoints)
    {
        alive = false;
        return;
    }
    std::list<ObjectOnMap*> visibleObjects = this->getMap()->getVisibleObjects(this, sightRadius);
    // Проверка, не находится ли мышь уже на каком-то растении.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (dynamic_cast<Plant*>(*obj))
        {
            // Если мышь уже на каком-то растении - откусить от него, сколько необходимо или возможно.
            if ((*obj)->get_xCoord() == get_xCoord() && (*obj)->get_yCoord() == get_yCoord())
            {
                if ((*obj)->getVolume() > 0)
                {
                    satietyPoints += (*obj)->giveFood(getMaxSatiety() - getSatietyPoints());
                    return;
                }
            }
        }
    }
    // Если мышь не на каком-то растении - подойти к растению в поле зрения.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (dynamic_cast<Plant*>(*obj) && (*obj)->getVolume() > 0)
        {
            goToFood(*obj);
            return;
        }
    }
    // Если растений в поле зрения нет - пойти в случайном направлении.
    goRandomDirection();
}

