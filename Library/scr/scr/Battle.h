
#ifndef _BATTLE_H_
#define _BATTLE_H_
#include "../library/Scene.h"
#include "Player.h"

#define	ONE_FR	60.f

class CBattle : public CScene
{
public:
	enum OBJECT_ID {
		
		PLAYER1,
		PLAYER2,
		PLAYER3,

		PLAYER_MAX,

		BACKGROUND = 0,
		OBJ_MAX,

		BLOCK = 0,
		BLOCK_MAX = BLOCK + 6,
		

		BATTLE_MAX
	};


	enum BATTLE_SCENE
	{
		CHARA_SELECT,

		BATTLE,

		RESULT
	};

	static const float WALK_SPEED;		//	(��)�ړ��X�s�[�h
	static const float GROUND_Y_LOW;	//	�X�e�[�W�̒n�ʈʒuY
	static const float STAGE_Z;			//	�X�e�[�W��Z�������̊���W
	static const float STAGE_X;			//	�X�e�[�W��X�������̍ő�l
	static const float STAGE_Y;			//	�X�e�[�W��Y�������̍ő�l
#define BLOCK_W 20.f
#define BLOCK_H 5.f

	/*
		�L�����Z���N�g�N���X
	*/
	class CSelect
	{
	private:
		CBattle* pBattle;	//	CBattle�̃|�C���^

	public:
		//	�R���X�g���N�^
		CSelect( CBattle* _pBattle );
	
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

	/*
		�o�g�����U���g�N���X
	*/
	class CResult
	{
	private:
		CBattle* pBattle;	//	CBattle�̃|�C���^

	public:
		//	�R���X�g���N�^
		CResult( CBattle* _pBattle );
	
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

private:
	CBattleObject battleObj[OBJ_MAX];
	CPlayer playerObj[PLAYER_MAX];
	CBarrier barrierObj[BLOCK_MAX];
	
	CSelect*	pSelect;	//	�L�����Z���N�g�N���X�̃|�C���^
	CResult*	pResult;	//	���U���g�N���X�̃|�C���^



public:
	//	�R���X�g���N�^
	CBattle( int _id );

	//	�f�X�g���N�^
	~CBattle();

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