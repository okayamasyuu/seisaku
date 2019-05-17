#include "stdafx.h"
#include "Enemy2.h"
#include "Player.h"
#include "Game.h"
#include "kabe.h"

Enemy2::Enemy2()
{
}


Enemy2::~Enemy2()
{
	DeleteGO(m_skinModelRender);
}
bool Enemy2::Start()
{
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		45.0,        //半径
		40.0,       //高さ
		m_position
	);

	//ワイヤーフレーム表示を有効にする
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	for (int i = 0; i < 4; i++) {

		//ボックス形状のゴースト作成する
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //第一引数は座標。
			CQuaternion::Identity,     //第二引数は回転クォータニオン。
			{ 60.0, 10.0, 60.0 }     //第三引数はボックスのサイズ。
		);
	}


	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/backgound/Enemy.cmo");

	//m_moveSpeed.x = 10.0;

	m_skinModelRender->SetPosition(m_position);
	m_skinModelRender->SetScale(scale);
	//m_PSObject.CreateMesh(m_position, m_rotion, scale, m_skinModelRender);
	return true;
}
void Enemy2::Update()
{
	//エネミーの移動
		
	m_position += m_moveSpeed;

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
	if (len < 500.0f) {

		toPlayer.Normalize();//正規化して１になっている
		toPlayer.x *= 16; //スピード
		toPlayer.z *= 16;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		
			if ( m_charaCon.IsOnGround() /*&& PL->m_position.y > m_position.y*/) {
				m_moveSpeed.y += 300;
			}
	}	
	else {
		toPlayer.x = 0; //スピード
		toPlayer.z = 0;
		m_moveSpeed.x = toPlayer.x;
		m_moveSpeed.z = toPlayer.z;
	}


	//HPダメージ
	Game* ga = FindGO<Game>("game");
	QueryGOs<Player>("プレイヤー", [&](Player * pl)->bool {
		CVector3 diff = pl->m_position - m_position;
		
			if (diff.Length() < 30.0f && pl->hp > 0 && ga->Clear_flag == false ) {
				pl->hp--;
			}
			return true;
		});
	//落ちたら破棄
	if (m_position.y < -500) {
		DeleteGO(this);
	}
	//キャラクターの座標とゴーストの座標のあたり判定を行う。
	//btCollisionObject& contactObjectはゴーストオブジェクトのこと
	PhysicsWorld().ContactTest(PL->m_charaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {
			DeleteGO(this);
		}
		});
	//重力
	m_moveSpeed.y -= 400.0f * GameTime().GetFrameDeltaTime();

	//キャラコンに移動速度を与える
	m_position = m_charaCon.Execute(m_moveSpeed);

	//ゴーストをエネミーと一緒に移動させる
	CVector3 pos = m_position;
	pos.y += 130;
	m_ghostobj.SetPosition(pos);


	//キャラコンで動かした結果をCSkinModelRenderに反映させる。
	m_skinModelRender->SetPosition(m_charaCon.GetPosition());
	//m_skinModelRender->SetPosition(m_position);
}
