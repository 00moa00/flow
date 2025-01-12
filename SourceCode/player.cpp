#include "all.h"

int player_state;
int p_key;
OBJ2D player;
Sprite* sprHP;
Sprite* sprHPG;
Sprite* sprST;
Sprite* sprSTG;

extern int stageNo;
//extern OBJ2D item[ITEM_MAX];  //デバック用
 //Game Game::instance_;

struct PLAYER_SPR
{
	Sprite* sprPlayer;
	const wchar_t* filePath;
}
p_sprData[] = {
	{NULL,L"./Data/Images/player.png"},
	{NULL,L"./Data/Images/player_box.png"},
};


//playerの初期設定
void player_init()
{
	
	player_state = 0;
	p_key = 0;
	player.moveAlg = nullptr;
}


//playerの終了処理
void player_deinit()
{
	int dataNum = sizeof(p_sprData) / sizeof(PLAYER_SPR);
	for (int i = 0; i < dataNum; i++)
	{
		safe_delete(p_sprData[i].sprPlayer);
	}
	safe_delete(sprHP);
	safe_delete(sprHPG);
	safe_delete(sprST);
	safe_delete(sprSTG);


}


//playerの更新
void player_update()
{
	int dataNum = sizeof(p_sprData) / sizeof(PLAYER_SPR);

	switch (player_state)
	{
	case 0:
		//初期設定
		for (int i = 0; i < dataNum; i++)
		{
			p_sprData[i].sprPlayer = sprite_load(p_sprData[i].filePath);
		}

		sprHP = sprite_load(L"./Data/Images/hp_sotowaku.png");
		sprHPG = sprite_load(L"./Data/Images/hp_gage.png");
		sprST = sprite_load(L"./Data/Images/sutamina_sotowaku.png");
		sprSTG = sprite_load(L"./Data/Images/sutamina_gage.png");



		player_state++;
		/*fallthrough*/
	case 1:
		//パラメ???設定
		player = {};
		player.pos = { 100, 1200 }; 
		//player.scale        = { 0.5f , 0.5f };
		//player.texPos       = { 0.0f , 0.0f };
		//player.texSize      = { PLAYER_TEX_W,PLAYER_TEX_H };
		//player.pivot        = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
		player.jumpCount = 0;
		player.timer = 0;
		player.act = PLAYER_ACT::OBJ_INIT;
		player.hp = PLAYER_HP;
		player.sutamina = PLAYER_SUTAMINA;
		player.moveAlg = player_act;
		player.timer = 400;
		player.toumeiFlag = false;
		player.color.x = 1;
		player.color.y = 1;
		player.color.z = 1;
		player.color.w = 1;
		player_state++;

		/*fallthrough*/
	case 2:
		//通常時//
		//透明要処理
		if (player.toumeiFlag == true)
		{
			player.color.w = 1.0f;
			player.toumeiFlag = false;
		}
		
		(*player.moveAlg)(&player);
		areaCheck();

		//行動の方で書くと同じことを二回書かないといけないので
		if (player.sutamina < PLAYER_SUTAMINA)
			player.sutamina += PLAYER_SUTAMINA_SPEEDK;

		player.timer++;
		
		//GAMEOVER処理
		if (!(player.hp > 0)) 
		{
			player_state++;
			player.anime = 0;
			player.animeTimer = 0;
			player.texPos = { 0, 5 * player.texSize.y };

			player.speed.x = 0;

	    }
		break;
	case 3:
		player.timer = 0;

		player.anime = player.animeTimer / 10;
		if (player.anime > 3)
		{
			player.timer = 0;
				player.texSize.x = PLAYER_TEX_H;
				player.texSize.y = PLAYER_TEX_W+100;
				player.pivot.y = PLAYER_PIVOT_X+150;
			
			    player.anime = 4;

		}
		else if (player.anime <4) {
			player.texPos.x = player.anime * player.texSize.x;
			player.animeTimer++;
		}

	}


	player.timer++;
}

