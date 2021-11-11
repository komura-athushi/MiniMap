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
	//�}�b�v�̍����摜�B
	m_spriteRender.Init("Assets/sprite/map.DDS",512,512);
	m_spriteRender.SetPosition(MAP_CENTER_POSITION);

	//�}�b�v���S�̐Ԃ��摜�B
	m_playerSprite.Init("Assets/sprite/player.dds",50,50);
	m_playerSprite.SetPosition(MAP_CENTER_POSITION);

	//�G�l�~�[��\���A���F���摜�B
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

	//�}�b�v�ɕ\������͈͂ɓG��������B
	if (WorldPositionConvertToMapPosition(playerPosition, enemyPosition, mapPosition))
	{ 
		//�}�b�v�ɕ\������悤�ɐݒ肷��A
		m_isImage = true;
		//SpriteRender�ɍ��W��ݒ�B
		m_enemySprite.SetPosition(mapPosition);
	}
	//�}�b�v�ɕ\������͈͂ɓG�����Ȃ�������B
	else
	{
		//�}�b�v�ɕ\�����Ȃ��B
		m_isImage = false;
	}

	m_spriteRender.Update();
	m_playerSprite.Update();
	m_enemySprite.Update();
}

const bool Map::WorldPositionConvertToMapPosition(Vector3 worldCenterPosition, Vector3 worldPosition,Vector3& mapPosition)
{
	//Y���W�̓}�b�v�̍��W�Ƃ͊֌W�Ȃ��̂ŁA0�ɂ���B
	worldCenterPosition.y = 0.0f;
	worldPosition.y = 0.0f;
	Vector3 diff = worldPosition - worldCenterPosition;
	//�}�b�v�̒��S�Ƃ���I�u�W�F�N�g�Ƃ̋��������ȏ㗣��Ă�����B
	
	if (diff.LengthSq() >= LIMITED_RANGE_IMAGE * LIMITED_RANGE_IMAGE)
	{
		//�\�����Ȃ��悤�ɂ���B
		return false;
	}

	//�x�N�g���̒������擾�B
	float length = diff.Length();

	//�J�����̑O�����x�N�g������B
	//�N�H�[�^�j�I���𐶐��B
	Vector3 forward = g_camera3D->GetForward();
	Quaternion rot;
	rot.SetRotationY(atan2(-forward.x, forward.z));
	
	//�x�N�g���ɃJ�����̉�]��K�p�B
	rot.Apply(diff);

	//�x�N�g���𐳋K���B
	diff.Normalize();

	//�}�b�v�̑傫��/���������ŁB
	//�x�N�g�����}�b�v���W�n�ɕϊ�����B
	diff *= length * MAP_RADIUS / LIMITED_RANGE_IMAGE;
	
	//�}�b�v�̒������W�Ə�L�x�N�g�������Z����B
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