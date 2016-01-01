#pragma once
#include <Windows.h>




















class cTimer
{
public:
	cTimer();
	~cTimer();


private:
	bool m_bStop;
	bool m_bPause;

	DWORD m_StartTime;						// Ÿ�̸� ���� ���� �ð�
	DWORD m_PauseTime;						// �߰��߰� �Ͻ������� �� �ð�

	DWORD m_BeginPauseTime;					// ���������� Pause�� �ð�


public:
	DWORD ElapsedTime() const;				// �Ͻ����� �ð��� �����ϰ� Start���� �帥 �ð�
	DWORD PausedTime() const;				// Start���� �Ͻ����� �� �ð�


public:
	void Start();
	void Stop();
	void Pause();
};

