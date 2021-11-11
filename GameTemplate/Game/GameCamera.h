#pragma once

class Player;

class GameCamera : public IGameObject
{
public:
	GameCamera();
	~GameCamera();
	bool Start() override;
	void Update() override;
private:
	//視点と注視点を更新する。
 	void UpdatePositionAndTarget();
	Player* m_player = nullptr;
	Vector3	m_toCameraPos;
};

