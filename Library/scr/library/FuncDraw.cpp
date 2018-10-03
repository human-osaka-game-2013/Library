#include "Texture.h"
#include "graphic.h"

//----------------------------------------------------------------------------
//	�v���g�^�C�v�錾
//----------------------------------------------------------------------------


//	(������)�`��
//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
//	6,7�F����uv���W 8,9�F�E��uv���W 
void VertexDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
			float fTu, float fTv, float fTu2, float fTv2)
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	CUSTOMVERTEX customVertex[4] ={
		{ fXpos			, fYpos			, 0.5f, 1.0f, 0xffffffff, fTu, fTv },
		{ fXpos+fWidth	, fYpos			, 0.5f, 1.0f, 0xffffffff, fTu2, fTv },
		{ fXpos+fWidth	, fYpos+fHeight , 0.5f, 1.0f, 0xffffffff, fTu2, fTv2 },
		{ fXpos			, fYpos+fHeight , 0.5f, 1.0f, 0xffffffff, fTu, fTv2 }
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

//	�F����ς���(������)�`��
//	����>1�F�e�N�X�`���̔ԍ� 2,3�F�`��̊�ƂȂ鍶��̓_xy, 4,5�F���_�̏c���� 
//	6,7�F����uv���W 8,9�F�E��uv���W 
//	������11�`14�F�FARGB�l
void CustomCorolDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
				float fTu, float fTv, float fTu2, float fTv2, int iA, int iR, int iG, int iB )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	CUSTOMVERTEX customVertex[4] ={
	 { fXpos		, fYpos			, 0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu, fTv },
	 { fXpos+fWidth	, fYpos			, 0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv },
	 { fXpos+fWidth	, fYpos+fHeight , 0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv2 },
	 { fXpos		, fYpos+fHeight , 0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu, fTv2 }
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );
}

//	���S�_����`��
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4,5�F�摜�̏c����
//	������6,7�F�摜�̍����UV���W 8,9:�摜�̉E����UV���W
void CenterDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	CUSTOMVERTEX customVertex[4] = {
		{ fXpos -fWidth/2, fYpos -fHeight/2, 0.5f, 1.0f, 0xffffffff, fTu1, fTv1 },
		{ fXpos + fWidth/2, fYpos -fHeight/2, 0.5f, 1.0f, 0xffffffff, fTu2, fTv1 },
		{ fXpos + fWidth/2, fYpos +fHeight/2, 0.5f, 1.0f, 0xffffffff, fTu2, fTv2 },
		{ fXpos -fWidth/2, fYpos +fHeight/2, 0.5f, 1.0f, 0xffffffff, fTu1, fTv2 },
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

//	���S�_����`�� (��])
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F�摜�̏c����
//	������7,8�F�摜�̍����UV���W 9,10:�摜�̉E����UV���W
void SpinerDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	float fRad = fAngle * D3DX_PI / 180.0f;

	CUSTOMVERTEX customVertex[4] = {
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, fTu1, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, fTu2, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, fTu2, fTv2 },
		
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, 0xffffffff, fTu1, fTv2 },
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

//	���S�_����`�� (�F���ω�)
//	������1�F�e�N�X�`���̔ԍ� 2,3�F��ƂȂ钆�S�_ 4�F�X�������p�x(�X���Ȃ��Ȃ�0��OK) 5,6�F���_�̏c����
//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
void ColorKeyDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int iA, int iR, int iG, int iB )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	float fRad = fAngle * D3DX_PI / 180.0f;

	CUSTOMVERTEX customVertex[4] = {
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu1, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv2 },
		
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu1, fTv2 },
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}

//	���S�_����`�� (�L�k)
//	������1�F�e�N�X�`���̔ԍ� 2,3�F�L�k�������_X,Y 4�F�p�x 5,6�F�摜�̏c����
//	������7,8�F�����UV���W 9,10:�E����UV���W 11�`14�FARGB�l
void ElasticityDraw ( int TextuerNumber, float fXpos, float fYpos, float& fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int& iA, int& iR, int& iG, int& iB )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	float fRad = fAngle * D3DX_PI / 180.0f;

	CUSTOMVERTEX customVertex[4] = {
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu1, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - ( -fHeight/2 ) * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + ( -fHeight/2 ) * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv1 },
		
		{ fXpos + fWidth/2 * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + fWidth/2 * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu2, fTv2 },
		
		{ fXpos + ( -fWidth/2 ) * cosf ( fRad ) - fHeight/2 * sinf ( fRad ),
		  fYpos + ( -fWidth/2 ) * sinf ( fRad ) + fHeight/2 * cosf ( fRad ),
		  0.5f, 1.0f, D3DCOLOR_ARGB( iA, iR, iG, iB ), fTu1, fTv2 },
	};

	TEXTUREINFO* TextureInfo = GetTextInfo();

	pD3Device -> SetTexture ( 0, TextureInfo[TextuerNumber].pTexture );
	pD3Device -> DrawPrimitiveUP(
		D3DPT_TRIANGLEFAN,
		2,
		customVertex,
		sizeof ( CUSTOMVERTEX ) );	
}