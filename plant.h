#ifndef PLANT_H
#define PLANT_H

#include "objectonmap.h"
/* Класс Растение, наследуемый от Объекта на карте. */
class Plant : public ObjectOnMap
{
private:
    // Максимальный объем питательных веществ.
    int maxVolume;
    // Текущий объем питательных веществ в растении.
    int volume;
    // Скорость роста.
    int growSpeed;
public:
    // Конструктор.
    Plant(int x, int y, Map* map);
    // Метод для выполнения жизненного шага растением.
    virtual void liveStep() override;
    // Геттер для sightRadius, нужный для того, чтобы класс не был абстрактным.
    virtual int getSightRadius() override;
    // Геттер для satietyPoints, нужный для того, чтобы класс не был абстрактным.
    virtual int getSatietyPoints() override;
    // Метод для роста растения.
    void grow();
    // Метод для отдачи растением части своих питательных веществ животному.
    virtual int giveFood(int foodVolume) override;
    // Геттер для volume.
    virtual int getVolume() override;
    // Геттер для alive, нужный для того, чтобы класс не был абстрактным.
    virtual bool isAlive() override;
    // Метод для изменения alive, нужный для того, чтобы класс не был абстрактным.
    virtual void die() override;
    // Метод, нужный для того, чтобы класс не был абстрактным.
    virtual bool hasMeat() override;
};

#endif // PLANT_H
