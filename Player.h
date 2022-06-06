#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "DebugText.h"


/// <summary>
/// ���L����
/// </summary>
class Player
{
private:


//	���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
//���f��
	Model* model_ = nullptr;
//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;


//input 
	Input* input_;
//debugText
	DebugText* debugText_;




public:
	const float PI = 3.141592f;
	
  float transformX = 0.0f;
  float transformY = 0.0f;
  float rotation = 0.0f;
  float scale = 1.0f;

  float affin[3][3] = {
	{1.0f, 0.0f, 0.0f},
    {0.0f, 1.0f, 0.0f},
    {0.0f, 0.0f, 1.0f}
  };


	//Vector3
	Vector3 scale_;
	Vector3 rotate_;
	Vector3 translation_;


	// �P�ʍs��
	Matrix4 matUnit_={
		1.0f,0.0f,0.0f,0.0f,
		0.0f,1.0f,0.0f,0.0f,
		0.0f,0.0f,1.0f,0.0f,
		0.0f,0.0f,0.0f,1.0f
	};

public:
/// <summary>
/// ������
/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

/// <summary>
/// �X�V
/// </summary>
	void Update();

/// <summary>
/// �`��
/// </summary>
	void Draw(ViewProjection viewProjection);



};
