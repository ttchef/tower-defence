
#include "playing/enemy.h"

Enemy spawnEnemy() {
    Enemy e;
    e.pos = (Vector2){50, 550};
    e.active = true;
    return e;
}

void drawEnemy(Enemy *enemy) {
    DrawCircle(enemy->pos.x, enemy->pos.y, 10, BLUE);    
}

