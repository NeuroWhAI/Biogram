#pragma once
#include <d3dx9.h>
#include <vector>


































class cGraph
{
public:
	cGraph();
	virtual ~cGraph();


private:



public:
	int Update();
	int Render();


protected:
	virtual int OnUpdate();
	virtual int OnRender();
};

