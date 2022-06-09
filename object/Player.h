#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <random>

// 乱数シード生成器
static std::random_device seed_gen;
// メルセンヌ・ツイスターの乱数エンジン
static std::mt19937_64 engine(seed_gen());
// 乱数範囲の指定
static std::uniform_real_distribution<float> distT(-10, 10);
static std::uniform_real_distribution<float> distR(0,360);


/// <summary>
/// 自キャラ
/// </summary>
class Player {
  private:
	//	ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	// input
	Input* input_;
	// debugText
	DebugText* debugText_;

  private:

	 /// <summary>
	/// 位置セット
	/// </summary>
	void SetTrans();

  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	
};
