#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// �e �匳
	worldTransform_[PartId::kRoot].Initialize();

	// �q �Ғ�
	worldTransform_[PartId::kSpine].Initialize();
	worldTransform_[PartId::kSpine].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::kSpine].parent_ = &worldTransform_[PartId::kRoot];

	// �㔼�g
	// ��
	worldTransform_[PartId::kChest].Initialize();
	worldTransform_[PartId::kChest].translation_ = {0, 0, 0};
	worldTransform_[PartId::kChest].parent_ = &worldTransform_[PartId::kSpine];
	// ��
	worldTransform_[PartId::kHead].Initialize();
	worldTransform_[PartId::kHead].translation_ = {0, 4.5f, 0};
	worldTransform_[PartId::kHead].parent_ = &worldTransform_[PartId::kChest];
	// ���r
	worldTransform_[PartId::kArmL].Initialize();
	worldTransform_[PartId::kArmL].translation_ = {-4.5f, 0, 0};
	worldTransform_[PartId::kArmL].parent_ = &worldTransform_[PartId::kChest];
	// �E�r
	worldTransform_[PartId::kArmR].Initialize();
	worldTransform_[PartId::kArmR].translation_ = {4.5f, 0, 0};
	worldTransform_[PartId::kArmR].parent_ = &worldTransform_[PartId::kChest];

	//�����g
	// �K
	worldTransform_[PartId::kHip].Initialize();
	worldTransform_[PartId::kHip].translation_ = {0, -4.5f, 0};
	worldTransform_[PartId::kHip].parent_ = &worldTransform_[PartId::kSpine];
	// ����
	worldTransform_[PartId::kLegL].Initialize();
	worldTransform_[PartId::kLegL].translation_ = {4.5f, -4.5f, 0};
	worldTransform_[PartId::kLegL].parent_ = &worldTransform_[PartId::kHip];

	// �E��
	worldTransform_[PartId::kLegR].Initialize();
	worldTransform_[PartId::kLegR].translation_ = {-4.5f, -4.5f, 0};
	worldTransform_[PartId::kLegR].parent_ = &worldTransform_[PartId::kHip];
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update() {
#pragma region �L�����N�^�[�ړ�����

	// �L�����N�^�[�ړ�����
	{
		//�L�����N�^�[�̈ړ��x�N�g��
		Vector3 move = {0, 0, 0};
		// ���s�ړ�
		{ // X����
			if (input_->PushKey(DIK_RIGHT)) {
				move.x = 0.1;
			} else if (input_->PushKey(DIK_LEFT)) {
				move.x = -0.1;
			}
			// Y����
			if (input_->PushKey(DIK_UP)) {
				move.y = 0.1;
			} else if (input_->PushKey(DIK_DOWN)) {
				move.y = -0.1;
			}
		}
		//��]
		{ //�㔼�g
			if (input_->PushKey(DIK_U)) {
				worldTransform_[kChest].rotation_.y += 1;
			} else if (input_->PushKey(DIK_I)) {
				worldTransform_[kChest].rotation_.y += -1;
			}
			//�����g
			if (input_->PushKey(DIK_J)) {
				worldTransform_[kHip].rotation_.y += 1;
			} else if (input_->PushKey(DIK_K)) {
				worldTransform_[kHip].rotation_.y += -1;
			}
		}

		worldTransform_[0].translation_ += move;
		for (int i = 0; i < kNumPartId; i++) {
			PartUpdate(worldTransform_[i]);
		}
	}

#pragma endregion
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(ViewProjection viewProjection) {
	for (int i = 0; i < kNumPartId; i++) {
		if (i < 2) {
			continue;
		}
		model_->Draw(worldTransform_[i], viewProjection, textureHandle_);
	}
}

void Player::PartUpdate(WorldTransform& worldTransform_) {

	// �q�̍X�V
	
	// �R�ړ������s����v�Z
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	// �e�̍s����|���Z���
	if (worldTransform_.parent_ != nullptr) {
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	}
	// �s��̓]��
	worldTransform_.TransferMatrix();
}