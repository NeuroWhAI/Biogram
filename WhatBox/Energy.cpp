#include "Energy.h"

#include <cmath>




























Energy::Energy()
	: m_energy(0.0)
{

}


Energy::Energy(double energy)
	: m_energy(energy)
{

}


Energy::~Energy()
{

}

//###############################################################

void Energy::setEnergy(double energy)
{
	m_energy = energy;
}


void Energy::addEnergy(double deltaEnergy)
{
	m_energy += deltaEnergy;
}


double Energy::getEnergy() const
{
	return m_energy;
}

//---------------------------------------------------------------

void Energy::setMass(double mass)
{
	m_energy = mass * 9.0e4/*c'^2*/;
}


void Energy::addMass(double deltaMass)
{
	m_energy += deltaMass * 9.0e4/*c'^2*/;
}


double Energy::toMass() const
{
	return m_energy / 9.0e4/*c'^2*/;
}

//---------------------------------------------------------------

void Energy::setTemperature(double temp, double mass)
{
	m_energy = temp * mass;
}


void Energy::addTemperature(double deltaTemp, double mass)
{
	m_energy += deltaTemp * mass;
}


double Energy::toTemperature(double mass) const
{
	return m_energy / mass;
}

