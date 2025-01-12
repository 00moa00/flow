#include "all.h"

using namespace GameLib;

Tuto Tuto::instance_;
extern int stageNo;
Sprite* sprtuto;

void Tuto::init()
{
    Scene::init();	    // ���N���X��init���Ă�
    juge_init();

    
    isPaused = false;   // �|�[�Y�t���O�̏�����
    bg_ = new BG;
}

void Tuto::deinit()
{
    // �e�N�X�`���̉��
    texture::releaseAll();

    //safe_delete(bg_);

    // ���y�̃N���A
    music::clear();

    enemy_deinit();
    player_deinit();
    item_deinit();
    safe_delete(sprtuto);
}

void Tuto::update()
{
    using namespace input;


    //�\�t�g���Z�b�g (�o�b�N�X�y�[�X�ƃG���^�[�L�[��������)
    if ((STATE(0) & PAD_SELECT) && (TRG(0) & PAD_START))
    {
        changeScene(Title::instance());

    }

    switch (state)
    {
    case STAGE_INIT:
        //////// �����ݒ� ////////
        stageNo = 0;
        timer = 0;
        GameLib::setBlendMode(Blender::BS_ALPHA);   // �ʏ�̃A���t�@����

        texture::load(loadTexture);
        sprtuto = sprite_load(L"./Data/Images/tuto.png");


        bg_->init();   //�w�i��init()�Ăяo��
        enemy_init();
        player_init();

        state = STAGE;    // �����������̏I��

        /*fallthrough*/     // case 1:�̏����������ɍs���K�v�����邽�߁A�킴��break;���L�q���Ă��Ȃ�

    case STAGE:
        //////// �ʏ펞�̏��� ////////

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
    //// ��ʃN���A
    GameLib::clear(VECTOR4(0, 0, 0, 1));

    bg_->drawBack();     // �w�i�̕`��
    bg_->drawTerrain();  // �n�`�̕`��
    enemy_render();
    player_render();
    sprite_render(sprtuto, 0, 0);

}
