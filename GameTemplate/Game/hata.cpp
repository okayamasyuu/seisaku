#include "stdafx.h"
#include "hata.h"
#include "Player.h"
#include "Clear.h"
#include "title.h"
#include "Game.h"

hata::hata()
{
}


hata::~hata()
{
	DeleteGO(m_skinModelRender);
}
bool hata::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/hatahata.cmo");

	/*scale.x = 2.0f;
	scale.y = 3.0f;
	scale.z = 2.0f;
	
	m_position.x = 900.0f;
*/
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(scale);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_skinModelRender);
	return true;
}
void hata::Update()
{
	//クリア判定
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->m_position - m_position;
		if (diff.Length() < 100.0f) {
			Game* ga = FindGO<Game>("game");
		     ga->Clear_flag = true;
		    NewGO<Clear>(0, "クリア");
		    ga->m_timer += 5;
			/*pl->m_moveSpeed.x =  0.0f;
	          pl->m_moveSpeed.z =  0.0f;*/
		     if (ga->m_timer == 300 ) {
				 ga->m_timer = 0;
				 NewGO<title>(0);
		      DeleteGO(ga);
		     }
		}
		
		
		return true;
	});
}
