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
    int             timer;      // �^�C�}�[

      //�ǉ�
    bool xFlip_ = false;
    bool xFlip() { return xFlip_; }  //false �E  true ��
    void setXFlip(bool f) { xFlip_ = f; }
    void flip() { xFlip_ = !xFlip_; }

    bool onGround;
    char pad[3];
    VECTOR2         pos;        // �ʒu
    VECTOR2         scale;      // �X�P�[��
    VECTOR2         texPos;     // �摜�ʒu
    VECTOR2         texSize;    // �摜�T�C�Y
    VECTOR2         pivot;      // ��_
    VECTOR4         color;      // �F
    VECTOR2         collider;   // �L�����N�^�[�p�����蔻��ϐ�

    VECTOR2         speed;      // ���x
    int             jumpCount;  // �c��W�����v��
    int             jumpTimer;  //�W�����v�^�C�}�[
    int             act;        // �v���C���[�̍s���J�ڗp
    int             anime;      // �A�j�������݉��R�}�ڂ�
    int             animeTimer; // �A�j���p�^�C�}�[
    int             hp;         //�̗�
    int             sutamina;   //�X�^�~�i
    bool            kabeFlag;   //�ǃt���O
    bool            toumeiFlag;     //�����t���O

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

