#include "all.h"

using namespace GameLib;

Tuto Tuto::instance_;
extern int stageNo;
Sprite* sprtuto;

void Tuto::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ
    juge_init();

    
    isPaused = false;   // ポーズフラグの初期化
    bg_ = new BG;
}

void Tuto::deinit()
{
    // テクスチャの解放
    texture::releaseAll();

    //safe_delete(bg_);

    // 音楽のクリア
    music::clear();

    enemy_deinit();
    player_deinit();
    item_deinit();
    safe_delete(sprtuto);
}

void Tuto::update()
{
    using namespace input;


    //ソフトリセット (バックスペースとエンターキー同時押し)
    if ((STATE(0) & PAD_SELECT) && (TRG(0) & PAD_START))
    {
        changeScene(Title::instance());

    }

    switch (state)
    {
    case STAGE_INIT:
        //////// 初期設定 ////////
        stageNo = 0;
        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // 通常のアルファ処理

        texture::load(loadTexture);
        sprtuto = sprite_load(L"./Data/Images/tuto.png");


        bg_->init();   //背景のinit()呼び出し
        enemy_init();
        player_init();

        state = STAGE;    // 初期化処理の終了

        /*fallthrough*/     // case 1:の処理も同時に行う必要があるため、わざとbreak;を記述していない

    case STAGE:
        //////// 通常時の処理 ////////

        timer++;

            bg_->update();
            enemy_update();
            player_update();
            juge_update();

        if (player_isAlive() == false)
        {
            timer = 0;
            state = OVERE;
        }
        if(!all_enemycheck()) changeScene(Title::instance());


        break;

    case OVERE:
        timer++;
        if (timer > 60 * 2)
            changeScene(Over::instance());
        break;
    }


}

void Tuto::draw()
{
    //// 画面クリア
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg_->drawBack();     // 背景の描画
    bg_->drawTerrain();  // 地形の描画
    enemy_render();
    player_render();
    sprite_render(sprtuto, 0, 0);

}
