#include "RailCamera.h"

/// <summary>
/// 初期化
/// </summary>
void RailCamera::Initialize(Vector3 wTrans, Vector3 rad) {
	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = wTrans;
	worldTransform_.rotation_ = rad;
	

	//viewProjection_.farZ = 1000;
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();
}

/// <summary>
/// 更新
/// </summary>
void RailCamera::Update() {

	Move();
	Rotate();
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	viewProjection_.eye = worldTransform_.translation_;
	// ワールド前方ベクトル
	Vector3 forward(0, 0, 1);
	forward = MathUtility::Vector3Transform(forward, worldTransform_.matWorld_);
	// 視点から前方に適当な距離進んだ位置が注視点
	forward += viewProjection_.eye;
	viewProjection_.target = forward;
	// ワールド上方ベクトル
	Vector3 up(0, 1, 0);
	// レールカメラの回転を反映（レールカメラの上方ベクトル）
	viewProjection_.up = MathUtility::Vector3Transform(up, worldTransform_.matWorld_);
	// ビュープロジェクションの更新
	viewProjection_.UpdateMatrix();

	debugText_->SetPos(30, 90);
	debugText_->Printf(
	  "eye : x,%f  y,%f z,%f", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	debugText_->SetPos(10, 110);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 130);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);
	debugText_->SetPos(10, 150);
	debugText_->Printf("farZ : %f", viewProjection_.farZ);
}

/// <summary>
/// 移動
/// </summary>
void RailCamera::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 平行移動
	{ // X方向
		if (input_->PushKey(DIK_RIGHT)) {
			move.z = 0.1f;
		} else if (input_->PushKey(DIK_LEFT)) {
			move.z = -0.1f;
		}
		// Y方向
		if (input_->PushKey(DIK_UP)) {
			move.y = 0.1f;
		} else if (input_->PushKey(DIK_DOWN)) {
			move.y = -0.1f;
		}
	}

	worldTransform_.translation_ += move;
}

/// <summary>
/// 回転
/// </summary>
void RailCamera::Rotate() {
	Vector3 rot = {0, 0, 0};
	if (input_->PushKey(DIK_8)) {
		rot.y = 0.1f;
	}
	if (input_->PushKey(DIK_9)) {
		rot.y = -0.1f;
	}
	worldTransform_.rotation_.y += rot.y;
}

/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 RailCamera::GetWorldPosition() {
	//
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}