#include "all.h"

int player_state;
int p_key;
OBJ2D player;
Sprite* sprHP;
Sprite* sprHPG;
Sprite* sprST;
Sprite* sprSTG;

extern int stageNo;
//extern OBJ2D item[ITEM_MAX];  //�f�o�b�N�p
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


//player�̏����ݒ�
void player_init()
{
	
	player_state = 0;
	p_key = 0;
	player.moveAlg = nullptr;
}


//player�̏I������
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


//player�̍X�V
void player_update()
{
	int dataNum = sizeof(p_sprData) / sizeof(PLAYER_SPR);

	switch (player_state)
	{
	case 0:
		//�����ݒ�
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
		//�p����???�ݒ�
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
		//�ʏ펞//
		//�����v����
		if (player.toumeiFlag == true)
		{
			player.color.w = 1.0f;
			player.toumeiFlag = false;
		}
		
		(*player.moveAlg)(&player);
		areaCheck();

		//�s���̕��ŏ����Ɠ������Ƃ��񏑂��Ȃ��Ƃ����Ȃ��̂�
		if (player.sutamina < PLAYER_SUTAMINA)
			player.sutamina += PLAYER_SUTAMINA_SPEEDK;

		player.timer++;
		
		//GAMEOVER����
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

//player��?��
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



	////hp�Q?�W////
	primitive::rect(
		10, 10,
		player.hp-20, 20,
		0, 0,
		ToRadian(0),
		0.5, 1.0, 0.5, 0.6f
	);

	////�Q?�W�̉�?��
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
	//�Q?�W

	////�X??�i�Q?�W////
		//�Q?�W
	primitive::rect(
		10, 60,
		player.sutamina, 20,
		0, 0,
		ToRadian(0),
		1.0, 1.0, 0.2, 0.7f
	);

//�Q?�W�̉�?��
	sprite_render(sprST,
		0, 50, 
		1, 1, 
		0, 0, 
		500,60,
        0,0,
		ToRadian(0), 
		1.0f, 1.0f, 1.0f, 1.0f);
	primitive::circle(player.pos.x - Spos.x, player.pos.y - Spos.y, 1.0f);

//	player�̓����蔻��
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

		//��?
	case PLAYER_ACT::IDLE_INIT:
		//�A�j���̏����ݒ�
		obj->anime      = 0;
		obj->animeTimer = 0;
		player.texPos     = { 0,0 * player.texSize.y };

		obj->act++;
		/*fallthrough*/

	case PLAYER_ACT::IDLE:
		//���̍s���œ���
		player_moveY(obj);
		player_moveX(obj);

	    //�A�j������
		obj->anime = obj->animeTimer / 5 % 4;
		obj->texPos.x = obj->anime * obj->texSize.x;
		++obj->animeTimer;

         
		//��?����W�����v
		//--------------------------------------------------------------
	     if ((TRG(0) & PAD_TRG1) && obj->onGround)
		{
			obj->act = PLAYER_ACT::JUMP_START_INIT;
			break;
		}

		{
			const float speedX = fabsf(obj->speed.x);
			if (speedX < 0.125f)//�A�C�h����Ԃ�
			{
				obj->act = PLAYER_ACT::IDLE_INIT;
				break;
			}
			if (speedX >= 4.5f)      // �����Ԃ�
			{
				obj->act = PLAYER_ACT::RUN_INIT;
				break;
			}

		}
		//������
		if (fabsf(obj->speed.x) >= 0.125f)
		{
			obj->act = PLAYER_ACT::WALK_INIT;
			break;
		}
		break;
		//-----------------------------------------------------------

		//�����s��
	case PLAYER_ACT::WALK_INIT:

		//�A�j���̏����ݒ�
		//obj->anime = 0;
		//obj->animeTimer = 0;
		//obj->texPos = { 0,1 * obj->texSize.y };

		obj->act++;
		/*fallthough*/

	case PLAYER_ACT::WALK:

		/*-------- ���̍s���ł̓��� --------*/
		player_moveY(obj);
		player_moveX(obj);

		///*-------     �A�j������     -------*/
		//obj->anime = obj->animeTimer / 5 % 5;
		//obj->texPos.x = obj->anime * obj->texSize.x;
		//++obj->animeTimer;

		//�W�����v�J��
		if ((TRG(0) & PAD_TRG1) && obj->onGround)
		{
			obj->act = PLAYER_ACT::JUMP_START_INIT;
			break;
		}
		{
			const float speedX = fabsf(obj->speed.x);

			if (speedX < 0.125f)  //�A�C�h����Ԃ�
			{
				obj->act = PLAYER_ACT::IDLE_INIT;
				break;
			}
			if (speedX >= 4.5f)      // �����Ԃ�
			{
				obj->act = PLAYER_ACT::RUN_INIT;
				break;
			}

		}
		break;
//--------------------------------
// ����
//--------------------------------
	case PLAYER_ACT::RUN_INIT:

		/*-------- �A�j���̏����ݒ� --------*/
		//obj->anime = 0;
		//obj->animeTimer = 0;
		//obj->texPos = { 0, 2 * player.texSize.y };

		++obj->act;
		/*fallthrough*/

	case PLAYER_ACT::RUN:

		/*-------- ���̍s���ł̓��� --------*/
		player_moveY(obj);
		player_moveX(obj);

		/*-------     �A�j������     -------*/
		//obj->anime = obj->animeTimer / 4 % 6;
		//obj->texPos.x = obj->anime * obj->texSize.x;
		//++obj->animeTimer;

		/*--------    �s���̑J��    --------*/

			if ((TRG(0) & PAD_TRG1) && obj->onGround)
			{
				obj->act = PLAYER_ACT::JUMP_START_INIT;
				break;
			}
			if (fabsf(obj->speed.x) < 4.5f)      // ������Ԃ�
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

		/*-------- ���̍s���ł̓��� --------*/

		player_moveY(obj);
		player_moveX(obj);
		obj->setSpeedY(-JUMP_H);

		/*-------     �A�j������     -------*/

		obj->anime = obj->animeTimer / 2;
		if (obj->anime > 3)
		{
			obj->anime = 3;
			obj->act = PLAYER_ACT::JUMP_KEEP_INIT;
			break;
		}
		obj->texPos.x = obj->anime * obj->texSize.x;
		obj->animeTimer++;
		/*--------    �s���̑J��    --------*/
		
		

//--------------------------------
// �W�����v��
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
			{   // PAD_TRG1��������Ă���ꍇ
				obj->setSpeedY(-JUMP_H);
				obj->addJumpTimer(-1);
			}
			else
			{   // PAD_TRG1��������Ă��Ȃ��ꍇ
				obj->setJumpTimer(0);
			}
			
		}
		


		//���n
	if (obj->onGround)
	{
		obj->act = PLAYER_ACT::JUMP_END_INIT;
	}
	break;

	//--------------------------------
	// �W�����v���n
	//--------------------------------
    case PLAYER_ACT::JUMP_END_INIT:

		obj->anime = 0;
		obj->animeTimer = 0;
		player.texPos = { 0, 4 * player.texSize.y };

		obj->speed.x = 0;

		++obj->act;
		/*fallthrough*/

	case PLAYER_ACT::JUMP_END:

		/*-------- ���̍s���ł̓��� --------*/
		// �Ȃ�

		/*-------     �A�j������     -------*/

		player.anime = player.animeTimer / 7;
		if (player.anime > 2)
		{
			player.anime = 2;
		}
		player.texPos.x = player.anime * player.texSize.x;
		player.animeTimer++;
		/*--------    �s���̑J��    --------*/
		// �Ȃ�
		if (player.animeTimer == 14)
		obj->act = PLAYER_ACT::IDLE_INIT;
		break;
	
}
	//��?�h�ؑ�
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
		//�A�j���̏����ݒ�
		obj->anime = 0;
		obj->animeTimer = 0;
		//player.texPos     = { 0,0 * player.texSize.y };

		obj->act++;
		/*fallthrough*/

	case PLAYERBOX_ACT::B_IDLE:
		//���̍s���œ���
		playerbox_moveY(obj);
		playerbox_moveX(obj);


		break;


	}
	

	//��?�h�ؑ�
	if (GetAsyncKeyState('X') & 1)
	{
		obj->moveAlg = player_act;
		obj->act = 0;
	}
}

