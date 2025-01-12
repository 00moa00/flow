#ifndef INCLUDED_TITLE
#define	INCLUDED_TITLE

//******************************************************************************
//
//
//      �^�C�g���V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Title�N���X
//
//==============================================================================

class Title : public Scene
{
public:
    static Title* instance() { return &instance_; }

	void update();
	void draw();

private:
    static Title instance_;
    int se; //�V�[���Z���N�g�p�ϐ�
    Scene* select[2] = { Story::instance(), Tuto::instance() };
};

//�X�e�[�W�ύX�p�֐�
void sceneChenge(int stage, int diff);

//******************************************************************************

#endif // !INCLUDED_TITLE
