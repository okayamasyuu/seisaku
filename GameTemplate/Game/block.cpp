#include "stdafx.h"
#include "block.h"
#include "Player.h"
#include "Game.h"
#include "Coin2.h"

block::block()
{
}


block::~block()
{
	DeleteGO(m_skinModelRender);
}
bool block::Start()
{
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/block.cmo");

	//当たり用のデータ。
	m_skinModelData.Load(L"modelData/backgound/blockColli.cmo");
	m_skinModel.Init(m_skinModelData);


	/*scale.x = 2.5f;
	scale.y = 2.5f;
	scale.z = 2.5f;*/
	
	m_skinModelRender->SetScale(scale);
	m_skinModelRender->SetPosition(m_position);
	//m_skinModelRender->SetRotation(m_rotation);
	m_PSObject.CreateMesh(m_position, CQuaternion::Identity, scale, m_skinModel);
	
	return true;
}
void block::Update()
{

	
	//プレイヤーとブロック、当たったらコインが出る
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->m_position - m_position;

		if (diff.Length() < 100.0f) {
			if (block_count == 1) {
				//効果音
				auto ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/coinGet.wav");
				ss->Play(false);

				block_count--;
				Game* ga = FindGO<Game>("game");
				ga->C_count += 1;
				Coin2* coin2 = NewGO<Coin2>(0, "コイン２");
				coin2->m_position = m_position;//コインの座標にブロックの座標を代入
				coin2->m_movespeed.y += 3.0f;
			
				/*coin2->m_time++;
				if (coin2->m_time == 2) {
					coin2->m_time = 0;
					coin2 = FindGO<Coin2>("コイン２");
					DeleteGO(coin2);
				}*/

				//ブロックとコインの距離が一定距離、離れたら破棄
			  /* QueryGOs<Coin2>("コイン２", [&](Coin2* coin2)->bool {
				for (int i = 0; i < 5; i++) {
					CVector3 v = coin2->m_position - m_blo[i]->m_position;
					if (v.Length() > 500) {
						coin2 = FindGO<Coin2>("コイン２");
						DeleteGO(coin2);
					}
				}
				return true;
			  });*/

			}
			else {
			}
		}
		return true;
	});
	
}
