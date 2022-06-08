#pragma once
#include "Matrix4.h"
#include "Vector3.h"
#include "WorldTransform.h"


class Affin {

  private:
	float PI = 3.14159f;

	//çsóÒêÈåæ

	Matrix4 matTrans_;
	
	Matrix4 matRotX_;		
	Matrix4 matRotY_;	
	Matrix4 matRotZ_;	
	Matrix4 matRot_;

	Matrix4 matScale_;

	Matrix4 matWorld_;

	// íPà çsóÒ
	Matrix4 matUnit_;

  public:
	
	float radConvert(float value);
	Matrix4 matUnit();

	Matrix4 matTrans(float moveX, float moveY, float moveZ);
	
	Matrix4 matRotateX(float rotationX);
	Matrix4 matRotateY(float rotationY);
	Matrix4 matRotateZ(float rotationZ);
	Matrix4 matRotation(float rotateX, float rotateY, float rotateZ);

	Matrix4 matScale(float scaleX, float scaleY, float scaleZ);

	Matrix4 matWorld(Vector3 move, Vector3 rotate, Vector3 scale);
};
