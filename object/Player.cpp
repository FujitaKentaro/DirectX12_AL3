#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();


	   {
		// XYZ�̈ړ��ʂ�ݒ�
		Vector3 move = {2, 2, 2};
		Vector3 rotatte = {45, 45, 45};
		Vector3 scale = {2, 2, 2};

		Matrix4 matWorld_= affin_.matUnit();

		matWorld_ = affin_.matWorld(move,rotatte,scale);

		worldTransform_.matWorld_ *= matWorld_;

		worldTransform_.TransferMatrix();
		}

}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(){


}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

