#pragma once










///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : 전처리 옵션
// Desc : 실행후 변경점이 없는 사항에 대해선 최적화를위해 전처리를 쓴다.
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define nUSE_COORDINATE
#ifndef USE_COORDINATE				// 좌표계 사용
#define NOTUSE_COORDINATE
#endif

#define USE_VFR
#ifndef USE_VFR						// 가변프레임레이트 사용
#define NOTUSE_VFR
#endif

#define nUSE_RSLIGHT
#ifndef USE_RSLIGHT					// D3DRS_LIGHTING 사용
#define NOTUSE_RSLIGHT
#endif

#define VIEW_3D
#ifndef VIEW_3D						// 3D뷰냐 쿼터뷰냐
#define VIEW_QUARTER
#endif

#define nDIMENSION_3D
#ifndef DIMENSION_3D				// 3D냐 2D냐
#define DIMENSION_2D
#endif

#define SINGLE_GAME
#ifndef SINGLE_GAME					// 싱글게임이냐 멀티게임이냐
#define MULTI_GAME
#endif

