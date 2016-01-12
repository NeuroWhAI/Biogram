#include "VoidDirector.h"

#include "VoidGameDevice.h"



























VoidDirector::VoidDirector()
{

}


VoidDirector::~VoidDirector()
{

}

//#################################################################

int VoidDirector::init()
{



	return 0;
}


double VoidDirector::evaluate(const VoidGameDevice& device)
{
	size_t fail = device.getFailCount();
	double success = device.getSuccessCount();


	if (fail == 0)
		return success;
	return success / (1.0 + fail);
}

