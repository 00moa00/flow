#ifndef INCLUDED_COMMON
#define	INCLUDED_COMMON

//******************************************************************************
//
//
//      common
//
//
//******************************************************************************

//------< インクルード >---------------------------------------------------------
#include <DirectXMath.h>

//define 

#define SCREEN_W   1280
#define SCREEN_H    720
//------< 関数 >----------------------------------------------------------------

static float(*const ToRadian)(float) = DirectX::XMConvertToRadians;  // 角度をラジアンに
static float(*const ToDegree)(float) = DirectX::XMConvertToDegrees;  // ラジアンを角度に


enum stage
{
    STAGE_INIT = 0,
    STAGE0_INIT,
    STAGE0,
    STAGE1_INIT,
    STAGE1,
    STAGE2_INIT,
    STAGE2,
    STAGE = 10,
    OVERE,
    CLEAR,
};


#endif // !INCLUDED_COMMON
