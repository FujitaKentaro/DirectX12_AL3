#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "DebugText.h"


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


//input 
	Input* input_;
//debugText
	DebugText* debugText_;




public:

	//Vector3
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translation_;


	// 単位行列
	Matrix4 matUnit_={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

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

