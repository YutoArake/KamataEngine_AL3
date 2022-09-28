#pragma once

#include "Model.h"
#include "WorldTransform.h"

#include "MathMyFunc.h"
using namespace MathMyFunc;

/// <summary>
/// ���L����
/// </summary>
class Player{
private:
	// ���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	// ���f��
	Model* model_ = nullptr;
	// �e�N�X�`���n���h��
	uint32_t textureHandle_ = 0u;

	Input* input_ = nullptr;
	DebugText* debugText_ = nullptr;

	AffinMatrix mat;

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
	void Draw(ViewProjection viewProjection);

	void Move();
};

