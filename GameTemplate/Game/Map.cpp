#include "stdafx.h"
#include "Map.h"

#include "Player.h"
#include "MovingFloor.h"

namespace
{
	Vector3 MAP_CENTER_POSITION = Vector3(704.0f, 284.0f, 0.0f);

	float MAP_RADIUS = 240.0f;
	float LIMITED_RANGE_IMAGE = 600.0f;
}

Map::Map()
{

}

Map::~Map()
{

}

bool Map::Start()
{
	//マップの黒い画像。
	m_spriteRender.Init("Assets/sprite/map.DDS",512,512);
	m_spriteRender.SetPosition(MAP_CENTER_POSITION);

	//マップ中心の赤い画像。
	m_playerSprite.Init("Assets/sprite/player.dds",50,50);
	m_playerSprite.SetPosition(MAP_CENTER_POSITION);

	//エネミーを表す、黄色い画像。
	m_enemySprite.Init("Assets/sprite/enemy.dds", 35, 35);

	m_movingFloor = FindGO<MovingFloor>("movingFloor");
	m_player = FindGO<Player>("player");

	return true;
}

void Map::Update()
{
	Vector3 playerPosition = m_player->GetPosition();
	Vector3 enemyPosition = m_movingFloor->GetPosition();

	Vector3 mapPosition;

	//マップに表示する範囲に敵がいたら。
	if (WorldPositionConvertToMapPosition(playerPosition, enemyPosition, mapPosition))
	{ 
		//マップに表示するように設定する、
		m_isImage = true;
		//SpriteRenderに座標を設定。
		m_enemySprite.SetPosition(mapPosition);
	}
	//マップに表示する範囲に敵がいなかったら。
	else
	{
		//マップに表示しない。
		m_isImage = false;
	}

	m_spriteRender.Update();
	m_playerSprite.Update();
	m_enemySprite.Update();
}

const bool Map::WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition,Vector3& mapPosition)
{
	//Y座標はマップの座標とは関係ないので、0にする。
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;
	//マップの中心とするオブジェクトとの距離が一定以上離れていたら。
	
	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE * LIMITED_RANGE_IMAGE)
	{
		//表示しないようにする。
		return false;
	}

	//ベクトルの長さを取得。
	float length = diff.Length();

	//カメラの前方向ベクトルから。
	//クォータニオンを生成。
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationY(atan2(-forward.x, forward.z));
	
	//ベクトルにカメラの回転を適用。
	rot.Apply(diff);

	//ベクトルを正規化。
	diff.Normalize();

	//マップの大きさ/距離制限で。
	//ベクトルをマップ座標系に変換する。
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE;
	
	//マップの中央座標と上記ベクトルを加算する。
	mapPosition = Vector3(MAP_CENTER_POSITION.x + diff.x, MAP_CENTER_POSITION.y + diff.z, 0.0f);
	return true;
}

void Map::Render(RenderContext& rc)
{
	m_spriteRender.Draw(rc);
	m_playerSprite.Draw(rc);
	if (m_isImage == false)
	{
		return;
		
	}
	m_enemySprite.Draw(rc);
}