#include "Player.h"


void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = textureHandle;

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
	
		worldTransform_.Initialize();
	SetTrans();
		
	
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(){


}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection){

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}

/// <summary>
/// ランダム位置セット
/// </summary>
void Player::SetTrans() {

	{
		// XYZの移動量を設定
		Vector3 move = {distT(engine), distT(engine), distT(engine)};
		Vector3 rotatte = {distR(engine), distR(engine), distR(engine)};
		Vector3 scale = {1, 1, 1};

		Matrix4 matWorld_ = Affin::matUnit();

		matWorld_ = Affin::matWorld(move, rotatte, scale);

		worldTransform_.matWorld_ *= matWorld_;

		worldTransform_.TransferMatrix();
	}
}