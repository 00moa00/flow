#ifndef INCLUDED_TITLE
#define	INCLUDED_TITLE

//******************************************************************************
//
//
//      タイトルシーン
//
//
//******************************************************************************

//==============================================================================
//
//      Titleクラス
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
    int se; //シーンセレクト用変数
    Scene* select[2] = { Story::instance(), Tuto::instance() };
};

//ステージ変更用関数
void sceneChenge(int stage, int diff);

//******************************************************************************

#endif // !INCLUDED_TITLE
