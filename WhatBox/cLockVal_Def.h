#pragma once
























template <typename T>
cLockVal<T>::cLockVal()
{
	InitializeCriticalSection(&m_Sec);
}


template <typename T>
cLockVal<T>::~cLockVal()
{
	DeleteCriticalSection(&m_Sec);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
T cLockVal<T>::GetValue()
{
	Lock();
	T temp = m_Value;
	UnLock();


	return temp;
}


template <typename T>
void cLockVal<T>::SetValue(T Val)
{
	Lock();
	m_Value = Val;
	UnLock();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <typename T>
void cLockVal<T>::Lock()
{
	EnterCriticalSection(&m_Sec);
}


template <typename T>
void cLockVal<T>::UnLock()
{
	LeaveCriticalSection(&m_Sec);
}

