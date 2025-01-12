#ifndef INCLUDED_SPRITE_DATA
#define	INCLUDED_SPRITE_DATA
//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

#include "../GameLib/texture.h"

#if 4
//******************************************************************************
// TODO:04 �e�N�X�`���p���x���̒�`
//------------------------------------------------------------------------------
/*
�ۑ�j
    �w�i�p�̃e�N�X�`�������ʂ��郉�x�����`����B
    ���L��TEXNO���ɁAMAP_BACK��MAP_TERRAIN��ǉ�����B
*/
//******************************************************************************
#endif
// ���x����`
enum TEXNO
{
    // �Q�[��
    PLAYER,
    MAP_BACK,
    MAP_TERRAIN
};

extern GameLib::LoadTexture loadTexture[];

//------< �v���C���[ >-----------------------------------------------------------
//�����
extern GameLib::SpriteData sprPlayer_Up0;
extern GameLib::SpriteData sprPlayer_Up1;
extern GameLib::SpriteData sprPlayer_Up2;

//�E����
extern GameLib::SpriteData sprPlayer_Right0;
extern GameLib::SpriteData sprPlayer_Right1;
extern GameLib::SpriteData sprPlayer_Right2;

//������
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//������
extern GameLib::SpriteData sprPlayer_Left0;
extern GameLib::SpriteData sprPlayer_Left1;
extern GameLib::SpriteData sprPlayer_Left2;

//******************************************************************************
#endif // !INCLUDED_SPRITE_DATA