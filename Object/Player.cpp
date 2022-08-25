#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	model_ = model;
	textureHandle_ = TextureManager::Load("mario.png");
	

	// 3D���e�B�N���̃��[���h�g�����X�t�H�[���̏�����
	worldTransform3DReticle_.Initialize();

	//�X�v���C�g����
	sprite2DReticle_.reset(
	  Sprite::Create(textureReticle, Vector2{640, 360}, Vector4{1, 1, 1, 1}, Vector2(0.5, 0.5)));

	// worldTransform_.parent_ = &cameraWorldTransform_;
	Vector3 move(0, 0, 20);

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	worldTransform_.Initialize();
	worldTransform_.translation_ = move;
	worldTransform_.matWorld_ = MathUtility::Matrix4Translation(
	  worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

/// <summary>
/// �X�V
/// </summary>
void Player::Update(ViewProjection viewprojection) {

	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

#pragma region �L�����N�^�[�ړ�����

	// �L�����N�^�[�ړ�����
	Move();
	Rotate();

	//�s��X�V
	MatUpdate(worldTransform_);

	//�L�����U��
	Attack();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

	//���@�̃��[���h���W����3D���e�B�N���̃��[���h���W���v�Z
	{
		//���@����3D���e�B�N���ւ̋���
		const float kDistancePlayerTo3DReticle = 50.0f;
		//���@����3D���e�B�N���ւ̃I�t�Z�b�g(Z+����)
		Vector3 offset = {0, 0, 1.0f};
		//���@�̃��[���h�s��̉�]�𔽉f
		offset = Affin::VecMat(offset, worldTransform_.matWorld_);
		//�x�N�g���̒����𐮂���
		float len = sqrt(offset.x * offset.x + offset.y * offset.y + offset.z * offset.z);
		if (len != 0) {
			offset /= len;
		}
		offset *= kDistancePlayerTo3DReticle;
		worldTransform3DReticle_.translation_ = offset;
		worldTransform3DReticle_.matWorld_ = Affin::matTrans(worldTransform_.translation_);
		worldTransform3DReticle_.TransferMatrix();
	}
	// 3D���e�B�N���̃��[���h���W����2D���e�B�N���̃X�N���[�����W���v�Z
	{
		Vector3 positionReticle = Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_);

		//�r���[�|�[�g�s��
		Matrix4 matViewport = {
		  640, 0, 0, 0, 0, -360, 0, 0, 0, 0, 1, 0, 640, 360, 0, 1,
		};

		//�r���[�|�[�g�s��
		Matrix4 matViewProjectionViewport;
		matViewProjectionViewport = viewprojection.matView;
		matViewProjectionViewport *= viewprojection.matProjection;
		matViewProjectionViewport *= matViewport;

		//���[���h���X�N���[�����W�ϊ�(������3D����2D�ɂȂ�)
		positionReticle = Affin::wDivision(positionReticle, matViewProjectionViewport);

		//�X�v���C�g�̃��e�B�N���ɍ��W�ݒ�
		sprite2DReticle_->SetPosition(Vector2(positionReticle.x, positionReticle.y));

		debugText_->SetPos(100, 100);
		debugText_->Printf("X:%f,Y:%f", positionReticle.x, positionReticle.y);
	}

	debugText_->SetPos(10, 10);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
	debugText_->SetPos(10, 30);
	debugText_->Printf(
	  "player : x,%f  y,%f z,%f", worldTransform_.rotation_.x, worldTransform_.rotation_.y,
	  worldTransform_.rotation_.z);

	// debugText_->SetPos(10, 230);
	// debugText_->Printf(
	//   "�e : x,%f  y,%f z,%f", worldTransform_.parent_->matWorld_.m[3][0],
	//   worldTransform_.parent_->matWorld_.m[3][1], worldTransform_.parent_->matWorld_.m[3][3]);
#pragma endregion
}

