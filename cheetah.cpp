#include "cheetah.h"
#include "lynx.h"
#include "snake.h"
#include "plant.h"

Cheetah::Cheetah(int x, int y, Map* map) : Animal(x, y, map)
{
}

void Cheetah::liveStep()
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
    // Проверка, не находится ли гепард уже на клетке с рысью или змеей.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (dynamic_cast<Lynx*>(*obj) || dynamic_cast<Snake*>(*obj) || (!dynamic_cast<Plant*>(*obj) && !(*obj)->isAlive() && !satietyPoints))
        {
            // Если гепард уже на клетке змеи или рыси - откусить от нее, сколько необходимо или возможно.
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
    // Если гепард не на клетке змеи или рыси - подойти к одному из них в поле зрения.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (((dynamic_cast<Lynx*>(*obj) || dynamic_cast<Snake*>(*obj))
            && (*obj)->isAlive()) || (!(*obj)->isAlive() && satietyPoints == 0 && (*obj)->hasMeat()))
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
    // Если нужных животных в поле зрения нет - пойти в случайном направлении.
    goRandomDirection();
}
