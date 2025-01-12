#pragma once


class Story : public Scene
{
public:
    static Story* instance() { return &instance_; }

    void init();
    void update();
    void draw();

    ~Story();

private:
    static Story instance_;
    
};

