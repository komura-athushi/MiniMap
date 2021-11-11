#pragma once

class Player;
class GameCamera;
class MovingFloor;
class Map;

class Game : public IGameObject
{
public:
	Game() {}
	~Game() {}
	bool Start();
	void Update();
	void Render(RenderContext& rc);
private:
	ModelRender				m_background;
	PhysicsStaticObject		m_physicsStaticObject;
	Player*					m_player = nullptr;
	GameCamera*				m_gameCamera = nullptr;
	MovingFloor*			m_movingFloor = nullptr;
	Map*					m_map = nullptr;
};

