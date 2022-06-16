#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>


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
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_= nullptr;

public:

	////パーツID
 // enum PartId {
	//  kRoot,	// 大元
	//  kSpine,	// 脊椎
	//  kChest,	// 胸
	//  kHead,	// 頭
	//  kArmL,	// 左腕
	//  kArmR,	// 右腕
	//  kHip,		// 尻
	//  kLegL,	// 左あし
	//  kLegR,	// 右あし

	//  kNumPartId
 // };


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


	/// <summary>
	/// 行列の計算
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

	
};
