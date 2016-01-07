#pragma once



























class TimeManager
{
public:
	TimeManager();
	virtual ~TimeManager();


protected:
	double m_pitch;
	float m_pitchF;


protected:
	double m_elapsedTime;


public:
	int update();


public:
	void setPitch(double pitch);
	void setPitch(float pitchF);

	double getPitch() const;
	float getPitchF() const;


public:
	double getElapsedTime() const;
	void resetElapsedTime();
};

