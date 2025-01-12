#ifndef ENEMY_H
#define ENEMY_H

#define ENEMY_MAX  (50)

#define ENEMY_ACCEL_X (1.0f)
#define ENEMY_SPEED_X_MAX (3.0f)

#define ENEMY_SIZE_X (43)
#define ENEMY_SIZE_Y (87-16)

#define SECOND (2)

#define SHOT_MAX   (100)
#define SHOT_SPEED	(4.0f)


void setenemy(int);


void enemy_init();
void enemy_deinit();
void enemy_update();
void enemy_render();

void enemy_moveX(OBJ2D* obj);
void boss_moveX(OBJ2D* obj);
void enemy_moveY(OBJ2D* obj);
void enemy_moveY2(OBJ2D* obj);

void player_touch(bool i);

void enemy_moveX2(OBJ2D* obj);

void enemy_shot(OBJ2D* obj);

void enemy_anime(OBJ2D* obj, int koma);
void boss_anime(OBJ2D* obj, int koma);
void shot_anime(OBJ2D* obj, int koma);
//
void moveEnemy0(OBJ2D* obj);
void moveEnemy1(OBJ2D* obj);
//’Ç‰Á
void moveBoss(OBJ2D* obj);
void movehasira(OBJ2D* obj);
//void moveEnemy2(OBJ2D* obj);

void damage_hasira(OBJ2D* obj);

bool all_enemycheck();
bool all_hasiracheck();
bool stage_clear();


#endif // !ENEMY_H

