#pragma once
class BG
{
public:
    //------< 定数 >------------------------------------------------------------
    static const int WINDOW_W = 1920;                   // ウインドウの幅
    static const int WINDOW_H = 1080;                    // ウインドウの高さ
    static const int CLIENT_W = 1920;                   // クライアント領域の幅(画面内に?ップ?ップを?画する領域のこと、例300なら横軸300サイズ分までしか?画しない)
    static const int CLIENT_H = 1080;                    // クライアント領域の高さ(画面内に?ップ?ップを?画する領域のこと、例300なら縦軸300サイズ分までしか?画しない)

    static const int CHIP_SIZE = 64;                    // %演算子を使用するためint?を使用する
    static const int LOOP_X = CLIENT_W / CHIP_SIZE + (CLIENT_W % CHIP_SIZE ? 2 : 1);
    static const int LOOP_Y = CLIENT_H / CHIP_SIZE + (CLIENT_H % CHIP_SIZE ? 2 : 1);

    static const int CHIP_NUM_X = 64;                   // ?ップの横方向の?ップ数
    static const int CHIP_NUM_Y = 32;                   // ?ップの縦方向の?ップ数
    static const int CHIP_NUM_PER_LINE = 8;             // ?ップ?ップの1列が8個
    static const int CHIP_LINE_NUM = 4;                 // ?ップ?ップが４行

    static constexpr float CHIP_SIZE_F = static_cast<float>(CHIP_SIZE);
    static constexpr float WIDTH = static_cast<float>(CHIP_NUM_X * CHIP_SIZE);  // ?ップの幅（ドット）
    static constexpr float HEIGHT = static_cast<float>(CHIP_NUM_Y * CHIP_SIZE); // ?ップの高さ（ドット）
    static constexpr float SCROLL_MERGIN_X = 240.f;     // この数値より画面?に近づいたらスクロ?ルする（横）
    static constexpr float SCROLL_MERGIN_Y = 160.f;     // この数値より画面?に近づいたらスクロ?ルする（縦）
    static constexpr float ADJUST_Y = 0.25f;            // あたり判定での位置調整用（縦）
    static constexpr float ADJUST_X = 0.025f;           // あたり判定での位置調整用（横）

    // 地?（Terrain）の属性
    enum class TR_ATTR
    {
        TR_NONE = -1,   // -1:何もなし
        ALL_BLOCK,      //  0:四方ブロック
        UPPER_BLOCK,    //  1:上だけブロック
        HASHIGO,        //  2:はしご
        DOOR_BLOCK,     //  3:ドア
    };

    // 背景（Back）の属性
    enum class BG_ATTR
    {
        BG_NONE = -1,   // -1:何もなし
        NORMAL,         //  0:普通（特に何もなし）
        WATER,          //  1:水中（抵抗を受ける）
    };

private:
    // 地??ップテクス?ャの各部分の属性を定?する
    const TR_ATTR terrainAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::ALL_BLOCK,   TR_ATTR::UPPER_BLOCK, TR_ATTR::UPPER_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK, TR_ATTR::ALL_BLOCK,
        TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::DOOR_BLOCK,   TR_ATTR::TR_NONE,
        TR_ATTR::HASHIGO,     TR_ATTR::HASHIGO,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,
        TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,     TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,   TR_ATTR::TR_NONE,
    };

    // 背景?ップテクス?ャの各部分の属性を定?する
    const BG_ATTR bgAttr[CHIP_LINE_NUM * CHIP_NUM_PER_LINE] = {
        BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,    BG_ATTR::NORMAL,    BG_ATTR::NORMAL,   BG_ATTR::NORMAL,
        BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,      BG_ATTR::NORMAL,    BG_ATTR::NORMAL,    BG_ATTR::NORMAL,   BG_ATTR::NORMAL,
        BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,
        BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,     BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,   BG_ATTR::BG_NONE,
    };

    //------< 変数 >------------------------------------------------------------
    VECTOR2 scroll;                                         // 現在?示されている左上の地?の座標
    
    //OBJ2D* player?;  //ステ?ジ初期位置の座標取得用

    char back[CHIP_NUM_Y][CHIP_NUM_X];                      // 背景デ??
    char terrain[CHIP_NUM_Y][CHIP_NUM_X];                   // 地?デ??

public:
    BG();
    ~BG();

    // 初期化
    void init(/*OBJ2D* player*/);  //引数にプレイヤ?を渡す事で座標をコピ?する  

    // 更新
    void update();

    // ?画
    void drawBack();                                        // 背景?画
    void drawTerrain();                                     // 地??画

    // スクロ?ル位置取得
    float getScrollX() { return scroll.x; }
    float getScrollY() { return scroll.y; }
    const VECTOR2& getScrollPos() { return scroll; }

    // 当たり判定
    // 下方向
    bool isFloor(float, float, float);          // 床にめり込んでいるか
    void mapHoseiDown(OBJ2D*);                  // 下方向補正処理

    //// 上方向
    bool isCeiling(float, float, float);        // 天井にあたっているか
    void mapHoseiUp(OBJ2D*);                    // 上方向補正処理

    //// 横方向
    bool isWall(float x, float y, float height);           // 横方向に壁にめり込んでいるか
    void mapHoseiRight(OBJ2D*);                 // 右方向補正処理
    void mapHoseiLeft(OBJ2D*);                  // 左方向補正処理

    //ドアかどうか
    bool BG::isDoor(float x, float y, float height);

    //// 抵抗
    //float calcResistance(const OBJ2D*, float);
    //BG_ATTR getBackAttr(const VECTOR2&);
    //float getTeikou(BG_ATTR, float);
    //bool isInWater(const OBJ2D*);

    TR_ATTR getTerrainAttr(const VECTOR2&);

private:
    // クリア
    void clear();

    // ?ップデ??のロ?ド
    bool loadMapData(const char[][CHIP_NUM_X], char[][CHIP_NUM_X]);
    bool loadMapData2(const char[][CHIP_NUM_X], char[][CHIP_NUM_X]);

    // BG、Terrain共通の?画関数
    void draw(int, char[][CHIP_NUM_X]);  // ?画処理（ス??ズなスクロ?ル）

    // ?ップスクロ?ル用
    void scrollMap();
    void scrollMap0();  //スクロ?ルプロト?イプ用

    bool isHitDown(float, float);
    bool isHitAll(float, float);
    bool isHitDoor(float, float);
    bool isUpperQuater(float);
    int getData(char[][BG::CHIP_NUM_X], const VECTOR2&);


};
    void set_bgstate(int No);