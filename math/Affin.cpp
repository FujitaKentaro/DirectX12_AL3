#include "Affin.h"
#include "math.h"

/// <summary>
/// 単位行列設定
/// </summary>
Matrix4 Affin::matUnit() {
	Matrix4 matUnit; 

	matUnit = {
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

	return matUnit;
}

/// <summary>
/// 平行移動
/// </summary>
Matrix4 Affin::matTrans(float moveX, float moveY, float moveZ) {
	Matrix4 matTrans;

	matTrans = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f,  0.0f,  0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		moveX, moveY, moveZ, 1.0f
	};

	return matTrans;
}

/// <summary>
/// 度数法 -> ラジアン
/// </summary>
float Affin::radConvert(float value) {
	float radValue;

	radValue = value * (PI / 180);

	return radValue;
}



/// <summary>
/// 回転 X方向
/// </summary>
Matrix4 Affin::matRotateX(float rotationX) {
	float rotRad = radConvert(rotationX);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);
	Matrix4 matRotX;

	matRotX = {
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, cosRad, sinRad,0.0f,
		0.0f, -sinRad, cosRad, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matRotX;
}

/// <summary>
/// 回転 Y方向
/// </summary>
Matrix4 Affin::matRotateY(float rotationY) {
	float rotRad = radConvert(rotationY);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);
	Matrix4 matRotY;

	matRotY = {
		cosRad, 0.0f, -sinRad, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinRad, 0.0f, cosRad, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

	return matRotY;
}

/// <summary>
/// 回転 Z方向
/// </summary>
Matrix4 Affin::matRotateZ(float rotationZ) {
	float rotRad = radConvert(rotationZ);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);
	Matrix4 matRotZ;

	matRotZ = {
		cosRad, sinRad, 0.0f, 0.0f,
		-sinRad, cosRad, 0.0f, 0.0f,
		0.0f,   0.0f,   1.0f, 0.0f, 
		0.0f,    0.0f,   0.0f, 1.0f};

	return matRotZ;
}

/// <summary>
/// 回転 Z->X->Y
/// </summary>
Matrix4 Affin::matRotation(float rotateX, float rotateY, float rotateZ) {

	Matrix4 x = matRotateX(rotateX); 
	Matrix4 y = matRotateY(rotateY);
	Matrix4 z = matRotateZ(rotateZ);
	Matrix4 matRot;

	x *= z;
	y *= x;
	matRot = y;	

	return matRot;
}

/// <summary>
/// 拡縮
/// </summary>
Matrix4 Affin::matScale(float scaleX, float scaleY, float scaleZ) {

	Matrix4 matScale = {
		scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY,0.0f,0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matScale;
}

/// <summary>
/// 拡縮*回転*移動
/// </summary>
Matrix4 Affin::matWorld(Vector3 move, Vector3 rotate, Vector3 scale) {
	Matrix4 scaleM = matScale(scale.x, scale.y, scale.z);
	Matrix4 rotateM = matRotation(rotate.x, rotate.y, rotate.z);
	Matrix4 moveM = matTrans(move.x, move.y, move.z);
	Matrix4 matWorld;

	rotateM *= scaleM;
	moveM *= rotateM;
	matWorld = moveM;

	return matWorld;
}
