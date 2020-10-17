#include "GraphStore.h"

GraphStore::GraphStore() : current(nullptr)
{
}

GraphStore::~GraphStore()
{
	current = nullptr;
}

void GraphStore::CreateGraph(const Graph & graph)
{
	graphstore.push_back(graph);
}

void GraphStore::UseGraph(const std::string id)
{
	for (size_t i = 0; i < graphstore.getsize(); i++)
	{
		if (graphstore[i].getID() == id)
		{
			current = &graphstore[i];
			break;
		}
	}
}

void GraphStore::DeleteGraph(const std::string id)
{
	int cnt = 0;
	for (size_t i = 0; i < graphstore.getsize(); i++)
	{
		if (graphstore[i].getID() == id)
		{
			if (current != nullptr)
			{
				if (current->getID() == id)
				{
					current = nullptr;
				}
			}
			graphstore.erase(i);
			cnt++;
			std::cout << "Graph with this id is deleted!\n";
			break;
		}
	}

	if (cnt == 0)
	{
		std::cout << "Graph with this id doesn't exist!\n";
	}
}

void GraphStore::CreateNode(const std::string id)
{
	current->addNode(Node(id));
}

void GraphStore::DeleteNode(const std::string id)
{
	if (current->CheckNode(id))
	{
		current->removeNode(id);
		std::cout << "Node with id " << id << " is deleted!\n";
	}
	else
		std::cout << "Node with that id doesn't exist\n";

}

void GraphStore::CreateARC(const std::string startID, const std::string endID, const unsigned int weight)
{
	current->addArc(startID, endID, false, weight);
}

void GraphStore::DeleteARC(const std::string startID, const std::string endID)
{
	if (!(current->CheckNode(startID) && current->CheckNode(endID)))
	{
		std::cout << "Node or nodes doesn't exist!\n";
	}
	else
	{
		current->removeArc(startID, endID);
		std::cout << "The ARC between " << startID << " and " << endID << " is deleted!\n";
	}
}

void GraphStore::SaveInFile(std::string path)
{
	path += "\\graphstore.txt";
	std::ofstream file(path);

	if (!file)
	{
		std::cout << "Bad File!\n";
	}
	else
		{
		for (size_t i = 0; i < graphstore.getsize(); i++)
		{
			if (i != 0)
				file << std::endl;
			graphstore[i].SaveInFile(file);
		}
	}

	file.close();
}

void GraphStore::ReadFromFile(std::string path)
{
	path += "\\graphstore.txt";
	std::ifstream file(path);
	
	if(file)
	{
		std::string id,adjID, buffer;
		bool direction;
		unsigned int numnodes = 0, weight = 0, adjs = 0;

		while (!file.eof())
		{
			file >> id >> direction >> numnodes;
			if (id.size() > 0)
			{

				CreateGraph(Graph(id, direction));
				UseGraph(id);

				file >> buffer;

				for (size_t i = 0; i < numnodes; i++)
				{
					file >> id;
					CreateNode(id);
				}

				for (size_t j = 0; j < numnodes; j++)
				{
					file >> buffer;
					file >> adjs;
					for (size_t i = 0; i < adjs; i++)
					{
						file >> adjID >> weight;
						CreateARC(current->getNodes()[j].getid(), adjID, weight);
					}
				}
			}
		}
		current = nullptr;
		std::cout << "graphstore.txt is successfully loaded!\n";
	}

	file.close();
}

bool GraphStore::CheckGraph(const std::string id)
{
	for (size_t i = 0; i < graphstore.getsize(); i++)
	{
		if (graphstore[i].getID() == id)
		{
			return true;
		}
	}

	return false;
}

size_t GraphStore::getPathByIndex(MyVector<MyVector<std::string>> & paths, const bool longest)
{
	size_t idx = 0;
	for (size_t i = 1; i < paths.getsize(); i++)
	{
		if (longest)
		{
			if (paths[i].getsize() >= paths[idx].getsize())
			{
				idx = i;
			}
		}
		else
		{
			if (paths[i].getsize() <= paths[idx].getsize())
			{
				idx = i;
			}
		}
	}

	return idx;
}

Graph * GraphStore::getCurrent() const
{
	return current;
}

void GraphStore::PrintCurrentGraph() const
{
	if(current != nullptr)
		current->printGraph();
}

void GraphStore::BFS(const std::string startID, const std::string endID)
{
	if (current->CheckNode(startID) && current->CheckNode(endID))
	{
		MyVector<std::string> path = current->bfs(startID, endID);

		if (path.getsize() > 0) 
		{
			for (size_t i = 0; i < path.getsize(); i++)
			{
				if (i + 1 == path.getsize())
					std::cout << path[i] << std::endl;
				else
					std::cout << path[i] << "->";
			}
		}
		else
		{
			std::cout << "Path between " << startID << " and " << endID << " not exist!\n";
		}
	}
	else
	{
		std::cout << "Nodes or Node doesn't exist!\n";
	}
}

void GraphStore::DFS(const std::string startID, const std::string endID, const bool longest)
{
	if (current->CheckNode(startID) && current->CheckNode(endID))
	{
		MyVector<MyVector<std::string>> paths;
		current->dfs(startID, endID, paths);

		if (paths.getsize() > 0)
		{
			size_t idx = getPathByIndex(paths, longest);

			for (size_t i = 0; i < paths[idx].getsize(); i++)
			{
				if (i + 1 == paths[idx].getsize())
					std::cout << paths[idx][i] << std::endl;
				else
					std::cout << paths[idx][i] << "->";
			}
		}
		else
		{
			std::cout << "Path between " << startID << " and " << endID << " not exist!\n";
		}
	}
	else
	{
		std::cout << "Nodes or Node doesn't exist!\n";
	}
}

void GraphStore::Dijkstra(const std::string startID, const std::string endID)
{
	if (current->CheckNode(startID) && current->CheckNode(endID))
	{
		std::pair<MyVector<std::string>,unsigned int> path = current->dijkstra(startID, endID);

		if (path.first.getsize() > 0)
		{
			for (size_t i = 0; i < path.first.getsize(); i++)
			{
				if (i + 1 == path.first.getsize())
					std::cout << path.first[i] << " price: " << path.second << std::endl;
				else
					std::cout << path.first[i] << "->";
			}

		}
		else
		{
			std::cout << "Path between " << startID << " and " << endID << " not exist!\n";
		}
	}
	else
	{
		std::cout << "Nodes or Node doesn't exist!\n";
	}
}
