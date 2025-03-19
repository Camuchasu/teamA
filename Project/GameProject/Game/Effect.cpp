#include "Effect.h"
Effect::Effect(const char* name, const CVector3D& pos, const CVector3D& vec, const CVector2D& size)
    :ObjectBase(pos, eType_Effect)
    , m_vec(vec)
    , m_size(size)
    , alpfa(1.0)
    , scale(1.0)
{
    m_img = COPY_RESOURCE(name, CImage);
    m_img.ChangeAnimation(0, true);

}

Effect::~Effect()
{
}

void Effect::Update()
{
    static float gravity = 0.5;
    m_vec.y -= gravity;
    m_pos += m_vec;
    m_size.x -= scale;
    m_size.y -= scale;

    if (m_pos.y <= 0)
    {
        m_vec.y *= -0.8;
    }
    if (m_size.x <= 0)
    {
        Kill();
    }
    m_img.UpdateAnimation();
}

void Effect::Render()
{
    m_img.SetPos(CalcScreenPos());
    m_img.SetCenter(m_size / 2);
    m_img.SetSize(m_size);
    m_img.Draw();

}
