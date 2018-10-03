#include "graphic.h"
#include "Texture.h"

TEXTUREINFO TextureInfo [TEXTURE_MAX];

TEXTUREINFO* GetTextInfo () { return TextureInfo; }

// �e�N�X�`���̓ǂݍ���
// ��1�����F("�摜�̖��O.�g���q"), ��2�����F�e�N�X�`���̔ԍ�, ���ߐFRGB 
bool LoadTexture ( LPCSTR lpFileName, int TextuerNumber, int iColorRed, int iColorGreen, int iColorBlue )
{
	LPDIRECT3DDEVICE9 pD3Device = Getd3Device ();

	// �e�N�X�`�������ɓǂݍ���ł���ꍇ�͂����ŉ������
	if ( FAILED (D3DXCreateTextureFromFileExA (
					pD3Device,
					lpFileName,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT_NONPOW2,
					D3DX_DEFAULT,
					0,
					D3DFMT_UNKNOWN,
					D3DPOOL_MANAGED,
					D3DX_FILTER_NONE,
					D3DX_FILTER_NONE,
					D3DCOLOR_ARGB ( 0, iColorRed, iColorGreen, iColorBlue ),
					NULL, NULL,
					&TextureInfo [TextuerNumber].pTexture))) {
						MessageBoxA(0,"�e�N�X�`�����ǂݍ��߂܂���ł���(����;)",NULL,MB_OK);
						return false;
	}

	// �e�N�X�`�����擾
	D3DSURFACE_DESC desc;

	TextureInfo [TextuerNumber].pTexture -> GetLevelDesc ( 0, &desc );
	TextureInfo [TextuerNumber].width = desc.Width;
	TextureInfo [TextuerNumber].height = desc.Height;

	

	return true;
}

//	�g�p����S�Ẳ摜��ǂݍ���
bool AllLoadTexture ()
{
	LoadTexture ( "resource/texture/Logo.png", TEX_TEAM_LOGO, 0, 0, 255 );
	LoadTexture ( "resource/texture/stage1.png", TEX_BACKGROUND, 0, 0, 255 );

	return true;
}

// �e�N�X�`���̉��
// ��1�����F�e�N�X�`���̔ԍ�
void ReleaseTexture ( int TextuerNumber )
{
	SAFE_RELEASE ( TextureInfo[TextuerNumber].pTexture );
}

// �g�p���Ă���S�Ẵe�N�X�`���̉��
void ReleaseAllTexture ()
{
	for ( int i = 0; i < TEXTURE_MAX; i++ )
	{
		ReleaseTexture (i);
	}
}