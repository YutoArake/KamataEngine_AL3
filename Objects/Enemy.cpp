#include "Enemy.h"
#include <cassert>

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ŏ󂯎�����̂������o�ϐ��ɑ��
	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("teki.png");

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();

	// �������W���Z�b�g
	worldTransform_.translation_ = { 20.0f, 1.0f, 20.0f };
	// �s��̌v�Z
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// ���x�̐ݒ�
	velocity_ = { 0.0f, 0.0f, -0.1f };

	// �ڋ߃t�F�[�Y��������
	ApproachInitialize();
}

void Enemy::Update() {

	// �f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<EnemyBullet>& bullet) {
		return bullet->IsDead();
		});

	// �ړ�����
	Move();

	// �s��̌v�Z
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// �e���X�V
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	// �e��`��
	for (std::unique_ptr<EnemyBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
	}
}

void Enemy::Move() {
	// �t�F�[�Y�ɍ��킹�č��W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	switch (phase_) {
	case Phase::Approach:
	default:
		Approach();
		break;
	case Phase::Leave:
		Leave();
		break;
	}
}

void Enemy::Approach() {
	// ���x
	Vector3 approachVelocity = { 0.0f, 0.0f, -0.1f };

	// ���˃^�C�}�[���f�N�������g
	fireTimer--;
	// �w�莞�ԂɒB����
	if (fireTimer <= 0) {
		// �e�𔭎�
		Fire();
		// ���˃^�C�}�[��������
		fireTimer = kFireInterval;
	}

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += approachVelocity;
	// �K��̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::ApproachInitialize() {
	// ���˃^�C�}�[��������
	fireTimer = kFireInterval;
}

void Enemy::Leave() {
	// ���x
	Vector3 leaveVelocity = { -0.2f, 0.2f, -0.1f };

	// �ړ��i�x�N�g�������Z�j
	worldTransform_.translation_ += leaveVelocity;
}

void Enemy::Fire() {
	// �e�̑��x
	const float kBulletSpeed = -1.0f;
	Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

	// ���x�x�N�g�������L�����ɍ��킹�ĉ�]������
	velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

	// �e�𐶐����A����������
	std::unique_ptr<EnemyBullet> newBullet = std::make_unique<EnemyBullet>();
	newBullet->Initialize(model_, worldTransform_.translation_, velocity);

	// �e��o�^����
	bullets_.push_back(std::move(newBullet));
}