#ifndef _SELECT_H_
#define _SELECT_H_
#include "../library/Scene.h"

class CSelect : public CScene
{
private:

public:
	//	�R���X�g���N�^
	CSelect( int _id );

public:
	//	������
	bool Init();	
	//	����
	int	 Control();	
	//	2D�`��
	void Draw();	
	//	3D�`��
	void Render( CRenderManager* pRndMg );	
};

#endif