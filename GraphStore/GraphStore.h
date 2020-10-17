#ifndef GraphStore_H
#define GraphStore_H
#include "Graph.h"
class GraphStore
{
private:
	Graph * current;
	MyVector<Graph> graphstore;

public:
	GraphStore();
	~GraphStore();

	void CreateGraph(const Graph & graph);
	void UseGraph(const std::string id);
	void DeleteGraph(const std::string id);
	void CreateNode(const std::string id);
	void DeleteNode(const std::string id);
	void CreateARC(const std::string startID, const std::string endID, const unsigned int weight = 1);
	void DeleteARC(const std::string startID, const std::string endID);
	
	void SaveInFile(std::string path);
	void ReadFromFile(std::string path);

	bool CheckGraph(const std::string id);
	size_t getPathByIndex(MyVector<MyVector<std::string>> & paths, const bool longest);
	Graph* getCurrent() const;
	void PrintCurrentGraph() const;

	void BFS(const std::string startID, const std::string endID);
	void DFS(const std::string startID, const std::string endID, const bool longest);
	void Dijkstra(const std::string startID, const std::string endID);
};

#endif
