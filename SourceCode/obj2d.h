#pragma once
struct OBJ2D
{
    
    typedef void (*MOVE) (OBJ2D*);
    MOVE                moveAlg;
    GameLib::Sprite* spr_data;
    //
    GameLib::fRECT hitBox_;
    GameLib::fRECT attackBox_;
    //
    VECTOR2             size;
    
    int             state;
    int             timer;      // タイマー

      //追加
    bool xFlip_ = false;
    bool xFlip() { return xFlip_; }  //false 右  true 左
    void setXFlip(bool f) { xFlip_ = f; }
    void flip() { xFlip_ = !xFlip_; }

    bool onGround;
    char pad[3];
    VECTOR2         pos;        // 位置
    VECTOR2         scale;      // スケール
    VECTOR2         texPos;     // 画像位置
    VECTOR2         texSize;    // 画像サイズ
    VECTOR2         pivot;      // 基準点
    VECTOR4         color;      // 色
    VECTOR2         collider;   // キャラクター用当たり判定変数

    VECTOR2         speed;      // 速度
    int             jumpCount;  // 残りジャンプ回数
    int             jumpTimer;  //ジャンプタイマー
    int             act;        // プレイヤーの行動遷移用
    int             anime;      // アニメが現在何コマ目か
    int             animeTimer; // アニメ用タイマー
    int             hp;         //体力
    int             sutamina;   //スタミナ
    bool            kabeFlag;   //壁フラグ
    bool            toumeiFlag;     //透明フラグ

void addPositionX(float x) { pos.x += x; }
void addPositionY(float y) { pos.y += y; }

void setPositionX(float x) { pos.x = x; }
void setSpeed(const VECTOR2& s) { speed = s; }
void setSpeedX(float x) { speed.x = x; }
void setSpeedY(float y) { speed.y = y; }
void addSpeedX(float x) { speed.x += x; }
void addSpeedY(float y) { speed.y += y; }
void addJumpTimer(int a) { jumpTimer += a; }
void setJumpTimer(int a) { jumpTimer = a; }

};

OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::MOVE moveAlg, VECTOR2 pos);

