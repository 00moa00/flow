#pragma once

#include "all.h"

void juge_init();
void juge_deinit();
void juge_update();
void juge_draw();

bool hanteiR(float x1, float x2, float gx1, float gx2, float y1, float y2, float gy1, float gy2);  //当たり判定四角形
//当たり判定用
bool hitcheck(float, float, float, float);

#define DAMAGE_OFFSET    8