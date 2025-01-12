#include "all.h"

//ルアー言語

Story Story::instance_;

using namespace GameLib;

int story_state=0;    // 状態
int story_fonter;   //この変数の値でどのセリフを描画するか管理する
int story_haikei;   //この変数の値でどの画像を描画するか管理する
int story_timer=0;    // タイマー

struct SPR_DATA
{
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2         texPos;
    VECTOR2         texSize;
    VECTOR2         pivot;
    int             scene;    //表示文章、背景管理用変数

} backData[] = 
{
    
    {NULL,L"./Data/Images/scene_back/sa_scene0.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_back/sa_scene1.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_back/sa_scene2.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_back/sa_scene3.png",{0,0},{1280,720},{0,0}, 0},
     {NULL,L"./Data/Images/scene_back/sa_scene3.png",{0,0},{1280,720},{0,0}, -1},
    
};

SPR_DATA fonData[] =
{
    {NULL,L"./Data/Images/scene_rano/rano00.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_rano/rano01.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_rano/rano01.png",{0,0},{1280,720},{0,0}, -1},   //画像1枚目の区切り
    {NULL,L"./Data/Images/scene_rano/rano.png",{0,0},{1280,720},{0,0}, 0}, 
    {NULL,L"./Data/Images/scene_rano/rano02.png",{0,0},{1280,720},{0,0}, -1}, //画像2枚目の区切り
    {NULL,L"./Data/Images/scene_rano/rano02.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_rano/rano03.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_rano/rano01.png",{0,0},{1280,720},{0,0}, -1},  //画像3枚目の区切り 
    {NULL,L"./Data/Images/scene_rano/rano.png",{0,0},{1280,720},{0,0}, 0},
    {NULL,L"./Data/Images/scene_rano/rano01.png",{0,0},{1280,720},{0,0}, -1},

};


void Story::init()
{
    Scene::init();	    // 基底クラスのinitを呼ぶ
    //story_state = 0;
    //story_timer = 0;
    //story_fonter = 0;
    //story_haikei = 0;
}

void Story::update()
{

    using namespace input;

    int back_size = sizeof(backData) / sizeof(SPR_DATA);
    int fon_size = sizeof(fonData) / sizeof(SPR_DATA);

    switch (state)
    {
    case 0:

        for (int i = 0; i < back_size; i++)
        {
            if (backData[i].scene < 0) continue;
            backData[i].spr = sprite_load(backData[i].filePath);
        }

        for (int i = 0; i < fon_size; i++)
        {
            if (fonData[i].scene < 0) continue;
            fonData[i].spr = sprite_load(fonData[i].filePath);
        }

        story_fonter = 0;
        story_haikei = 0;

        state++;
        /*fallthrough*/

    case 1:
        if ((GetAsyncKeyState(MK_LBUTTON) & 1) || (TRG(0) & PAD_RIGHT) || (TRG(0) & PAD_START))
        {
            if (story_fonter < fon_size)
            story_fonter++;
        }

        if (fonData[story_fonter].scene < 0)
        {
            if (story_haikei < back_size)
            {
                story_haikei++;
                story_fonter++;
            }

        }

        if (backData[story_haikei].scene < 0)
        {

            changeScene(Game::instance());
            story_haikei++;
        }

        break;

    }
    if (story_haikei >= back_size)  story_haikei = back_size - 1;
    if (story_fonter >= fon_size)  story_fonter = fon_size - 1;

}

void Story::draw()
{
    //背景描画
    if (!(backData[story_haikei].scene < 0))
    {
        sprite_render(
            backData[story_haikei].spr,
            0, 0,
            1.0f, 1.0f,
            backData[story_haikei].texPos.x, backData[story_haikei].texPos.y,
            backData[story_haikei].texSize.x, backData[story_haikei].texSize.y,
            backData[story_haikei].pivot.x, backData[story_haikei].pivot.y,
            0
        );
    }

    //文章描画
    if (!(fonData[story_fonter].scene < 0))
    {
        sprite_render(
            fonData[story_fonter].spr,
            0, 0,
            1.0f, 1.0f,
            fonData[story_fonter].texPos.x, fonData[story_fonter].texPos.y,
            fonData[story_fonter].texSize.x, fonData[story_fonter].texSize.y,
            fonData[story_fonter].pivot.x, fonData[story_fonter].pivot.y,
            0
        );
    }
}

Story::~Story()
{
    int back_size = sizeof(backData) / sizeof(SPR_DATA);
    int fon_size = sizeof(fonData) / sizeof(SPR_DATA);
    for (int i = 0; i < back_size; i++)
    {
        if (backData[i].scene < 0) continue;
        safe_delete(backData[i].spr);
    }
    for (int i = 0; i < fon_size; i++)
    {
        if (fonData[i].scene < 0) continue;
        safe_delete(fonData[i].spr);
    }
}
