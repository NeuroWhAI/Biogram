#include "BiogramWorld.h"

#include <type_traits>



























template <typename T_DEVICE>
int BiogramWorld::initDeviceForeachCage(const T_DEVICE& originalDevice)
{
	static_assert(std::is_base_of<Device, T_DEVICE>::value,
		"is_base_of<Device, T_DEVICE>");


	for (auto& cage : m_pCageList)
	{
		auto newDevice = std::make_shared<T_DEVICE>(originalDevice);
		newDevice->connectTo(cage);

		this->addDevice(newDevice);
	}


	return 0;
}


template <typename T_DIRECTOR>
int BiogramWorld::initDirector(const T_DIRECTOR& originalDirector)
{
	static_assert(std::is_base_of<Director, T_DIRECTOR>::value,
		"is_base_of<Director, T_DIRECTOR>");


	auto newDirector = std::make_shared<T_DIRECTOR>(originalDirector);
	m_directorList.emplace_back(newDirector);


	return 0;
}

