#pragma once
#include<iostream>
#include<map>
#include<set>
#include<queue>
#include<vector>


template<typename T,typename S>
class Graph
{
private:
	struct Node
	{
		T value;
		int id;
		std::set<Node*> neighbours;
		Node() = default;
		Node(int id, const T& value) : value(value), id(id) {}
	};
	std::map<int, Node> nodes;
	std::map<S, int> index;
	int nextIndex = 0;
public:
	void add(S id,const T& value)
	{
		//if (nodes.contains(index[id]))
		//	throw std::exception("Cvor sa datim ID-om vec postoji u grafu");
		nodes.insert(std::make_pair(nextIndex, Node(nextIndex, value)));
		index.insert(std::make_pair(id, nextIndex));
		nextIndex++;
	}

	/*int operator[](S ind)
	{
		return index[ind];
	}*/

	T operator[](int ind)
	{
		return nodes[ind].value;
	}

	T operator[](S ind)
	{
		return nodes[index[ind]].value;
	}

	

	std::vector<std::vector<int>> getAdjacencyMatrixW()
	{
		std::vector<std::vector<int>> matrix;
		for (auto& x : nodes)
		{
			std::vector<int> temp(this->size(), INT_MAX);
			temp[x.first] = 0;
			for (Node* el : x.second.neighbours)
			{
				int ind = el->id;
				temp[ind] = 1;
			}
			matrix.push_back(temp);
		}
		return matrix;
	}



	void remove(S id)
	{
		//if (!nodes.contains(index[id]))
			//throw std::exception("Cvor sa datim ID-om ne postoji u grafu");
		for (auto& x : nodes[index[id]].neighbours)
			nodes[x->id_cvora].neighbours.erase(&nodes[index[id]]);
		nodes.erase(id);
	}

	void connect(S id1, S id2)
	{
		nodes[index[id1]].neighbours.emplace(&nodes[index[id2]]);
		nodes[index[id2]].neighbours.emplace(&nodes[index[id1]]);
	}

	size_t size()const
	{
		return this->nodes.size();
	}

	void disconnect(S id1, S id2)
	{
		//if (!nodes.contains(index[id1]) || !nodes.contains(index[id2]))
		//	throw std::exception("U grafu ne postoje cvorovi sa datim id");
		//if (!nodes[index[id1]].neighbours.contains(&nodes[index[id2]]))
		//	throw std::exception("Ne postoji veza izmedju cvorova sa datim id");
		nodes[index[id1]].neighbours.erase(&nodes[index[id2]]);
		nodes[index[id2]].neighbours.erase(&nodes[index[id1]]);
	}


	static int shortestDistance(Graph& g, S id1, S id2)
	{
		std::set<int> visited;
		std::map<int, int> levels;
		std::queue<Node*> toVisit;
		visited.insert(g.index[id1]);
		toVisit.push(&g.nodes[g.index[id1]]);
		levels.insert(std::make_pair(g.index[id1], 0));
		while (!toVisit.empty())
		{
			Node* curr = toVisit.front();
			toVisit.pop();
			for (Node* el : curr->neighbours)
			{
				if (!visited.contains(el->id))
				{
					levels.insert(std::make_pair(el->id, levels[curr->id] + 1));
					visited.insert(el->id);
					toVisit.push(el);
					if (el->id == g.index[id2])
						return levels[g.index[id2]];
				}
			}
		}
		return -1;
	}

	static void warshallAlgorithm(std::vector<std::vector<int>>& D)
	{
		int n = D.size();
		for (int k = 0; k < n; k++)
			for (int i = 0; i < n; i++)
				for (int j = 0; j < n; j++)
					if ((D[i][j] > (D[i][k] + D[k][j])) && D[i][k] != INT_MAX && D[k][j] != INT_MAX)
						D[i][j] = D[i][k] + D[k][j];
	}
};
