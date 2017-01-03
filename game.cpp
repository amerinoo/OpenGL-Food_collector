/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"
using namespace std;


// Constructors
Game::Game(){ }

Game::Game(int height, int width, float seed)
    : height(height), width(width), seed(seed), map(NULL){ }

// Getters
int Game::getHeight(){ return height; }

int Game::getWidth(){ return width; }

void Game::draw(){
    player->draw();
    enemy->draw();
    vector<vector<Cell *> > m = map->getMap();
    for (int i = 0; i < map->getHeight(); i++)
        for (int j = 0; j < map->getWidth(); j++)
            m[i][j]->draw();
}

void Game::drawText(const char * title, bool isConnected){
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0.0, width, 0.0, height);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    Drawer& drawer = Drawer::getInstance();
    drawer.printTitle(title);
    drawer.printScore(player->getScore(), enemy->getScore());
    drawer.printLevel(level);
    drawer.printVelocity(Agent::agentVelocity);
    drawer.printFood(map->getFoodRemaining());
    drawer.printArduino(isConnected);

    glMatrixMode(GL_MODELVIEW);
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
}

void Game::resetGame(){
    level = 0;
    pause = false;
    newGame();
}

void Game::newGame(){
    newMap();
    level += 1;
    player = new Agent(PLAYER, map->getInitPosition(PLAYER), new Strategy(map));
    enemy  = new Agent(ENEMY, map->getInitPosition(ENEMY), new ExpectimaxAgent(map, 4));
    // enemy  = new Agent(ENEMY, map->getInitPosition(ENEMY), new ReflexAgent(map));
    player->setAgent(enemy);
    enemy->setAgent(player);
    map->print();
}

void Game::pauseGame(){
    pause = !pause;
}

void Game::integrate(long t){
    if (!pause) {
        integrate(player, t);
        integrate(enemy, t);
    }
}

void Game::integrate(Agent * agent, long t){
    if (agent->integrate(t) || agent->isQuiet()) {
        if (map->hasFood()) {
            if (agent->getNeedAction()) {
                agent->setPosition(agent->getNextPosition());
                Direction d = agent->getStrategy()->getAction();
                agent->setNextDirection(d);
                agent->tryNextDirection();
            }
            agent->move();
        } else { finish(); }
    }
}

void Game::finish(){
    if (playerWin()) newGame();
    else resetGame();
}

bool Game::playerWin(){ return player->getScore() > enemy->getScore(); }

void Game::moveAgent(CellType cellType, Direction direction){
    if (cellType == PLAYER) {
        if (player->isQuiet()) player->setDirection(direction);
        else player->setNextDirection(direction);
    }
}

void Game::shoot(CellType cellType){
    if (cellType == PLAYER) {
        player->shoot();
    }
}

void Game::newMap(){
    if (map != NULL) delete map;
    map = new Map(height, width);
    if (seed != -1) map->setSeed(seed);
    map->generate();
}
