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
	SetTrans();
		
	
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

/// <summary>
/// �����_���ʒu�Z�b�g
/// </summary>
void Player::SetTrans() {

	{
		// XYZ�̈ړ��ʂ�ݒ�
		Vector3 move = {distT(engine), distT(engine), distT(engine)};
		Vector3 rotatte = {distR(engine), distR(engine), distR(engine)};
		Vector3 scale = {1, 1, 1};

		Matrix4 matWorld_ = Affin::matUnit();

		matWorld_ = Affin::matWorld(move, rotatte, scale);

		worldTransform_.matWorld_ *= matWorld_;

		worldTransform_.TransferMatrix();
	}
}