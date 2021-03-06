#pragma once

#include "Utility.h"


























class Object
{
public:
	Object();
	virtual ~Object();


protected:
	double m_mass;
	double m_temperature;
	Utility::PointF m_location;
	float m_radius;


public:
	void setMass(double mass);
	void addMass(double deltaMass);
	double getMass() const;

	void setTemperature(double temp);
	void addTemperature(double deltaTemp);
	double getTemperature() const;

	void setLocationX(float x);
	void setLocationY(float y);
	void setLocation(float x, float y);
	void setLocation(const Utility::PointF location);
	void addLocationX(float dx);
	void addLocationY(float dy);
	void addLocation(float dx, float dy);
	void addLocation(const Utility::PointF deltaLocation);
	Utility::PointF getLocation() const;

	void setRadius(float radius);
	void addRadius(float deltaRadius);
	float getRadius() const;
};

