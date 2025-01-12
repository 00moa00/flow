#include "all.h"

extern OBJ2D player;
extern OBJ2D enemy[ENEMY_MAX];
extern OBJ2D item[ITEM_MAX];
extern bool kabeFlag;
extern int stageNo;

int juge_timer;
bool juge_muteki;

void juge_init()
{
    juge_timer = 0;
    juge_muteki = false;
}

void juge_deinit()
{
}

void juge_update()
{
    BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
    VECTOR2 Spos = bg->getScrollPos();
    if (player.moveAlg == player_act)
    {
        for (int i = 0; i < ENEMY_MAX; i++)
        {
            if (!(player.moveAlg == player_box))
            {
                if (player.timer < PLAYER_TOUMEI)
                {
                    player.color.w = 0.6f;
                    player.toumeiFlag = true;
                }
            }

            if (enemy[i].moveAlg != nullptr)
            {
                if (enemy[i].moveAlg != movehasira)
                {
                    if (hanteiR(player.pos.x - Spos.x - player.pivot.x * 0.5, enemy[i].pos.x - Spos.x - enemy[i].pivot.x * 0.5,
                        player.texSize.x * 0.5, enemy[i].texSize.x * 0.5,
                        player.pos.y - Spos.y - player.pivot.y * 0.5, enemy[i].pos.y - Spos.y - enemy[i].pivot.y * 0.5,
                        player.texSize.y * 0.5, enemy[i].texSize.y * 0.5))
                    {

                            if (!juge_muteki)  //ダメージ発生時用の無敵時間用if
                            {
                                juge_muteki = true;
                                player_damage();

                                juge_timer = 0;
                            }

                        if (juge_timer > 60) //ダメージ発生時用の無敵時間用if
                        {
                            juge_muteki = false;
                        }

                    }
                }
                else
                {
                    //柱限定の当たり判定
                    if (hanteiR(player.pos.x - Spos.x - player.pivot.x*0.5, enemy[i].pos.x - Spos.x ,
                        player.texSize.x*0.5, enemy[i].texSize.x-enemy[i].pivot.x*2,
                        player.pos.y - Spos.y - player.pivot.y*0.5, /*enemy[i].pos.y - Spos.y - enemy[i].pivot.y *0.5f*/0,
                        player.texSize.y*0.5, /*enemy[i].texSize.y*/ enemy[i].pos.y - Spos.y))
                    {
                        (player.pos.x <= enemy[i].pos.x) ? player.pos.x = player.pos.x - DAMAGE_OFFSET : player.pos.x = player.pos.x + DAMAGE_OFFSET;
                    }

                }
            }

        }

    }
    //
    else if (player.moveAlg == player_box)
    {
        

        for (int i = 0; i < ENEMY_MAX; i++)
        {
            float oldX = enemy[i].pos.x;
            float deltaX = enemy[i].pos.x - oldX;
            bool judgeFlag = false;
            if (enemy[i].moveAlg != nullptr)
            {
                if (enemy[i].moveAlg != moveBoss && enemy[i].moveAlg != movehasira)
                {
                    if (hanteiR(player.pos.x - Spos.x - player.pivot.x, enemy[i].pos.x - Spos.x - enemy[i].pivot.x * 0.5,
                        player.texSize.x, enemy[i].texSize.x * 0.5,
                        player.pos.y - Spos.y - player.pivot.y, enemy[i].pos.y - Spos.y - enemy[i].pivot.y * 0.5,
                        player.texSize.y, enemy[i].texSize.y * 0.5))
                    {

                        (player.pos.x <= enemy[i].pos.x) ? enemy[i].pos.x += DAMAGE_OFFSET : enemy[i].pos.x -= DAMAGE_OFFSET;
                        if ((enemy[i].scale.x > 0 && player.speed.x >= 0) || (enemy[i].scale.x < 0 && player.speed.x <= 0)) enemy[i].scale.x *= -1;
                        judgeFlag = true;


                    }

                }
                    

                else if (enemy[i].moveAlg == movehasira)
                {    
                    //柱限定の当たり判定
                    if (hanteiR(player.pos.x - Spos.x - player.pivot.x, enemy[i].pos.x - Spos.x - enemy[i].pivot.x * 0.5,
                        player.texSize.x, enemy[i].texSize.x * 0.5,
                        player.pos.y - Spos.y - player.pivot.y, 0,
                        player.texSize.y, enemy[i].pos.y - Spos.y))
                    {
                        (player.pos.x <= enemy[i].pos.x) ? player.pos.x -= DAMAGE_OFFSET : player.pos.x += DAMAGE_OFFSET;
                        if ((player.speed.x > PLAYER_SPEED_X_MAX || player.speed.x < -PLAYER_SPEED_X_MAX) && juge_timer > 30)  //ダメージ発生時用の無敵時間用if
                        {
                                damage_hasira(&enemy[i]);

                                juge_timer = 0;

                        }
                    }

                }




                    
                }
                //敵を倒す時の処理
                if (judgeFlag  == true && enemy[i].kabeFlag == true)
                {
                    {
                        enemy[i] = {};
                    }
                }
            }
        }
    
    //
    
    //アイテムとプレイヤーの処理
    for (int i = 0; i < ITEM_MAX; i++)
    {

        if (item[i].moveAlg == item_card)
        {

            if (item[i].act == red)
            {
                if ((player_getkey() >> 16) & 0xff)
                {
                    item[i].moveAlg = nullptr;
                    continue;
                }
            }
            if (item[i].act == blue)
            {
                if ((player_getkey() >> 8) & 0xff)
                {
                    item[i].moveAlg = nullptr;
                    continue;
                }
            }
            if (item[i].act == green)
            {
                if (player_getkey() & 0xff)
                {
                    item[i].moveAlg = nullptr;
                    continue;
                }
            }
        }

        if (hanteiR(player.pos.x - Spos.x - player.pivot.x * 0.5, item[i].pos.x - Spos.x - item[i].pivot.x,
            player.texSize.x * 0.5, item[i].texSize.x,
            player.pos.y - Spos.y - player.pivot.y * 0.5, item[i].pos.y - Spos.y - item[i].pivot.y,
            player.texSize.y * 0.5, item[i].texSize.y))
        {

            if (item[i].moveAlg == item_door)
            {
                //ここでプレイヤーも保持しているカードキーと比較する
                if (door_check(&item[i], player_getkey())) //合致していたらtrue
                {
                    if (TRG(0) & PAD_START)
                    door_setflag(&item[i], true);
                }

                continue;

            }

            if (item[i].moveAlg != nullptr)
            {
                player_setkey(item[i].act);
                item[i].moveAlg = nullptr;
            }

        }

    }
    juge_timer++;

}

void juge_draw()
{
}

bool hanteiR(float x1, float x2, float gx1, float gx2, float y1, float y2, float gy1, float gy2)
{
    float left1, right1, top1, bottom1;
    float left2, right2, top2, bottom2;

    //1つ目の四角形のセット
    left1 = x1;
    right1 = x1 + gx1;
    top1 = y1;
    bottom1 = y1 + gy1;

    //2つ目の四角形のセット
    left2 = x2;
    right2 = x2 + gx2;
    top2 = y2;
    bottom2 = y2 + gy2;

    //座標や大きさは予めセットされているものとする
    if ((right1 > left2) && (left1 < right2) && (top1 < bottom2) && (bottom1 > top2))
    {
        return true;
    }
    else
        return false;
}

