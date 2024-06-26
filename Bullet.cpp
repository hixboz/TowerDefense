#include <Bullet.h>
#include <QPixmap>
#include <QTimer>
#include "qmath.h"


Bullet::Bullet(QGraphicsItem *parent)
{
    setPixmap(QPixmap(":/images/bullet.png"));

    //connect a timer to move
    QTimer *move_timer = new QTimer(this);
    connect(move_timer,SIGNAL(timeout()),this,SLOT(move()));

    move_timer->start(50);
}


void Bullet::move(){
    int STEP_SIZE = 30;
    double theta = rotation();    // degrees

    double dx = STEP_SIZE * qCos(qDegreesToRadians(theta));
    double dy = STEP_SIZE * qSin(qDegreesToRadians(theta));

    setPos(x()+dx, y()+dy);

}
