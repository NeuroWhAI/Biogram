#pragma once
#include <d3dx9.h>
#include <vector>

class cLayer;
class cLayer_Fade;
class cLayer_UI;
class cLayer_Effect;
class cLayer_Unit;
class cLayer_Back;




























class cWorld
{
public:
	cWorld();
	~cWorld();


public:
	enum LAYER
	{
		LAYER_Fade,
		LAYER_UI,
		LAYER_Effect,
		LAYER_Unit,
		LAYER_Back,
	};


private:
	std::vector<cLayer*> m_pLayerList;


public:
	int Init();
	int Destroy();

	int Update();
	int Render();

	// UI, Effect, Unit, Back 초기화 (Fade는 제외)
	int Reset();


public:
	cLayer_Fade* GetFadeLayer();
	cLayer_UI* GetUILayer();
	cLayer_Effect* GetEffectLayer();
	cLayer_Unit* GetUnitLayer();
	cLayer_Back* GetBackLayer();
};

