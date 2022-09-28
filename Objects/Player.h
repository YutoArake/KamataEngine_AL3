#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <memory>
#include <list>

#include "PlayerBullet.h"

/// <summary>
/// ���L����
/// </summary>
class Player {
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	AffinMatrix mat;

	// �e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;

public:
	/// <summary>
	/// ������
	/// </summary>
	/// <param name="model">���f��</param>
	/// <param name="textureHandle">�e�N�X�`���n���h��</param>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// ���t���[������
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ����
	/// </summary>
	void Rotate();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

	/// <summary>
	/// ���W�̃Q�b�^�[
	/// </summary>
	Vector3 GetWorldPosition();
};

