#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>

class Game : public QGraphicsView{
public:
    Game();
    QGraphicsScene *scene;
    void mousePressEvent(QMouseEvent *event);

private:


};

#endif // GAME_H
