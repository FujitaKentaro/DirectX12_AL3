#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"

/// <summary>
/// アフィン行列 （角度指定：度数法）
/// </summary>
namespace Affin {  

	//円周率
	const float PI = 3.141592654f;
	// 度数法 -> ラジアン変換
	float radConvert(float value);

	// 単位行列 set
	Matrix4 matUnit();

	// 平行移動
	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	
	// 回転
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);

	//拡縮
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	//拡縮 -> 回転 -> 移動
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);
}// namespace Affin
