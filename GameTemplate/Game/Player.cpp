#include "stdafx.h"
#include "Player.h"
#include "title.h"
#include "block.h"
#include "Coin.h"
#include "Game.h"
#include "camera.h"
#include "GameOver.h"
#include "Enemy.h"

Player::Player()
{
}


Player::~Player()
{
	DeleteGO(m_skinModelRender);
	DeleteGO(font);
}
bool Player::Start()
{
	
	//キャラクターコントローラーを初期化。
	m_charaCon.Init(
		20.0,        //半径 大きさ
		100.0,       //高さ
		m_position
	);

	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Black);

	font->SetPosition({ -320.0f, 300.0f }); //位置


	

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");

	//影を落とす側　SetShadowCasterFlag
	m_skinModelRender->SetShadowCasterFlag(true);
	return true;
}
void Player::Update()
{
	//HP
	wchar_t text[256];
	swprintf(text, L"HP%02d", hp);

	font->SetText(text);
	font->SetPosition({ -320, 300 });

	/*if (m_position.y = -150) {
		NewGO<GameOver>(0);
		DeleteGO(this);
		NewGO<title>(0);
	}*/

	CPad& pad = Pad(0);
	m_moveSpeed.x = pad.GetLStickXF() * 750.0f;
	m_moveSpeed.z = pad.GetLStickYF() * 750.0f;

	//ゲーム数学を参考にしたプログラム
	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる
	//m_moveSpeed.x / m_moveSpeed.zの結果はtanθになる。
	//atan2を使用して、角度を求めている。
	//ボタンを押した方向に回転（X軸とY軸だけ）する（向く）
	/*auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 1.0) {
		return;
	}
	rotat.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));*/

	//atan2はtanθの値を角度(ラジアン単位)に変換してくれる
	//押した方向に回転する、斜めの方向にも向く
	 angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	 
	 //ジャンプ
	 //Aボタンが押されていて、かつ地面にいたら Jキー
	 if (Pad(0).IsPress(enButtonA) && m_charaCon.IsOnGround()) {
		 m_moveSpeed.y += 565.0;
	
	 }
	
	//サンプル１２
	
	//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
	//このフレームではキャラは移動していないので旋回する必要はない。
	if ( fabsf( m_moveSpeed.x ) < 0.001f
		&& fabsf( m_moveSpeed.z ) < 0.001f 
		&& fabsf( m_moveSpeed.y ) < 0.001f) {
		return;
	}
	
	//m_moveSpeed.xとm_moveSpeed.zの絶対値がともに0.001以下ということは
	//このフレームではキャラは移動していないので旋回する必要はない。
	
	//カメラ
	//camera* came = FindGO<camera>("カメラ");
	//上下に移動するコード
	//注視点から視点のベクトルを求める
	//カメラに向いた方向に進む
	//CVector3 cameraDir = came->target - came->camePos;

	//cameraDir.Normalize();
	//m_position += cameraDir * 2.5f * pad.GetRStickYF();

	//右左に移動するコード
	//カメラの横ベクトルを求める
	//CVector3 cameraDirX;

	//カメラの進行方向と上ベクトルとの外積を計算する
	//外積は二つのベクトルに直行する
	//ベクトルを求めることができる

	//cameraDirX.Cross({0.0, 1.0, 0.0}, cameraDir);
	//cameraDirX.Normalize();
	//m_position += cameraDirX * 2.5f * pad.GetRStickXF();

	
	//重力
	m_moveSpeed.y -= 1200.0f * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//キャラコンに移動速度を与える
	
	m_skinModelRender->SetPosition(m_position);//プレイヤーに移動を教える

	//押した方向に回転を教える
	//rotat.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));

	//斜めの方向にも回転を教える　-angleにすると向かせたい方向の
	//逆に向く
	rotat.SetRotation(CVector3::AxisY, angle);

	m_skinModelRender->SetRotation(rotat);
	
}
