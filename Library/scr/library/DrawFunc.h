
#ifndef _DRAW_FUNC_H_
#define _DRAW_FUNC_H_


//	(������)�`��
//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
//	6,7�F����uv���W 8,9�F�E��uv���W 
void VertexDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
			float fTu, float fTv, float fTu2, float fTv2);

//	�F����ς���(������)�`��
//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
//	6,7�F����uv���W 8,9�F�E��uv���W 
//	������11�`14�F�FARGB�l
void CustomCorolDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
				float fTu, float fTv, float fTu2, float fTv2, int iA, int iR, int iG, int iB );

//	���S�_����`��
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4,5�F�摜�̏c����
//	������6,7�F�摜�̍����UV���W 8,9:�摜�̉E����UV���W
void CenterDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 );

//	���S�_����`�� (��])
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F�摜�̏c����
//	������7,8�F�摜�̍����UV���W 9,10:�摜�̉E����UV���W
void SpinerDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 );

//	���S�_����`�� (�F���ω�)
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F���_�̏c����
//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
void ColorKeyDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int iA, int iR, int iG, int iB );

//	���S�_����`�� (�L�k)
//	������1�F�e�N�X�`���̔ԍ� 2,3�F�L�k�������_X,Y 4�F�p�x 5,6�F�摜�̏c����
//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
void ElasticityDraw ( int TextuerNumber, float fXpos, float fYpos, float& fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int& iA, int& iR, int& iG, int& iB );

#endif