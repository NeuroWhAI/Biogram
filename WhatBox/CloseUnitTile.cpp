#include "CloseUnitTile.h"

#include <numeric>

#include "Unit.h"



























CloseUnitTile::CloseUnitTile()
{

}


CloseUnitTile::~CloseUnitTile()
{

}

//###############################################################

int CloseUnitTile::afterUpdate(double timePitch)
{
	float timePitchF = static_cast<float>(timePitch);


	ObjectIterator objIterator1 = getObjectIterator();

	while(!objIterator1.isEnd())
	{
		auto pUnit1 = *objIterator1;
		auto location1 = pUnit1->getLocation();
		float radius1 = pUnit1->getRadius();
		double mass1 = pUnit1->getMass();


		ObjectIterator objIterator2 = objIterator1;
		++objIterator2;
		while(!objIterator2.isEnd())
		{
			auto pUnit2 = *objIterator2;
			auto location2 = pUnit2->getLocation();
			float radius2 = pUnit2->getRadius();
			double mass2 = pUnit2->getMass();


			Utility::PointF subVec = location1 - location2;
			float meetDistance = radius1 + radius2;
			float distanceSq = subVec.getLengthSq();

			// �浹������
			if (distanceSq < meetDistance*meetDistance)
			{
				float distance = std::sqrt(distanceSq);


				// �Ϻ��� ��ġ�� ��Ȳ���� �������� �� �ֵ��� ��
				if (distance == 0.0f)
					subVec.x = 4.0f;


				// distance�� �ʹ� ������ �̴� ���� �ʹ� Ŀ���Ƿ� ������ ��
				if (distance < 4.0f)
					distance = 4.0f;


				// �̴� ���� ���
				float massRate = static_cast<float>(mass1 / (mass1 + mass2));
				float power = meetDistance / distance * 0.5f * timePitchF;
				float pushPower1 = power * (1.0f - massRate);
				float pushPower2 = power * massRate;
				subVec /= distance;


				// �о
				pUnit1->addSpeed(subVec * pushPower1);
				pUnit2->addSpeed(-subVec * pushPower2);
			}


			++objIterator2;
		}


		++objIterator1;
	}


	return 0;
}


bool CloseUnitTile::afterAddUnit(std::shared_ptr<Unit> pObj)
{



	return true;
}


bool CloseUnitTile::beforeRemoveUnit(std::shared_ptr<Unit> pObj)
{
	


	return true;
}

