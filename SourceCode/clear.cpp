#include "All.h"

using namespace GameLib;

Clear Clear::instance_;
Sprite* sprclear;
void Clear::update()
{
    using namespace input;

    switch (state)
    {
    case 0:
        sprclear = sprite_load(L"./Data/Images/clear.png");

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);
        /*fallthrough*/
        state++;

    case 1:
        if (TRG(0) & PAD_START)
            changeScene(Title::instance());






        break;
    }
   
}

void Clear::draw()
{

    GameLib::clear(VECTOR4(1.0f, 0.5f, 1.0f, 1));
    sprite_render(sprclear, 0, 0);
    
    
}
