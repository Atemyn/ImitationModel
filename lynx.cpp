#include "lynx.h"
#include "mouse.h"
#include "snake.h"
#include "plant.h"

Lynx::Lynx(int x, int y, Map* map) : Animal(x, y, map)
{
    healthPoints = rand() % 46 + 25;
    meatVolume = healthPoints + 25;
}

void Lynx::liveStep()
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
    // Проверка, не находится ли рысь уже на клетке с мышью или змеей.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (dynamic_cast<Mouse*>(*obj) || dynamic_cast<Snake*>(*obj) || (!dynamic_cast<Plant*>(*obj) && !(*obj)->isAlive() && !satietyPoints))
        {
            // Если рысь уже на клетке змеи или мыши - откусить от нее, сколько необходимо или возможно.
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
    // Если рысь не на клетке змеи или мыши - подойти к одному из них в поле зрения.
    for (std::list <ObjectOnMap*>::iterator obj = visibleObjects.begin(); obj != visibleObjects.end(); ++obj)
    {
        if (((dynamic_cast<Mouse*>(*obj) || dynamic_cast<Snake*>(*obj)) && (*obj)->isAlive())
           || (!(*obj)->isAlive() && satietyPoints == 0 && (*obj)->hasMeat()))
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
