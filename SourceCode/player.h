#pragma once

// プレイヤ?の画像の定数
#define PLAYER_TEX_W          (200)   // プレイヤ?の画像1つの幅
#define PLAYER_TEX_H          (300)   // プレイヤ?の画像1つの高さ
#define PLAYERBOX_TEX_W          (100)   // プレイヤ?の画像1つの幅
#define PLAYERBOX_TEX_H          (100)   // プレイヤ?の画像1つの高さ
#define PLAYER_PIVOT_X        (100)    // プレイヤ?の横方向の中心
#define PLAYER_PIVOT_Y        (300)   // プレイヤ?の縦方向の下?
#define PLAYERBOX_PIVOT_X        (50)    // プレイヤ?の横方向の中心
#define PLAYERBOX_PIVOT_Y        (100)   // プレイヤ?の縦方向の下?

// プレイヤ?の加速・減速の定数
#define PLAYER_ACCEL_X        (0.2f)  // プレイヤ?の横方向の加速度（加速用）
#define PLAYER_DECEL_X        (0.4f)  // プレイヤ?の横方向の加速度（減速用）
#define PLAYER_SPEED_X_MAX    (5.0f)  // プレイヤ?の横方向の速度の最大値
#define PLAYER_SPEED_DASH      5     //?ッシュ速度
#define SPEED_Y_MAX            14
//プレイヤ?の移動限界位置の定数
#define PLAYER_LIMIT_L         (PLAYER_TEX_W * 0.5f)
#define PLAYER_LIMIT_R         (SCREEN_W - PLAYER_TEX_W * 0.5f)
#define JUMP_H                 10          //ジャンプの高さ
#define PLAYER_HP              490         //プレイヤ?のHP
#define PLAYER_SUTAMINA        460         //ス??ナの量
#define PLAYER_SUTAMINA_SPEEDK  1          //プレイヤ?のス??ナ回復速度
#define PLAYER_SUTAMINA_SPEEDS  10         //プレイヤ?のス??ナ消費速度
#define PLAYER_INTAVAL          20         //ス??ナ回復までのイン??バル
#define PLAYER_TOUMEI           200        //プレイヤ?の透明時間
#define GRAVITY                (1.0f)      // 重力の定数
#define GROUND_Y               (640.0f)    // 地面の高さの定数


#define PLAYER_SIZE_X (25)      //画像横幅の1/4
#define PLAYER_SIZE_Y (150-16)  //画像立幅の半分-16
#define PLAYERBOX_SIZE_X (25)      //画像横幅の1/4
#define PLAYERBOX_SIZE_Y (100-16)  //画像立幅の半分-16

//------< 行動 >----------------------------------------------------------------

// プレイヤ?の各行動を?す定数
enum PLAYER_ACT
{
    OBJ_INIT = 0,       //   初期の数値設定
    IDLE_INIT,          //   待?_初期設定
    IDLE,               //   待?
    WALK_INIT,          //   歩き_初期設定
    WALK,               //   歩き
    RUN_INIT,           //   走り_初期設定
    RUN,                //   走り

    //ジャンプ
    JUMP_START_INIT,
    JUMP_START,
    JUMP_KEEP_INIT,
    JUMP_KEEP,
    JUMP_END_INIT,
    JUMP_END,

    GAME_OVER_INIT,        //ゲ??オ?バ?
     GAME_OVER,
};

enum PLAYERBOX_ACT
{
    B_OBJ_INIT = 0,       //   初期の数値設定
    B_IDLE_INIT,          //   待?_初期設定
    B_IDLE,               //   待?
    B_WALK_INIT,          //   歩き_初期設定
    B_WALK,               //   歩き
    B_RUN_INIT,           //   走り_初期設定
    B_RUN,                //   走り

};

//------< 関数 >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_act(OBJ2D* obj);     //人状態の処理     
void player_box(OBJ2D* obj);     //箱状態の処理
void areaCheck();
void player_moveX(OBJ2D* obj);
void player_moveY(OBJ2D* obj);
void playerbox_moveX(OBJ2D* obj);
void playerbox_moveY(OBJ2D* obj);
void player_damage();
void player_color();
bool player_isAlive();

int player_getkey();

void player_setkey(int diff);
void player_setpos(VECTOR2 pos);
VECTOR2 player_pos();
