
#ifndef ENEMY_H
#define ENEMY_H

#include "definies.h"

#define MAX_ENEMIES 100

typedef enum {
    GOBLIN,
    GOLEM,
} EnemyType;

typedef struct {
    EnemyType type;
    bool active;
    float interpolate;
    int32_t pointsIndex;
    float speed;
    int32_t size;
    Vector2 pos;
    int32_t health;
    int32_t startHealth;
    int32_t value;
    Color color;
} Enemy;

Enemy spawnEnemy(EnemyType type);
void updateEnemy(GameManager* gm, Enemy* enemy);
void drawEnemy(Enemy* enemy);

#endif
