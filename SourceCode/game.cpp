//******************************************************************************
//
//
//      ゲ??
//
//
//******************************************************************************

//------< インクル?ド >---------------------------------------------------------
#include "all.h"
#include <windows.h>
#include <tchar.h>

//------< using >---------------------------------------------------------------
using namespace GameLib;

POINT po;

//------< 変数 >----------------------------------------------------------------
Game Game::instance_;
extern int stageNo;


//--------------------------------
//  初期化処理
//--------------------------------
void Game::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ
    juge_init();

    isPaused = false;   // ??ズフラグの初期化
    bg_ = new BG;
}

//--------------------------------
//  終了処理
//--------------------------------
void Game::deinit()
{
    // テクス?ャの解放
    texture::releaseAll();

    safe_delete(bg_);

    // 音楽のクリア
    music::clear();

    enemy_deinit();
    player_deinit();
    item_deinit();

}

//--------------------------------
//  更新処理
//--------------------------------
void Game::update()
{
    using namespace input;


    //TODO_10 ?フトリセット
    if ((STATE(0) & PAD_SELECT) && (TRG(0) & PAD_START))
    {
        changeScene(Title::instance());

    }

    // ??ズ処理
    //if (input::TRG(0) & PAD_START)
    //    isPaused = !isPaused;       // 0コンのス??ト??ンが押されたら??ズ状態が反?
    //if (isPaused) return;           // この時?で??ズ中ならリ??ン

    switch (state)
    {
    case STAGE_INIT:
        //////// 初期設定 ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルフ?処理


        //TODO_06 テクス?ャの読み込み
        texture::load(loadTexture);


        bg_->init();   //背景のinit()呼び出し
        enemy_init();
        player_init();
        item_init();

        state = STAGE;    // 初期化処理の終了

        /*fallthrough*/     // case 1:の処理も同時に行う必要があるため、わざとbreak;を記述していない

    case STAGE:
        //////// 通常時の処理 ////////

        timer++;

        if (!door_flag())
        {
            bg_->update();
            enemy_update();
            player_update();
            juge_update();
        }
        item_update();

        if (GetAsyncKeyState('3') & 1)
        {
            stageNo = 4;
            player_setpos(VECTOR2(3072, 512));
            set_bgstate(STAGE0_INIT);
        }

        if (player_isAlive() == false)
        {
           timer = 0;
           state = OVERE;
        }

        if (stage_clear())
            state = CLEAR;

        if ((STATE(0) & PAD_L3) || (STATE(0) & PAD_R3))
        {
            changeScene(Title::instance());
        }

        break;

    case OVERE:
        timer++;
        if (timer > 60 * 2)
            changeScene(Over::instance());
        break;

    case CLEAR:
        changeScene(Clear::instance());
        break;

    }
}

//--------------------------------
//  ?画処理
//--------------------------------
void Game::draw()
{
    // 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg_->drawBack();     // 背景の?画
    bg_->drawTerrain();  // 地?の?画
    enemy_render();
    item_render();
    player_render();

}

//******************************************************************************