//playerの?画
void player_render()
{
	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
	VECTOR2 Spos = bg->getScrollPos();

	sprite_render(
		player.spr_data,
		player.pos.x - Spos.x,      player.pos.y - Spos.y,
		player.scale.x,    player.scale.y,
		player.texPos.x,   player.texPos.y,
		player.texSize.x,  player.texSize.y,
		player.pivot.x,    player.pivot.y,
		ToRadian(0),
		player.color.x,player.color.y,player.color.z,player.color.w
	);



	////hpゲ?ジ////
	primitive::rect(
		10, 10,
		player.hp-20, 20,
		0, 0,
		ToRadian(0),
		0.5, 1.0, 0.5, 0.6f
	);

	////ゲ?ジの下?き
	sprite_render(
		sprHP,
		0,0,
		1,1,
		0,0,
		500,40,
		0,0,
		ToRadian(0),
		1.0f,1.0f,1.0f,1.0f
		);
	primitive::rect(0, 0, 100, 40, 0, 0, ToRadian(0), 0, 0, 0, 0.4f);
	//ゲ?ジ

	////ス??ナゲ?ジ////
		//ゲ?ジ
	primitive::rect(
		10, 60,
		player.sutamina, 20,
		0, 0,
		ToRadian(0),
		1.0, 1.0, 0.2, 0.7f
	);

//ゲ?ジの下?き
	sprite_render(sprST,
		0, 50, 
		1, 1, 
		0, 0, 
		500,60,
        0,0,
		ToRadian(0), 
		1.0f, 1.0f, 1.0f, 1.0f);
	primitive::circle(player.pos.x - Spos.x, player.pos.y - Spos.y, 1.0f);

//	playerの当たり判定
	//primitive::rect(
	//	player.pos.x - Spos.x-player.pivot.x*0.5, player.pos.y - Spos.y-player.pivot.y*0.5,
	//	player.texSize.x * 0.5, player.texSize.y * 0.5,
	//	0, 0,
	//	ToRadian(0),
	//	1.0, 1.0, 0.5, 0.6f
	//);


}
void player_act(OBJ2D* obj)
{
	switch (obj->act)
	{
	case PLAYER_ACT::OBJ_INIT:
		obj->spr_data = p_sprData[0].sprPlayer;
		obj->scale = { 1.5f , 1.5f };
		obj->texPos = { 0.0f , 0.0f };
		obj->texSize = { PLAYER_TEX_W,PLAYER_TEX_H };
		obj->pivot = { PLAYER_PIVOT_X,PLAYER_PIVOT_Y };
		obj->collider = { PLAYER_SIZE_X , PLAYER_SIZE_Y };
		obj->act++;
		/*fallthrough*/

		//待?
	case PLAYER_ACT::IDLE_INIT:
		//アニメの初期設定
		obj->anime      = 0;
		obj->animeTimer = 0;
		player.texPos     = { 0,0 * player.texSize.y };

		obj->act++;
		/*fallthrough*/

	case PLAYER_ACT::IDLE:
		//この行動で動作
		player_moveY(obj);
		player_moveX(obj);

	    //アニメ処理
		obj->anime = obj->animeTimer / 5 % 4;
		obj->texPos.x = obj->anime * obj->texSize.x;
		++obj->animeTimer;

         
		//待?からジャンプ
		//--------------------------------------------------------------
	     if ((TRG(0) & PAD_TRG1) && obj->onGround)
		{
			obj->act = PLAYER_ACT::JUMP_START_INIT;
			break;
		}

		{
			const float speedX = fabsf(obj->speed.x);
			if (speedX < 0.125f)//アイドル状態へ
			{
				obj->act = PLAYER_ACT::IDLE_INIT;
				break;
			}
			if (speedX >= 4.5f)      // 走り状態へ
			{
				obj->act = PLAYER_ACT::RUN_INIT;
				break;
			}

		}
		//歩きへ
		if (fabsf(obj->speed.x) >= 0.125f)
		{
			obj->act = PLAYER_ACT::WALK_INIT;
			break;
		}
		break;
		//-----------------------------------------------------------

		//歩き行動
	case PLAYER_ACT::WALK_INIT:

		//アニメの初期設定
		//obj->anime = 0;
		//obj->animeTimer = 0;
		//obj->texPos = { 0,1 * obj->texSize.y };

		obj->act++;
		/*fallthough*/

	case PLAYER_ACT::WALK:

		/*-------- この行動での動作 --------*/
		player_moveY(obj);
		player_moveX(obj);

		///*-------     アニメ処理     -------*/
		//obj->anime = obj->animeTimer / 5 % 5;
		//obj->texPos.x = obj->anime * obj->texSize.x;
		//++obj->animeTimer;

		//ジャンプ遷移
		if ((TRG(0) & PAD_TRG1) && obj->onGround)
		{
			obj->act = PLAYER_ACT::JUMP_START_INIT;
			break;
		}
		{
			const float speedX = fabsf(obj->speed.x);

			if (speedX < 0.125f)  //アイドル状態へ
			{
				obj->act = PLAYER_ACT::IDLE_INIT;
				break;
			}
			if (speedX >= 4.5f)      // 走り状態へ
			{
				obj->act = PLAYER_ACT::RUN_INIT;
				break;
			}

		}
		break;
//--------------------------------
// 走り
//--------------------------------
	case PLAYER_ACT::RUN_INIT:

		/*-------- アニメの初期設定 --------*/
		//obj->anime = 0;
		//obj->animeTimer = 0;
		//obj->texPos = { 0, 2 * player.texSize.y };

		++obj->act;
		/*fallthrough*/

	case PLAYER_ACT::RUN:

		/*-------- この行動での動作 --------*/
		player_moveY(obj);
		player_moveX(obj);

		/*-------     アニメ処理     -------*/
		//obj->anime = obj->animeTimer / 4 % 6;
		//obj->texPos.x = obj->anime * obj->texSize.x;
		//++obj->animeTimer;

		/*--------    行動の遷移    --------*/

			if ((TRG(0) & PAD_TRG1) && obj->onGround)
			{
				obj->act = PLAYER_ACT::JUMP_START_INIT;
				break;
			}
			if (fabsf(obj->speed.x) < 4.5f)      // 歩き状態へ
			{
				obj->act = PLAYER_ACT::WALK_INIT;
				break;
			}

			break;

	case PLAYER_ACT::JUMP_START_INIT:

		//TODO_09
		obj->anime = 0;
		obj->animeTimer = 0;
		obj->jumpTimer = 16;
		player.texPos = { 0, 3 * player.texSize.y };
		obj->act++;
		/*fallthrough*/

	case PLAYER_ACT::JUMP_START:

		/*-------- この行動での動作 --------*/

		player_moveY(obj);
		player_moveX(obj);
		obj->setSpeedY(-JUMP_H);

		/*-------     アニメ処理     -------*/

		obj->anime = obj->animeTimer / 2;
		if (obj->anime > 3)
		{
			obj->anime = 3;
			obj->act = PLAYER_ACT::JUMP_KEEP_INIT;
			break;
		}
		obj->texPos.x = obj->anime * obj->texSize.x;
		obj->animeTimer++;
		/*--------    行動の遷移    --------*/
		
		

//--------------------------------
// ジャンプ中
//--------------------------------
	case PLAYER_ACT::JUMP_KEEP_INIT:
		obj->anime = 0;
		obj->animeTimer = 0;
		player.texPos = { 0,3 * player.texSize.y };
		obj->act++;

		/*fallthrough*/

	case PLAYER_ACT::JUMP_KEEP:
		player_moveY(obj);
		player_moveX(obj);
		if (obj->jumpTimer > 0)
		{

			if (STATE(0) & PAD_TRG1)
			{   // PAD_TRG1が押されている場合
				obj->setSpeedY(-JUMP_H);
				obj->addJumpTimer(-1);
			}
			else
			{   // PAD_TRG1が押されていない場合
				obj->setJumpTimer(0);
			}
			
		}
		


		//着地
	if (obj->onGround)
	{
		obj->act = PLAYER_ACT::JUMP_END_INIT;
	}
	break;

	//--------------------------------
	// ジャンプ着地
	//--------------------------------
    case PLAYER_ACT::JUMP_END_INIT:

		obj->anime = 0;
		obj->animeTimer = 0;
		player.texPos = { 0, 4 * player.texSize.y };

		obj->speed.x = 0;

		++obj->act;
		/*fallthrough*/

	case PLAYER_ACT::JUMP_END:

		/*-------- この行動での動作 --------*/
		// なし

		/*-------     アニメ処理     -------*/

		player.anime = player.animeTimer / 7;
		if (player.anime > 2)
		{
			player.anime = 2;
		}
		player.texPos.x = player.anime * player.texSize.x;
		player.animeTimer++;
		/*--------    行動の遷移    --------*/
		// なし
		if (player.animeTimer == 14)
		obj->act = PLAYER_ACT::IDLE_INIT;
		break;
	
}
	//モ?ド切替
	if (GetAsyncKeyState('C') & 1)
	{
		obj->moveAlg = player_box;
		obj->act = 0;
		obj->timer = PLAYER_TOUMEI;
	}
}

