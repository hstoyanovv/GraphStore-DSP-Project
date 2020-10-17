#ifndef Node_H
#define Node_H
#include<string>
#include<fstream>
#include "MyVector.h"
#include "MyQueue.h"
#include "MyStack.h"

struct Adjacency
{
	std::string id;
	unsigned int weight;

	Adjacency()
	{
		weight = 1;
	}
	Adjacency(const std::string id, const unsigned int weight, const bool visited)
	{
		this->id = id;
		this->weight = weight;
	}
};

class Node
{
private:
	std::string id;
	MyVector<Adjacency> Adjacencies;

public:
	Node();
	Node(std::string id);
	~Node();

	void addAdj(const Adjacency & adj);
	void removeAdj(const std::string & Id);

	void SaveNodeInFile(std::ofstream & file);
	const std::string getid() const;
	MyVector<Adjacency> getAdjs() const;

};


#endif
