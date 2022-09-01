#include "MathMyFunc.h"
using namespace MathMyFunc;

// 度数をラジアンに変換する
float MathMyFunc::RadianTransform(float angle) {
	float rad;
	rad = angle * PI / 180;
	return rad;
}

// ラジアンを度数に変換する
float MathMyFunc::DegreeTransform(float angle) {
	float degree;
	degree = angle * 180 / PI;
	return degree;
}

// 単位行列を代入する
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f};
}

// スケール行列を生成する
void MathMyFunc::GenerateScaleMatrix(Vector3 scale, Matrix4& matScale) {
	// 単位行列を代入する
	GenerateIdentityMatrix(matScale);

	// スケーリング倍率を行列に設定する
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
}

// X軸回転の行列を生成する
void MathMyFunc::GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation) {
	// 単位行列を代入する
	GenerateIdentityMatrix(matRotation);

	// X軸回転行列の各要素を設定する
	matRotation.m[1][1] = cos(rotation.x);
	matRotation.m[1][2] = sin(rotation.x);
	matRotation.m[2][1] = -sin(rotation.x);
	matRotation.m[2][2] = cos(rotation.x);
}

// Y軸回転の行列を生成する
void MathMyFunc::GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation) {
	// 単位行列を代入する
	GenerateIdentityMatrix(matRotation);

	// Y軸回転行列の各要素を設定する
	matRotation.m[0][0] = cos(rotation.y);
	matRotation.m[0][2] = -sin(rotation.y);
	matRotation.m[2][0] = sin(rotation.y);
	matRotation.m[2][2] = cos(rotation.y);
}

// Z軸回転の行列を生成する
void MathMyFunc::GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation) {
	// 単位行列を代入する
	GenerateIdentityMatrix(matRotation);

	// Z軸回転行列の各要素を設定する
	matRotation.m[0][0] = cos(rotation.z);
	matRotation.m[0][1] = sin(rotation.z);
	matRotation.m[1][0] = -sin(rotation.z);
	matRotation.m[1][1] = cos(rotation.z);
}

// 平行移動行列を生成する
void MathMyFunc::GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans) {
	// 単位行列を代入する
	GenerateIdentityMatrix(matTrans);

	// 移動量を行列に設定する
	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;
}

// 行列の計算(mat1が元になる値)
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 mat1, Matrix4 mat2) {
	// 代入用変数
	Matrix4 result;

	for (int i = 0; i < 4; i++) {
		result.m[0][i] = mat1.m[0][0] * mat2.m[0][i] + mat1.m[0][1] * mat2.m[1][i] +
			mat1.m[0][2] * mat2.m[2][i] + mat1.m[0][3] * mat2.m[3][i];
		result.m[1][i] = mat1.m[1][0] * mat2.m[0][i] + mat1.m[1][1] * mat2.m[1][i] +
			mat1.m[1][2] * mat2.m[2][i] + mat1.m[1][3] * mat2.m[3][i];
		result.m[2][i] = mat1.m[2][0] * mat2.m[0][i] + mat1.m[2][1] * mat2.m[1][i] +
			mat1.m[2][2] * mat2.m[2][i] + mat1.m[2][3] * mat2.m[3][i];
		result.m[3][i] = mat1.m[3][0] * mat2.m[0][i] + mat1.m[3][1] * mat2.m[1][i] +
			mat1.m[3][2] * mat2.m[2][i] + mat1.m[3][3] * mat2.m[3][i];
	}

	return result;
}

// Vector3とMatrix4の掛け算
Vector3 MathMyFunc::MatrixCalculation(Vector3 vector, Matrix4 mat) {
	// 代入用変数
	Vector3 result;

	result.x = vector.x * mat.m[0][0] + vector.y * mat.m[1][0] + vector.z * mat.m[2][0];
	result.y = vector.x * mat.m[0][1] + vector.y * mat.m[1][1] + vector.z * mat.m[2][1];
	result.z = vector.x * mat.m[0][2] + vector.y * mat.m[1][2] + vector.z * mat.m[2][2];

	return result;
}