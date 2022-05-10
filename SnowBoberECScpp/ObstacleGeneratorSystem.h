#pragma once
#include "System.h"
#include "TexturesManager.h"

class ObstacleGeneratorSystem : public System {
public :
     ObstacleGeneratorSystem(int obstaclesMinIndex, int gridMinIndex, int scoreMinIndex, int maxNumberOfObstacles_, const TexturesManager* texManager);

	void update(long gameFrame, float delta, World* world);

private:
    const TexturesManager* textures;
    int maxNumberOfObstacles;
    int obstacleMin, obstacleMax;
    int current;
    int spawnRate;
    int gridMin, gridMax;
    int scoreMin, scoreMax;
    int initialSpeed;
    int speedCount;
    int frame;

    void createGridFlag(World* world);

    void createGridStick(World* world);

    void createRail(World* world);

    void createBox(World* world);

    void createScorePoint(World* world, int positionX);
};

