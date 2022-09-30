#include "Skydome.h"
#include <cassert>

void Skydome::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	// �����Ŏ󂯎�����̂������o�ϐ��ɑ��
	model_ = model;

	// ���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	// �X�P�[������������
	worldTransform_.scale_ = { 100.0f, 100.0f, 100.0f };
	// �s��̌v�Z�A�]��
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
	// �]��
	worldTransform_.TransferMatrix();
}

void Skydome::Update() {

}

void Skydome::Draw(const ViewProjection& viewProjection) {
	// 3D���f���̕`��
	model_->Draw(worldTransform_, viewProjection);
}