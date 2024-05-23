#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QString>
#include <QGraphicsPixmapItem>

class Game : public QGraphicsView{
public:
    Game();
    QGraphicsScene *scene;
    void setCursor(QString filename);
    QGraphicsPixmapItem *cursor;

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

private:


};

#endif // GAME_H
