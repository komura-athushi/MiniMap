#include "stdafx.h"
#include "GameCamera.h"

#include "Player.h"

GameCamera::GameCamera()
{

}

GameCamera::~GameCamera()
{

}

bool GameCamera::Start()
{
	m_player = FindGO<Player>("player");

	m_toCameraPos = Vector3(0.0f,300.0f,250.0f);
	return true;
}

void GameCamera::Update()
{
	if (m_player == nullptr)
	{
		m_player = FindGO<Player>("player");
		return;
	}

	/*Vector3 target = m_player->GetPosition();
	g_camera3D->SetTarget(target);
	g_camera3D->SetPosition(target + m_toPos);
	*/
	UpdatePositionAndTarget();
}

void GameCamera::UpdatePositionAndTarget()
{
	//カメラを更新。
	//注視点を計算する。
	Vector3 target = m_player->GetPosition();
	//プレイヤの足元からちょっと上を注視点とする。
	target.y += 80.0f;
	target += g_camera3D->GetForward() * 20.0f;

	Vector3 toCameraPosOld = m_toCameraPos;
	//パッドの入力を使ってカメラを回す。
	float x = g_pad[0]->GetRStickXF();
	float y = g_pad[0]->GetRStickYF();
	//Y軸周りの回転
	Quaternion qRot;
	qRot.SetRotationDeg(Vector3::AxisY, 1.5f * x);
	qRot.Apply(m_toCameraPos);
	//X軸周りの回転。
	Vector3 axisX;
	axisX.Cross(Vector3::AxisY, m_toCameraPos);
	axisX.Normalize();
	qRot.SetRotationDeg(axisX, 1.5f * y);
	qRot.Apply(m_toCameraPos);
	//カメラの回転の上限をチェックする。
	//注視点から視点までのベクトルを正規化する。
	//正規化すると、ベクトルの大きさが１になる。
	//大きさが１になるということは、ベクトルから強さがなくなり、方向のみの情報となるということ。
	Vector3 toPosDir = m_toCameraPos;
	toPosDir.Normalize();
	if (toPosDir.y < -0.5f) {
		//カメラが上向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}
	else if (toPosDir.y > 0.8f) {
		//カメラが下向きすぎ。
		m_toCameraPos = toCameraPosOld;
	}


	//視点を計算する。
	Vector3 pos = target + m_toCameraPos;

	//バネカメラに注視点と視点を設定する。
	g_camera3D->SetPosition(pos);
	g_camera3D->SetTarget(target);
}