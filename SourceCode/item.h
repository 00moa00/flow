#pragma once

#define ITEM_MAX     10
#define ITEM_SIZE_X  32
#define ITEM_SIZE_Y  32

void setitem(int);

void item_init();
void item_deinit();
void item_update();
void item_render();
void item_move(OBJ2D*obj);
void item_moveY(OBJ2D*obj);
void item_card(OBJ2D* obj);
void item_door(OBJ2D* obj);

bool door_check(OBJ2D* obj, int diff);
bool door_flag();
void door_setflag(OBJ2D* obj, bool flag);
void door_anime(OBJ2D* obj, int koma);

enum Items
{
    red=0,
    blue,
    green,

};
