#pragma once
class Player: public IGameObject 
{
public:
	Player();
	~Player();
	bool Start() override;
	void Update() override;
	void Render(RenderContext& rc);
	const Vector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �ړ����x�����Z�B
	/// </summary>
	/// <param name="addMoveSpeed">���Z����ړ����x�B</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	/// <summary>
	/// �L�����N�^�[�R���g���[���[���擾�B
	/// </summary>
	/// <returns>�L�����N�^�[�R���g���[���[�B</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}
private:
	/// <summary>
	/// �ړ������B
	/// </summary>
	void Move();
	Vector3							m_position;
	Vector3							m_moveSpeed = Vector3::Zero;
	ModelRender						m_modelRender;
	CharacterController				m_characterController;

};

