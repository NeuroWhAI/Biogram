#include "Object.h"



























Object::Object()
	: m_mass(0.0)
	, m_temperature(0.0)
	, m_location(0.0f, 0.0f)
	, m_radius(0.0f)
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

void Object::setLocationX(float x)
{
	m_location.x = x;
}


void Object::setLocationY(float y)
{
	m_location.y = y;
}


void Object::setLocation(float x, float y)
{
	m_location.x = x;
	m_location.y = y;
}


void Object::setLocation(const Utility::PointF location)
{
	m_location = location;
}


void Object::addLocationX(float dx)
{
	m_location.x += dx;
}


void Object::addLocationY(float dy)
{
	m_location.y += dy;
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

void Object::setRadius(float radius)
{
	m_radius = radius;
}


void Object::addRadius(float deltaRadius)
{
	m_radius += deltaRadius;
}


float Object::getRadius() const
{
	return m_radius;
}

