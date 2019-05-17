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
	//�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		45.0,        //���a
		40.0,       //����
		m_position
	);

	//���C���[�t���[���\����L���ɂ���
	//PhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);

	for (int i = 0; i < 4; i++) {

		//�{�b�N�X�`��̃S�[�X�g�쐬����
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //�������͍��W�B
			CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
			{ 60.0, 10.0, 60.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
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
	//�G�l�~�[�̈ړ�
		
	m_position += m_moveSpeed;

	//�G�̃V�X�e��

	Player* PL = FindGO<Player>("�v���C���[");
	CVector3 toPlayer = { 0.0f, 0.0f, 0.0f };  //������
	//�v���C���[��ǂ�������
	//�y�v���C���[�̍��W�z�|�y�����X�^�[�̍��W�z���v�Z
	//�G�l�~�[����v���C���[�Ɍ������ĐL�т�x�N�g�����v�Z����B
	toPlayer = PL->m_position - m_position;


	////
	//dbg::DrawVector(toPlayer, m_position);

	//toPlayer�̋������v�Z
	float len = toPlayer.Length();

	//�������`�ȉ��ɂȂ�����ǂ��Ă���
	if (len < 500.0f) {

		toPlayer.Normalize();//���K�����ĂP�ɂȂ��Ă���
		toPlayer.x *= 16; //�X�s�[�h
		toPlayer.z *= 16;
		m_moveSpeed.x += toPlayer.x;
		m_moveSpeed.z += toPlayer.z;
		
			if ( m_charaCon.IsOnGround() /*&& PL->m_position.y > m_position.y*/) {
				m_moveSpeed.y += 300;
			}
	}	
	else {
		toPlayer.x = 0; //�X�s�[�h
		toPlayer.z = 0;
		m_moveSpeed.x = toPlayer.x;
		m_moveSpeed.z = toPlayer.z;
	}


	//HP�_���[�W
	Game* ga = FindGO<Game>("game");
	QueryGOs<Player>("�v���C���[", [&](Player * pl)->bool {
		CVector3 diff = pl->m_position - m_position;
		
			if (diff.Length() < 30.0f && pl->hp > 0 && ga->Clear_flag == false ) {
				pl->hp--;
			}
			return true;
		});
	//��������j��
	if (m_position.y < -500) {
		DeleteGO(this);
	}
	//�L�����N�^�[�̍��W�ƃS�[�X�g�̍��W�̂����蔻����s���B
	//btCollisionObject& contactObject�̓S�[�X�g�I�u�W�F�N�g�̂���
	PhysicsWorld().ContactTest(PL->m_charaCon, [&](const btCollisionObject & contactObject) {
		if (m_ghostobj.IsSelf(contactObject)) {
			DeleteGO(this);
		}
		});
	//�d��
	m_moveSpeed.y -= 400.0f * GameTime().GetFrameDeltaTime();

	//�L�����R���Ɉړ����x��^����
	m_position = m_charaCon.Execute(m_moveSpeed);

	//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
	CVector3 pos = m_position;
	pos.y += 130;
	m_ghostobj.SetPosition(pos);


	//�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	m_skinModelRender->SetPosition(m_charaCon.GetPosition());
	//m_skinModelRender->SetPosition(m_position);
}
