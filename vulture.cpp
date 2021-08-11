#include "vulture.h"
#include "plant.h"

Vulture::Vulture(int x, int y, Map* map) : Animal(x, y, map)
{
    healthPoints = rand() % 46 + 15;
    meatVolume = healthPoints + 15;
}

void Vulture::liveStep()
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
    // Проверка, не находится ли гриф уже на клетке с трупом животного.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (!dynamic_cast<Plant*>(*obj) && !(*obj)->isAlive())
        {
            // Если гриф уже на клетке с трупом животного - откусить от него, сколько необходимо или возможно.
            if ((*obj)->get_xCoord() == get_xCoord() && (*obj)->get_yCoord() == get_yCoord())
            {
                if ((*obj)->hasMeat())
                {
                    satietyPoints += (*obj)->giveFood(getMaxSatiety() - getSatietyPoints());
                    return;
                }
            }
        }
    }
    // Если гриф не на клетке с трупом животного - подойти к одному из них в поле зрения.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (!dynamic_cast<Plant*>(*obj) && !(*obj)->isAlive() && (*obj)->hasMeat())
        {
            goToFood(*obj);
            return;
        }
    }
    // Если трупов животных в поле зрения нет - пойти в случайном направлении.
    goRandomDirection();
}
