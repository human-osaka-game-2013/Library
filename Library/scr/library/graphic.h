#ifndef	_GRAPHIC_H_
#define _GRAPHIC_H_

#include "lib_head.h"
//	
LPDIRECT3DDEVICE9	Getd3Device ();

//	�g�p����S�Ẳ摜��ǂݍ���
bool AllLoadTexture ();

// �e�N�X�`���̔ԍ��ƃe�N�X�`���S�̂̏c���̑傫��
struct TEXTUREINFO
{
	// �e�N�X�`���̊i�[�|�C���^
	LPDIRECT3DTEXTURE9	pTexture;

	int		width, height;
};

TEXTUREINFO* GetTextInfo();

// �摜�̒��_���W�Ȃǂ̍\����
struct CUSTOMVERTEX
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};
struct VERTEXS
{
	FLOAT	x, y, z, rhw;

	DWORD	color;

	FLOAT	tu, tv;
};

#endif