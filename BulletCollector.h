//
// Created by dadu on 02/04/23.
//

#ifndef PROYECTO1DATOS2CE_SERVER_BULLETCOLLECTOR_H
#define PROYECTO1DATOS2CE_SERVER_BULLETCOLLECTOR_H

#include "Bullet.h"

class BulletCollector {
public:
    Bullet* cHeadPtr;
    BulletCollector();
    void insertF(Bullet* x);
    void deleteF();
    bool available() const;
    void showCol() const;

    int getQuantity() const;

    void setQuantity(int nQuantity);

    int getDamage();

    void setDamage(int damage);

private:
    int quantity;

    int damage;
};


#endif //PROYECTO1DATOS2CE_SERVER_BULLETCOLLECTOR_H
