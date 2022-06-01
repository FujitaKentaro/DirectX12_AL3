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

}

/// <summary>
/// 更新
/// </summary>
void Player::Update(){

	Vector3 move = { 0,0,0 };
	Matrix4 matTrans = MathUtility::Matrix4Identity();

	
	if(input_->PushKey(DIK_W)){
		move.y = 0.1f;
	}
	if (input_->PushKey(DIK_S)) {
		move.y = -0.1f;
	}
	if (input_->PushKey(DIK_D)) {
		move.x = 0.1f;
	}
	if (input_->PushKey(DIK_A)) {
		move.x = -0.1f;
	}

	matTrans = MathUtility::Matrix4Translation(move.x, move.y,move.z);
	
	worldTransform_.matWorld_ *=matTrans ;

	worldTransform_.TransferMatrix();

	
	////デバッグテキストの表示
	//debugText_->SetPos(40, 50);
	//debugText_->Printf();
	


}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}
