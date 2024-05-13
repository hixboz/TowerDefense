
#include <Game.h>
#include <Tower.h>

Game::Game()
{
    //create a scene
    scene = new QGraphicsScene(this);

    //Set the scene
    setScene(scene);

    //create a tower
    Tower *t = new Tower();

    //add the tower to the scene
    scene->addItem(t);

    setFixedSize(800,600);

}
