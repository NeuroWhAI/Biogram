#pragma once

#include <memory>
#include <vector>

class ComPort;
class BiogramCage;
class ObjectViewer;
class Director;



























class Device
{
public:
	Device(const std::vector<std::pair<int, int>>& portNum_address,
		int thickness = 1);
	virtual ~Device();


private:
	std::shared_ptr<BiogramCage> m_pConnectedCage;


private:
	std::shared_ptr<ComPort> m_pComPort;
	std::vector<std::pair<int, int>> m_connectionInfo;


public:
	virtual int init();
	virtual int update(double timeSpeed);
	virtual int render();


public:
	int connectTo(std::shared_ptr<BiogramCage> pCage);


protected:
	double readCom(int portNum) const;
	bool writeCom(int portNum, double value);


public:
	virtual double evaluate(std::shared_ptr<Director> pDirector);


public:
	std::shared_ptr<BiogramCage> getConnectedCage();
	std::shared_ptr<const ComPort> getComPort() const;


private:
	std::vector<std::pair<int, int>> createThickComPort(
		const std::vector<std::pair<int, int>>& portNum_address,
		int thickness);
};

