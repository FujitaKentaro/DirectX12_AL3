#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
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

		//�ړ����E���W
		const float kMoveLimitX = 35;
		const float kMoveLimitY = 19;

		//�͈͂𒴂��Ȃ�����
		worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
		worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
		worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
		worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

		worldTransform_.translation_ += move;
		//�s��X�V
		MatUpdate(worldTransform_);

		debugText_->SetPos(10,10);
		    debugText_->Printf(
		      "player : x,%f  y,%f z,%f", worldTransform_.translation_.x,
		      worldTransform_.translation_.y, worldTransform_.translation_.z);
	}

#pragma endregion
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(ViewProjection viewProjection) {
	
		model_->Draw(worldTransform_, viewProjection, textureHandle_);
	
}

void Player::MatUpdate(WorldTransform& worldTransform_) {

	// �p�[�c�̍X�V
	
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