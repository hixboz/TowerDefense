
#include <Game.h>
#include <Tower.h>
#include <Bullet.h>
#include <QGraphicsScene>
#include "Enemy.h"
#include <QPixmap>
#include <QMouseEvent>
#include <QGraphicsPixmapItem>

Game::Game(): QGraphicsView()
{
    //create a scene
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,800,600);

    //Set the scene
    setScene(scene);

    //create a tower
    Tower *t = new Tower();
    t->setPos(250,250);

    //add the tower to the scene
    scene->addItem(t);
    
    //set cursor
    cursor = nullptr;
    setMouseTracking(true);

    setFixedSize(800,600);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    // create an enemy
    Enemy *enemy = new Enemy();
    scene->addItem(enemy);

    // test code
    setCursor(":images/tower.png");

}

void Game::setCursor(QString filename)
{
    if(cursor){
        scene->removeItem(cursor);
        delete cursor;
    }
    cursor = new QGraphicsPixmapItem();
    cursor->setPixmap(QPixmap(filename));
    scene->addItem(cursor);
}

void Game::mouseMoveEvent(QMouseEvent *event)
{
    if(cursor){
        cursor->setPos(event->pos());
    }
}



void Game::mousePressEvent(QMouseEvent *event)
{
    //create a bullet
    Bullet *bullet = new Bullet();
    bullet->setPos(event->pos());
    bullet->setRotation(40);
    scene->addItem(bullet);
}
