#include "ObjectBase.h"
#define FIELD_CENTER_Z (SCREEN_HEIGHT * 0.75f)
CVector2D ObjectBase::m_scroll(0, 0);
// コンストラクタ
ObjectBase::ObjectBase(int Type)
	: ObjectBase(CVector3D::zero, Type)
{
}

ObjectBase::ObjectBase(const CVector3D& pos,int Type)
    : Task((int)ETaskPrio::Object,0,Type)
	, m_pos(pos)
	, m_isGrounded(true)
	, mp_shadowImg(nullptr)
{
	// 影の画像を読み込み
	mp_shadowImg = CImage::CreateImage("image/shadow.png");
	mp_shadowImg->SetCenter(mp_shadowImg->GetSize() * 0.5f);
}

// デストラクタ
ObjectBase::~ObjectBase()
{
	// 影の画像データを削除
	if (mp_shadowImg != nullptr)
	{
		delete mp_shadowImg;
		mp_shadowImg = nullptr;
	}
}

// 座標を取得
const CVector3D& ObjectBase::GetPos() const
{
	return m_pos;
}

// 座標を設定
void ObjectBase::SetPos(const CVector3D& pos)
{
	m_pos = pos;
}

// 3次元座標から2次元座標を計算
CVector2D ObjectBase::CalcScreenPos(bool grounded) const
{
	return CalcScreenPos(m_pos, grounded);
}

CVector2D ObjectBase::CalcScreenPos(const CVector3D& pos, bool grounded) const
{
	CVector2D ret;

	// X座標はそのまま設定
	ret.x = pos.x - pos.z * 0.65;
	// 通常座標を求める場合
	if (!grounded)
	{
		// Y座標は、3次元座標のY（高さ）とZ（奥行）を合わせる
		float posZ = FIELD_CENTER_Z + pos.z;
		ret.y = -pos.y + posZ;
	}
	// 高さを考慮しない地面の位置を求める場合
	else
	{
		// Y座標は、3次元座標のZ（奥行）のみ反映する
		ret.y = FIELD_CENTER_Z + pos.z;
	}

	return ret - m_scroll;

}

// 更新
void ObjectBase::Update()
{

}

// 描画
void ObjectBase::Render()
{
}

// 影描画
void ObjectBase::RenderShadow()
{
	// 影を地面の位置で描画
	mp_shadowImg->SetPos(CalcScreenPos(true));
	mp_shadowImg->Draw();
}

bool ObjectBase::CollisionCube(ObjectBase* b1, ObjectBase* b2)
{
	b1->m_Max = b1->m_pos + b1->m_Cube;//最大値の設定
	b1->m_Min = b1->m_pos - b1->m_Cube;//最低値の設定
	b2->m_Max = b2->m_pos + b2->m_Cube;//最大値の設定
	b2->m_Min = b2->m_pos - b2->m_Cube;//最低値の設定
	if (b1->m_Min.x > b2->m_Max.x || b1->m_Max.x < b2->m_Min.x ||
		b1->m_Min.y > b2->m_Max.y || b1->m_Max.y < b2->m_Min.y ||
		b1->m_Min.z > b2->m_Max.z || b1->m_Max.z < b2->m_Min.z)
	{
		return false;
	}
	return true;
}

void ObjectBase::RenderCube()
{
#ifdef _DEBUG
	m_Max = m_pos + m_Cube;
	m_Min = m_pos - m_Cube;
	Utility::DrawQuad(CalcScreenPos(CVector3D(m_Min.x, m_Max.y, m_pos.z)),
		CVector2D(m_Cube.x * 2, m_Cube.y * 2), CVector4D(1, 0, 0, 0.5f));
#endif 
}
