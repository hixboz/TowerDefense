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
    attack_area->setPen(QPen(Qt::DotLine));

    //move the polygon
    QPointF poly_center(1.65,1.65);
    poly_center = poly_center * SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+44,y()+44);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());

    // connect a timer to attack target
    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), this, SLOT(acquire_target()));
    timer->start(1000);

    // set attack destination
    attack_dest = QPointF(800,0);
}

double Tower::distanceTo(QGraphicsItem *item)
{
    QLineF ln(pos(),item->pos());
    return ln.length();
}

void Tower::fire()
{
    Bullet *bullet = new Bullet();
    bullet->setPos(x()+44, y()+44);

    QLineF ln(QPointF(x()+44, y()+44), attack_dest);
    int angle = -1 * ln.angle();

    bullet->setRotation(angle);
    game->scene->addItem(bullet);

}

void Tower::acquire_target()
{
    //Get a list of all items colliding with attack area
    QList<QGraphicsItem *> colliding_items = attack_area->collidingItems();

    if(colliding_items.size() == 1){
        has_target = false;
        return;
    }

    double closest_distance = 300;
    QPointF closest_point = QPointF(0,0);
    for(size_t i=0, n=colliding_items.size(); i<n; i++){
        Enemy *enemy = dynamic_cast<Enemy *>(colliding_items[i]);
        if(enemy){
            double this_dist = distanceTo(enemy);
            if (this_dist < closest_distance){
                closest_distance = this_dist;
                closest_point = colliding_items[i]->pos();
                has_target = true;
            }
        }
    }

    attack_dest = closest_point;
    fire();

}
