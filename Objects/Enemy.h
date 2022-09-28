#pragma once

#include "Model.h"
#include "WorldTransform.h"
#include <memory>
#include <list>

#include "EnemyBullet.h"

// ���@�N���X�̑O���錾
class Player;

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

	// ���L����
	Player* player_ = nullptr;

	// �s���t�F�[�Y
	enum class Phase {
		Approach,	// �ڋ߂���
		Leave,		// ���E����
	};

	// �t�F�[�Y
	Phase phase_ = Phase::Approach;

	// ���x
	Vector3 velocity_;

	// �e
	std::list<std::unique_ptr<EnemyBullet>> bullets_;

	// ����<frm>
	static const int32_t kLifeTime = 60 * 5;
	// �f�X�^�C�}�[
	int32_t deathTimer_ = kLifeTime;
	// �f�X�t���O
	bool isDead_ = false;

	// ���˃^�C�}�[
	int32_t fireTimer = 0;

public:
	// ���ˊԊu
	static const int kFireInterval = 60;

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

	/// <summary>
	/// �ڋ�
	/// </summary>
	void Approach();

	/// <summary>
	/// �ڋ߃t�F�[�Y������
	/// </summary>
	void ApproachInitialize();

	/// <summary>
	/// ���E
	/// </summary>
	void Leave();

	/// <summary>
	/// �e����
	/// </summary>
	void Fire();

	/// <summary>
	/// ���@�N���X�̃Z�b�^�[
	/// </summary>
	void SetPlayer(Player* player) { player_ = player; }

	/// <summary>
	/// ���W�̃Q�b�^�[
	/// </summary>
	Vector3 GetWorldPosition();
};