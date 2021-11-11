#include "stdafx.h"
#include "Game.h"

#include "Player.h"
#include "GameCamera.h"
#include "MovingFloor.h"
#include "Map.h"

namespace 
{
	Vector3		BACKGROUND_SCALE = Vector3(0.7f, 1.0f, 0.7f);
}

bool Game::Start()
{

	m_background.Init("Assets/modelData/sample/background.tkm");
	m_background.SetScale(BACKGROUND_SCALE);
	m_background.Update();

	m_physicsStaticObject.CreateFromModel(m_background.GetModel(), m_background.GetModel().GetWorldMatrix());

	SkyCube* skyCube = NewGO<SkyCube>(0, "skyCube");
	skyCube->SetScale(Vector3::One * 400.0f);

	//NewGOの引数で、Update関数の処理順番を設定する。
	//動く床→プレイヤーの順番にする。
	m_player = NewGO<Player>(1, "player");
	m_gameCamera = NewGO<GameCamera>(2, "gameCamera");
	m_movingFloor = NewGO<MovingFloor>(0, "movingFloor");
	m_movingFloor->SetPosition(Vector3(0.0f, 0.0f, -510.0f));

	//PhysicsWorld::GetInstance()->EnableDrawDebugWireFrame();

	m_map = NewGO<Map>(0, "map");
	
	return true;
}

void Game::Update()
{
	
}

void Game::Render(RenderContext& rc)
{
	
	m_background.Draw(rc);
}