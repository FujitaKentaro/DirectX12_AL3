#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
//#include "WorldTransform.h"
#include "DebugCamera.h"
#include <DirectXMath.h>
#include"Player.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

public: // メンバ関数
  /// <summary>
  /// コンストクラタ
  /// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

private: // メンバ変数
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;
	DebugCamera* debugCamera_ = nullptr;

	//値を表示したい変数
	uint32_t value_ = 0;

	//スプライト
	Sprite* sprite_ = nullptr;

	//3Dモデル
	Model* model_ = nullptr;

	//音声再生ハンドル
	uint32_t voiceHandle_ = 0;

	//サウンドデーターハンドル
	uint32_t soundDataHandle_ = 0;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//字キャラ
	Player* player_ = nullptr;

	//ワールドトランスフォーム
	//WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	//Vector3
	Vector3 scale ;
	Vector3 rotate;
	Vector3 translation;


	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
