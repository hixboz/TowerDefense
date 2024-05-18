#include <Tower.h>
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>
#include "Bullet.h"
#include <QLineF>
#include "Game.h"
#include <QTimer>
#include <QGraphicsRectItem>
#include <QObject>

extern Game * game;

#define SCALE_FACTOR 65;

Tower::Tower(QGraphicsItem *parent):QObject(), QGraphicsPixmapItem(parent)
{
    //set the graphics
    setPixmap(QPixmap(":/images/tower.png"));

    //create vector points
    QVector<QPointF> points;

    points << QPoint(1,0) << QPoint(2,0)
    << QPoint(3,1) << QPoint(3,2)
    << QPoint(2,3) << QPoint(1,3)
    << QPoint(0,2) << QPoint(0,1) ;

    //scale points;
    for (int i=0; i<points.size(); i++){
        points[i] = points[i] * SCALE_FACTOR;
    }

    //create a polygon
    QPolygonF polygon(points);


    //create QGraphicsPolygonItem
    attack_area = new QGraphicsPolygonItem(polygon,this);

    //move the polygon
    QPointF poly_center(1.65,1.65);
    poly_center = poly_center * SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+44,y()+44);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // connect a timer to attack target
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(attack_target()));
    timer->start(1000);

    // set attack destination
    attack_dest = QPointF(800,0);
}

void Tower::attack_target()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+44, y()+44);

    QLineF ln(QPointF(x()+44, y()+44), attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);

}
