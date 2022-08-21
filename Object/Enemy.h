#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

// ���@�N���X�̑O���錾
class Player;

enum class Phase {
	None,     // ��~
	Approach, // �ڋ�
	Leave,    // ���E
};

class Enemy {
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
	DebugText* debugText_ = nullptr;

	// ���L����
	Player* player_ = nullptr;

	//�e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	Phase phase_ = Phase::None;
	// ���˃^�C�}�[
	int32_t fireTimer_ = 0;

  public:
	// ���ˊԊu
	static const int kFireInterval = 60;
	// �e���X�g���擾
	const std::list<std::unique_ptr<EnemyBullet>>& GetBullets_() { return bullets_; }
	float r = 2;

  public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);
	void SetPlayer(Player* player);

	/// <summary>
	/// �s��̌v�Z
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	/// <summary>
	/// �e����
	/// </summary>
	void Fire();

	/// <summary>
	/// �ڋ߃t�F�[�Y������
	/// </summary>
	void ApproachInitialize();

	/// <summary>
	/// ���[���h���W���擾
	/// </summary>
	Vector3 GetWorldPosition();

	/// <summary>
	/// �Փ˂����m������Ăяo�����R�[���o�b�N�֐�
	/// </summary>
	void OnCollision();
};