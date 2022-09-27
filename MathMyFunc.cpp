#include <random>
#include "MathMyFunc.h"
using namespace MathMyFunc;

// 度数をラジアンに変換する
float MathMyFunc::RadianTransform(float degreeAngle) {
	float rad;
	rad = degreeAngle * PI / 180;
	return rad;
}

// ラジアンを度数に変換する
float MathMyFunc::DegreeTransform(float radAngle) {
	float degree;
	degree = radAngle * 180 / PI;
	return degree;
}

// 転置行列
void MathMyFunc::TransposedMatrix(Matrix4& mat) {
	Matrix4 m1;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			m1.m[j][i] = mat.m[i][j];
		}
	}

	mat = m1;
}

// 単位行列を代入する
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = { 1.0f, 0.0f, 0.0f, 0.0f,
				0.0f, 1.0f, 0.0f, 0.0f,
				0.0f, 0.0f, 1.0f, 0.0f,
				0.0f, 0.0f, 0.0f, 1.0f
	};
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
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 m1, Matrix4 m2) {
	// 代入用変数
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

// Vector3とMatrix4の掛け算
Vector3 MathMyFunc::MatrixCalculation(Vector3 vector, Matrix4 mat) {
	// 代入用変数
	Vector3 result;

	result.x = vector.x * mat.m[0][0] + vector.y * mat.m[1][0] + vector.z * mat.m[2][0];
	result.y = vector.x * mat.m[0][1] + vector.y * mat.m[1][1] + vector.z * mat.m[2][1];
	result.z = vector.x * mat.m[0][2] + vector.y * mat.m[1][2] + vector.z * mat.m[2][2];

	return result;
}

namespace MathRandom {
#pragma region 乱数生成
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());

	//乱数範囲の設定(角度)
	std::uniform_real_distribution<float> distAngle(0.0f, PI);

	//乱数範囲の設定(座標)
	std::uniform_real_distribution<float> distPos(-10.0f, 10.0f);
#pragma endregion

} // namespace MathRandom