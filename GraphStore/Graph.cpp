#include "Graph.h"

Graph::Graph()
{
}

Graph::Graph(std::string id, bool direction, unsigned int NumberOfNodes) : id(id),direction(direction),NumberOfNodes(NumberOfNodes)
{
}

Graph::~Graph()
{
}

void Graph::addNode(const Node & node)
{
		Nodes.push_back(node);
		NumberOfNodes++;
}

void Graph::removeNode(const std::string id)
{
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (Nodes[i].getid() == id)
		{
			Nodes.erase(i);
			NumberOfNodes--;
			break;
		}
	}

	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		Nodes[i].removeAdj(id);
	}
}

void Graph::addArc(const std::string startID, const std::string endID,const bool visited, const unsigned int weight)
{
	int startIdx = 0, endIdx = 0;
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (Nodes[i].getid() == startID)
		{
			startIdx = i;
		}
		else if (Nodes[i].getid() == endID)
		{
			endIdx = i;
		}
	}

	if (direction)
	{
		Nodes[startIdx].addAdj(Adjacency(endID, weight, visited));
	}
	else
	{
		Nodes[startIdx].addAdj(Adjacency(endID, weight, visited));
		Nodes[endIdx].addAdj(Adjacency(startID, weight, visited));
	}
}

void Graph::removeArc(const std::string startID, const std::string endID)
{

	int startIdx = 0, endIdx = 0;
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (Nodes[i].getid() == startID)
		{
			startIdx = i;
		}
		else if (Nodes[i].getid() == endID)
		{
			endIdx = i;
		}
	}

	if (direction)
	{
		Nodes[startIdx].removeAdj(endID);
	}
	else
	{
		Nodes[startIdx].removeAdj(endID);
		Nodes[endIdx].removeAdj(startID);
	}
}

bool Graph::CheckNode(const std::string id)
{
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (Nodes[i].getid() == id)
		{
			return true;
		}
	}

	return false;
}

 const std::string Graph::getID() const
{
	return id;
}

 MyVector<Node> Graph::getNodes() const
{
	return Nodes;
}

const unsigned int Graph::getNumberOfNodes() const
{
	return NumberOfNodes;
}

const Node Graph::getNodeByID(const std::string id)
{
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (Nodes[i].getid() == id)
		{
			return Nodes[i];
		}
	}
}

void Graph::printGraph()
{
	std::cout << id << " " << direction << " " << NumberOfNodes << std::endl;
	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		std::cout << Nodes[i].getid() << ':';

		for (size_t j = 0; j < Nodes[i].getAdjs().getsize(); j++)
		{
			std::cout << Nodes[i].getAdjs()[j].id << " ";
		}

		std::cout << std::endl;
	}
}

void Graph::SaveInFile(std::ofstream & file)
{
	file << id << " " << direction << " " << NumberOfNodes << '\n';
	file << "Nodes:";

	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (i + 1 == Nodes.getsize())
			file << " " << Nodes[i].getid() << std::endl;
		else
			file << " " << Nodes[i].getid();
	}

	for (size_t i = 0; i < Nodes.getsize(); i++)
	{
		if (i + 1 == Nodes.getsize())
		{
			Nodes[i].SaveNodeInFile(file);
		}
		else
		{
			Nodes[i].SaveNodeInFile(file);
			file << std::endl;
		}
			
			
	}
}

 MyVector<std::string> Graph::bfs(const std::string startID, const std::string endID)
{
	MyQueue<MyVector<std::string>> possiblepaths;
	MyVector<std::string> FirstPath;

	FirstPath.push_back(startID);
	possiblepaths.push(FirstPath);

	while (!possiblepaths.empty())
	{
		FirstPath = possiblepaths.front();
		possiblepaths.pop();

		std::string LastNode = FirstPath[FirstPath.getsize() - 1];

		if (LastNode == endID)
		{
			return FirstPath;
		}
		else
		{
			Node node = getNodeByID(LastNode);

			for (size_t i = 0; i < node.getAdjs().getsize(); i++)
			{
				if (!FirstPath.contains(node.getAdjs()[i].id))
				{
					MyVector<std::string> NewPath = FirstPath;
					NewPath.push_back(node.getAdjs()[i].id);
					possiblepaths.push(NewPath);

				}

			}
		}
	}

}

void Graph::dfs(const std::string startID, const std::string endID, MyVector<MyVector<std::string>> & paths)
{
	MyStack<MyVector<std::string>> possiblepaths;
	MyVector<std::string> FirstPath;

	FirstPath.push_back(startID);
	possiblepaths.push(FirstPath);

	while (!possiblepaths.empty())
	{
		FirstPath = possiblepaths.top();
		possiblepaths.pop();

		std::string LastNode = FirstPath[FirstPath.getsize() - 1];

		if (LastNode == endID)
		{
			paths.push_back(FirstPath);
		}
		else
		{
			Node node = getNodeByID(LastNode);

			for (size_t i = 0; i < node.getAdjs().getsize(); i++)
			{
				if (!FirstPath.contains(node.getAdjs()[i].id))
				{
					MyVector<std::string> NewPath = FirstPath;
					NewPath.push_back(node.getAdjs()[i].id);
					possiblepaths.push(NewPath);

				}

			}
		}
	}
}

std::pair<MyVector<std::string>,unsigned int> Graph::dijkstra(const std::string startID, const std::string endID)
{
	MyVector<std::pair<MyVector<std::string>, unsigned int>> possiblepaths;
	std::pair<MyVector<std::string>, unsigned int> possiblepath;

	MyVector<std::string> buffer;
	buffer.push_back(startID);
	possiblepath = std::make_pair(buffer, 0);
	possiblepaths.push_back(possiblepath);

	while (!possiblepaths.empty())
	{
		size_t minWeightidx = 0;
		for (size_t i = 1; i < possiblepaths.getsize(); i++)
		{
			possiblepath = possiblepaths[i];
			if (possiblepath.second < possiblepaths[minWeightidx].second)
			{
				minWeightidx = i;
			}
		}

		std::pair<MyVector<std::string>, unsigned int> CheapestPath = possiblepaths[minWeightidx];
		possiblepaths.erase(minWeightidx);

		std::string LastNode = CheapestPath.first[CheapestPath.first.getsize() - 1];

		if (LastNode == endID)
		{
			return CheapestPath;
		}
		else
		{
			Node node = getNodeByID(LastNode);
			for (size_t i = 0; i < node.getAdjs().getsize(); i++)
			{
				unsigned int weight = node.getAdjs()[i].weight;

				if (!CheapestPath.first.contains(node.getAdjs()[i].id))
				{
					std::pair<MyVector<std::string>, unsigned int> NewPath = CheapestPath;
					NewPath.second += weight;
					NewPath.first.push_back(node.getAdjs()[i].id);

					possiblepaths.push_back(NewPath);
				}
			}

		}
	}
}

