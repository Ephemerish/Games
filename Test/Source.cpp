#include <iostream>
#include <string>

int m_rightScore = 0;
int m_leftScore = 0;

std::string getStanding()
{
	std::string standing;
	standing = std::to_string(m_leftScore) + " : " + std::to_string(m_rightScore);
	return standing;
}

int main()
{
	m_rightScore++;
	std::cout << getStanding();
	std::cin.get();
	return 0;
}