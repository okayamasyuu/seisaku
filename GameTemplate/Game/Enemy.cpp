#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include "Game.h"
#include "kabe.h"

Enemy::Enemy()
{
}


Enemy::~Enemy()
{
	DeleteGO(m_skinModelRender);
}
bool Enemy::Start()
{
	
    //キャラクターコントローラーを初期化。
	m_charaCon.Init(
		50.0,        //半径
		40.0,       //高さ
		m_position
	);

	//ワイヤーフレーム表示を有効にする
	//lPhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	
	for (int i = 0; i < 4; i++) {
		
		//ボックス形状のゴースト作成する
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //第一引数は座標。
			CQuaternion::Identity,     //第二引数は回転クォータニオン。
			{ 70.0, 10.0, 70.0 }     //第三引数はボックスのサイズ。
		);
	}
	
	
	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/Enemy.cmo");

	m_skinModelRender->SetShadowCasterFlag(true);
	m_moveSpeed.x = 10.0;
	
	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(scale);
	//m_PSObject.CreateMesh(m_position, m_rotion, scale, m_skinModelRender);

	return true;
}
void Enemy::Update()
{

	//エネミーの移動

	m_position += m_moveSpeed;

	if (m_position.x > 900.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = -15.0f;//↓
	}
	if (m_position.z < -900.0f) {
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.x = -15.0f;//←
	}
	if (m_position.x < -900.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 15.0f;//↑
	}
	if (m_position.z > 900.0f) {
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.x = 15.0;//→
		if (m_position.x > 900.0f) {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = -15.0f;//↓
		}
	}
		
	//敵のシステム
	
	Player* PL = FindGO<Player>("プレイヤー");
	CVector3 toPlayer = { 0.0f, 0.0f, 0.0f };  //初期化
	//プレイヤーを追いかける
	//【プレイヤーの座標】－【モンスターの座標】を計算
	//エネミーからプレイヤーに向かって伸びるベクトルを計算する。
	toPlayer = PL->m_position - m_position;


	////
	//dbg::DrawVector(toPlayer, m_position);

	//toPlayerの距離を計算
	float len = toPlayer.Length();

	//距離が～以下になったら追ってくる
	if (len < 550.0f) {

		toPlayer.Normalize();//正規化して１になっている
		toPlayer.x *= 18; //スピード
		toPlayer.z *= 18;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		/*if (PL->m_position.y > 100) {
			m_position.y += 10;
		}*/
	}
	else {
	}
	Player m_play;

	//HPダメージ
		Game* ga = FindGO<Game>("game");
		QueryGOs<Player>("プレイヤー", [&](Player* pl)->bool {
		CVector3 diff = pl->m_position - m_position;
		//if (pl->Junp_flag == false) {
			if (diff.Length() < 17.0f && pl->hp > 0 && ga->Clear_flag == false/* && pl->m_charaCon.IsOnGround()*/) {
				pl->hp--;

				/*diff.Length() < 17.0f&& m_play.GetHP() > 0 && ga->Clear_flag == false)
				m_play.GetHP();*/
			}
			return true;
		//}
	});

		if (m_position.y < -250) {
			DeleteGO(this);
		}
	//キャラクターの座標とゴーストの座標のあたり判定を行う。
	//btCollisionObject& contactObjectはゴーストオブジェクトのこと
		PhysicsWorld().ContactTest(PL->m_charaCon, [&](const btCollisionObject & contactObject) {
			if (m_ghostobj.IsSelf(contactObject)) {
				QueryGOs<kabe>("壁", [&](kabe * ka)->bool {
					/*kabe* ka = FindGO<kabe>("壁");*/

					ka->enemy_count++;
					
					return true;
				});
				DeleteGO(this);    //踏んだら破棄
			}
		});

		//重力
		m_moveSpeed.y -= 400.0f * GameTime().GetFrameDeltaTime();

		//キャラコンに移動速度を与える
		m_position = m_charaCon.Execute(m_moveSpeed);

		//ゴーストをエネミーと一緒に移動させる
		CVector3 pos = m_position;
		pos.y += 150;
		m_ghostobj.SetPosition(pos);
		

		//キャラコンで動かした結果をCSkinModelRenderに反映させる。
	    m_skinModelRender->SetPosition(m_charaCon.GetPosition()); 
		//m_skinModelRender->SetPosition(m_position);
}
