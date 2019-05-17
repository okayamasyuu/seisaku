#include "stdafx.h"
#include "grund.h"


grund::grund()
{
}
grund::~grund()
{
	DeleteGO(m_skinModelRender);
}
bool grund::Start()
{


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/floer.cmo");

	
	/*scale.x = 30.0f;
	scale.y = 3.0f;
	scale.z = 30.0f;*/
	/*m_position.y = -55.0;*/

	//‰e‚ð—Ž‚Æ‚³‚ê‚é‘¤@SetShadowReceiverFlag
	m_skinModelRender->SetShadowReceiverFlag(true);

	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	m_phyStaticObject.CreateMesh(m_position,CQuaternion::Identity, scale, m_skinModelRender);
	return true;
}
void grund::Update()
{

}