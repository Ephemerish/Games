#include <string>

namespace Pong
{
	class Score
	{
	private:
		int m_leftScore;
		int m_rightScore;
	public:
		Score();
		~Score();
		void addPointsLeft();
		void addPointsRight();
		std::string getStanding();
	};
}

