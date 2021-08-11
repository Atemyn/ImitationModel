#ifndef VULTURE_H
#define VULTURE_H

#include "animal.h"
/* Класс Стервятник, наследуемый от Животного. */
class Vulture : public Animal
{
public:
    // Конструктор.
    Vulture(int x, int y, Map* map);
    // Переписанный метод для выполнения стервятником жизненного шага.
    virtual void liveStep() override;
};

#endif // VULTURE_H
