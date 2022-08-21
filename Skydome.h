#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include "TextureManager.h"


class Skydome {
  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//�e�N�X�`���n���h��
	//uint32_t textureHandle_ = 0u;

	//���f��
	Model* model_ = nullptr;
	Vector3 scale = {100.0f, 100.0f, 100.0f};
  public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);
};
