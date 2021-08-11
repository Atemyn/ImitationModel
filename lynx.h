#ifndef LYNX_H
#define LYNX_H

#include "animal.h"
/* Класс Рысь, наследуемый от Животного. */
class Lynx : public Animal
{
public:
    // Конструктор.
    Lynx(int x, int y, Map* map);
    // Переписанный метод для выполнения рысью жизненного шага.
    virtual void liveStep() override;
};

#endif // LYNX_H
