#pragma once

class Tuto : public Scene
{
public:
    static Tuto* instance() { return &instance_; }

    void init();
    void deinit();
    void update();
    void draw();

    BG* bg() { return bg_; }   //bg_‚ÌƒQƒbƒ^[

private:
    bool                isPaused;
    BG* bg_;   //”wŒi‚ğŠÇ—‚·‚é‚æ‚¤‚Ì•Ï”

    static Tuto instance_;
};
