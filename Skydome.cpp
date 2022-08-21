#include "Skydome.h"

/// <summary>
/// ������
/// </summary>
void Skydome::Initialize(Model* model) {

	
	model_ = model;
	worldTransform_.Initialize();

	worldTransform_.matWorld_ *= MathUtility::Matrix4Scaling(scale.x, scale.y, scale.z);
	worldTransform_.TransferMatrix();
}

/// <summary>
/// �X�V
/// </summary>
void Skydome::Update() {}

/// <summary>
/// �`��
/// </summary>
void Skydome::Draw(ViewProjection viewProjection) {
	// �`��
	model_->Draw(worldTransform_, viewProjection );
}
