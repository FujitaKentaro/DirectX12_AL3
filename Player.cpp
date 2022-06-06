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

	//デバッグテキストの表示
	debugText_->SetPos(40, 50);
	debugText_->Printf(
	  "player : (%f,%f,%f)", worldTransform_.matWorld_.m[3][0], worldTransform_.matWorld_.m[3][1],
	  worldTransform_.matWorld_.m[3][2]);

	Vector3 move = { 0,0,0 };
	Matrix4 matTrans = matUnit_;

	
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

	//worldTransform_.matWorld_ = MathUtility::Matrix4Identity();
	worldTransform_.matWorld_ *=matTrans ;


	// 移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	//範囲を超えない処理
	worldTransform_.matWorld_.m[3][0] = max(worldTransform_.matWorld_.m[3][0], -kMoveLimitX);
	worldTransform_.matWorld_.m[3][0] = min(worldTransform_.matWorld_.m[3][0], +kMoveLimitX);

	worldTransform_.matWorld_.m[3][1] = max(worldTransform_.matWorld_.m[3][1], -kMoveLimitY);
	worldTransform_.matWorld_.m[3][1] = min(worldTransform_.matWorld_.m[3][1], +kMoveLimitY);

	worldTransform_.TransferMatrix();

	
	
	

}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection){
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

}


/*

transformX = 0.0f;
    transformY = 0.0f;
    rotation = 0.0f;
    scale = 1.0f;

    // キー入力

    //平行移動
    if (input_->PushKey(DIK_W)) {
    	transformY += 0.05f;
    }

    if (keys[DIK_S]) {
    	transformY -= 0.05f;
    }

    if (keys[DIK_A]) {
    	transformX -= 0.05f;
    }

    if (keys[DIK_D]) {
    	transformX += 0.05f;
    }

    // 拡大縮小
    if (keys[DIK_Z]) {
    	scale -= 0.1f;
    }

    if (keys[DIK_C]) {
    	scale += 0.1f;
    }

    // 回転
    if (keys[DIK_Q]) {
    	rotation -= PI / 32;
    }

    if (keys[DIK_E]) {
    	rotation += PI / 32;
    }

    // アフィン行列の生成
    affin[0][0] = scale * cos(rotation);
    affin[0][1] = scale * (-sin(rotation));
    affin[0][2] = transformX;

    affin[1][0] = scale * sin(rotation);
    affin[1][1] = scale * cos(rotation);
    affin[1][2] = transformY;

    affin[2][0] = 0.0f;
    affin[2][1] = 0.0f;
    affin[2][2] = 1.0f;

    // アフィン変換
    for (int i = 0; i < _countof(vertices); i++) {
    	vertices[i].x =
    	  vertices[i].x * affin[0][0] + vertices[i].y * affin[0][1] + 1.0f * affin[0][2];
    	vertices[i].y =
    	  vertices[i].x * affin[1][0] + vertices[i].y * affin[1][1] + 1.0f * affin[1][2];
    	vertices[i].z =
    	  vertices[i].x * affin[2][0] + vertices[i].y * affin[2][1] + 1.0f * affin[2][2];
    }
    

*/