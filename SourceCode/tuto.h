#pragma once

class Tuto : public Scene
{
public:
    static Tuto* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

    BG* bg() { return bg_; }   //bg_のゲッター

private:
    bool                isPaused;
    BG* bg_;   //背景を管理するようの変数

    static Tuto instance_;
};
