#pragma once

// �v���C��?�̉摜�̒萔
#define PLAYER_TEX_W          (200)   // �v���C��?�̉摜1�̕�
#define PLAYER_TEX_H          (300)   // �v���C��?�̉摜1�̍���
#define PLAYERBOX_TEX_W          (100)   // �v���C��?�̉摜1�̕�
#define PLAYERBOX_TEX_H          (100)   // �v���C��?�̉摜1�̍���
#define PLAYER_PIVOT_X        (100)    // �v���C��?�̉������̒��S
#define PLAYER_PIVOT_Y        (300)   // �v���C��?�̏c�����̉�?
#define PLAYERBOX_PIVOT_X        (50)    // �v���C��?�̉������̒��S
#define PLAYERBOX_PIVOT_Y        (100)   // �v���C��?�̏c�����̉�?

// �v���C��?�̉����E�����̒萔
#define PLAYER_ACCEL_X        (0.2f)  // �v���C��?�̉������̉����x�i�����p�j
#define PLAYER_DECEL_X        (0.4f)  // �v���C��?�̉������̉����x�i�����p�j
#define PLAYER_SPEED_X_MAX    (5.0f)  // �v���C��?�̉������̑��x�̍ő�l
#define PLAYER_SPEED_DASH      5     //?�b�V�����x
#define SPEED_Y_MAX            14
//�v���C��?�̈ړ����E�ʒu�̒萔
#define PLAYER_LIMIT_L         (PLAYER_TEX_W * 0.5f)
#define PLAYER_LIMIT_R         (SCREEN_W - PLAYER_TEX_W * 0.5f)
#define JUMP_H                 10          //�W�����v�̍���
#define PLAYER_HP              490         //�v���C��?��HP
#define PLAYER_SUTAMINA        460         //�X??�i�̗�
#define PLAYER_SUTAMINA_SPEEDK  1          //�v���C��?�̃X??�i�񕜑��x
#define PLAYER_SUTAMINA_SPEEDS  10         //�v���C��?�̃X??�i����x
#define PLAYER_INTAVAL          20         //�X??�i�񕜂܂ł̃C��??�o��
#define PLAYER_TOUMEI           200        //�v���C��?�̓�������
#define GRAVITY                (1.0f)      // �d�͂̒萔
#define GROUND_Y               (640.0f)    // �n�ʂ̍����̒萔


#define PLAYER_SIZE_X (25)      //�摜������1/4
#define PLAYER_SIZE_Y (150-16)  //�摜�����̔���-16
#define PLAYERBOX_SIZE_X (25)      //�摜������1/4
#define PLAYERBOX_SIZE_Y (100-16)  //�摜�����̔���-16

//------< �s�� >----------------------------------------------------------------

// �v���C��?�̊e�s����?���萔
enum PLAYER_ACT
{
    OBJ_INIT = 0,       //   �����̐��l�ݒ�
    IDLE_INIT,          //   ��?_�����ݒ�
    IDLE,               //   ��?
    WALK_INIT,          //   ����_�����ݒ�
    WALK,               //   ����
    RUN_INIT,           //   ����_�����ݒ�
    RUN,                //   ����

    //�W�����v
    JUMP_START_INIT,
    JUMP_START,
    JUMP_KEEP_INIT,
    JUMP_KEEP,
    JUMP_END_INIT,
    JUMP_END,

    GAME_OVER_INIT,        //�Q??�I?�o?
     GAME_OVER,
};

enum PLAYERBOX_ACT
{
    B_OBJ_INIT = 0,       //   �����̐��l�ݒ�
    B_IDLE_INIT,          //   ��?_�����ݒ�
    B_IDLE,               //   ��?
    B_WALK_INIT,          //   ����_�����ݒ�
    B_WALK,               //   ����
    B_RUN_INIT,           //   ����_�����ݒ�
    B_RUN,                //   ����

};

//------< �֐� >----------------------------------------------------------------
void player_init();
void player_deinit();
void player_update();
void player_render();

void player_act(OBJ2D* obj);     //�l��Ԃ̏���     
void player_box(OBJ2D* obj);     //����Ԃ̏���
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
