#include <iostream>
#include <vector>
#include <algorithm>

int xGridSize;
int yGridSize;

struct Node
{
	int x;
	int y;
	bool isWall;
	bool isClosed;
	float fCost;
	float hCost;
	std::vector<Node*> neighbors;
	Node* parent;
};

std::vector<Node*> Nodes;
Node* Start;
Node* End;

void initNode(Node* node, const int& x, const int& y, bool l_isWall)
{
	node->x = x;
	node->y = y;
	node->isWall = l_isWall;
	node->isClosed = false;
	node->fCost = INFINITY;
	node->hCost = INFINITY;
	node->parent = nullptr;
}

void initNeighbours(Node* node)
{
	if (node->x > 0) node->neighbors.push_back(&Nodes[node->y][node->x - 1]);
	if (node->y > 0) node->neighbors.push_back(&Nodes[node->y - 1][node->x]);
	if (node->x < xGridSize - 1) node->neighbors.push_back(&Nodes[node->y][node->x + 1]);
	if (node->y < yGridSize - 1) node->neighbors.push_back(&Nodes[node->y + 1][node->x]);
}

void Init()
{
	std::string row;
	bool isStartFound = false;
	std::cout << "Input Dimension" << std::endl;
	std::cin >> xGridSize >> yGridSize;
	std::cout<< "\nInput Grid" << std::endl;

	for (int y = 0; y < yGridSize; y++)
	{
		Nodes.push_back(new Node[xGridSize]);
		std::cin >> row;
		for (int x = 0; x < xGridSize; x++)
		{
			bool isWall = false;
			if (row[x] == 'x') isWall = true;
			else if (row[x] == 'C' && !isStartFound) { Start = &Nodes[y][x]; isStartFound = true; }
			else if (row[x] == 'C' && isStartFound) End = &Nodes[y][x];
			else if (row[x] == '.') {}
			else { std::cout << "Error" << std::endl << "Invalid Input" << std::endl; exit;}

			initNode(&Nodes[y][x], x, y, isWall);
		}
	}

	for (int y = 0; y < yGridSize; y++)
	{
		for (int x = 0; x < xGridSize; x++)
		{
			initNeighbours(&Nodes[y][x]);
		}
	}
}

void AStarAlgo()
{
	auto GetDist = [](Node* P1, Node* P2) { return sqrt(pow(P2->x - P1->x, 2) + pow(P2->y - P1->y, 2)); };

	Node* currentNode = Start;
	Start->hCost = 0.0f;
	Start->fCost = GetDist(Start, End);

	std::vector<Node*> nodesToTest;
	nodesToTest.push_back(Start);

	while (!nodesToTest.empty() && currentNode != End)
	{
		std::sort(nodesToTest.begin(), nodesToTest.end(), [](const Node* a, const Node* b) { return a->fCost < b->fCost; });

		while (!nodesToTest.empty() && nodesToTest.front()->isClosed)
			nodesToTest.erase(nodesToTest.begin());

		if (nodesToTest.empty())
			break;

		currentNode = nodesToTest.front();
		currentNode->isClosed = true;

		for (auto nodeNeighbour : currentNode->neighbors)
		{
			if (!nodeNeighbour->isClosed && !nodeNeighbour->isWall)
				nodesToTest.push_back(nodeNeighbour);

			auto BestNode = currentNode->hCost + GetDist(currentNode, nodeNeighbour);

			if (BestNode < nodeNeighbour->hCost)
			{
				nodeNeighbour->parent = currentNode;
				nodeNeighbour->hCost = BestNode;

				nodeNeighbour->fCost = nodeNeighbour->hCost + GetDist(nodeNeighbour, End);
			}
		}
	}
}

void ShowPath()
{
	std::cout << "\nBest Path:" << std::endl;
	std::vector<std::vector<char>> finalGrid;

	for (size_t x = 0; x < xGridSize; x++)
	{
		std::vector<char> temp;
		for (size_t y = 0; y < yGridSize; y++)
		{
			if (Nodes[y][x].isWall) temp.push_back('x');
			else if (y == Start->y && x == Start->x || y == End->y && x == End->x) temp.push_back('C');
			else temp.push_back(' ');
		}
		finalGrid.push_back(temp);
		temp.clear();
	}

	if (End != nullptr)
	{
		Node* p = End->parent;
		while (p != nullptr && p != Start)
		{
			finalGrid[p->x][p->y] = '.';
			p = p->parent;
		}
	}

	for (size_t y = 0; y < yGridSize; y++)
	{
		for (size_t x = 0; x < xGridSize; x++)
		{
			std::cout << finalGrid[x][y];
		}
		std::cout << std::endl;
	}
}

void Delete()
{
	for (int y = 0; y < yGridSize; y++)
	{
		for (int x = 0; x < xGridSize; x++)
		{
			delete (&Nodes[y][x]);
		}
	}
}

int main()
{
	Init();
	AStarAlgo();
	ShowPath();

	//Delete();
	std::getchar();
}