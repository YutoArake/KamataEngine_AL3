#include <random>
#include "MathMyFunc.h"
using namespace MathMyFunc;

// �x�������W�A���ɕϊ�����
float MathMyFunc::RadianTransform(float degreeAngle) {
	float rad;
	rad = degreeAngle * PI / 180;
	return rad;
}

// ���W�A����x���ɕϊ�����
float MathMyFunc::DegreeTransform(float radAngle) {
	float degree;
	degree = radAngle * 180 / PI;
	return degree;
}

// �]�u�s��
void MathMyFunc::TransposedMatrix(Matrix4& mat) {
	Matrix4 m1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m1.m[j][i] = mat.m[i][j];
		}
	}

	mat = m1;
}

// �P�ʍs���������
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
	};
}

// �X�P�[���s��𐶐�����
void MathMyFunc::GenerateScaleMatrix(Vector3 scale, Matrix4& matScale) {
	// �P�ʍs���������
	GenerateIdentityMatrix(matScale);

	// �X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
}

// X����]�̍s��𐶐�����
void MathMyFunc::GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation) {
	// �P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// X����]�s��̊e�v�f��ݒ肷��
	matRotation.m[1][1] = cos(rotation.x);
	matRotation.m[1][2] = sin(rotation.x);
	matRotation.m[2][1] = -sin(rotation.x);
	matRotation.m[2][2] = cos(rotation.x);
}

// Y����]�̍s��𐶐�����
void MathMyFunc::GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation) {
	// �P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// Y����]�s��̊e�v�f��ݒ肷��
	matRotation.m[0][0] = cos(rotation.y);
	matRotation.m[0][2] = -sin(rotation.y);
	matRotation.m[2][0] = sin(rotation.y);
	matRotation.m[2][2] = cos(rotation.y);
}

// Z����]�̍s��𐶐�����
void MathMyFunc::GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation) {
	// �P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// Z����]�s��̊e�v�f��ݒ肷��
	matRotation.m[0][0] = cos(rotation.z);
	matRotation.m[0][1] = sin(rotation.z);
	matRotation.m[1][0] = -sin(rotation.z);
	matRotation.m[1][1] = cos(rotation.z);
}

// ���s�ړ��s��𐶐�����
void MathMyFunc::GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans) {
	// �P�ʍs���������
	GenerateIdentityMatrix(matTrans);

	// �ړ��ʂ��s��ɐݒ肷��
	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;
}

// �s��̌v�Z(mat1�����ɂȂ�l)
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 m1, Matrix4 m2) {
	// ����p�ϐ�
	Matrix4 result;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			for (int k = 0; k < 4; k++) {
				result.m[i][j] += m1.m[i][k] * m2.m[k][j];
			}
		}
	}

	m1 = result;
	return m1;
}

// Vector3��Matrix4�̊|���Z
Vector3 MathMyFunc::MatrixCalculation(Vector3 vector, Matrix4 mat) {
	// ����p�ϐ�
	Vector3 result;

	result.x = vector.x * mat.m[0][0] + vector.y * mat.m[1][0] + vector.z * mat.m[2][0];
	result.y = vector.x * mat.m[0][1] + vector.y * mat.m[1][1] + vector.z * mat.m[2][1];
	result.z = vector.x * mat.m[0][2] + vector.y * mat.m[1][2] + vector.z * mat.m[2][2];

	return result;
}

namespace MathRandom {
#pragma region ��������
	//�����V�[�h������
	std::random_device seed_gen;
	//�����Z���k�E�c�C�X�^�[�̗����G���W��
	std::mt19937_64 engine(seed_gen());

	//�����͈͂̐ݒ�(�p�x)
	std::uniform_real_distribution<float> distAngle(0.0f, PI);

	//�����͈͂̐ݒ�(���W)
	std::uniform_real_distribution<float> distPos(-10.0f, 10.0f);
#pragma endregion

} // namespace MathRandom