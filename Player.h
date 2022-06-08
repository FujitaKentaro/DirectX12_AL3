#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include "Input.h"
#include "DebugText.h"
#include "Affin.h"


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

	Affin affin_;

//input 
	Input* input_;
//debugText
	DebugText* debugText_;
	

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

