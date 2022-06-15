#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

// �����V�[�h������
static std::random_device seed_gen;
// �����Z���k�E�c�C�X�^�[�̗����G���W��
static std::mt19937_64 engine(seed_gen());
// �����͈͂̎w��
static std::uniform_real_distribution<float> distT(-10, 10);
static std::uniform_real_distribution<float> distR(0,360);


/// <summary>
/// ���L����
/// </summary>
class Player {
  private:
	//	���[���h�ϊ��f�[�^
	WorldTransform worldTransform_[10];
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// input
	Input* input_;
	// debugText
	DebugText* debugText_;

public:

	//�p�[�cID
  enum PartId {
	  kRoot,	// �匳
	  kSpine,	// �Ғ�
	  kChest,	// ��
	  kHead,	// ��
	  kArmL,	// ���r
	  kArmR,	// �E�r
	  kHip,		// �K
	  kLegL,	// ������
	  kLegR,	// �E����

	  kNumPartId
  };

  private:

	 /// <summary>
	/// �ʒu�Z�b�g
	/// </summary>
	void SetTrans();

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

	void PartUpdate(WorldTransform& worldTransfom);

	
};
