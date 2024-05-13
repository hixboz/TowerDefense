#include <Tower.h>
#include <QPixmap>
#include <QVector>
#include <QPointF>
#include <QPolygonF>

#define SCALE_FACTOR 65;

Tower::Tower(QGraphicsItem *parent)
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

    //move the center
    QPointF poly_center(1.65,1.65);
    poly_center = poly_center * SCALE_FACTOR;
    poly_center = mapToScene(poly_center);
    QPointF tower_center(x()+44,y()+44);
    QLineF ln(poly_center,tower_center);
    attack_area->setPos(x()+ln.dx(),y()+ln.dy());
}
