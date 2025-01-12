#ifndef INCLUDED_SCENE
#define INCLUDED_SCENE

//******************************************************************************
//
//
//      �V�[��
//
//
//******************************************************************************

//==============================================================================
//
//      Scene�N���X
//
//==============================================================================
class Scene
{
protected:
    int state;          // ���
    int timer;          // �^�C�}�[
    Scene* nextScene;   // ���̃V�[��

public:
    Scene* execute();   // ���s����

    virtual void init()
    { // ����������
        state = 0;
        timer = 0;
        nextScene = nullptr;
    };
    virtual void deinit() {};   // �I������(���z�֐�)
    virtual void update() {};   // �X�V����(���z�֐�)
    virtual void draw()   {};   // �`�揈��(���z�֐�)

    void changeScene(Scene *scene) { nextScene = scene; }   // �V�[���ύX����
    Scene *getScene() const { return nextScene; }           // nextScene�̃Q�b�^�[
};

//******************************************************************************
//
//
//      �V�[���Ǘ�
//
//
//******************************************************************************

//==============================================================================
//
//      SceneManager�N���X
//
//==============================================================================

class SceneManager
{
public:
    void execute(Scene*);  // ���s����
};

//******************************************************************************

#endif // !INCLUDED_SCENE