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
	各	クラスの座標と大きさをコメントしておく　maxで大きさと
	座標を調整する
	ファイルパス　STEGE
	オブジェクトの名前
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
			Player* pl = NewGO<Player>(0, "プレイヤー");
			pl->m_position = objData.position;
			pl->rotat = objData.rotation;
			return true;
		}
		else if (objData.EqualObjectName(L"floer")) {
			grund* gr = NewGO<grund>(0, "床");
			gr->m_position = objData.position;
			gr->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"hako")) {
			grund2* gr2 = NewGO<grund2>(0, "背景");
			gr2->m_position = objData.position;
			gr2->m_rot = objData.rotation;
			gr2->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"Enemy")) {
			Enemy* en = NewGO<Enemy>(0, "敵");
			en->m_position = objData.position;
			en->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"Enemy2")) {
			Enemy2* en2 = NewGO<Enemy2>(0, "敵2");
			en2->m_position = objData.position;
			en2->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"block")) {
			block* bl = NewGO<block>(0, "ブロック");
			bl->m_position = objData.position;
			bl->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"moveblock")) {
			moveblock* bl2 = NewGO<moveblock>(0, "ブロック2");
			bl2->m_position = objData.position;
			bl2->m_rotation = objData.rotation;
			bl2->scale = objData.scale;

			return true;
		}
		else if (objData.EqualObjectName(L"coinG")) {
			Coin* co = NewGO<Coin>(0, "コイン");
			co->m_position = objData.position;
			co->m_rotation = objData.rotation;
			co->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"hatahata")) {
			hata* ha = NewGO<hata>(0, "旗");
			ha->m_position = objData.position;
			ha->scale = objData.scale;
			return true;
		}
		else if (objData.EqualObjectName(L"kabe")) {
			kabe* ka = NewGO<kabe>(0, "壁");
			ka->m_position = objData.position;
			ka->m_rot = objData.rotation;
			ka->scale = objData.scale;
			return true;
		
		}
		else if (objData.EqualObjectName(L"kabe2")) {
			KABEd* KA = NewGO<KABEd>(0, "壁2");
			KA->m_position = objData.position;
			KA->m_rot = objData.rotation;
			KA->scale = objData.scale;
			return true;

		}
	});

}
Game::~Game()
{
	DeleteGOs("プレイヤー");
	DeleteGOs("床");
	DeleteGOs("敵");
	DeleteGOs("ブロック");
	DeleteGOs("ブロック2");
	DeleteGOs("コイン");
	DeleteGOs("旗");
	DeleteGOs("背景");
	DeleteGOs("死んだ");
	DeleteGOs("敵2");
	DeleteGOs("壁");
	DeleteGOs("壁2");

	camera* ca = FindGO<camera>("カメラ");
	DeleteGO(ca);

	CoinHUD* HUD = FindGO<CoinHUD>("スコア");
	DeleteGO(HUD);

	////ブロックから出たコインの破棄
	QueryGOs<Coin2>("コイン２", [](Coin2 * coin2)->bool
		{
			DeleteGO(coin2);
			return true;
		});

	QueryGOs<Clear>("クリア", [](Clear * cl)->bool
		{
			DeleteGO(cl);
			return true;
		});
	DeleteGO(m_dirLig);
	/*QueryGOs<GameOver>("死んだ", [](GameOver* ov)->bool
	{
		DeleteGOs(ov);
	return true;
	});
	//
	//Enemy* en = FindGO<Enemy>("敵");
	//DeleteGO(en);

	//Player* pl = FindGO<Player>("プレイヤー");
	//DeleteGO(pl);
	
	

	//grund* gl = FindGO<grund>("grund");
	//DeleteGO(gl);

	//QueryGOs<block>("ブロック", [](block* bl)->bool
	//{
	//	DeleteGO(bl);
	//	return true;
	//});

	//QueryGOs<Coin>("コイ", [](Coin* co)->bool
	//{
	//	DeleteGO(co);
	//	return true;
	//});


	

	//hata* hat = FindGO<hata>("旗");
	//DeleteGO(hat);

	

	/*Box* box = FindGO<Box>("箱");
	DeleteGO(box);*/
}
bool Game::Start()
{
	//カメラを設定。
	MainCamera().SetTarget({ 0.0f, 70.0f, 0.0f });
	MainCamera().SetNear(10.0f);
	MainCamera().SetFar(10000.0f);
	MainCamera().SetPosition({ 0.0f, 70.0f, 200.0f });
	MainCamera().Update();
	
	NewGO<camera>(0, "カメラ");

	////コインの枚数
	NewGO<CoinHUD>(0, "スコア");
	//平行光源を作成する。
	m_dirLig = NewGO<prefab::CDirectionLight>(0);//ライト
	CVector3 lightDir = { 1, -1, 1 };
	lightDir.Normalize();
	m_dirLig->SetDirection(lightDir);
	m_dirLig->SetColor({ 10.0f, 10.0f, 10.0f, 1.0f });
	LightManager().SetAmbientLight({ 0.2, 0.2, 0.2 });
	GraphicsEngine().GetShadowMap().SetLightDirection(lightDir);

	//NewGO<>(0, "プレイヤー");

	//NewGO<grund>(0, "grund"); //床

	//NewGO<Enemy>(0, "敵");
	//
	//m_blo[0] = NewGO<block>(0, "ブロック"); //ブロック
	//m_blo[0]->m_position.x = 200.0f;
	//m_blo[0]->m_position.y = 200.0f;

	//m_blo[1] = NewGO<block>(0, "ブロック");
	//m_blo[1]->m_position.x = 400.0f;
	//m_blo[1]->m_position.y = 200.0f;

	//m_blo[2] = NewGO<block>(0, "ブロック");
	//m_blo[2]->m_position.x = 600.0f;
	//m_blo[2]->m_position.y = 200.0f;

	//m_blo[3] = NewGO<block>(0, "ブロック");
	//m_blo[3]->m_position.x = 700.0f;
	//m_blo[3]->m_position.y = 200.0f;

	//m_blo[4] = NewGO<block>(0, "ブロック");
	//m_blo[4]->m_position.x = 100.0f;
	//m_blo[4]->m_position.y = 100.0f;
	//m_blo[4]->m_position.z = 200.0f;
	//


	////最初から配置されているコイン
	//Coin* m_coi[3] = { nullptr };
	//m_coi[0] = NewGO<Coin>(0, "コイ");
	//m_coi[0]->m_position.x = 200.0f;
	//m_coi[0]->m_position.y = 400.0f;

	//m_coi[1] = NewGO<Coin>(0, "コイ");
	//m_coi[1]->m_position.x = 400.0f;
	//m_coi[1]->m_position.y = 400.0f;

	////ゴール地点
	//NewGO<hata>(0, "旗");

	

	//NewGO<Box>(0, "箱");
	return true;
}

void Game::Update()
{
	

	//HPが0
	Player* pl = FindGO<Player>("プレイヤー");
	if (pl->hp <= 0 ) {
		NewGO<GameOver>(0, "死んだ");
		m_timer += 5;
		if (m_timer == 500) {
			DeleteGO(this);
			NewGO<title>(0);
			
		}
	}
	if (pl->m_position.y < -100.0) {
		NewGO<GameOver>(0, "死んだ");
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
	

	//クリア
	/*QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		
		CVector3 diff = pl->m_position - ha->m_position;

		if (diff.Length() < 100.0f) {
			Clear_flag = true;
			NewGO<Clear>(0, "クリア");
			m_timer += 5;
			if (m_timer == 500 && Clear_flag == true) {
				NewGO<title>(0);
				DeleteGO(this);
			}
		}
		return true;
	});*/
}