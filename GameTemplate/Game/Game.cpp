#include "stdafx.h"
#include "Game.h"
#include "title.h"
#include "tkEngine/light/tkDirectionLight.h"
#include "Player.h"
#include "camera.h"
#include "kabe.h"
#include "block.h"
#include "grund.h"
#include "Enemy.h"
#include "GameOver.h"
#include "Coin.h"
#include "Coin2.h"
#include "CoinHUD.h"
#include "Clear.h"
#include "hata.h"
#include "grund2.h"
#include "Enemy2.h"
#include "moveblock.h"
#include "KABEd.h"


Game::Game()
{
	/*
	�e	�N���X�̍��W�Ƒ傫�����R�����g���Ă����@max�ő傫����
	���W�𒲐�����
	�t�@�C���p�X�@STEGE
	�I�u�W�F�N�g�̖��O
	//level00
	coinG*
	block*
	moveblock*
	hata
	hako*
	Enemy*
	unityChan
	floer
	kabe
	kabe2
	*/
	m_level.Init(L"STEGE.tkl", [&](LevelObjectData & objData) {
		if (objData.EqualObjectName(L"unityChan")) {
			Player* pl = NewGO<Player>(0, "�v���C���[");
			pl->m_position = objData.position;
			pl->rotat = objData.rotation;
			return true;
		}
		else if (objData.EqualObjectName(L"floer")) {
			grund* gr = NewGO<grund>(0, "��");
			gr->m_position = objData.position;
			gr->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"hako")) {
			grund2* gr2 = NewGO<grund2>(0, "�w�i");
			gr2->m_position = objData.position;
			gr2->m_rot = objData.rotation;
			gr2->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"Enemy")) {
			Enemy* en = NewGO<Enemy>(0, "�G");
			en->m_position = objData.position;
			en->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"Enemy2")) {
			Enemy2* en2 = NewGO<Enemy2>(0, "�G2");
			en2->m_position = objData.position;
			en2->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"block")) {
			block* bl = NewGO<block>(0, "�u���b�N");
			bl->m_position = objData.position;
			bl->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"moveblock")) {
			moveblock* bl2 = NewGO<moveblock>(0, "�u���b�N2");
			bl2->m_position = objData.position;
			bl2->m_rotation = objData.rotation;
			bl2->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"coinG")) {
			Coin* co = NewGO<Coin>(0, "�R�C��");
			co->m_position = objData.position;
			co->m_rotation = objData.rotation;
			co->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"hatahata")) {
			hata* ha = NewGO<hata>(0, "��");
			ha->m_position = objData.position;
			ha->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"kabe")) {
			kabe* ka = NewGO<kabe>(0, "��");
			ka->m_position = objData.position;
			ka->m_rot = objData.rotation;
			ka->scale = objData.scale;
			return true;
		
		}
		else if (objData.EqualObjectName(L"kabe2")) {
			KABEd* KA = NewGO<KABEd>(0, "��2");
			KA->m_position = objData.position;
			KA->m_rot = objData.rotation;
			KA->scale = objData.scale;
			return true;

		}
	});

}
Game::~Game()
{
	DeleteGOs("�v���C���[");
	DeleteGOs("��");
	DeleteGOs("�G");
	DeleteGOs("�u���b�N");
	DeleteGOs("�u���b�N2");
	DeleteGOs("�R�C��");
	DeleteGOs("��");
	DeleteGOs("�w�i");
	DeleteGOs("����");
	DeleteGOs("�G2");
	DeleteGOs("��");
	DeleteGOs("��2");

	camera* ca = FindGO<camera>("�J����");
	DeleteGO(ca);

	CoinHUD* HUD = FindGO<CoinHUD>("�X�R�A");
	DeleteGO(HUD);

	////�u���b�N����o���R�C���̔j��
	QueryGOs<Coin2>("�R�C���Q", [](Coin2 * coin2)->bool
		{
			DeleteGO(coin2);
			return true;
		});

	QueryGOs<Clear>("�N���A", [](Clear * cl)->bool
		{
			DeleteGO(cl);
			return true;
		});
	DeleteGO(m_dirLig);
	/*QueryGOs<GameOver>("����", [](GameOver* ov)->bool
	{
		DeleteGOs(ov);
	return true;
	});
	//
	//Enemy* en = FindGO<Enemy>("�G");
	//DeleteGO(en);

	//Player* pl = FindGO<Player>("�v���C���[");
	//DeleteGO(pl);
	
	

	//grund* gl = FindGO<grund>("grund");
	//DeleteGO(gl);

	//QueryGOs<block>("�u���b�N", [](block* bl)->bool
	//{
	//	DeleteGO(bl);
	//	return true;
	//});

	//QueryGOs<Coin>("�R�C", [](Coin* co)->bool
	//{
	//	DeleteGO(co);
	//	return true;
	//});


	

	//hata* hat = FindGO<hata>("��");
	//DeleteGO(hat);

	

	/*Box* box = FindGO<Box>("��");
	DeleteGO(box);*/
}
bool Game::Start()
{
	//�J������ݒ�B
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();
	
	NewGO<camera>(0, "�J����");

	////�R�C���̖���
	NewGO<CoinHUD>(0, "�X�R�A");
	//���s�������쐬����B
	m_dirLig = NewGO<prefab::CDirectionLight>(0);//���C�g
	CVector3 lightDir = { 1, -1, 1 };
	lightDir.Normalize();
	m_dirLig->SetDirection(lightDir);
	m_dirLig->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	LightManager().SetAmbientLight({ 0.2, 0.2, 0.2 });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);

	//NewGO<>(0, "�v���C���[");

	//NewGO<grund>(0, "grund"); //��

	//NewGO<Enemy>(0, "�G");
	//
	//m_blo[0] = NewGO<block>(0, "�u���b�N"); //�u���b�N
	//m_blo[0]->m_position.x = 200.0f;
	//m_blo[0]->m_position.y = 200.0f;

	//m_blo[1] = NewGO<block>(0, "�u���b�N");
	//m_blo[1]->m_position.x = 400.0f;
	//m_blo[1]->m_position.y = 200.0f;

	//m_blo[2] = NewGO<block>(0, "�u���b�N");
	//m_blo[2]->m_position.x = 600.0f;
	//m_blo[2]->m_position.y = 200.0f;

	//m_blo[3] = NewGO<block>(0, "�u���b�N");
	//m_blo[3]->m_position.x = 700.0f;
	//m_blo[3]->m_position.y = 200.0f;

	//m_blo[4] = NewGO<block>(0, "�u���b�N");
	//m_blo[4]->m_position.x = 100.0f;
	//m_blo[4]->m_position.y = 100.0f;
	//m_blo[4]->m_position.z = 200.0f;
	//


	////�ŏ�����z�u����Ă���R�C��
	//Coin* m_coi[3] = { nullptr };
	//m_coi[0] = NewGO<Coin>(0, "�R�C");
	//m_coi[0]->m_position.x = 200.0f;
	//m_coi[0]->m_position.y = 400.0f;

	//m_coi[1] = NewGO<Coin>(0, "�R�C");
	//m_coi[1]->m_position.x = 400.0f;
	//m_coi[1]->m_position.y = 400.0f;

	////�S�[���n�_
	//NewGO<hata>(0, "��");

	

	//NewGO<Box>(0, "��");
	return true;
}

void Game::Update()
{
	

	//HP��0
	Player* pl = FindGO<Player>("�v���C���[");
	if (pl->hp <= 0 ) {
		NewGO<GameOver>(0, "����");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			
		}
	}
	if (pl->m_position.y < -100.0) {
		NewGO<GameOver>(0, "����");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);

		}
	}

	if (Clear_flag == false) {
		if (Pad(0).IsPress(enButtonSelect) == true) {
			NewGO<title>(0);
			DeleteGO(this);
		}
	}
	

	//�N���A
	/*QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		
		CVector3 diff = pl->m_position - ha->m_position;

		if (diff.Length() < 100.0f) {
			Clear_flag = true;
			NewGO<Clear>(0, "�N���A");
			m_timer += 5;
			if (m_timer == 500 && Clear_flag == true) {
				NewGO<title>(0);
				DeleteGO(this);
			}
		}
		return true;
	});*/
}