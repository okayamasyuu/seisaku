#include "stdafx.h"
#include "camera.h"
#include "Player.h"

camera::camera()
{
}


camera::~camera()
{
	
}
bool camera::Start()
{
	//Player *play = FindGO<Player>("プレイヤー");
	return true;
}
void camera::Update()
{
	Player *play = FindGO<Player>("プレイヤー");
	 target = play->m_position; //注視点
	target.y += 50.0f;

	//視点計算
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	/*CVector3*/ camePos = target + Pos; //キャラクタを斜め上から見ているような視点にする
	camePos = target;

	//視点の場所
	camePos.y += 400.0f;
	camePos.z -= 800.0f;

	

	MainCamera().SetTarget(target);  //注視点
	MainCamera().SetPosition(camePos); //視点
	//MainCamera().SetViewAngle();//画角
	MainCamera().Update();
	
}
