#include "PlayerBullet.h"
#include <cassert>
#include "Affin.h"


/// <summary>
/// ������
/// </summary>
void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("ddddog.png");

	// ���[���h�g�����X�t�H�[��
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;

	worldTransform_.TransferMatrix();

}

/// <summary>
/// �X�V
/// </summary>
void PlayerBullet::Update() {
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);
	worldTransform_.TransferMatrix();

}

/// <summary>
/// �`��
/// </summary>
void PlayerBullet::Draw(const ViewProjection& viewProjection) {
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}