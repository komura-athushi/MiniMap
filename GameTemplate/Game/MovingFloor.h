#pragma once

class MovingFloor : public IGameObject
{
public:
	MovingFloor();
	~MovingFloor();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc) override;
	/// <summary>
	/// ���W��ݒ�B
	/// </summary>
	/// <param name="position">���W�B</param>
	void SetPosition(const Vector3& position)
	{
		m_position = position;
	}
	const Vector3& GetPosition() const
	{
		return m_position;
	}
private:
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();
	Vector3					m_position;
	Vector3					m_firstPosition;
	ModelRender				m_modelRender;
	enum enMovingFloorState
	{
		enMovingFloorState_MovingRight,
		enMovingFloorState_MovingLeft
	};
	enMovingFloorState		m_MovingFloorState = enMovingFloorState_MovingRight;

};

