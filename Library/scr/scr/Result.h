
#ifndef _RESULT_H_
#define _RESULT_H_
#include "../library/Scene.h"

class CResult : public CScene
{
private:

public:
	//	�R���X�g���N�^
	CResult( int _id );

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