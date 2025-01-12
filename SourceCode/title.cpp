//******************************************************************************
//
//
//      タイトル
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"
#include <iostream>
#include <iomanip>


using namespace std;
Sprite* sprtitle;
Sprite* sprcur;

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< 変数 >----------------------------------------------------------------
Title Title::instance_;
int stageNo;

float curpos_x, curpos_y;
POINT  pt;

//--------------------------------
//  更新処理
//--------------------------------
void Title::update()
{
    using namespace input;


    switch (state)
    {
    case 0:
        //////// 初期設定 ////////
        sprtitle = sprite_load(L"./Data/Images/title3.png");
        sprcur = sprite_load(L"./Data/Images/ui.png");

        stageNo = 1;
        se = 0;                                     //0はゲームシーン 1はチュートリアル
        timer = 0;                                  // タイマーを初期化
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理
        state++;                                    // 初期化処理の終了
        curpos_x = SCREEN_W / 2;
        curpos_y = SCREEN_H / 2;

        /*fallthrough*/                             // 意図的にbreak;を記述していない

    case 1:
        //////// 通常時の処理 ////////

        ShowCursor(FALSE);
        GetCursorPos(&pt);
        ScreenToClient(window::getHwnd(), &pt);

        curpos_x = pt.x;
        curpos_y = pt.y;

        //if (curpos_x >= SCREEN_W - 37) { curpos_x = SCREEN_W - 37; }
        //if (curpos_x <= 0)             { curpos_x = 0; }
        //if (curpos_y <= 0)             { curpos_y = 0; }
        //if (curpos_y >= SCREEN_H - 53) { curpos_y = SCREEN_H - 53; }

        if (curpos_x > 70 && curpos_x < 345 && curpos_y>550 && curpos_y < 640) {
            if (GetAsyncKeyState(MK_LBUTTON))  //左ボタンがクリックされたら
            {
                changeScene(Story::instance());
            }
        }
        if (curpos_x > 400 && curpos_x < 680 && curpos_y>550 && curpos_y < 640) {
            if (GetAsyncKeyState(MK_LBUTTON))  //左ボタンがクリックされたら
            {
                changeScene(Tuto::instance());
            }
        }





        if (TRG(0) & PAD_LEFT) se--;
        if (TRG(0) & PAD_RIGHT) se++;

        if (se < 0)  se = 0;

        if (TRG(0) & PAD_START)             // PAD_TRG1が押されたら
            changeScene(select[se%2]);  // ゲームシーンに切り替え



        timer++;                            // タイマーを足す

        break;
    }
}

//--------------------------------
//  描画処理
//--------------------------------
void Title::draw()
{
    sprite_render(sprtitle, 0, 0);
    sprite_render(sprcur, curpos_x, curpos_y);


}


struct DOOR_POS
{
    VECTOR2 red_door1 = { 3776, 1792 };
    VECTOR2 red_door2 = { 192, 1600 };
    VECTOR2 blue_door1 = { 2432, 512 };
    VECTOR2 blue_door2 = { 192, 448 };
    VECTOR2 green_door1 = { 3072, 512 };
    VECTOR2 green_door2 = { 128, 1280 };
} door_pos;

void sceneChenge(int stage, int diff)
{
    switch (stage)
    {
    case 0: //チュートリアルの場合
        break;  //何もなし

    case 1: //ステージ1の場合
        stageNo = 2;
        player_setpos(door_pos.red_door2);
        break;

    case 2: //ステージ2の場合
        if (diff == red)
        {
            stageNo = 1;
            player_setpos(door_pos.red_door1);

        }
        if (diff == blue)
        {
            stageNo = 3;
            player_setpos(door_pos.blue_door2);

        }
        if (diff == green)
        {
            Title::instance()->changeScene(Clear::instance());
            player_setpos(door_pos.green_door2);
        }
        break;

    case 3:
        stageNo = 2;
        player_setpos(door_pos.blue_door1);
        break;

    case 4:
        stageNo = 3;
        player_setpos(door_pos.green_door1);
        break;

    }


}

//******************************************************************************
