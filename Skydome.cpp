#include "Skydome.h"

/// <summary>
/// èâä˙âª
/// </summary>
void Skydome::Initialize(Model* model) {

	
	model_ = model;
	worldTransform_.Initialize();

	worldTransform_.matWorld_ *= MathUtility::Matrix4Scaling(scale.x, scale.y, scale.z);
	worldTransform_.TransferMatrix();
}

/// <summary>
/// çXêV
/// </summary>
void Skydome::Update() {}

/// <summary>
/// ï`âÊ
/// </summary>
void Skydome::Draw(ViewProjection viewProjection) {
	// ï`âÊ
	model_->Draw(worldTransform_, viewProjection );
}
