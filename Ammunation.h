//
// Created by dadu on 02/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_AMMUNATION_H
#define PROYECTO1DATOS2CE_SERVER_AMMUNATION_H

#include "Bullet.h"
#include "BulletCollector.h"
class Ammunation {
public:
    Ammunation();

    ~Ammunation();

    BulletCollector* bulletCollector =new BulletCollector();

    Bullet *getHead() const;

    void setHead(Bullet *nHead);

    int getQuantity();

    void setQuantity(int nQuantity);

    void insertBullets(int num);

    void noImpact();

    void impact();

    int countBullets();

    int getDamage();

    void setDamage(int damage);

    bool isNoAmmunation() const;

    void setNoAmmunation(bool noAmmunation);



private:
    int quantity;
    Bullet* head;
    int damage;
    bool noAmmunation;
};




#endif //PROYECTO1DATOS2CE_SERVER_AMMUNATION_H
