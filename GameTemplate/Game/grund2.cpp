#include "stdafx.h"
#include "grund2.h"


grund2::grund2()
{
}


grund2::~grund2()
{
	DeleteGO(m_skinModelRender);
}
bool grund2::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/hako.cmo");

//	m_rot.SetRotationDeg(CVector3::AxisY, 55);
	
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetRotation(m_rot);
	m_phyStaticObject.CreateMesh(m_position, m_rot, scale, m_skinModelRender);
	return true;
}
void grund2::Update()
{

}