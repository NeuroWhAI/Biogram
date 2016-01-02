#include "Object.h"



























Object::Object()
	: m_mass(0.0)
	, m_temperature(0.0)
	, m_location(0.0f, 0.0f)
	, m_speed(0.0, 0.0)
{
	
}


Object::~Object()
{

}

//###############################################################

void Object::setMass(double mass)
{
	m_mass = mass;
}


void Object::addMass(double deltaMass)
{
	m_mass += deltaMass;
}


double Object::getMass() const
{
	return m_mass;
}

//---------------------------------------------------------------

void Object::setTemperature(double temp)
{
	m_temperature = temp;
}


void Object::addTemperature(double deltaTemp)
{
	m_temperature += deltaTemp;
}


double Object::getTemperature() const
{
	return m_temperature;
}

//---------------------------------------------------------------

void Object::setLocation(float x, float y)
{
	m_location.x = x;
	m_location.y = y;
}


void Object::setLocation(const Utility::PointF location)
{
	m_location = location;
}


void Object::addLocation(float dx, float dy)
{
	m_location.x += dx;
	m_location.y += dy;
}


void Object::addLocation(const Utility::PointF deltaLocation)
{
	m_location += deltaLocation;
}


Utility::PointF Object::getLocation() const
{
	return m_location;
}

//---------------------------------------------------------------

void Object::setSpeed(double x, double y)
{
	m_speed.x = x;
	m_speed.y = y;
}


void Object::setSpeed(const Utility::PointD speed)
{
	m_speed = speed;
}


void Object::addSpeed(double dx, double dy)
{
	m_speed.x += dx;
	m_speed.y += dy;
}


void Object::addSpeed(const Utility::PointD deltaSpeed)
{
	m_speed += deltaSpeed;
}


Utility::PointD Object::getSpeed() const
{
	return m_speed;
}

