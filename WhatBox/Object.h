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
	Utility::PointD m_speed;


public:
	void setMass(double mass);
	void addMass(double deltaMass);
	double getMass() const;

	void setTemperature(double temp);
	void addTemperature(double deltaTemp);
	double getTemperature() const;

	void setLocation(float x, float y);
	void setLocation(const Utility::PointF location);
	void addLocation(float dx, float dy);
	void addLocation(const Utility::PointF deltaLocation);
	Utility::PointF getLocation() const;

	void setSpeed(double x, double y);
	void setSpeed(const Utility::PointD speed);
	void addSpeed(double dx, double dy);
	void addSpeed(const Utility::PointD deltaSpeed);
	Utility::PointD getSpeed() const;
};

