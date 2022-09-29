#pragma once

#include "Model.h"
#include "WorldTransform.h"

/// <summary>
/// ���L�����̒e
/// </summary>
class Skydome {
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;

	AffinMatrix mat;

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
};