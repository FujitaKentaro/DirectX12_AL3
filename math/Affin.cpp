#include "Affin.h"
#include "math.h"

/// <summary>
/// íPà çsóÒê›íË
/// </summary>
Matrix4 Affin::matUnit() {

	matUnit_ = {
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

	return matUnit_;
}

/// <summary>
/// ïΩçsà⁄ìÆ
/// </summary>
Matrix4 Affin::matTrans(float moveX, float moveY, float moveZ) {

	matTrans_ = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f,  1.0f,  0.0f,  0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		moveX, moveY, moveZ, 1.0f
	};

	return matTrans_;
}

/// <summary>
/// ìxêîñ@ -> ÉâÉWÉAÉì
/// </summary>
float Affin::radConvert(float value) {
	float radValue;

	radValue = value * (PI / 180);

	return radValue;
}



/// <summary>
/// âÒì] Xï˚å¸
/// </summary>
Matrix4 Affin::matRotateX(float rotationX) {
	float rotRad = radConvert(rotationX);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);

	matRotX_ = {
		1.0f, 0.0f, 0.0f, 0.0f, 
		0.0f, cosRad, sinRad,0.0f,
		0.0f, -sinRad, cosRad, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matRotX_;
}

/// <summary>
/// âÒì] Yï˚å¸
/// </summary>
Matrix4 Affin::matRotateY(float rotationY) {
	float rotRad = radConvert(rotationY);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);

	matRotY_ = {
		cosRad, 0.0f, -sinRad, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinRad, 0.0f, cosRad, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f};

	return matRotY_;
}

/// <summary>
/// âÒì] Zï˚å¸
/// </summary>
Matrix4 Affin::matRotateZ(float rotationZ) {
	float rotRad = radConvert(rotationZ);
	float cosRad = cos(rotRad);
	float sinRad = sin(rotRad);

	matRotZ_ = {
		cosRad, sinRad, 0.0f, 0.0f,
		-sinRad, cosRad, 0.0f, 0.0f,
		0.0f,   0.0f,   1.0f, 0.0f, 
		0.0f,    0.0f,   0.0f, 1.0f};

	return matRotZ_;
}

/// <summary>
/// âÒì] Z->X->Y
/// </summary>
Matrix4 Affin::matRotation(float rotateX, float rotateY, float rotateZ) {

	Matrix4 x = matRotateX(rotateX); 
	Matrix4 y = matRotateY(rotateY);
	Matrix4 z = matRotateZ(rotateZ);

	x *= z;
	y *= x;
	matRot_ = y;	

	return matRot_;
}

/// <summary>
/// ägèk
/// </summary>
Matrix4 Affin::matScale(float scaleX, float scaleY, float scaleZ) {

	matScale_ = {
		scaleX, 0.0f, 0.0f, 0.0f,
		0.0f, scaleY,0.0f,0.0f,
		0.0f, 0.0f, scaleZ, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};

	return matScale_;
}

/// <summary>
/// ägèk*âÒì]*à⁄ìÆ
/// </summary>
Matrix4 Affin::matWorld(Vector3 move, Vector3 rotate, Vector3 scale) {
	Matrix4 scaleM = matScale(scale.x, scale.y, scale.z);
	Matrix4 rotateM = matRotation(rotate.x, rotate.y, rotate.z);
	Matrix4 moveM = matTrans(move.x, move.y, move.z);

	rotateM *= scaleM;
	moveM *= rotateM;
	matWorld_ = moveM;

	return matWorld_;
}
