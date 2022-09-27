#pragma once

#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

// 円周率
const float PI = 3.141592f;

// 構造体
// アフィン変換用
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

	// プロトタイプ宣言
	// ラジアン変換
	float RadianTransform(float degreeAngle);
	// 度数変換
	float DegreeTransform(float radAngle);

	// 転置行列
	void TransposedMatrix(Matrix4& mat);
	// 各種行列生成
	void GenerateIdentityMatrix(Matrix4& mat);
	void GenerateScaleMatrix(Vector3 scale, Matrix4& matScale);
	void GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation);
	void GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans);

	// 行列計算
	Matrix4 MatrixCalculation(Matrix4 mat1, Matrix4 mat2);
	Vector3 MatrixCalculation(Vector3 vector, Matrix4 mat);
	// プロトタイプ宣言ここまで

} // namespace MathMyFunc