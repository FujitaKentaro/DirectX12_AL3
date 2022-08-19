#include "Enemy.h"

/// <summary>
/// ������
/// </summary>
void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("zako.png");

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();

	worldTransform_.translation_.z = 10.0f;
	worldTransform_.translation_.x = 10.0f;

	//�e�X�V
	//	Fire();

	//�ڋ߃t�F�[�Y������
	ApproachInitialize();
}

/// <summary>
/// �X�V
/// </summary>
void Enemy::Update() {

	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) { return bullet->IsDead(); });

	//�s��X�V
	MatUpdate(worldTransform_);

	switch (phase_) {
	case Phase::None:

	case Phase::Approach:
	default:
		worldTransform_.translation_.z += -0.05f;
		if (worldTransform_.translation_.z < 0.0f) {
			phase_ = Phase::Leave;
		}

		fireTimer_--;

		if (fireTimer_ <= 0) {
			// �e�𔭎�
			Fire();
			// ���˃^�C�}�[��������
			fireTimer_ = kFireInterval;
		}

		break;
	case Phase::Leave:

		worldTransform_.translation_.x += -0.1f;
		worldTransform_.translation_.y += 0.1f;
		break;
	}
	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}

	debugText_->SetPos(10, 50);
	debugText_->Printf(
	  "enemy : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 70);
	debugText_->Printf(
	  "enemy : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);
}

/// <summary>
/// �`��
/// </summary>
void Enemy::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::MatUpdate(WorldTransform& worldTransform_) {

	// �p�[�c�̍X�V

	// �R�ړ������s����v�Z
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	// �e�̍s����|���Z���
	if (worldTransform_.parent_ != nullptr) {
		worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;
	}

	// �s��̓]��
	worldTransform_.TransferMatrix();
}

/// <summary>
/// �e����
/// </summary>
void Enemy::Fire() {

	//�e�̑��x
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0, 0, kBulletSpeed);

	// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
	velocity = Affin::VecMat(velocity, worldTransform_.matWorld_);

	// �e�𐶐����A������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// �e��o�^����
	bullets_.push_back(std::move(newBullet));
}

/// <summary>
/// �ڋ߃t�F�[�Y������
/// </summary>
void Enemy::ApproachInitialize() {
	// ���˃^�C�}�[��������
	fireTimer_ = kFireInterval;
}