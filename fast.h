// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <iomanip>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <getopt.h>

using namespace std;

struct Pokemon
{
	int x;
	int y;
	bool visited = false;
};


class Fast
{
private:
	
	
	size_t minIndex = 0;

public:
	vector<Pokemon> vertices;
	vector<size_t> edges;
	double total = 0;

	Fast() {}

	Fast(vector<Pokemon> &vec)
	: vertices(vec) {}

	double find_dist(Pokemon &a, Pokemon &b)
	{
		double dist = sqrt((double(a.x) - double(b.x)) * (double(a.x) - double(b.x)) +
			(double(a.y) - double(b.y)) * (double(a.y) - double(b.y)));
		return dist;
	}

	void read_input()
	{
		int size;
		cin >> size;
		vertices.reserve(size);
		Pokemon temp;
		int count = 0;
		double min = std::numeric_limits<double>::infinity();
		while (cin >> temp.x >> temp.y)
		{
			vertices.push_back(temp);
			if (count != 0)
			{
				double num = find_dist(vertices.front(), vertices[count]);
				if (num < min)
				{
					min = num;
					minIndex = count;
				}
			}
			count++;
		}
		//cout << minIndex << '\n';
	}

	double check_vertex(size_t k, size_t i, size_t j) // checks a with respect to the edge {b, c}
	{
		return find_dist(vertices[i], vertices[k]) + find_dist(vertices[j], vertices[k]) - find_dist(vertices[i], vertices[j]);
	}

	void insert_vertex(size_t a)
	{
		double min = std::numeric_limits<double>::infinity();
		size_t index = 0;
		for (size_t i = 0; i < edges.size() - 1; i++)
		{
			double temp = check_vertex(a, edges[i], edges[i + 1]);
			//cout << "Distance at " << i << ": " << temp << '\n';
			if (temp < min)
			{
				min = temp;
				index = i + 1;
			}
		}
		total += find_dist(vertices[edges[index - 1]], vertices[a]);
		total += find_dist(vertices[a], vertices[edges[index]]);
		total -= find_dist(vertices[edges[index]], vertices[edges[index - 1]]);
		edges.insert(edges.begin() + index, a);
		//cout << "inserted " << a << '\n';
		//print_result();
	}

	void find_path()
	{
		// 1. Start from index 0 and connect it to its closest neighbor to form the first edge
		// 2. Arbitrarily select a node outside the partial tour
		// 3. From the partial tour find the edge that minimizes: Cik + Ckj - Cij
		// 4. Loop until everything's connected

		//
		edges.push_back(0);
		vertices[0].visited = true;
		edges.push_back(minIndex);
		vertices[minIndex].visited = true;
		total += find_dist(vertices[0], vertices[minIndex]);
		total += find_dist(vertices[0], vertices[minIndex]);
		//cout << total << '\n';
		for (size_t i = 1; i < vertices.size(); i++)
		{
			if (!vertices[i].visited)
			{
				insert_vertex(i);
				vertices[i].visited = true;
			}
		}
		//total += find_dist(vertices[0], vertices[edges.size() - 1]);
	}

	void print_result()
	{
		cout << total << '\n';
		for (size_t i = 0; i < edges.size(); i++)
		{
			cout << edges[i] << " ";
		}
		cout << '\n';
	}
};