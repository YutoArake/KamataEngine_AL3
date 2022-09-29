#include "EnemyBullet.h"
#include <cassert>

void EnemyBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ŏ󂯎�����̂������o�ϐ��ɑ��
	model_ = model;
	// �e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("black.jpg");

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �����Ŏ󂯎�����������W�A���x���Z�b�g
	worldTransform_.translation_ = position;
	velocity_ = velocity;
}

void EnemyBullet::Update() {
	// ���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	// ���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	// ���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void EnemyBullet::Draw(const ViewProjection& viewProjection) {
	// ���f���̕`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

Vector3 EnemyBullet::GetWorldPosition() {
	// ���[���h���W������ϐ�
	Vector3 worldPos;
	// ���[���h�s��̕��s�ړ��������擾�i���[���h���W�j
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void EnemyBullet::OnCollision() {
	isDead_ = true;
}