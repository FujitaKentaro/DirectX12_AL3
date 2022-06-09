#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"


namespace Affin {  

	//‰~Žü—¦
	float PI = 3.14159f;
	// “x”–@ -> ƒ‰ƒWƒAƒ“•ÏŠ·
	float radConvert(float value);

	// ’PˆÊs—ñ set
	Matrix4 matUnit();

	// •½sˆÚ“®
	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	
	// ‰ñ“]
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);

	//Šgk
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	//Šgk -> ‰ñ“] -> ˆÚ“®
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);
}// namespace Affin
