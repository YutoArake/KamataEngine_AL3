#pragma once

#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// �G
/// </summary>
class Enemy {
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	// �s��v�Z�p
	AffinMatrix mat;

	// ���x
	Vector3 velocity_;

	// ����<frm>
	static const int32_t kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// �f�X�t���O�̃Q�b�^�[
	/// </summary>
	bool IsDead() const { return isDead_; }

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

};