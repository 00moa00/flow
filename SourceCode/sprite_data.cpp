//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< �C���N���[�h >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< �f�[�^ >---------------------------------------------------------------

#if 5
//******************************************************************************
// TODO:05 �e�N�X�`���ǂݍ���
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���LLoadTexture�^�z����ɁA�w�i�ƒn�`�e�N�X�`���ǂݍ��ݗp�̃f�[�^���`����B

�q���g�j
    �w�i�e�N�X�`���̃p�X  L"./Data/Maps/back_chip.png"
    �n�`�e�N�X�`���̃p�X  L"./Data/Maps/terrain_chip.png"
    ���ꂼ��3�ڂ̃p�����[�^�� 273U �Ƃ��邱�ƁB

����j
    2D�摜���[�h�f�[�^��3�ڂ̃p�����[�^�́A�����ɕ`�悷��ő�C���X�^���X���ƂȂ�B
    �}�b�v�f�[�^�͉�21,�c13���̉摜����x�ɕ`�悷��iSpriteBatch�j���߁A21*13=273��
    �C���X�^���X���K�v�ƂȂ�Bunsigned�̂��߁A������U������273U�ƂȂ�B
*/
//******************************************************************************
#endif
//------------------------------------------------------------------------------
// 2D�摜���[�h�f�[�^
LoadTexture loadTexture[] = {
    {  TEXNO::MAP_BACK,     L"./Data/Maps/back_chip00.png",        static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) /*273U*/ },
    {  TEXNO::MAP_TERRAIN,  L"./Data/Maps/terrin_chip00.png",      static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) /*273U*/ },

    //L"./Data/Maps/terrain_chip.png"
    //L"./Data/Maps/back_chip.png"
     
    { -1, nullptr }	// �I���t���O
};

//------< �}�N�� >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // �摜�̐^�񒆂����S
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // �摜�̑��������S

//------< �v���C���[ >----------------------------------------------------------
//�����
SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 0, 48, 64);
SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 0, 48, 64);
SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 0, 48, 64);

//�E����
SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 1, 48, 64);
SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 1, 48, 64);
SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 1, 48, 64);

//������
SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 2, 48, 64);
SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 2, 48, 64);
SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 2, 48, 64);

//������
SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 3, 48, 64);
SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 3, 48, 64);
SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 3, 48, 64);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
