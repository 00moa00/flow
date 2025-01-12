#ifndef INCLUDED_OVER
#define ONCLUDED_OVER

class Over : public Scene
{
    static Over instance_;


    void update();
    void draw();

public:
    static Over* instance() { return &instance_; }
    int se;
    Scene* select[2] = { Game::instance(),Title::instance() };
};

#endif // !INCLUDED_OVER

