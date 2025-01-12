//******************************************************************************
//
//
//      �Q??
//
//
//******************************************************************************

//------< �C���N��?�h >---------------------------------------------------------
#include "all.h"
#include <windows.h>
#include <tchar.h>

//------< using >---------------------------------------------------------------
using namespace GameLib;

POINT po;

//------< �ϐ� >----------------------------------------------------------------
Game Game::instance_;
extern int stageNo;


//--------------------------------
//  ����������
//--------------------------------
void Game::init()
{
    Scene::init();	    // ���N���X��init���Ă�
    juge_init();

    isPaused = false;   // ??�Y�t���O�̏�����
    bg_ = new BG;
}

//--------------------------------
//  �I������
//--------------------------------
void Game::deinit()
{
    // �e�N�X?���̉��
    texture::releaseAll();

    safe_delete(bg_);

    // ���y�̃N���A
    music::clear();

    enemy_deinit();
    player_deinit();
    item_deinit();

}

//--------------------------------
//  �X�V����
//--------------------------------
void Game::update()
{
    using namespace input;


    //TODO_10 ?�t�g���Z�b�g
    if ((STATE(0) & PAD_SELECT) && (TRG(0) & PAD_START))
    {
        changeScene(Title::instance());

    }

    // ??�Y����
    //if (input::TRG(0) & PAD_START)
    //    isPaused = !isPaused;       // 0�R���̃X??�g??���������ꂽ��??�Y��Ԃ���?
    //if (isPaused) return;           // ���̎�?��??�Y���Ȃ烊??��

    switch (state)
    {
    case STAGE_INIT:
        //////// �����ݒ� ////////

        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t?����


        //TODO_06 �e�N�X?���̓ǂݍ���
        texture::load(loadTexture);


        bg_->init();   //�w�i��init()�Ăяo��
        enemy_init();
        player_init();
        item_init();

        state = STAGE;    // �����������̏I��

        /*fallthrough*/     // case 1:�̏����������ɍs���K�v�����邽�߁A�킴��break;���L�q���Ă��Ȃ�

    case STAGE:
        //////// �ʏ펞�̏��� ////////

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
//  ?�揈��
//--------------------------------
void Game::draw()
{
    // ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg_->drawBack();     // �w�i��?��
    bg_->drawTerrain();  // �n?��?��
    enemy_render();
    item_render();
    player_render();

}

//******************************************************************************