//--------------------------------------
//  �v���C��?��Y�����̈ړ�
//--------------------------------------
void player_moveY(OBJ2D* obj)
{
	// Y�����̈ړ�
	obj->addSpeedY(GRAVITY);

	//���L�̃v���O��?��?���̎d�l�ɏ���������
	//Transform* transform = obj->transform();

	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
	//ActorComponent* actorComp = obj->actorComponent();   //jumptimer��jumpflag���Ǘ����Ă��邾���Ȃ̂�Player�ő�p�ł���Ǝv���܂�
	//Collider* collider = obj->collider();   //Collider��player�ƕǂ��ڐG��������player���߂荞�܂Ȃ��悤���Ԃ����ׂ̐��l
	                                          //�摜�T�C�Y�����Ɍv�Z���ċ��߂鍡���(25, 300-16)

	//// Y�����̍R�͂̌v�Z  //calcResistance�֐��͂܂��������ĂȂ��̂ň�U�R�����g���Ă���
    //player.addSpeedY(bg->calcResistance(obj, transform->speed().y));

	//// �ő呬�x����
	obj->setSpeedY(clamp(obj->speed.y, -SPEED_Y_MAX, SPEED_Y_MAX));

	//// �ʒu�X�V
	float oldY = obj->pos.y;           // �ړ��O�̈ʒu��ێ�
	obj->addPositionY(obj->speed.y);
	float deltaY = obj->pos.y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������

	//actorComp->setOnGround(false);
	obj->onGround = false;

	//// �������̂����蔻��
	if (deltaY > 0)
	{
		if (bg->isFloor(obj->pos.x, obj->pos.y, obj->collider.x))
		{
			// ���ɂ������Ă�����
			bg->mapHoseiDown(obj);    //  �������̕␳����
			obj->onGround = true;   // �n�ʃt���O
		}
	}

	// ������̂����蔻��
	if (deltaY < 0)
	{                                               // PLAYER_SIZE_Y, PLAYER_SIZE_X
		if (bg->isCeiling(obj->pos.x, obj->pos.y - obj->collider.y, obj->collider.x))
		{
			// �V��ɂ������Ă�����
			bg->mapHoseiUp(obj);
			obj->jumpCount = 0;
		}
	}


}

