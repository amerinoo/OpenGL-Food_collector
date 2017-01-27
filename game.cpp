/*
 * Project name: Food collection
 * Version 4
 * Student : Albert Eduard Merino Pulido
 */
#include "game.h"
using namespace std;


// Constructors
Game::Game(){ }

Game::Game(int height, int width, float seed, StrategyType strategyTypePlayer, StrategyType strategyTypeEnemy)
    : height(height), width(width), seed(seed), strategyTypePlayer(strategyTypePlayer),
    strategyTypeEnemy(strategyTypeEnemy), map(NULL){
    player = new Agent(PLAYER, getStrategyByType(PLAYER, strategyTypePlayer));
    enemy  = new Agent(ENEMY, getStrategyByType(ENEMY, strategyTypeEnemy));
    player->setAgent(enemy);
    enemy->setAgent(player);
}

// Getters
int Game::getHeight(){ return height; }

int Game::getWidth(){ return width; }

bool Game::isPaused(){ return pause; }

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
    player->setMap(map);
    enemy->setMap(map);
    std::cout << map->toString();
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
                agent->observationFunction(*map);
            }
            agent->move();
        } else {
            agent->final(*map);
            finish();
        }
    }
} // integrate

void Game::finish(){
    bool playerWins = playerWin();

    showGameResults(playerWins);
    if (playerWins) newGame();
    else resetGame();
}

bool Game::playerWin(){ return player->getScore() > enemy->getScore(); }

void Game::showGameResults(bool playerWins){
    if (playerWins) cout << "Player Wins!" << endl;
    else cout << "Enemy Wins!" << endl;
    cout << "Player: " << player->getScore() << std::endl;
    cout << "Enemy: " << enemy->getScore() << std::endl;
    cout << "Level: " << level << std::endl;
    cout << std::endl << "**********************" << std::endl << std::endl;
}

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

Strategy * Game::getStrategyByType(CellType agent, StrategyType strategyType){
    switch (strategyType) {
        case REFLEX_AGENT:
            return new ReflexAgent(map, agent);

        case EXPECTIMAX_AGENT:
            return new ExpectimaxAgent(map, agent, 4);

        case REINFORCEMENT_AGENT:
            return new PacmanQAgent(map, agent);

        default:
            return new Strategy(map, agent);
    }
}
