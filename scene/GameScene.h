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

	Vector3 box[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
	  {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };
	Vector3 boxScale[8];
	Vector3 boxRotate[8];
	Vector3 boxTrans[8];

	Vector4 scale[4] = {
	  {2.0f, 0.0f, 0.0f, 0.0f},
	  {0.0f, 2.0f, 0.0f, 0.0f},
	  {0.0f, 0.0f, 2.0f, 0.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f}
    };

	Vector4 scale1[4];
	Vector4 scale2[4];
	Vector4 scale3[4];

	Vector4 rotateX[4] = {
	  {1.0f, 0.0f,     0.0f,    0.0f},
	  {0.0f, 0.7071f,  0.7071f, 0.0f},
	  {0.0f, -0.7071f, 0.7071f, 0.0f},
	  {0.0f, 0.0f,     0.0f,    1.0f}
    };
	Vector4 rotateY[4] = {
	  {0.7071f, 0.0f, -0.7071f, 0.0f},
	  {0.0f,    1.0f, 0.0f,     0.0f},
	  {0.7071f, 0.0f, 0.7071f,  0.0f},
	  {0.0f,    0.0f, 0.0f,     1.0f}
    };
	Vector4 rotateZ[4] = {
	  {0.7071f,  0.7071f, 0.0f, 0.0f},
	  {-0.7071f, 0.7071f, 0.0f, 0.0f},
	  {0.0f,     0.0f,    1.0f, 0.0f},
	  {0.0f,     0.0f,    0.0f, 1.0f}
    };

	Vector3 rotateX1[8];
	Vector3 rotateY1[8];
	Vector3 rotateZ1[8];
	Vector3 rotateX2[8];
	Vector3 rotateY2[8];
	Vector3 rotateZ2[8];

	Vector4 translation[4] = {
	  {1.0f, 0.0f, 0.0f, 10.0f},
	  {0.0f, 1.0f, 0.0f, 10.0f},
	  {0.0f, 0.0f, 1.0f, 10.0f},
	  {0.0f, 0.0f, 0.0f, 1.0f }
    };
	Vector4 translation1[4];
	Vector4 translation2[4];
	Vector4 translation3[4];

	int edgeList[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},

	  {0, 4},
      {1, 5},
      {2, 6},
      {3, 7},

	  {4, 5},
      {5, 6},
      {6, 7},
      {7, 4}
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