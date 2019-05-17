#include "stdafx.h"
#include "moveblock.h"


moveblock::moveblock()
{
}


moveblock::~moveblock()
{
	DeleteGO(m_skinModelRender);
}
bool moveblock::Start()
{

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/block.cmo");

	//当たり用のデータ。
	m_skinModelData.Load(L"modelData/backgound/blockColli.cmo");
	m_skinModel.Init(m_skinModelData);

	m_moveSpeed.z = 20;

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_skinModel);

	return true;
}
void moveblock::Update()
{
	//m_position += m_moveSpeed;

	//if (m_position.z > 500.0f) {
	//
	//	m_moveSpeed.z = -30.0f;//↓
	//}
	//if (m_position.z < -300.0f) {

	//	m_moveSpeed.z = 30.0f;//↑
	//}

	//キャラコンに移動速度を与える
	//m_position = m_charaCon.Execute(m_moveSpeed);

	//キャラコンで動かした結果をCSkinModelRenderに反映させる。
	//m_skinModel->SetPosition(GetPosition());
	
	m_skinModelRender->SetPosition(m_position);
}