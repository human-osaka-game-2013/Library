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
	//	コンストラクタ
	CLogo( int _id );	

public:
	//	初期化
	bool Init();	
	//	処理
	int	 Control();	
	//	2D描画
	void Draw();	
	//	3D描画
	void Render( CRenderManager* pRndMg ){};	
};

#endif