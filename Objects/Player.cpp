#include "Player.h"
#include <cassert>

void Player::Initialize(Model* model, Model* modelB, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ŏ󂯎�����̂������o�ϐ��ɑ��
	model_ = model;
	modelB_ = modelB;
	textureHandle_ = textureHandle;

	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

void Player::Update() {

	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) {
		return bullet->IsDead();
		});

	// �L�����N�^�[�̉�]����
	Rotate();

	// �L�����N�^�[�̈ړ�����
	Move();

	// �L�����N�^�[�̍U������
	Attack();

	// �e���X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}

#pragma region �f�o�b�O�e�L�X�g
	// player���W
	// debugText_->SetPos(50.0f, 50.0f);
	// debugText_->Printf("pos : (%f, %f, %f)", worldTransform_.translation_.x, worldTransform_.translation_.y, worldTransform_.translation_.z);
#pragma endregion
}

void Player::Draw(const ViewProjection& viewProjection) {
	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection);

	// �e��`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Player::Move() {
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	// �L�����N�^�[�̈ړ�����
	const float kPlayerSpeed = 0.1f;

	// �����E�L�[����������move��ω�������
	if (input_->PushKey(DIK_RIGHTARROW)) {
		move.x = kPlayerSpeed;
	}
	else if (input_->PushKey(DIK_LEFTARROW)) {
		move.x = -kPlayerSpeed;
	}
	if (input_->PushKey(DIK_UPARROW)) {
		move.y = kPlayerSpeed;
	}
	else if (input_->PushKey(DIK_DOWNARROW)) {
		move.y = -kPlayerSpeed;
	}

	// �ړ��ʂ����Z
	worldTransform_.translation_ += move;

	//�ړ����E���W
	const float kMoveLimiteX = 34.0f;
	const float kMoveLimiteY = 18.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	// �X�V
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void Player::Rotate() {
	//�����������ŉ�]�x�N�g����ύX
	if (input_->PushKey(DIK_U)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ -= {0.0f, (PI / 180), 0.0f};
	}
	else if (input_->PushKey(DIK_I)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ += {0.0f, (PI / 180), 0.0f};
	}
}

void Player::Attack() {
	if (input_->TriggerKey(DIK_SPACE)) {
		// �e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

		// ���x�x�N�g�������L�����ɍ��킹�ĉ�]������
		velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

		// �e�𐶐����A����������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(modelB_, worldTransform_.translation_, velocity);

		// �e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}

Vector3 Player::GetWorldPosition() {
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void Player::OnCollision() {

}