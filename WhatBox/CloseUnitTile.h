#pragma once

#include "Tile.h"

#include "Unit.h"



























class CloseUnitTile : public Tile<Unit>
{
public:
	CloseUnitTile();
	virtual ~CloseUnitTile();


protected:
	virtual int afterUpdate(double timePitch) override;
	virtual bool afterAddUnit(std::shared_ptr<Unit> pObj) override;
	virtual bool beforeRemoveUnit(std::shared_ptr<Unit> pObj) override;
};

