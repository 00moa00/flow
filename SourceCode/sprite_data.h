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
// TODO:04 テクスチャ用ラベルの定義
//------------------------------------------------------------------------------
/*
課題）
    背景用のテクスチャを識別するラベルを定義する。
    下記のTEXNO内に、MAP_BACKとMAP_TERRAINを追加せよ。
*/
//******************************************************************************
#endif
// ラベル定義
enum TEXNO
{
    // ゲーム
    PLAYER,
    MAP_BACK,
    MAP_TERRAIN
};

extern GameLib::LoadTexture loadTexture[];

//------< プレイヤー >-----------------------------------------------------------
//上歩き
extern GameLib::SpriteData sprPlayer_Up0;
extern GameLib::SpriteData sprPlayer_Up1;
extern GameLib::SpriteData sprPlayer_Up2;

//右歩き
extern GameLib::SpriteData sprPlayer_Right0;
extern GameLib::SpriteData sprPlayer_Right1;
extern GameLib::SpriteData sprPlayer_Right2;

//下歩き
extern GameLib::SpriteData sprPlayer_Down0;
extern GameLib::SpriteData sprPlayer_Down1;
extern GameLib::SpriteData sprPlayer_Down2;

//左歩き
extern GameLib::SpriteData sprPlayer_Left0;
extern GameLib::SpriteData sprPlayer_Left1;
extern GameLib::SpriteData sprPlayer_Left2;

//******************************************************************************
#endif // !INCLUDED_SPRITE_DATA
