#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>


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

public:

	////�p�[�cID
 // enum PartId {
	//  kRoot,	// �匳
	//  kSpine,	// �Ғ�
	//  kChest,	// ��
	//  kHead,	// ��
	//  kArmL,	// ���r
	//  kArmR,	// �E�r
	//  kHip,		// �K
	//  kLegL,	// ������
	//  kLegR,	// �E����

	//  kNumPartId
 // };


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
	/// �s��̌v�Z
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	
};