void player_box(OBJ2D* obj)
{
	switch (obj->act)
	{
	case PLAYERBOX_ACT::B_OBJ_INIT:
		obj->spr_data = p_sprData[1].sprPlayer;
		obj->scale = { 1.5f , 1.5f };
		obj->texPos = { 0.0f , 0.0f };
		obj->texSize = { PLAYERBOX_TEX_W,PLAYERBOX_TEX_H };
		obj->pivot = { PLAYERBOX_PIVOT_X,PLAYERBOX_PIVOT_Y };
		obj->collider = { PLAYERBOX_SIZE_X , PLAYERBOX_SIZE_Y };
		obj->act++;
		/*fallthrough*/

	case PLAYERBOX_ACT::B_IDLE_INIT:
		//アニメの初期設定
		obj->anime = 0;
		obj->animeTimer = 0;
		//player.texPos     = { 0,0 * player.texSize.y };

		obj->act++;
		/*fallthrough*/

	case PLAYERBOX_ACT::B_IDLE:
		//この行動で動作
		playerbox_moveY(obj);
		playerbox_moveX(obj);


		break;


	}
	

	//モ?ド切替
	if (GetAsyncKeyState('X') & 1)
	{
		obj->moveAlg = player_act;
		obj->act = 0;
	}
}

