#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

// �~����
const float PI = 3.141592f;

// �\����
// �A�t�B���ϊ��p
typedef struct {
	Matrix4 scale;
	Matrix4 rotX;
	Matrix4 rotY;
	Matrix4 rotZ;
	Matrix4 rot;
	Matrix4 trans;
	Matrix4 mix;
} AffinMatrix;

namespace MathMyFunc {

	// �v���g�^�C�v�錾
	// ���W�A���ϊ�
	float RadianTransform(float degreeAngle);
	// �x���ϊ�
	float DegreeTransform(float radAngle);

	// �]�u�s��
	void TransposedMatrix(Matrix4& mat);
	// �e��s�񐶐�
	void GenerateIdentityMatrix(Matrix4& mat);
	void GenerateScaleMatrix(Vector3 scale, Matrix4& matScale);
	void GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans);

	// �s��v�Z
	Matrix4 MatrixCalculation(Matrix4 mat1, Matrix4 mat2);
	Vector3 MatrixCalculation(Vector3 vector, Matrix4 mat);
	// �v���g�^�C�v�錾�����܂�

} // namespace MathMyFunc