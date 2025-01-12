//******************************************************************************
//
//
//		SPRITE_DATA
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include "all.h"

//------< using >---------------------------------------------------------------
using namespace GameLib;

//------< データ >---------------------------------------------------------------

#if 5
//******************************************************************************
// TODO:05 テクスチャ読み込み
//------------------------------------------------------------------------------
/*
課題）
    下記LoadTexture型配列内に、背景と地形テクスチャ読み込み用のデータを定義せよ。

ヒント）
    背景テクスチャのパス  L"./Data/Maps/back_chip.png"
    地形テクスチャのパス  L"./Data/Maps/terrain_chip.png"
    それぞれ3つ目のパラメータは 273U とすること。

解説）
    2D画像ロードデータの3つ目のパラメータは、同時に描画する最大インスタンス数となる。
    マップデータは横21,縦13個分の画像を一度に描画する（SpriteBatch）ため、21*13=273個の
    インスタンスが必要となる。unsignedのため、末尾にUをつけて273Uとなる。
*/
//******************************************************************************
#endif
//------------------------------------------------------------------------------
// 2D画像ロードデータ
LoadTexture loadTexture[] = {
    {  TEXNO::MAP_BACK,     L"./Data/Maps/back_chip00.png",        static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) /*273U*/ },
    {  TEXNO::MAP_TERRAIN,  L"./Data/Maps/terrin_chip00.png",      static_cast<UINT>(BG::LOOP_X * BG::LOOP_Y) /*273U*/ },

    //L"./Data/Maps/terrain_chip.png"
    //L"./Data/Maps/back_chip.png"
     
    { -1, nullptr }	// 終了フラグ
};

//------< マクロ >--------------------------------------------------------------
#define SPRITE_CENTER(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)/2 }  // 画像の真ん中が中心
#define SPRITE_BOTTOM(texno,left,top,width,height)	{ (texno),(left),(top),(width),(height),(width)/2,(height)   }  // 画像の足元が中心

//------< プレイヤー >----------------------------------------------------------
//上歩き
SpriteData sprPlayer_Up0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 0, 48, 64);
SpriteData sprPlayer_Up1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 0, 48, 64);
SpriteData sprPlayer_Up2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 0, 48, 64);

//右歩き
SpriteData sprPlayer_Right0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 1, 48, 64);
SpriteData sprPlayer_Right1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 1, 48, 64);
SpriteData sprPlayer_Right2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 1, 48, 64);

//下歩き
SpriteData sprPlayer_Down0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 2, 48, 64);
SpriteData sprPlayer_Down1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 2, 48, 64);
SpriteData sprPlayer_Down2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 2, 48, 64);

//左歩き
SpriteData sprPlayer_Left0 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 0, 64 * 3, 48, 64);
SpriteData sprPlayer_Left1 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 1, 64 * 3, 48, 64);
SpriteData sprPlayer_Left2 = SPRITE_BOTTOM(TEXNO::PLAYER, 48 * 2, 64 * 3, 48, 64);

//------------------------------------------------------------------------------
#undef SPRITE_CENTER
#undef SPRITE_BOTTOM

//******************************************************************************
