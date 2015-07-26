//#include <stdio.h>
//#include <stdlib.h>
//
//#include "read_file.h"
//
//bool	bReadFlag = false;
//
//void SetTable ( int iTableNum, int i_W, int i_H, int i_L_C, char* p )
//{
//	int iTemp = atoi(p);
//
//	if ( i_L_C < 5 )
//	{
//		iAddBlockTable[iTableNum][i_W][i_H].iType		= iTemp / 10;
//		iAddBlockTable[iTableNum][i_W][i_H].iDirection	= iTemp % 10;
//	}
//	else
//	{
//		iBlockTable[iTableNum][i_W][i_H].iType		= iTemp / 10;
//		iBlockTable[iTableNum][i_W][i_H].iDirection	= iTemp % 10;
//	}
//}
//
//#ifndef	STR
//void ReadTable ( FILE* fp, int iTableNum )
//{
//	char	buf[256];
//	char* p, *q;
//	
//	int iWidth = 0, iHeight = 3;
//	int	iLoopCount = 1;
//
//	while ( fgets ( buf, 256, fp) != NULL )
//	{
//		p = buf;
//		
//		do
//		{
//			q = strstr( p, "," );
//			
//			if ( q != NULL ) *q = '\0';
//
//			SetTable ( iTableNum, iWidth, iHeight, iLoopCount, p );
//
//			p = q + 1;
//
//			iWidth++;
//
//		}while ( q != NULL );
//
//		//printf ( "\n" );
//		if ( iLoopCount < 4 )		{ iHeight--;	}
//		else if ( iLoopCount == 4 )	{ iHeight = 0;	}
//		else if ( iLoopCount > 4 )	{ iHeight++;	}
//
//		iWidth = 0;
//		iLoopCount++;
//	}
//	iHeight = 0;
//}
//
//#else
//
//void SetTable ( FILE* fp, int iTableNum )
//{
//	int result = 0, iWidth = 0;
//	while ( ( result = fscanf( fp, "%d, %d, %d, %d, %d,"
//							,&iBlockTable[iTableNum][0][iHeight] 
//							,&iBlockTable[iTableNum][1][iHeight]
//							,&iBlockTable[iTableNum][2][iHeight]
//							,&iBlockTable[iTableNum][3][iHeight]
//							,&iBlockTable[iTableNum][4][iHeight] ) ) != EOF )
//	{
//		printf("%d %d %d %d %d\n"
//				,iBlockTable[iTableNum][0][iHeight]
//				,iBlockTable[iTableNum][1][iHeight]
//				,iBlockTable[iTableNum][2][iHeight]
//				,iBlockTable[iTableNum][3][iHeight]
//				,iBlockTable[iTableNum][4][iHeight]	);
//
//		iHeight++;
//	}
//}
//
//#endif
//
//bool ReadFile( char* pFileName, int iFileType )
//{
//	FILE*	fp;
//		
//	if ( ( fp = fopen( pFileName, "r" ) ) != NULL )
//	{
//		ReadTable (fp, iFileType);
//
//		fclose (fp);
//	}
//	else
//	{
//		//printf( "%sファイルが開けません", cFileName );
//		return false;
//	}
//	
//	return true;
//}
//
////	ステージブロックの種類か向きを渡す
////	引数＞1：セット番号 2：ブロックの種類(eTYPE),ブロックの向き(eDirection) 3：行数(STAGE_WIDTH), 4：列数(STAGE_HEIGHT)
//int	PassStageBlock ( int iSetNum, int iInfoType, int iWidth, int iHeight )
//{
//	int	iTemp = 0;
//
////#ifdef	_DEBUG
////	iSetNum = 6;
////#endif
//
//	switch ( iInfoType )
//	{
//	case eTYPE:
//		iTemp = iBlockTable[iSetNum][iWidth][iHeight].iType;
//
//		break;
//
//	case eDirection:
//		iTemp = iBlockTable[iSetNum][iWidth][iHeight].iDirection;
//
//		break;
//	}
//
//	return iTemp;
//}
//
////	控えブロックの種類か向きを渡す
////	引数＞1：セット番号 2：種類(eTYPE)か向き(eDirection)を入れる 3：行数(STAGE_WIDTH), 4：列数(STAGE_HEIGHT)
//int	PassAddBlock ( int iSetNum, int iInfoType, int iWidth, int iHeight )
//{
//	int	iTemp = 0;
//
////#ifdef	_DEBUG
////	iSetNum = 6;
////#endif
//
//	switch ( iInfoType )
//	{
//	case eTYPE:
//		iTemp = iAddBlockTable[iSetNum][iWidth][iHeight].iType;
//
//		break;
//
//	case eDirection:
//		iTemp = iAddBlockTable[iSetNum][iWidth][iHeight].iDirection;
//
//		break;
//	}
//
//	return iTemp;
//}