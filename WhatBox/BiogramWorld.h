#pragma once

#include <memory>
#include <vector>

class TimeManager;
class Unit;



























class BiogramWorld
{
public:
	BiogramWorld();
	virtual ~BiogramWorld();


protected:
	std::shared_ptr<TimeManager> m_pTimeManager;


protected:
	std::vector<std::shared_ptr<Unit>> m_pUnitList;


public:
	int update();


protected:
	// * �ùķ��̼� �ӵ��� �������� ���ؼ�
	//   ����Ȯ���� �߻��ϴ� ���� �����ϱ�����
	//   �ð��� �帣�� �ӵ��� ����.
	int updateTimeSpeed();
	int updateUnit();


public:
	double getTimeSpeed() const;
	const std::vector<std::shared_ptr<Unit>>& getUnitList() const;
};

