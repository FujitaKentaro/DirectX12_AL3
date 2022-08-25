#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.png");
	

	// 3Dレティクルのワールドトランスフォームの初期化
	worldTransform3DReticle_.Initialize();

	//スプライト生成
	sprite2DReticle_.reset(
	  Sprite::Create(textureReticle, Vector2{640, 360}, Vector4{1, 1, 1, 1}, Vector2(0.5, 0.5)));

	// worldTransform_.parent_ = &cameraWorldTransform_;
	Vector3 move(0, 0, 20);

	// シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = move;
	worldTransform_.matWorld_ = MathUtility::Matrix4Translation(
	  worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

/// <summary>
/// 更新
/// </summary>
void Player::Update(ViewProjection viewprojection) {

	// デスフラグの立った弾を削除
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

#pragma region キャラクター移動処理

	// キャラクター移動処理
	Move();
	Rotate();

	//行列更新
	MatUpdate(worldTransform_);

	//キャラ攻撃
	Attack();

	//弾更新
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//自機のワールド座標から3Dレティクルのワールド座標を計算
	{
		//自機から3Dレティクルへの距離
		const float kDistancePlayerTo3DReticle = 50.0f;
		//自機から3Dレティクルへのオフセット(Z+向き)
		Vector3 offset = {0, 0, 1.0f};
		//自機のワールド行列の回転を反映
		offset = Affin::VecMat(offset, worldTransform_.matWorld_);
		//ベクトルの長さを整える
		float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
		if (len != 0) {
			offset /= len;
		}
		offset *= kDistancePlayerTo3DReticle;
		worldTransform3DReticle_.translation_ = offset;
		worldTransform3DReticle_.matWorld_ = Affin::matTrans(worldTransform_.translation_);
		worldTransform3DReticle_.TransferMatrix();
	}
	// 3Dレティクルのワールド座標から2Dレティクルのスクリーン座標を計算
	{
		Vector3 positionReticle = Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_);

		//ビューポート行列
		Matrix4 matViewport = {
		  640, 0, 0, 0, 0, -360, 0, 0, 0, 0, 1, 0, 640, 360, 0, 1,
		};

		//ビューポート行列
		Matrix4 matViewProjectionViewport;
		matViewProjectionViewport = viewprojection.matView;
		matViewProjectionViewport *= viewprojection.matProjection;
		matViewProjectionViewport *= matViewport;

		//ワールド→スクリーン座標変換(ここで3Dから2Dになる)
		positionReticle = Affin::wDivision(positionReticle, matViewProjectionViewport);

		//スプライトのレティクルに座標設定
		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

		debugText_->SetPos(100, 100);
		debugText_->Printf("X:%f,Y:%f", positionReticle.x, positionReticle.y);
	}

	debugText_->SetPos(10, 10);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

	// debugText_->SetPos(10, 230);
	// debugText_->Printf(
	//   "親 : x,%f  y,%f z,%f", worldTransform_.parent_->matWorld_.m[3][0],
	//   worldTransform_.parent_->matWorld_.m[3][1], worldTransform_.parent_->matWorld_.m[3][3]);
#pragma endregion
}

/// <summary>
/// 描画
/// </summary>
void Player::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
	//弾描画
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::MatUpdate(WorldTransform& worldTransform_) {

	// パーツの更新

	// ３移動合成行列を計算
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	// 親の行列を掛け算代入

	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	// 行列の転送
	worldTransform_.TransferMatrix();
}

/// <summary>
/// 動作
/// </summary>
void Player::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	// 平行移動
	{ // X方向
		if (input_->PushKey(DIK_D)) {
			move.x = 0.1f;
		} else if (input_->PushKey(DIK_A)) {
			move.x = -0.1f;
		}
		// Y方向
		if (input_->PushKey(DIK_W)) {
			move.y = 0.1f;
		} else if (input_->PushKey(DIK_S)) {
			move.y = -0.1f;
		}
		// Z方向
		if (input_->PushKey(DIK_3)) {
			move.z = 0.1f;
		} else if (input_->PushKey(DIK_4)) {
			move.z = -0.1f;
		}
	}

	//移動限界座標
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ += move;
}

/// <summary>
/// 回転移動
/// </summary>
void Player::Rotate() {
	Vector3 rotate = {0, 0, 0};

	// 回転
	{ // X方向
		if (input_->PushKey(DIK_Q)) {
			rotate.x = 1;
		} else if (input_->PushKey(DIK_E)) {
			rotate.x = -1;
		}
		// Y方向
		if (input_->PushKey(DIK_1)) {
			rotate.y = 1;
		} else if (input_->PushKey(DIK_2)) {
			rotate.y = -1;
		}
	}

	//移動限界座標
	const float kRotateLimitX = 80;
	const float kRotateLimitY = 80;

	//範囲を超えない処理
	worldTransform_.rotation_.x = max(worldTransform_.rotation_.x, -kRotateLimitX);
	worldTransform_.rotation_.x = min(worldTransform_.rotation_.x, +kRotateLimitX);
	worldTransform_.rotation_.y = max(worldTransform_.rotation_.y, -kRotateLimitY);
	worldTransform_.rotation_.y = min(worldTransform_.rotation_.y, +kRotateLimitY);

	worldTransform_.rotation_ += rotate;
}

/// <summary>
/// 攻撃
/// </summary>
void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		//弾の速度
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// 速度ベクトルを自機の向きに合わせて回転させる
		velocity = Affin::VecMat(velocity, worldTransform_.parent_->matWorld_);
		velocity = Affin::VecMat(velocity, worldTransform_.matWorld_);

		// 弾を生成し、初期化
		Vector3 playerRot, playerPos;
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		// 平行
		playerPos = worldTransform_.parent_->translation_;
		playerPos += worldTransform_.translation_;
		// 回転
		playerRot = worldTransform_.parent_->rotation_;
		playerRot += worldTransform_.rotation_;

		Vector3 plPos, retPos;

		retPos = Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_);
		plPos = Affin::GetWorldTrans(worldTransform_.matWorld_);

		velocity = MathUtility::operator-(retPos, plPos);

		float len =
		  sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
		if (len != 0) {
			velocity /= len;
		}
		velocity *= kBulletSpeed;

		// 弾の初期化
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// 弾を登録する
		bullets_.push_back(std::move(newBullet));
	}
}

/// <summary>
/// ワールド座標を取得
/// </summary>
Vector3 Player::GetWorldPosition() {
	//
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

/// <summary>
/// 衝突を検知したら呼び出されるコールバック関数
/// </summary>
void Player::OnCollision() {}

/// <summary>
/// UI描画
/// </summary>
void Player::DrawUI() { sprite2DReticle_->Draw(); }