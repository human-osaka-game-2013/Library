
#ifndef _TITLE_H_
#define _TITLE_H_
#include "../library/Scene.h"

class CTitle : public CScene
{
private:

public:
	//	�R���X�g���N�^
	CTitle( int _id );

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