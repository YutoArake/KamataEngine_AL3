#include "WorldTransform.h"

void WorldTransform::UpdateWorldTransform(WorldTransform& worldTransform, AffinMatrix mat) {
	//�e��s��ݒ�
	GenerateScaleMatrix(worldTransform.scale_, mat.scale);
	GenerateRotateXMatrix(worldTransform.rotation_, mat.rotX);
	GenerateRotateYMatrix(worldTransform.rotation_, mat.rotY);
	GenerateRotateZMatrix(worldTransform.rotation_, mat.rotZ);
	GenerateTransformMatrix(worldTransform.translation_, mat.trans);

	//��]�s��̍���
	mat.rot = MatrixCalculation(MatrixCalculation(mat.rotX, mat.rotZ), mat.rotY);

	//�s��̍���
	mat.mix = MatrixCalculation(MatrixCalculation(mat.scale, mat.rot), mat.trans);

	//�s��̌v�Z
	//�P�ʍs����
	GenerateIdentityMatrix(worldTransform.matWorld_);
	//�X�P�[���A��]�A���s�ړ��s��̌v�Z
	worldTransform.matWorld_ = MatrixCalculation(worldTransform.matWorld_, mat.mix);
	//�e�̃��[���h�s��ƌv�Z
	if (worldTransform.parent_ != NULL) {
		worldTransform.matWorld_ =
			MatrixCalculation(worldTransform.matWorld_, worldTransform.parent_->matWorld_);
	}

	//�s��̓]��
	worldTransform.TransferMatrix();
}