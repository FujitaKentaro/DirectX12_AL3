#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>

#include "PlayerBullet.h"


/// <summary>
/// ���L����
/// </summary>
class Player {
  private:
	//	���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_= nullptr;

	//�e
	PlayerBullet* bullet_ = nullptr;

public:

	////�p�[�cID
 
public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// ���s�ړ�
	/// </summary>
	void Move();
	/// <summary>
	/// ��]�ړ�
	/// </summary>
	void Rotate();

	/// <summary>
	/// �s��̌v�Z
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();
};
