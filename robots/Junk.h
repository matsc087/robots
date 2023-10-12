/**
 * Copyright (C) David Wolfe, 1999.  All rights reserved.
 * Ported to Qt and adapted for TDDD86, 2015.
 */

#ifndef JUNK_H
#define JUNK_H

#include "Unit.h"
#include <QGraphicsScene>

class Junk : public Unit {
public:
    Junk(const Point& p): Unit(p){}

    /*
    * Draws this junk onto the given QGraphicsScene.
    */
    void draw(QGraphicsScene* scene) const;

    void moveTowards(const Point&);

    bool isAlive() const;

    void doCrash();

    bool isToBeJunked() const;

    Junk* clone();

};

#endif // JUNK_H
