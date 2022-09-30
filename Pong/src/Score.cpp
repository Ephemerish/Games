#include "Score.h"
namespace Pong
{
		Score::Score() :m_leftScore(0), m_rightScore (0)
		{

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
			std::string standing;
			standing = "\t\t\t";
			standing += std::to_string(m_leftScore) + " : " + std::to_string(m_rightScore);
			return standing;
		}

		Score::~Score()
		{

		}
}