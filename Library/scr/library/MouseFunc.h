
#ifndef	_MOUSE_FUNC_H_
#define _MOUSE_FUNC_H_

long GetCursorPosX ();	//	�}�E�X���W�̎擾X
long GetCursorPosY ();	//	�}�E�X���W�̎擾Y

long GetCursorMoveVolX ();	//	�}�E�X�̈ړ��ʂ̎擾X
long GetCursorMoveVolY ();	//	�}�E�X�̈ړ��ʂ̎擾Y

void AllButtonCheck ();	//	�}�E�X�̑S�Ẵ{�^�����`�F�b�N
//	�}�E�X�{�^���ʏ�Ԕ���
//	��1����( �{�^���̎�� )�A��2����( �{�^���̏�� )
bool MouseStCheck ( int, int );

#endif