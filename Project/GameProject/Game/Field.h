#pragma once
#pragma once
#include "../Base/Base.h"

class Field : public Base {
private:
    //画像オブジェクト（前景）
    CImage m_foreground;
    //画像オブジェクト（遠景）
    CImage m_town;
    //画像オブジェクト（最遠景）
    CImage m_sky;
    //地面の高さ
    float m_ground_y;

    struct Line {
        CVector2D s;
        CVector2D e;
    };
    std::list<Line> m_line_list;

public:
    /// コンストラクタ
    Field();
    /// 描画
    void Draw();

    /// 地面の高さを取得
    float GetGroundY() {
        return m_ground_y;
    }
    float GetGroundY(int x);
};




