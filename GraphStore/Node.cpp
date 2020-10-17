#include "Node.h"

Node::Node()
{
}

Node::Node(std::string id): id(id)
{
}

Node::~Node()
{
}

void Node::addAdj(const Adjacency & adj)
{
	size_t i = 0;
	for (i; i < Adjacencies.getsize(); i++)
	{
		if (Adjacencies[i].id == adj.id)
		{
			break;
		}
	}

	if(i == Adjacencies.getsize())
		Adjacencies.push_back(adj);
}

void Node::removeAdj(const std::string & Id)
{
	for (size_t i = 0; i < Adjacencies.getsize(); i++)
	{
		if (Adjacencies[i].id == Id)
		{
			Adjacencies.erase(i);
			break;
		}
	}
}

void Node::SaveNodeInFile(std::ofstream & file)
{
	file << "Adjancecies" << id << ": " << Adjacencies.getsize();
	for (size_t i = 0; i < Adjacencies.getsize(); i++)
	{
		file << " " << Adjacencies[i].id << " " << Adjacencies[i].weight;
	}
}

 MyVector<Adjacency> Node::getAdjs() const
{
	return Adjacencies;
}

const std::string Node::getid() const
{
	return id;
}
