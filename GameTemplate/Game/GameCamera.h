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
	//���_�ƒ����_���X�V����B
 	void UpdatePositionAndTarget();
	Player* m_player = nullptr;
	Vector3	m_toCameraPos;
};

