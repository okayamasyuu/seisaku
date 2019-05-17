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
	
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		20.0,        //���a �傫��
		100.0,       //����
		m_position
	);

	font = NewGO<prefab::CFontRender>(0);
	font->SetShadowParam(true, 2.0f, CVector4::Black);

	font->SetPosition({ -320.0f, 300.0f }); //�ʒu


	

	m_skinModelRender = NewGO<prefab::CSkinModelRender>(0);
	m_skinModelRender->Init(L"modelData/unityChan.cmo");

	//�e�𗎂Ƃ����@SetShadowCasterFlag
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

	//�Q�[�����w���Q�l�ɂ����v���O����
	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����
	//m_moveSpeed.x / m_moveSpeed.z�̌��ʂ�tan�ƂɂȂ�B
	//atan2���g�p���āA�p�x�����߂Ă���B
	//�{�^���������������ɉ�]�iX����Y�������j����i�����j
	/*auto moveSpeedXZ = m_moveSpeed;
	moveSpeedXZ.y = 0.0f;
	moveSpeedXZ.Normalize();
	if (moveSpeedXZ.LengthSq() < 1.0) {
		return;
	}
	rotat.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));*/

	//atan2��tan�Ƃ̒l���p�x(���W�A���P��)�ɕϊ����Ă����
	//�����������ɉ�]����A�΂߂̕����ɂ�����
	 angle = atan2(m_moveSpeed.x, m_moveSpeed.z);
	 
	 //�W�����v
	 //A�{�^����������Ă��āA���n�ʂɂ����� J�L�[
	 if (Pad(0).IsPress(enButtonA) && m_charaCon.IsOnGround()) {
		 m_moveSpeed.y += 565.0;
	
	 }
	
	//�T���v���P�Q
	
	//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
	//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
	if ( fabsf( m_moveSpeed.x ) < 0.001f
		&& fabsf( m_moveSpeed.z ) < 0.001f 
		&& fabsf( m_moveSpeed.y ) < 0.001f) {
		return;
	}
	
	//m_moveSpeed.x��m_moveSpeed.z�̐�Βl���Ƃ���0.001�ȉ��Ƃ������Ƃ�
	//���̃t���[���ł̓L�����͈ړ����Ă��Ȃ��̂Ő��񂷂�K�v�͂Ȃ��B
	
	//�J����
	//camera* came = FindGO<camera>("�J����");
	//�㉺�Ɉړ�����R�[�h
	//�����_���王�_�̃x�N�g�������߂�
	//�J�����Ɍ����������ɐi��
	//CVector3 cameraDir = came->target - came->camePos;

	//cameraDir.Normalize();
	//m_position += cameraDir * 2.5f * pad.GetRStickYF();

	//�E���Ɉړ�����R�[�h
	//�J�����̉��x�N�g�������߂�
	//CVector3 cameraDirX;

	//�J�����̐i�s�����Ə�x�N�g���Ƃ̊O�ς��v�Z����
	//�O�ς͓�̃x�N�g���ɒ��s����
	//�x�N�g�������߂邱�Ƃ��ł���

	//cameraDirX.Cross({0.0, 1.0, 0.0}, cameraDir);
	//cameraDirX.Normalize();
	//m_position += cameraDirX * 2.5f * pad.GetRStickXF();

	
	//�d��
	m_moveSpeed.y -= 1200.0f * GameTime().GetFrameDeltaTime();

	m_position = m_charaCon.Execute(m_moveSpeed);//�L�����R���Ɉړ����x��^����
	
	m_skinModelRender->SetPosition(m_position);//�v���C���[�Ɉړ���������

	//�����������ɉ�]��������
	//rotat.SetRotation(CVector3::Up, atan2f(moveSpeedXZ.x, moveSpeedXZ.z));

	//�΂߂̕����ɂ���]��������@-angle�ɂ���ƌ���������������
	//�t�Ɍ���
	rotat.SetRotation(CVector3::AxisY, angle);

	m_skinModelRender->SetRotation(rotat);
	
}
