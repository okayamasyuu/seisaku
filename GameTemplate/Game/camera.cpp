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
	//Player *play = FindGO<Player>("�v���C���[");
	return true;
}
void camera::Update()
{
	Player *play = FindGO<Player>("�v���C���[");
	 target = play->m_position; //�����_
	target.y += 50.0f;

	//���_�v�Z
	CVector3 Pos = { 0.0f, 50.0f, 100.0f };
	/*CVector3*/ camePos = target + Pos; //�L�����N�^���΂ߏォ�猩�Ă���悤�Ȏ��_�ɂ���
	camePos = target;

	//���_�̏ꏊ
	camePos.y += 400.0f;
	camePos.z -= 800.0f;

	

	MainCamera().SetTarget(target);  //�����_
	MainCamera().SetPosition(camePos); //���_
	//MainCamera().SetViewAngle();//��p
	MainCamera().Update();
	
}
