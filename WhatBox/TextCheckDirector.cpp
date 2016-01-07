#include "TextCheckDirector.h"

#include "TextPrinterDevice.h"



























TextCheckDirector::TextCheckDirector(std::wstring answer)
	: m_answer(answer)
{

}


TextCheckDirector::~TextCheckDirector()
{

}

//#################################################################

double TextCheckDirector::evaluate(const TextPrinterDevice& device)
{
	std::wstring text = device.getText();


	double score = 0.0;


	if (m_answer.length() > text.length())
		score -= m_answer.length() - text.length();
	else if (text.length() > m_answer.length())
		score -= text.length() - m_answer.length();
	else
		score += 1.0;


	const size_t answerLength = m_answer.size();
	const size_t textLength = text.length();
	for (size_t i = 0; i < answerLength && i < textLength; ++i)
	{
		if (m_answer[i] == text[i])
			score += 10.0;
		else
			score -= std::abs(static_cast<double>(m_answer[i]) - text[i]);
	}


	return score;
}

