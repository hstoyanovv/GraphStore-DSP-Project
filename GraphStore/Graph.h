#ifndef Graph_H
#define Graph_H
#include "Node.h"
class Graph
{
private:
	std::string id;
	bool direction;
	unsigned int NumberOfNodes;
	MyVector<Node> Nodes;

public:
	Graph();
	Graph(std::string id, bool direction = false, unsigned int NumberOfNodes = 0);
	~Graph();

	void addNode(const Node & node);
	void removeNode(const std::string id);
	void addArc(const std::string startID, const std::string endID, const bool visited, const unsigned int weight = 1);
	void removeArc(const std::string startID,const std::string endID);

	void SaveInFile(std::ofstream & file);
	bool CheckNode(const std::string id);

	MyVector<std::string> bfs(const std::string startID, const std::string endID);
	void dfs(const std::string startID, const std::string endID, MyVector<MyVector<std::string>> & paths);
	std::pair<MyVector<std::string>,unsigned int> dijkstra(const std::string startID, const std::string endID);

	const std::string getID() const;
	MyVector<Node> getNodes() const;
	const unsigned int getNumberOfNodes() const;
	const Node getNodeByID(const std::string id);


	void printGraph();
};

#endif