//--------------------------------------
//  プレイヤ?のY方向の移動
//--------------------------------------
void player_moveY(OBJ2D* obj)
{
	// Y方向の移動
	obj->addSpeedY(GRAVITY);

	//下記のプログラ?を?造体仕様に書き換える
	//Transform* transform = obj->transform();

	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
	//ActorComponent* actorComp = obj->actorComponent();   //jumptimerとjumpflagを管理しているだけなのでPlayerで代用できると思います
	//Collider* collider = obj->collider();   //Colliderはplayerと壁が接触した時にplayerがめり込まないよう隙間を取る為の数値
	                                          //画像サイズを元に計算して求める今回は(25, 300-16)

	//// Y方向の抗力の計算  //calcResistance関数はまだ実装してないので一旦コメントしておく
    //player.addSpeedY(bg->calcResistance(obj, transform->speed().y));

	//// 最大速度制限
	obj->setSpeedY(clamp(obj->speed.y, -SPEED_Y_MAX, SPEED_Y_MAX));

	//// 位置更新
	float oldY = obj->pos.y;           // 移動前の位置を保持
	obj->addPositionY(obj->speed.y);
	float deltaY = obj->pos.y - oldY;  // 移動後の位置から移動前の位置を引く

	//actorComp->setOnGround(false);
	obj->onGround = false;

	//// 下方向のあたり判定
	if (deltaY > 0)
	{
		if (bg->isFloor(obj->pos.x, obj->pos.y, obj->collider.x))
		{
			// 床にあたっていたら
			bg->mapHoseiDown(obj);    //  下方向の補正処理
			obj->onGround = true;   // 地面フラグ
		}
	}

	// 上方向のあたり判定
	if (deltaY < 0)
	{                                               // PLAYER_SIZE_Y, PLAYER_SIZE_X
		if (bg->isCeiling(obj->pos.x, obj->pos.y - obj->collider.y, obj->collider.x))
		{
			// 天井にあたっていたら
			bg->mapHoseiUp(obj);
			obj->jumpCount = 0;
		}
	}


}

