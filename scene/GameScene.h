#pragma once

#include "Audio.h"
#include "DebugCamera.h"
#include "DebugText.h"
#include "DirectXCommon.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"

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

	

	Vector3 startLineX_[5] = {
	  {10,  0, -10},
      {5,   0, -10},
      {0,   0, -10},
      {-5,  0, -10},
      {-10, 0, -10},
	};
	Vector3 endtLineX_[5] = {
	  {10,  0, 10},
      {5,   0, 10},
      {0,   0, 10},
      {-5,  0, 10},
      {-10, 0, 10},
	};
	Vector3 startLineZ_[5] = {
	  {10,  0, 10 },
      {10,  0, 5  },
      {-10, 0, -0 },
      {-10, 0, -5 },
      {-10, 0, -10},
	};
	Vector3 endtLineZ_[5] = {
	  {-10, 0, 10 },
      {-10, 0, 5  },
      {10,  0, 0  },
      {10,  0, -5 },
      {10,  0, -10},
	};

	Vector4 coloer[8] = {
	  {255, 255, 255, 255},
      {0,   0,   0,   255},
      {255, 0,   0,   255},
      {0,   255, 0,   255},
	  {0,   0,   255, 255},
      {255, 255, 0,   255},
      {255, 0,   255, 255},
      {0,   255, 255, 255}
    };

	// 3Dモデル
	Model* model_ = nullptr;

	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//ワールドトランスフォーム
	WorldTransform worldTransform_;
	//ビュープロジェクション
	ViewProjection viewProjection_;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
enum COLOER {
	WHITE,   // 白
	BLACK,   // 黒
	RED,     // 赤
	GREEN,   // 緑
	BLUE,    // 青
	YELLOW,  // 黄
	MAGENTA, //マゼンタ
	CYAN,    //シアン

};
//// 色指定サンプル
//#define WHITE 0xFFFFFFFF // 白
//#define BLACK 0x000000FF // 黒
//#define RED   0xFF0000FF // 赤
//#define GREEN 0x00FF00FF // 緑
//#define BLUE  0x0000FFFF // 青
//#define BLUE  0xFFFF00FF // 黄