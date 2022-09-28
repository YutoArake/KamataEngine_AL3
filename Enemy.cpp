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
	worldTransform_.translation_ = { 0.0f, 5.0f, 20.0f };
	// �s��̌v�Z
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// ���x�̐ݒ�
	velocity_ = { 0.0f, 0.0f, -0.1f };
}

void Enemy::Update() {
	// �ړ�����
	Move();

	// �s��̌v�Z
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void Enemy::Draw(const ViewProjection& viewProjection) {
	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move() {
	// ���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;
}