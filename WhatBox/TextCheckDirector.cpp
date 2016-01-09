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

int TextCheckDirector::readyForNextG()
{



	return 0;
}


double TextCheckDirector::evaluate(const TextPrinterDevice& device)
{
	std::wstring text = device.getText();


	double score = 0.0;


	const size_t answerLength = m_answer.size();
	const size_t textLength = text.length();


	if (answerLength > 0 && textLength > 0)
		score += 1.0;
	else if (answerLength == 0 && textLength == 0)
		score += 1.0;

	if (answerLength > textLength)
		score += 1.0 / (answerLength - textLength);
	else if (textLength > answerLength)
		score += 1.0 / (textLength - answerLength);
	else
		score += 1.1;


	for (size_t i = 0; i < answerLength && i < textLength; ++i)
	{
		if (m_answer[i] == text[i])
			score += 1.1;
		else
			score += 1.0 / std::abs(static_cast<double>(m_answer[i]) - text[i]);
	}


	return score;
}

