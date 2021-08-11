#ifndef MOUSE_H
#define MOUSE_H
#include "animal.h"
/* Класс Мышь, наследуемый от Животного. */
class Mouse : public Animal
{
public:
    // Конструктор.
    Mouse(int x, int y, Map* map);
    // Переписанный метод для выполнения мышью жизненного шага.
    virtual void liveStep() override;
};

#endif // MOUSE_H
