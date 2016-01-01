#pragma once
#include <vector>



































class cValueProcMgr
{
public:
	cValueProcMgr();
	~cValueProcMgr();


private:
	class cPtrValue
	{
	public:
		cPtrValue(float* pVal, float targetVal, float speed, float accelSpeed)
			: pVal(pVal), targetVal(targetVal), speed(speed), accelSpeed(accelSpeed)
		{}

		cPtrValue(const cPtrValue& other)
			: pVal(other.pVal), targetVal(other.targetVal), speed(other.speed), accelSpeed(other.accelSpeed)
		{}


	public:
		float* pVal;
		float targetVal;
		float speed;
		float accelSpeed;
	};


private:
	std::vector<cPtrValue> m_ptrValueList;


public:
	int AddValueAnimation(float* pVal, float targetVal, float speed, float accelSpeed = 0.f);
	int Remove(const float* pVal);
	bool isEnd(const float* pVal);


public:
	int FrameMove();
};

