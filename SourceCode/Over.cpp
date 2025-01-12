#include "All.h"

using namespace GameLib;

Over Over::instance_;
Sprite* sprover;

void Over::update()
{
    using namespace input;

    switch (state)
    {
    case 0:
        sprover = sprite_load(L"Data/Images/gameover2.png");

        se = 0;
        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);
        /*fallthrough*/
        ++state;
    case 1:
        if (TRG(0) & PAD_START)
            changeScene(Title::instance());

        break;
    }

}

void Over::draw()
{
    GameLib::clear(VECTOR4(0.0f, 0.5f, 1.0f, 1));

    sprite_render(sprover, 0, 0);

    //font::textOut(4, "ゲームオーバー", 60, 60, 4, 4, 1.0f, 1.0f, 0.0);
    //font::textOut(4, "", 60, 160, 2, 2, 0.0f, 1.0f, 1.0f);
}
