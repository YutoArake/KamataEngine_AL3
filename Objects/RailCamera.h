#pragma once

#include "WorldTransform.h"
#include "ViewProjection.h"

/// <summary>
/// ���[���J����
/// </summary>
class RailCamera {
private:
	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// �r���[�v���W�F�N�V����
	ViewProjection viewProjection_;

	AffinMatrix mat;

public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(const ViewProjection& viewProjection);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �ړ�
	/// </summary>
	void Move();

	/// <summary>
	/// ����
	/// </summary>
	void Rotate();

	/// <summary>
	/// �`��
	/// </summary>
	/// <param name="viewProjection">�r���[�v���W�F�N�V�����i�Q�Ɠn���j</param>
	// void Draw(const ViewProjection& viewProjection);
};