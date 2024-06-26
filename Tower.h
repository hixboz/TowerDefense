#ifndef TOWER_H
#define TOWER_H

#include <QGraphicsPixmapItem>
#include <QGraphicsPolygonItem>
#include <QGraphicsItem>
#include <QPointF>
#include <QObject>
#include "Game.h"
#include "Enemy.h"

class Tower : public QObject,public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Tower(QGraphicsItem *parent=0);
    double distanceTo(QGraphicsItem * item);
    void fire();

public slots:

    void acquire_target();

private:
    QGraphicsPolygonItem *attack_area;
    QPointF attack_dest;
    bool has_target;

};

#endif // TOWER_H
