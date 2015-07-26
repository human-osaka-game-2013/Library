
#ifndef _DRAW_FUNC_H_
#define _DRAW_FUNC_H_


//	(左上基準で)描画
//	引数>1：テクスチャの番号 2,3：描画の基準となる左上の点xy, 4,5：頂点の縦横幅 
//	6,7：左上uv座標 8,9：右下uv座標 
void VertexDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
			float fTu, float fTv, float fTu2, float fTv2);

//	色調を変えて(左上基準で)描画
//	引数>1：テクスチャの番号 2,3：描画の基準となる左上の点xy, 4,5：頂点の縦横幅 
//	6,7：左上uv座標 8,9：右下uv座標 
//	引数＞11～14：：ARGB値
void CustomCorolDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
				float fTu, float fTv, float fTu2, float fTv2, int iA, int iR, int iG, int iB );

//	中心点から描画
//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4,5：画像の縦横幅
//	引数＞6,7：画像の左上のUV座標 8,9:画像の右下のUV座標
void CenterDraw ( int TextuerNumber, float fXpos, float fYpos, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 );

//	中心点から描画 (回転)
//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4：傾けたい角度(傾けないなら0でOK) 5,6：画像の縦横幅
//	引数＞7,8：画像の左上のUV座標 9,10:画像の右下のUV座標
void SpinerDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2 );

//	中心点から描画 (色調変化)
//	引数＞1：テクスチャの番号 2,3：基準となる中心点 4：傾けたい角度(傾けないなら0でOK) 5,6：頂点の縦横幅
//	引数＞7,8：左上のUV座標 9,10:右下のUV座標 11～14：ARGB値
void ColorKeyDraw ( int TextuerNumber, float fXpos, float fYpos, float fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int iA, int iR, int iG, int iB );

//	中心点から描画 (伸縮)
//	引数＞1：テクスチャの番号 2,3：伸縮させる基準点X,Y 4：角度 5,6：画像の縦横幅
//	引数＞7,8：左上のUV座標 9,10:右下のUV座標 11～14：ARGB値
void ElasticityDraw ( int TextuerNumber, float fXpos, float fYpos, float& fAngle, float fWidth, float fHeight,
						float fTu1, float fTv1, float fTu2, float fTv2, int& iA, int& iR, int& iG, int& iB );

#endif