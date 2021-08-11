#ifndef SNAKE_H
#define SNAKE_H

#include "animal.h"
/* Класс Змея, наследуемый от Животного. */
class Snake : public Animal
{
public:
    // Конструктор.
    Snake(int x, int y, Map* map);
    // Переписанный метод для выполнения змеей жизненного шага.
    virtual void liveStep() override;
};

#endif // SNAKE_H
