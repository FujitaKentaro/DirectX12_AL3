#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"


namespace Affin {  

	//�~����
	float PI = 3.14159f;
	// �x���@ -> ���W�A���ϊ�
	float radConvert(float value);

	// �P�ʍs�� set
	Matrix4 matUnit();

	// ���s�ړ�
	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	
	// ��]
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);

	//�g�k
	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	//�g�k -> ��] -> �ړ�
	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);
}// namespace Affin
