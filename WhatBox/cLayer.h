#pragma once
#include <d3dx9.h>



























class cLayer
{
public:
	cLayer();
	virtual ~cLayer();


public:
	int Init();
	int Destroy();

	int Update();
	int Render();


protected:
	virtual int OnInit() = 0;
	virtual int OnDestory() = 0;

	virtual int OnUpdate() = 0;
	virtual int OnRender() = 0;
};

