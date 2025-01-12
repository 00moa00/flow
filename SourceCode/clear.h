#ifndef INCLUDED_CLEAR
#define INCLUDED_CLEAR

class Clear : public Scene
{
public:
    static Clear* instance() { return &instance_; }

    void update();
    void draw();

private:
    static Clear instance_;
    int se;
    Scene* select[2] = { Game::instance(),Tuto::instance() };
};


#endif // !INCLUDED_CLEAR