void playerbox_moveX(OBJ2D* obj)
{
	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();

	//// ���E���͂̎��o��
	using namespace input;
	float dashu = 0;
	if (STATE(0) & PAD_TRG1 && player.sutamina > 0)
	{
		player.sutamina -= PLAYER_SUTAMINA_SPEEDS;
		 dashu = PLAYER_SPEED_DASH;
	}
	switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
	{
	case PAD_LEFT:  // ��������������Ă���ꍇ
		obj->addSpeedX(-(PLAYER_ACCEL_X + dashu) ) ;
		
		break;
	case PAD_RIGHT: // �E������������Ă���ꍇ
		obj->addSpeedX(PLAYER_ACCEL_X + dashu);
		
		break;
	default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
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
		//// X�����̍R�͂̌v�Z
	//transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

	//// �ő呬�x?�F�b�N
	if (obj->speed.x > PLAYER_SPEED_X_MAX + dashu)
		obj->setSpeedX(PLAYER_SPEED_X_MAX + dashu);
	if (obj->speed.x < -PLAYER_SPEED_X_MAX - dashu)
		obj->setSpeedX(-PLAYER_SPEED_X_MAX - dashu);

	// X�����ړ�
	float oldX = obj->pos.x;
	obj->addPositionX(obj->speed.x );
	float deltaX = obj->pos.x - oldX;

	bool kabeFlag = false;  // �ǃt���O��false�ɂ��Ă����i�v���C��?�ł͎g�p���Ȃ��j

	// �E���������蔻��
	if (deltaX > 0)
	{
		if (bg->isWall(obj->pos.x + obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiRight(obj);     // �E�����̕␳����
			kabeFlag = true;                    // �ǃt���O��true�ɂ��Ă���
		}
	}

	// �����������蔻��
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
	// Y�����̈ړ�
	obj->addSpeedY(GRAVITY);

	//���L�̃v���O��?��?���̎d�l�ɏ���������
	//Transform* transform = obj->transform();
	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();
	//ActorComponent* actorComp = obj->actorComponent();   //jumptimer��jumpflag���Ǘ����Ă��邾���Ȃ̂�Player�ő�p�ł���Ǝv���܂�
	//Collider* collider = obj->collider();   //Collider��player�ƕǂ��ڐG��������player���߂荞�܂Ȃ��悤���Ԃ����ׂ̐��l
											  //�摜�T�C�Y�����Ɍv�Z���ċ��߂鍡���(25, 300-16)

	//// Y�����̍R�͂̌v�Z  //calcResistance�֐��͂܂��������ĂȂ��̂ň�U�R�����g���Ă���
	//player.addSpeedY(bg->calcResistance(obj, transform->speed().y));

	//// �ő呬�x����
	obj->setSpeedY(clamp(obj->speed.y, -SPEED_Y_MAX, SPEED_Y_MAX));

	//// �ʒu�X�V
	float oldY = obj->pos.y;           // �ړ��O�̈ʒu��ێ�
	obj->addPositionY(obj->speed.y);
	float deltaY = obj->pos.y - oldY;  // �ړ���̈ʒu����ړ��O�̈ʒu������

	//actorComp->setOnGround(false);
	obj->onGround = false;

	//// �������̂����蔻��
	if (deltaY > 0)
	{
		if (bg->isFloor(obj->pos.x, obj->pos.y, obj->collider.x))
		{
			// ���ɂ������Ă�����
			bg->mapHoseiDown(obj);    //  �������̕␳����
			obj->onGround = true;   // �n�ʃt���O
		}
	}

	//// ������̂����蔻��
	if (deltaY < 0)
	{
		if (bg->isCeiling(obj->pos.x, obj->pos.y - obj->collider.y, obj->collider.x))
		{
			// �V��ɂ������Ă�����
			bg->mapHoseiUp(obj);
			obj->jumpCount = 0;
		}
	}

}

//--------------------------------------
//  �v���C��?��X�����̈ړ�
//--------------------------------------
void player_moveX(OBJ2D* obj)
{

	BG* bg = (stageNo != 0) ? Game::instance()->bg() : Tuto::instance()->bg();

	//// ���E���͂̎��o��
	using namespace input;
	switch (STATE(0) & (PAD_LEFT | PAD_RIGHT))
	{
	case PAD_LEFT:  // ��������������Ă���ꍇ
		obj->addSpeedX(-PLAYER_ACCEL_X);
		obj->scale.x = -0.5f;
		break;
	case PAD_RIGHT: // �E������������Ă���ꍇ
		obj->addSpeedX(PLAYER_ACCEL_X);
		obj->scale.x = 0.5f;
		break;
	default:        // �ǂ����������Ă��Ȃ������E����Ă���ꍇ
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
	//�������p
	if ( (GetAsyncKeyState('V') & 1) && player.sutamina ==PLAYER_SUTAMINA) //PAD_TRG2 = X
	{
		player.sutamina = 0;
		player.timer = 0;
	}
	//// X�����̍R�͂̌v�Z
	//transform->addSpeedX(bg->calcResistance(obj, transform->speed().x));

	//// �ő呬�x?�F�b�N
	if (obj->speed.x > PLAYER_SPEED_X_MAX)
		obj->setSpeedX(PLAYER_SPEED_X_MAX);
	if (obj->speed.x < -PLAYER_SPEED_X_MAX)
		obj->setSpeedX(-PLAYER_SPEED_X_MAX);

	// X�����ړ�
	float oldX = obj->pos.x;
	obj->addPositionX(obj->speed.x);
	float deltaX = obj->pos.x - oldX;

	bool kabeFlag = false;  // �ǃt���O��false�ɂ��Ă����i�v���C��?�ł͎g�p���Ȃ��j

	// �E���������蔻��
	if (deltaX > 0)
	{
		if (bg->isWall(obj->pos.x + obj->collider.x,
			obj->pos.y, obj->collider.y))
		{
			bg->mapHoseiRight(obj);     // �E�����̕␳����
			kabeFlag = true;                    // �ǃt���O��true�ɂ��Ă���
		}
	}

	// �����������蔻��
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