#pragma once



























class Energy
{
public:
	Energy();
	Energy(double energy);
	virtual ~Energy();


protected:
	double m_energy;


public:
	void setEnergy(double energy);
	void addEnergy(double deltaEnergy);
	double getEnergy() const;

	void setMass(double mass);
	void addMass(double deltaMass);
	double toMass() const;

	void setTemperature(double temp, double mass);
	void addTemperature(double deltaTemp, double mass);
	double toTemperature(double mass) const;
};

