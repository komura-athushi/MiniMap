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
	/// 移動速度を加算。
	/// </summary>
	/// <param name="addMoveSpeed">加算する移動速度。</param>
	void AddMoveSpeed(const Vector3& addMoveSpeed)
	{
		m_moveSpeed += addMoveSpeed;
	}
	/// <summary>
	/// キャラクターコントローラーを取得。
	/// </summary>
	/// <returns>キャラクターコントローラー。</returns>
	CharacterController& GetCharacterController()
	{
		return m_characterController;
	}
private:
	/// <summary>
	/// 移動処理。
	/// </summary>
	void Move();
	Vector3							m_position;
	Vector3							m_moveSpeed = Vector3::Zero;
	ModelRender						m_modelRender;
	CharacterController				m_characterController;

};