/// <summary>
/// �`��
/// </summary>
void Player::Draw(ViewProjection viewProjection) {

	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//model_->Draw(worldTransform3DReticle_, viewProjection, textureHandle_);
	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::MatUpdate(WorldTransform& worldTransform_) {

	// �p�[�c�̍X�V

	// �R�ړ������s����v�Z
	worldTransform_.matWorld_ = Affin::matWorld(
	  worldTransform_.translation_, worldTransform_.rotation_, worldTransform_.scale_);

	// �e�̍s����|���Z���

	worldTransform_.matWorld_ *= worldTransform_.parent_->matWorld_;

	// �s��̓]��
	worldTransform_.TransferMatrix();
}

/// <summary>
/// ����
/// </summary>
void Player::Move() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};

	// ���s�ړ�
	{ // X����
		if (input_->PushKey(DIK_D)) {
			move.x = 0.1f;
		} else if (input_->PushKey(DIK_A)) {
			move.x = -0.1f;
		}
		// Y����
		if (input_->PushKey(DIK_W)) {
			move.y = 0.1f;
		} else if (input_->PushKey(DIK_S)) {
			move.y = -0.1f;
		}
		// Z����
		if (input_->PushKey(DIK_3)) {
			move.z = 0.1f;
		} else if (input_->PushKey(DIK_4)) {
			move.z = -0.1f;
		}
	}

	//�ړ����E���W
	const float kMoveLimitX = 35;
	const float kMoveLimitY = 19;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimitX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimitX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimitY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimitY);

	worldTransform_.translation_ += move;
}

/// <summary>
/// ��]�ړ�
/// </summary>
void Player::Rotate() {
	Vector3 rotate = {0, 0, 0};

	// ��]
	{ // X����
		if (input_->PushKey(DIK_Q)) {
			rotate.x = 1;
		} else if (input_->PushKey(DIK_E)) {
			rotate.x = -1;
		}
		// Y����
		if (input_->PushKey(DIK_1)) {
			rotate.y = 1;
		} else if (input_->PushKey(DIK_2)) {
			rotate.y = -1;
		}
	}

	//�ړ����E���W
	const float kRotateLimitX = 80;
	const float kRotateLimitY = 80;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.rotation_.x = max(worldTransform_.rotation_.x, -kRotateLimitX);
	worldTransform_.rotation_.x = min(worldTransform_.rotation_.x, +kRotateLimitX);
	worldTransform_.rotation_.y = max(worldTransform_.rotation_.y, -kRotateLimitY);
	worldTransform_.rotation_.y = min(worldTransform_.rotation_.y, +kRotateLimitY);

	worldTransform_.rotation_ += rotate;
}

/// <summary>
/// �U��
/// </summary>
void Player::Attack() {

	if (input_->TriggerKey(DIK_SPACE)) {

		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0, 0, kBulletSpeed);

		// ���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = Affin::VecMat(velocity, worldTransform_.parent_->matWorld_);
		velocity = Affin::VecMat(velocity, worldTransform_.matWorld_);

		// �e�𐶐����A������
		Vector3 playerRot, playerPos;
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		// ���s
		playerPos = worldTransform_.parent_->translation_;
		playerPos += worldTransform_.translation_;
		// ��]
		playerRot = worldTransform_.parent_->rotation_;
		playerRot += worldTransform_.rotation_;

		Vector3 plPos, retPos;

		retPos = Affin::GetWorldTrans(worldTransform3DReticle_.matWorld_);
		plPos = Affin::GetWorldTrans(worldTransform_.matWorld_);

		velocity = MathUtility::operator-(retPos, plPos);

		float len =
		  sqrt(velocity.x * velocity.x + velocity.y * velocity.y + velocity.z * velocity.z);
		if (len != 0) {
			velocity /= len;
		}
		velocity *= kBulletSpeed;

		// �e�̏�����
		newBullet->Initialize(model_, GetWorldPosition(), velocity);

		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}

/// <summary>
/// ���[���h���W���擾
/// </summary>
Vector3 Player::GetWorldPosition() {
	//
	Vector3 worldPos;
	//
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

/// <summary>
/// �Փ˂����m������Ăяo�����R�[���o�b�N�֐�
/// </summary>
void Player::OnCollision() {}

/// <summary>
/// UI�`��
/// </summary>
void Player::DrawUI() { sprite2DReticle_->Draw(); }