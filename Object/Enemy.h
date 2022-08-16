#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <memory>
#include <list>

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

	Phase phase_ = Phase::None;

  public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 行列の計算
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

};


