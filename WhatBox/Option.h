#pragma once










///////////////////////////////////////////////////////////////////////////////////////////////////////
// Name : ��ó�� �ɼ�
// Desc : ������ �������� ���� ���׿� ���ؼ� ����ȭ������ ��ó���� ����.
///////////////////////////////////////////////////////////////////////////////////////////////////////

#define nUSE_COORDINATE
#ifndef USE_COORDINATE				// ��ǥ�� ���
#define NOTUSE_COORDINATE
#endif

#define USE_VFR
#ifndef USE_VFR						// ���������ӷ���Ʈ ���
#define NOTUSE_VFR
#endif

#define nUSE_RSLIGHT
#ifndef USE_RSLIGHT					// D3DRS_LIGHTING ���
#define NOTUSE_RSLIGHT
#endif

#define VIEW_3D
#ifndef VIEW_3D						// 3D��� ���ͺ��
#define VIEW_QUARTER
#endif

#define nDIMENSION_3D
#ifndef DIMENSION_3D				// 3D�� 2D��
#define DIMENSION_2D
#endif

#define SINGLE_GAME
#ifndef SINGLE_GAME					// �̱۰����̳� ��Ƽ�����̳�
#define MULTI_GAME
#endif

