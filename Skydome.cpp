#include "Skydome.h"

/// <summary>
/// 初期化
/// </summary>
void Skydome::Initialize(Model* model) {

	
	model_ = model;
	worldTransform_.Initialize();

	worldTransform_.matWorld_ *= MathUtility::Matrix4Scaling(scale.x, scale.y, scale.z);
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 更新
/// </summary>
void Skydome::Update() {}

/// <summary>
/// 描画
/// </summary>
void Skydome::Draw(ViewProjection viewProjection) {
	// 描画
	model_->Draw(worldTransform_, viewProjection );
}
