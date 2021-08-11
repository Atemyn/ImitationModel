#ifndef CHEETAH_H
#define CHEETAH_H

#include "animal.h"
/* Класс Леопард, наследумый от Животного */
class Cheetah : public Animal
{
public:
    // Конструктор.
    Cheetah(int x, int y, Map* map);
    // Переписанный метод для выполнения леопардом жизненного шага.
    virtual void liveStep() override;
};

#endif // CHEETAH_H
