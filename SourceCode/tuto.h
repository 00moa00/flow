#pragma once

class Tuto : public Scene
{
public:
    static Tuto* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

    BG* bg() { return bg_; }   //bg_�̃Q�b�^�[

private:
    bool                isPaused;
    BG* bg_;   //�w�i���Ǘ�����悤�̕ϐ�

    static Tuto instance_;
};
