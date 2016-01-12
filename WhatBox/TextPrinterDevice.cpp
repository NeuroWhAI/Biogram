#include "TextPrinterDevice.h"

#include "System.h"

#include "Director.h"



























TextPrinterDevice::TextPrinterDevice()
	: Device({
		{0, 100},
		{1, 200},
		{2, 300},
		{3, 400} })
{

}


TextPrinterDevice::~TextPrinterDevice()
{

}

//#################################################################

int TextPrinterDevice::init()
{
	m_text.clear();
	m_realText.clear();


	return 0;
}


int TextPrinterDevice::update(double timeSpeed)
{
	if (std::abs(readCom(0)) > std::numeric_limits<double>::epsilon())
	{
		m_text.clear();
		m_realText.clear();


		for (int port = 1; port <= 3; ++port)
		{
			double readVal = std::abs(readCom(port));
			if (readVal > 65535) readVal = 65535;
			wchar_t ch = static_cast<wchar_t>(readVal);

			if (ch != L'\n' && ch != L'\r')
			{
				m_text.push_back(ch);
				m_realText.push_back(ch);
			}
			else
			{
				m_text.push_back(L'\0');
				m_realText.push_back(L'\0');
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

const std::wstring& TextPrinterDevice::getText() const
{
	return m_text;
}


const std::vector<wchar_t>& TextPrinterDevice::getRealText() const
{
	return m_realText;
}

