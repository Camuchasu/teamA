#include"../Task/Task.h"

class Field :public Task
{
private:
    int m_pos;
public:
    Field(const CVector3D& pos);

    void Update();
    void Render();

    CImage m_Sky;
    CImage m_Yama;
    CImage m_yuka;
    CImage m_kumo;
};