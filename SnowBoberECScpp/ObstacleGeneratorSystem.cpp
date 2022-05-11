#include "ObstacleGeneratorSystem.h"
#include "World.h"
#include "ConstValues.h"

ObstacleGeneratorSystem::ObstacleGeneratorSystem(int obstaclesMinIndex, int gridMinIndex, int scoreMinIndex, int maxNumberOfObstacles_, const TexturesManager* texManager) : textures(texManager) {
    maxNumberOfObstacles = maxNumberOfObstacles_;
    obstacleMin = obstaclesMinIndex;
    obstacleMax = obstaclesMinIndex + maxNumberOfObstacles - 1;
    current = 0;
    spawnRate = 300;
    gridMin = gridMinIndex;
    gridMax = gridMinIndex + maxNumberOfObstacles - 1;
    scoreMin = scoreMinIndex;
    scoreMax = scoreMinIndex + maxNumberOfObstacles - 1;
    initialSpeed = -3;
    speedCount = 3;
    frame = 0;
    srand(time(0));
}

void ObstacleGeneratorSystem::update(long gameFrame, float delta, World* world) {
    frame++;

    if (frame % int(ConstValues::NUMBER_OF_FRAMES_TO_INCREMENT) == 0) {
        spawnRate = spawnRate - spawnRate / speedCount;
        speedCount++;
        frame = 1;
    }

    if (frame % spawnRate == 0) {
        current++;
        if (current >= maxNumberOfObstacles) current = 0;

        int x = rand() % 1000;

        if (x < 333) {
            createBox(world);
            createScorePoint(world, int(ConstValues::V_WIDTH) + 300);
        }
        else if (x < 666) {
            createGridFlag(world);
            createGridStick(world);
            createScorePoint(world, int(ConstValues::V_WIDTH) + 500);
        }
        else {
            createRail(world);
            createScorePoint(world, int(ConstValues::V_WIDTH) + 550);
        }
    }
}

void ObstacleGeneratorSystem::createGridFlag(World* world) {
    world->addComponentToEntity<Position>(gridMin + current, Position(int(ConstValues::V_WIDTH), int(ConstValues::GRID_POSITION_Y)));
    world->addComponentToEntity<Visual>(gridMin + current, Visual(textures->grid, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT));
    world->addComponentToEntity<Move>(gridMin + current, Move(initialSpeed));
    world->addComponentToEntity<Collision>(gridMin + current, Collision(int(ConstValues::GRID_WIDTH), int(ConstValues::GRID_HEIGHT), ObstacleType::GRID));
}

void ObstacleGeneratorSystem::createGridStick(World* world) {
    world->addComponentToEntity<Position>(obstacleMin + current, Position(int(ConstValues::V_WIDTH), int(ConstValues::GRID_POSITION_Y)));
    world->addComponentToEntity<Visual>(obstacleMin + current, Visual(textures->gridStick, ConstValues::GRID_WIDTH, ConstValues::GRID_HEIGHT));
    world->addComponentToEntity<Move>(obstacleMin + current, Move(initialSpeed));
    world->addComponentToEntity<Collision>(obstacleMin + current, Collision(0, 0, ObstacleType::GRID));
}

void ObstacleGeneratorSystem::createRail(World* world) {
    world->addComponentToEntity<Position>(obstacleMin + current, Position(int(ConstValues::V_WIDTH), int(ConstValues::RAIL_POSITION_Y)));
    world->addComponentToEntity<Visual>(obstacleMin + current, Visual(textures->rail, ConstValues::RAIL_WIDTH, ConstValues::RAIL_HEIGHT));
    world->addComponentToEntity<Move>(obstacleMin + current, Move(initialSpeed));
    world->addComponentToEntity<Collision>(obstacleMin + current, Collision(int(ConstValues::RAIL_WIDTH) - 100, int(ConstValues::RAIL_HEIGHT), ObstacleType::RAIL));
}

void ObstacleGeneratorSystem::createBox(World* world) {
    world->addComponentToEntity<Position>(obstacleMin + current, Position(int(ConstValues::V_WIDTH), int(ConstValues::BOX_POSITION_Y)));
    world->addComponentToEntity<Visual>(obstacleMin + current, Visual(textures->box, ConstValues::BOX_WIDTH, ConstValues::BOX_HEIGHT));
    world->addComponentToEntity<Move>(obstacleMin + current, Move(initialSpeed));
    world->addComponentToEntity<Collision>(obstacleMin + current, Collision(int(ConstValues::BOX_WIDTH), int(ConstValues::BOX_HEIGHT), ObstacleType::BOX));
}

void ObstacleGeneratorSystem::createScorePoint(World* world, int positionX) {
    world->addComponentToEntity<Position>(scoreMin + current, Position(positionX, 0));
    world->addComponentToEntity<Visual>(scoreMin + current, Visual(textures->heart, ConstValues::SCORE_WIDTH, ConstValues::SCORE_HEIGHT, false));
    world->addComponentToEntity<Move>(scoreMin + current, Move(initialSpeed));
    world->addComponentToEntity<Collision>(scoreMin + current, Collision(int(ConstValues::SCORE_WIDTH), int(ConstValues::SCORE_HEIGHT), ObstacleType::SCORE_POINT));
}
