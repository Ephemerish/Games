#include "Score.h"

namespace Pong
{
		Score::Score() :m_leftScore(0), m_rightScore (0)
		{
			scoreFont.loadFromFile("assets/Inconsolata-Bold.ttf");
			standing.setFont(scoreFont);
			standing.setCharacterSize(40);
			standing.setPosition(100.f, 150.f);
			standing.setFillColor(sf::Color::White);
			standing.setString("0 : 0");
		}

		void Score::addPointsLeft()
		{
			m_leftScore++;
		}

		void Score::addPointsRight()
		{
			m_rightScore++;
		}

		std::string Score::getStanding()
		{
			std::string Standing;
			Standing = "\t\t\t";
			Standing += std::to_string(m_leftScore) + " : " + std::to_string(m_rightScore);
			standing.setString(Standing);
			return Standing;
		}

		Score::~Score()
		{

		}
}