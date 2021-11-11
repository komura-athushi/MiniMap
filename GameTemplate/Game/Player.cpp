#include "stdafx.h"
#include "Player.h"

Player::Player()
{

}

Player::~Player()
{

}

bool Player::Start()
{
	m_modelRender.Init("Assets/modelData/unityChan.tkm");
	m_characterController.Init(20.0f,
		100.0f,
		m_position);
	return true;
}

void Player::Update()
{
	Move();

	m_modelRender.Update();
}

void Player::Move()
{
	//���̃t���[���̈ړ��ʂ����߂�B
	//���X�e�B�b�N�̓��͗ʂ��󂯎��B
	float lStick_x = g_pad[0]->GetLStickXF();
	float lStick_y = g_pad[0]->GetLStickYF();
	//�J�����̑O�������ƉE�������擾�B
	Vector3 cameraForward = g_camera3D->GetForward();
	Vector3 cameraRight = g_camera3D->GetRight();
	//XZ���ʂł̑O�������A�E�����ɕϊ�����B
	cameraForward.y = 0.0f;
	cameraForward.Normalize();
	cameraRight.y = 0.0f;
	cameraRight.Normalize();
	//XZ�����̈ړ����x���N���A�B
	m_moveSpeed += cameraForward * lStick_y * 500.0f;	//�������ւ̈ړ����x�����Z�B
	m_moveSpeed += cameraRight * lStick_x * 500.0f;		//�E�����ւ̈ړ����x�����Z�B

	if (g_pad[0]->IsTrigger(enButtonA) //A�{�^���������ꂽ��
		&& m_characterController.IsOnGround()  //���A�n�ʂɋ�����
		) {
		//�W�����v����B
		m_moveSpeed.y = 400.0f;	//������ɑ��x��ݒ肵�āA
	}

	m_moveSpeed.y -= 980.0f * g_gameTime->GetFrameDeltaTime();
	//�L�����N�^�[�R���g���[���[���g�p���āA���W���X�V�B

	m_position = m_characterController.Execute(m_moveSpeed, g_gameTime->GetFrameDeltaTime());
	if (m_characterController.IsOnGround()) {
		//�n�ʂɂ����B
		m_moveSpeed.y = 0.0f;
	}

	//���W��ݒ�B
	m_modelRender.SetPosition(m_position);

	//������0�ɂ���B
	m_moveSpeed.x = 0.0f;
	m_moveSpeed.z = 0.0f;
}

void Player::Render(RenderContext& rc)
{
	m_modelRender.Draw(rc);
}