#pragma once

class MovingFloor;
class Player;

class Map : public IGameObject
{
public:
	Map();
	~Map();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
private:
	/// <summary>
	/// ワールド座標系からマップ座標系に変換。
	/// </summary>
	/// <param name="worldCenterPosition">マップの中心とするオブジェクトのワールド座標。</param>
	/// <param name="worldPosition">マップに表示したいオブジェクトのワールド座標。</param>
	/// <param name="mapPosition">変換した後のマップ座標。</param>
	/// <returns>マップに表示する座標ならtrue。</returns>
	const bool WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition, Vector3& mapPosition);
	SpriteRender				m_spriteRender;
	SpriteRender				m_playerSprite;
	SpriteRender				m_enemySprite;

	MovingFloor*				m_movingFloor = nullptr;
	Player*						m_player = nullptr;
	bool						m_isImage = false;
};

