#include "ViewProjection.h"

void ViewProjection::SetViewProjection() {
	//�J�������_���W��ݒ�
	eye = { 0.0f, 0.0f, -50.0f };

	//�J���������_���W��ݒ�
	target = { 0.0f, 0.0f, 0.0f };

	//�J����������x�N�g����ݒ�(�E��45�x�w��)
	up = { 0.0f, 1.0f, 0.0f };

	//�J����������������p��ݒ�
	fovAngleY = RadianTransform(45.0f);

	//�A�X�y�N�g���ݒ�
	aspectRatio = (float)16 / 9;

	//�j�A�N���b�v������ݒ�
	nearZ = 0.1f;

	//�t�@�[�N���b�v������ݒ�
	farZ = 1000.0f;

	//�r���[�v���W�F�N�V�����̏�����
	Initialize();
}

void ViewProjection::UpdateViewProjention(Input* input_, DebugText* debugText_, float viewAngle) {
	//���_�ړ�����
	{
		//���_�̈ړ��x�N�g��
		//Vector3 move = {0.0f, 0.0f, 0.0f};

		//���_�̈ړ�����
		//const float kEyeSpeed = 0.2f;

		//�����������ňړ��x�N�g����ύX
		//if (input_->PushKey(DIK_W)) {
		//	move.z += kEyeSpeed;
		//} else if (input_->PushKey(DIK_S)) {
		//	move.z -= kEyeSpeed;
		//}

		//���_�ړ��i�x�N�g���̉��Z�j
		//eye += move;

		//�s��̍Čv�Z
		//UpdateMatrix();

		//�f�o�b�N�p�\��
		//debugText_->SetPos(50.0f, 50.0f);
		//debugText_->Printf("eye:(%f,%f,%f)", eye.x, eye.y, eye.z);
	}

	//�����_�ړ�����
	{
		//���_�̈ړ��x�N�g��
		//Vector3 move = {0.0f, 0.0f, 0.0f};

		//���_�̈ړ�����
		//const float kTargetSpeed = 0.2f;

		//�����������ňړ��x�N�g����ύX
		//if (input_->PushKey(DIK_LEFT)) {
		//	move.x -= kTargetSpeed;
		//} else if (input_->PushKey(DIK_RIGHT)) {
		//	move.x += kTargetSpeed;
		//}

		//���_�ړ��i�x�N�g���̉��Z�j
		//target += move;

		//�s��̍Čv�Z
		//UpdateMatrix();

		//�f�o�b�N�p�\��
		//debugText_->SetPos(50.0f, 70.0f);
		//debugText_->Printf("target:(%f,%f,%f)", target.x, target.y, target.z);
	}

	//�������]����
	{
		//������̉�]����[���W�A��/frame]
		//const float kUpRotSpeed = 0.05f;

		//�����������ňړ��x�N�g����ύX
		//if (input_->PushKey(DIK_SPACE)) {
		//	viewAngle += kUpRotSpeed;
		//	// 2�΂𒴂�����0�ɖ߂�
		//	viewAngle = fmodf(viewAngle, PI * 2.0f);
		//}

		//������x�N�g�����v�Z�i���a1�̉~����̍��W�j
		//up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//�s��̍Čv�Z
		//UpdateMatrix();

		//�f�o�b�N�p�\��
		//debugText_->SetPos(50.0f, 90.0f);
		//debugText_->Printf("up:(%f,%f,%f)", up.x, up.y, up.z);
	}

	// Fov�ύX����
	{
		//��L�[�Ŏ���p���L����
		//if (input_->PushKey(DIK_UP)) {
		//	fovAngleY += 0.02f;
		//	//�΂𒴂��Ȃ��悤�ɂ���
		//	fovAngleY = min(max(fovAngleY, 0.01f), PI);
		//	//���L�[�Ŏ���p�����܂�
		//} else if (input_->PushKey(DIK_DOWN)) {
		//	fovAngleY -= 0.02f;
		//	// 0.01�������Ȃ��悤�ɂ���
		//	fovAngleY = min(max(fovAngleY, 0.01f), PI);
		//}

		//�s��̍Čv�Z
		//UpdateMatrix();

		//�f�o�b�N�p�\��
		//debugText_->SetPos(50.0f, 110.0f);
		//debugText_->Printf("fovAngleY(Degree):%f", DegreeTransform(fovAngleY));
	}

	//�N���b�v�����ύX����
	{
		// SHIFT,CTRL�Ńj�A�N���b�v�����𑝌�
		//if (input_->PushKey(DIK_LSHIFT)) {
		//	nearZ += 0.2f;
		//	//���L�[�Ŏ���p�����܂�
		//} else if (input_->PushKey(DIK_LCONTROL)) {
		//	nearZ -= 0.2f;
		//}

		//�s��̍Čv�Z
		//UpdateMatrix();

		//�f�o�b�N�p�\��
		//debugText_->SetPos(50.0f, 130.0f);
		//debugText_->Printf("nearZ:%f", nearZ);
	}
}