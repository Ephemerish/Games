#include <string>
#include <SFML/Graphics.hpp>
#include <cmath>

namespace Pong
{
	class Score
	{
	private:
		int m_leftScore;
		int m_rightScore;
	public:
		sf::Font scoreFont;
		sf::Text standing;
		Score();
		~Score();
		void addPointsLeft();
		void addPointsRight();
		std::string getStanding();
	};
}

