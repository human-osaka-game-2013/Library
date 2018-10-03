#ifndef _LOGO_H_
#define _LOGO_H_
#include "../library/Scene.h"
#include "LogoObject.h"

class CLogo : public CScene
{
public:
	enum OBJECT_ID {
		TEAM_LOGO,
		LOGO_MAX
	};

private:
	CLogoObject logo;

public:
	//	�R���X�g���N�^
	CLogo( int _id );	

public:
	//	������
	bool Init();	
	//	����
	int	 Control();	
	//	2D�`��
	void Draw();	
	//	3D�`��
	void Render( CRenderManager* pRndMg ){};	
};

#endif