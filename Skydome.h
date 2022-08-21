#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"


class Skydome {
  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//テクスチャハンドル
	//uint32_t textureHandle_ = 0u;

	//モデル
	Model* model_ = nullptr;
	Vector3 scale = {100.0f, 100.0f, 100.0f};
  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);
};
