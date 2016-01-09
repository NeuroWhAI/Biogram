#include "TextPrinterDevice.h"

#include "System.h"

#include "Director.h"



























TextPrinterDevice::TextPrinterDevice()
	: Device({
		{0, 100},
		{1, 200} })
{

}


TextPrinterDevice::~TextPrinterDevice()
{

}

//#################################################################

int TextPrinterDevice::readyForNextG()
{
	m_text.clear();
	m_textCompleted.clear();


	return 0;
}


int TextPrinterDevice::update(double timeSpeed)
{
	if (std::abs(readCom(0)) > std::numeric_limits<double>::epsilon())
	{
		double readVal = std::abs(readCom(1));
		if (readVal > 65535) readVal = 65535;
		wchar_t ch = static_cast<wchar_t>(readVal);

		if (ch == L'\0' || ch == L'\n' || ch == L'\r')
		{
			m_textCompleted = m_text;
			m_text.clear();
		}
		else
		{
			m_text.push_back(ch);

			// 문장이 너무 길면 강제로 완료시킴
			if (m_text.length() >= 64)
			{
				m_textCompleted = m_text;
				m_text.clear();
			}
		}
	}


	return 0;
}


int TextPrinterDevice::render()
{
	System::getInstance().getObjectViewer().
		draw(*this);


	return 0;
}

//#################################################################

double TextPrinterDevice::evaluate(std::shared_ptr<Director> pDirector)
{
	return pDirector->evaluate(*this);
}

//#################################################################

std::wstring TextPrinterDevice::getText() const
{
	return m_textCompleted;
}

