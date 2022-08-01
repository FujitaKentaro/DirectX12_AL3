#pragma once
#include "Affin.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "WorldTransform.h"
#include <cassert>
#include <memory>
#include <list>


class Enemy {
  private:
	//	���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// input
	Input* input_ = nullptr;
	// debugText
	DebugText* debugText_ = nullptr;



  public:
	void Initialize(Model* model);
	void Update();
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �s��̌v�Z
	/// </summary>
	void MatUpdate(WorldTransform& worldTransfom);

};
