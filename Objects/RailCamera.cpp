#include "RailCamera.h"

void RailCamera::Initialize(const ViewProjection& viewProjection) {
	// �V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	// ���[���h�g�����X�t�H�[���̏����ݒ�
	worldTransform_.translation_ = viewProjection.eye;
	worldTransform_.rotation_ = viewProjection.up;
	// farZ�̋�����K�؂Ȓl�ɂ���
	// viewProjection_.farZ = 
	// �r���[�v���W�F�N�V�����̏�����
	viewProjection_.Initialize();
}

void RailCamera::Update() {
	// �p�x
	Rotate();
	// ���W
	Move();

	// �r���[�v���W�F�N�V�����ɕ��s�ړ���������
	viewProjection_.eye = worldTransform_.translation_;
	// ���[���h�O���x�N�g��
	Vector3 forward(0.0f, 0.0f, 1.0f);
	// ���[���J�����̉�]�𔽉f
	forward = MatrixCalculation(forward, worldTransform_.matWorld_);
	// ���_����O���ɓK���ȋ����i�񂾈ʒu�������_
	viewProjection_.target.x = viewProjection_.eye.x + forward.x;
	viewProjection_.target.y = viewProjection_.eye.y + forward.y;
	viewProjection_.target.z = viewProjection_.eye.z + forward.z;
	// ���[���h������x�N�g��
	Vector3 up(0.0f, 1.0f, 0.0f);
	// ���[���J�����̉�]�𔽉f�i���[���J�����̏�����x�N�g���j
	viewProjection_.up = MatrixCalculation(up, worldTransform_.matWorld_);
	// �r���[�v���W�F�N�V�������X�V�Ɠ]��
	viewProjection_.UpdateMatrix();
	viewProjection_.TransferMatrix();

	// eye���W
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf("pos : (%f, %f, %f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
}

void RailCamera::Move() {
	// �L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = { 0.0f, 0.0f, 0.0f };

	// �L�����N�^�[�̈ړ�����
	const float kCameraSpeed = 0.1f;

	// �����E�L�[����������move��ω�������
	if (input_->PushKey(DIK_D)) {
		move.x = kCameraSpeed;
	}
	else if (input_->PushKey(DIK_A)) {
		move.x = -kCameraSpeed;
	}
	if (input_->PushKey(DIK_W)) {
		move.z = kCameraSpeed;
	}
	else if (input_->PushKey(DIK_S)) {
		move.z = -kCameraSpeed;
	}

	// �ړ��ʂ����Z
	worldTransform_.translation_ += move;

	// �X�V
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void RailCamera::Rotate() {
	//�����������ŉ�]�x�N�g����ύX
	if (input_->PushKey(DIK_Q)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ -= {0.0f, (PI / 180), 0.0f};
	}
	else if (input_->PushKey(DIK_E)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ += {0.0f, (PI / 180), 0.0f};
	}
}