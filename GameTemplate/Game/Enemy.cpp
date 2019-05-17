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
	
    //�L�����N�^�[�R���g���[���[���������B
	m_charaCon.Init(
		50.0,        //���a
		40.0,       //����
		m_position
	);

	//���C���[�t���[���\����L���ɂ���
	//lPhysicsWorld().SetDebugDrawMode(btIDebugDraw::DBG_DrawWireframe);
	
	for (int i = 0; i < 4; i++) {
		
		//�{�b�N�X�`��̃S�[�X�g�쐬����
		m_ghostobj.CreateBox(
			ghostPosi = m_position,    //�������͍��W�B
			CQuaternion::Identity,     //�������͉�]�N�H�[�^�j�I���B
			{ 70.0, 10.0, 70.0 }     //��O�����̓{�b�N�X�̃T�C�Y�B
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

	//�G�l�~�[�̈ړ�

	m_position += m_moveSpeed;

	if (m_position.x > 900.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = -15.0f;//��
	}
	if (m_position.z < -900.0f) {
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.x = -15.0f;//��
	}
	if (m_position.x < -900.0f) {
		m_moveSpeed.x = 0.0f;
		m_moveSpeed.z = 15.0f;//��
	}
	if (m_position.z > 900.0f) {
		m_moveSpeed.z = 0.0f;
		m_moveSpeed.x = 15.0;//��
		if (m_position.x > 900.0f) {
			m_moveSpeed.x = 0.0f;
			m_moveSpeed.z = -15.0f;//��
		}
	}
		
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
	if (len < 550.0f) {

		toPlayer.Normalize();//���K�����ĂP�ɂȂ��Ă���
		toPlayer.x *= 18; //�X�s�[�h
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

	//HP�_���[�W
		Game* ga = FindGO<Game>("game");
		QueryGOs<Player>("�v���C���[", [&](Player* pl)->bool {
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
	//�L�����N�^�[�̍��W�ƃS�[�X�g�̍��W�̂����蔻����s���B
	//btCollisionObject& contactObject�̓S�[�X�g�I�u�W�F�N�g�̂���
		PhysicsWorld().ContactTest(PL->m_charaCon, [&](const btCollisionObject & contactObject) {
			if (m_ghostobj.IsSelf(contactObject)) {
				QueryGOs<kabe>("��", [&](kabe * ka)->bool {
					/*kabe* ka = FindGO<kabe>("��");*/

					ka->enemy_count++;
					
					return true;
				});
				DeleteGO(this);    //���񂾂�j��
			}
		});

		//�d��
		m_moveSpeed.y -= 400.0f * GameTime().GetFrameDeltaTime();

		//�L�����R���Ɉړ����x��^����
		m_position = m_charaCon.Execute(m_moveSpeed);

		//�S�[�X�g���G�l�~�[�ƈꏏ�Ɉړ�������
		CVector3 pos = m_position;
		pos.y += 150;
		m_ghostobj.SetPosition(pos);
		

		//�L�����R���œ����������ʂ�CSkinModelRender�ɔ��f������B
	    m_skinModelRender->SetPosition(m_charaCon.GetPosition()); 
		//m_skinModelRender->SetPosition(m_position);
}