void playerbox_moveX(OBJ2D* obj)
{
	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();

	//// 左右入力の取り出し
	using namespace input;
	float dashu = 0;
	if (STATE(0) & PAD_TRG1 && player.sutamina > 0)
	{
		player.sutamina -= PLAYER_SUTAMINA_SPEEDS;
		 dashu = PLAYER_SPEED_DASH;
	}
	switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
	{
	case PAD_LEFT:  // 左だけが押されている場合
		obj->addSpeedX(-(PLAYER_ACCEL_X + dashu) ) ;
		
		break;
	case PAD_RIGHT: // 右だけが押されている場合
		obj->addSpeedX(PLAYER_ACCEL_X + dashu);
		
		break;
	default:        // どちらも押されていないか相殺されている場合
		if (obj->speed.x > 0)
		{
			obj->addSpeedX(-PLAYER_ACCEL_X / 2);
			if (obj->speed.x < 0) obj->setSpeedX(0.0f);
		}
		if (obj->speed.x < 0)
		{
			obj->addSpeedX(PLAYER_ACCEL_X / 2);
			if (obj->speed.x > 0) obj->setSpeedX(0.0f);
		}
		break;
	}
		//// X方向の抗力の計算
	//transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

	//// 最大速度?ェック
	if (obj->speed.x > PLAYER_SPEED_X_MAX + dashu)
		obj->setSpeedX(PLAYER_SPEED_X_MAX + dashu);
	if (obj->speed.x < -PLAYER_SPEED_X_MAX - dashu)
		obj->setSpeedX(-PLAYER_SPEED_X_MAX - dashu);

	// X方向移動
	float oldX = obj->pos.x;
	obj->addPositionX(obj->speed.x );
	float deltaX = obj->pos.x - oldX;

	bool kabeFlag = false;  // 壁フラグをfalseにしておく（プレイヤ?では使用しない）

	// 右方向あたり判定
	if (deltaX > 0)
	{
		if (bg->isWall(obj->pos.x + obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiRight(obj);     // 右方向の補正処理
			kabeFlag = true;                    // 壁フラグをtrueにしておく
		}
	}

	// 左方向あたり判定
	if (deltaX < 0)
	{
		if (bg->isWall(obj->pos.x - obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiLeft(obj);
			kabeFlag = true;
		}
	}
}

void playerbox_moveY(OBJ2D* obj)
{
	// Y方向の移動
	obj->addSpeedY(GRAVITY);

	//下記のプログラ?を?造体仕様に書き換える
	//Transform* transform = obj->transform();
	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
	//ActorComponent* actorComp = obj->actorComponent();   //jumptimerとjumpflagを管理しているだけなのでPlayerで代用できると思います
	//Collider* collider = obj->collider();   //Colliderはplayerと壁が接触した時にplayerがめり込まないよう隙間を取る為の数値
											  //画像サイズを元に計算して求める今回は(25, 300-16)

	//// Y方向の抗力の計算  //calcResistance関数はまだ実装してないので一旦コメントしておく
	//player.addSpeedY(bg->calcResistance(obj, transform->speed().y));

	//// 最大速度制限
	obj->setSpeedY(clamp(obj->speed.y, -SPEED_Y_MAX, SPEED_Y_MAX));

	//// 位置更新
	float oldY = obj->pos.y;           // 移動前の位置を保持
	obj->addPositionY(obj->speed.y);
	float deltaY = obj->pos.y - oldY;  // 移動後の位置から移動前の位置を引く

	//actorComp->setOnGround(false);
	obj->onGround = false;

	//// 下方向のあたり判定
	if (deltaY > 0)
	{
		if (bg->isFloor(obj->pos.x, obj->pos.y, obj->collider.x))
		{
			// 床にあたっていたら
			bg->mapHoseiDown(obj);    //  下方向の補正処理
			obj->onGround = true;   // 地面フラグ
		}
	}

	//// 上方向のあたり判定
	if (deltaY < 0)
	{
		if (bg->isCeiling(obj->pos.x, obj->pos.y - obj->collider.y, obj->collider.x))
		{
			// 天井にあたっていたら
			bg->mapHoseiUp(obj);
			obj->jumpCount = 0;
		}
	}

}

//--------------------------------------
//  プレイヤ?のX方向の移動
//--------------------------------------
void player_moveX(OBJ2D* obj)
{

	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();

	//// 左右入力の取り出し
	using namespace input;
	switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
	{
	case PAD_LEFT:  // 左だけが押されている場合
		obj->addSpeedX(-PLAYER_ACCEL_X);
		obj->scale.x = -0.5f;
		break;
	case PAD_RIGHT: // 右だけが押されている場合
		obj->addSpeedX(PLAYER_ACCEL_X);
		obj->scale.x = 0.5f;
		break;
	default:        // どちらも押されていないか相殺されている場合
		if (obj->speed.x > 0)
		{
			obj->addSpeedX(-PLAYER_ACCEL_X / 2);
			if (obj->speed.x < 0) obj->setSpeedX(0.0f);
		}
		if (obj->speed.x < 0)
		{
			obj->addSpeedX(PLAYER_ACCEL_X / 2);
			if (obj->speed.x > 0) obj->setSpeedX(0.0f);
		}
		break;
	}
	//透明化用
	if ( (GetAsyncKeyState('V') & 1) && player.sutamina ==PLAYER_SUTAMINA) //PAD_TRG2 = X
	{
		player.sutamina = 0;
		player.timer = 0;
	}
	//// X方向の抗力の計算
	//transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

	//// 最大速度?ェック
	if (obj->speed.x > PLAYER_SPEED_X_MAX)
		obj->setSpeedX(PLAYER_SPEED_X_MAX);
	if (obj->speed.x < -PLAYER_SPEED_X_MAX)
		obj->setSpeedX(-PLAYER_SPEED_X_MAX);

	// X方向移動
	float oldX = obj->pos.x;
	obj->addPositionX(obj->speed.x);
	float deltaX = obj->pos.x - oldX;

	bool kabeFlag = false;  // 壁フラグをfalseにしておく（プレイヤ?では使用しない）

	// 右方向あたり判定
	if (deltaX > 0)
	{
		if (bg->isWall(obj->pos.x + obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiRight(obj);     // 右方向の補正処理
			kabeFlag = true;                    // 壁フラグをtrueにしておく
		}
	}

	// 左方向あたり判定
	if (deltaX < 0)
	{
		if (bg->isWall(obj->pos.x - obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiLeft(obj);
			kabeFlag = true;
		}
	}

}


void player_damage()
{
	player.hp -= 55;
	if (player.hp <= 0)
	{
		player.hp = 0;
		player.state = 0;
	}

}

void player_color()
{
	player.color.x = 1.0f;
	player.color.y = 1.0f;
	player.color.z = 1.0f;
	player.color.w = 1.0f;

}

bool player_isAlive()
{
	if (player.hp <=0)return false;
	return  true;
}

int player_getkey()
{
	return p_key;
}


void areaCheck()
{

	if (player.pos.x < 0 + player.collider.x)
	{
		player.setPositionX(player.collider.x);
		player.setSpeedX(0.0f);
	}
	if (player.pos.x > BG::WIDTH - player.collider.x)
	{
		player.setPositionX(BG::WIDTH - player.collider.x);
		player.setSpeedX(0.0f);
	}
}


void player_setkey(int diff)
{
	switch (diff)
	{
	case red:
		p_key = 0xff0000;
		break;

	case blue:
		p_key = 0x00ff00;
		break;

	case green:
		p_key = 0x0000ff;
		break;
	}
}

void player_setpos(VECTOR2 pos)
{
	player.pos = pos;
}

VECTOR2 player_pos()
{
	return player.pos;
}