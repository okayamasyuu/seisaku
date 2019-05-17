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

	//������p�̃f�[�^�B
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

	
	//�v���C���[�ƃu���b�N�A����������R�C�����o��
	QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		CVector3 diff = pl->m_position - m_position;

		if (diff.Length() < 100.0f) {
			if (block_count == 1) {
				//���ʉ�
				auto ss = NewGO<prefab::CSoundSource>(0);
				ss->Init(L"sound/coinGet.wav");
				ss->Play(false);

				block_count--;
				Game* ga = FindGO<Game>("game");
				ga->C_count += 1;
				Coin2* coin2 = NewGO<Coin2>(0, "�R�C���Q");
				coin2->m_position = m_position;//�R�C���̍��W�Ƀu���b�N�̍��W����
				coin2->m_movespeed.y += 3.0f;
			
				/*coin2->m_time++;
				if (coin2->m_time == 2) {
					coin2->m_time = 0;
					coin2 = FindGO<Coin2>("�R�C���Q");
					DeleteGO(coin2);
				}*/

				//�u���b�N�ƃR�C���̋�������苗���A���ꂽ��j��
			  /* QueryGOs<Coin2>("�R�C���Q", [&](Coin2* coin2)->bool {
				for (int i = 0; i < 5; i++) {
					CVector3 v = coin2->m_position - m_blo[i]->m_position;
					if (v.Length() > 500) {
						coin2 = FindGO<Coin2>("�R�C���Q");
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
