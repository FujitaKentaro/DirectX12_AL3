#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "EnemyBullet.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <list>
#include <memory>

enum class Phase {
	None,     // 停止
	Approach, // 接近
	Leave,    // 離脱
};

class Enemy {
  private:
	//	ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_ = nullptr;

	//弾
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	Phase phase_ = Phase::None;
	// 発射タイマー
	int32_t fireTimer_ = 0;
  public:
	// 発射間隔
	static const int kFireInterval = 60;

  public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 行列の計算
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	/// <summary>
	/// 弾発射
	/// </summary>
	void Fire();

	/// <summary>
	/// 接近フェーズ初期化
	/// </summary>
	void ApproachInitialize();
};
