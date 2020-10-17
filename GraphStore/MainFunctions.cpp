#include "MainFunctions.h"

int getCommand(std::string command)
{
	if (command == "CREATE")
	{
		return 1;
	}
	else if (command == "USE")
	{
		return 2;
	}
	else if (command == "DELETE")
	{
		return 3;
	}
	else if (command == "SEARCH")
	{
		return 4;
	}
	else if (command == "exit")
	{
		return 5;
	}
	else
	{
		return 6;
	}
}

void CREATEType(GraphStore & graphstore)
{
	std::string type, id;
	std::cin >> type;

	if (type == "GRAPH")
	{
		std::string directed;
		std::cin >> id >> directed;
		if (!graphstore.CheckGraph(id))
		{
			if (directed == "directed")
				graphstore.CreateGraph(Graph(id, true));
			else
				graphstore.CreateGraph(Graph(id, false));
			std::cout << "Graph with id " << id << " is created!\n";
		}
		else
			std::cout << "Graph with this id already exist!\n";
		
	}
	else if (type == "NODE")
	{
		std::cin >> id;
		if (graphstore.getCurrent() != nullptr)
		{
			if (graphstore.getCurrent()->CheckNode(id))
				std::cout << "Node with that id already exist\n";
			else
				graphstore.CreateNode(id);
				std::cout << "Node with id " << id << " is created!\n";
		}
		else
			std::cout << "Please choose graph!\n";
	}
	else if (type == "ARC")
	{
		ARCInput(graphstore);
	}
	else
	{
		std::cout << "Please enter the correct Create Type\n";
	}
}

void ARCInput(GraphStore & graphstore)
{
	char startID[50] = { 0 }, endID[50] = { 0 }, weightstring[10] = { 0 };
	std::string buffer;
	unsigned int weight = 1;
	int cnt = 0, j = 0;
	std::getline(std::cin, buffer);

	if (graphstore.getCurrent() != nullptr)
	{
		for (size_t i = 1; i < buffer.size(); i++)
		{
			if (cnt == 0)
			{
				if (buffer[i] == ' ')
					cnt++;
				else
					startID[i - 1] = buffer[i];
			}
			else
			{
				if (buffer[i] == ' ')
				{
					i++;
					j = i;
					break;
				}
				else
					endID[j++] = buffer[i];
			}
		}
		cnt = 0;
		while(j < buffer.size())
			weightstring[cnt++] = buffer[j++];
		weight = atoi(weightstring);

		if (!(graphstore.getCurrent()->CheckNode(startID) && graphstore.getCurrent()->CheckNode(endID)))
			std::cout << "Node or nodes doesn't exist!\n";
		else
			graphstore.CreateARC(startID, endID, weight);
			std::cout << "The ARC between " << startID << " and " << endID << " is created!\n";
	}
	else
		std::cout << "Please choose graph!\n";
}

void USEGRAPH(GraphStore & graphstore)
{
	std::string type, id;
	std::cin >> type >> id;
	if (type == "GRAPH")
	{
		if (graphstore.CheckGraph(id))
		{
			graphstore.UseGraph(id);
			std::cout << "Graph with id " << id << " is ready to use!\n";
		}
		else
				std::cout << "Graph with id " << id << " not exist!\n";
	}
	else
		std::cout << "Please enter the correct type!\n";
}

void DELETEType(GraphStore & graphstore)
{
	std::string type, id;
	std::cin >> type;

	if (type == "GRAPH")
	{
		std::cin >> id;
		graphstore.DeleteGraph(id);
	}
	else if (type == "NODE")
	{
		std::cin >> id;

		if (graphstore.getCurrent() != nullptr)
		{
			graphstore.DeleteNode(id);
		}
		else
			std::cout << "Please choose graph!\n";
	}
	else if (type == "ARC")
	{
		std::string endID;
		std::cin >> id >> endID;

		if (graphstore.getCurrent() != nullptr)
		{
			graphstore.DeleteARC(id, endID);
		}
		else
			std::cout << "Please choose graph!\n";
	}
	else
	{
		std::cout << "Please enter the correct DELETE Type\n";
	}
}

void SEARCHType(GraphStore & graphstore)
{
	std::string startID, endID, type;
	std::cin >> startID >> endID >> type;

	if (graphstore.getCurrent() != nullptr)
	{

		if (type == "bfs")
		{
			graphstore.BFS(startID, endID);
		}
		else if (type == "dfs-shortest")
		{
			graphstore.DFS(startID, endID, false);
		}
		else if (type == "dfs-longest")
		{
			graphstore.DFS(startID, endID, true);
		}
		else if (type == "dijkstra")
		{
			graphstore.Dijkstra(startID, endID);
		}
		else
		{
			std::cout << "Please enter the correct SEARCH Type\n";
		}
	}
	else
		std::cout << "Please choose graph!\n";
}


void Run(char * path)
{
	GraphStore graphstore;
	graphstore.ReadFromFile(path);

	std::string command;
	int n = 0;

	while (n != 5)
	{
		std::cin >> command;
		n = getCommand(command);

		switch (n)
		{
		case 1:
		{
			CREATEType(graphstore);
			break;
		}
		case 2:
		{
			USEGRAPH(graphstore);
			break;
		}
		case 3:
		{
			DELETEType(graphstore);
			break;
		}
		case 4:
		{
			SEARCHType(graphstore);
			break;
		}
		case 5:
			graphstore.SaveInFile(path);
			break;
		case 6:
			std::cout << "Please enter the correct command!\n";
			break;
		}
	}

}
