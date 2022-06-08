#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "DebugText.h"
#include "Affin.h"


/// <summary>
/// 自キャラ
/// </summary>
class Player
{
private:


//	ワールド変換データ
	WorldTransform worldTransform_;
//モデル
	Model* model_ = nullptr;
//テクスチャハンドル
	uint32_t textureHandle_ = 0u;

	Affin affin_;

//input 
	Input* input_;
//debugText
	DebugText* debugText_;
	

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

