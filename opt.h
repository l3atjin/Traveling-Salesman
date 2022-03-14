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
#include "MST.h"
#include "fast.h"

using namespace std;

struct Node
{
	int x;
	int y;
	int entry;
	double d = std::numeric_limits<double>::infinity();
	bool visited = false;
};

class Opt
{
private:
	//vector<vector<double>> distance;
	vector<Node> vertices;
	vector<size_t> edges;
	vector<size_t> test;
	vector<vector<double>> distance;
	double upper = 0;п
              ютттииииииии	
	double runningTotal = 0;
	size_t minIndex = 0;

public:
	Opt() {}

	void solve()
	{
		//cout << "Entered solve" << endl;
		//cout << "Before genPerms" << endl;
		fill_dist();
		find_fast();
		vector<Node> temp;
		for (size_t i = 0; i < vertices.size(); i++)
		{
			temp.push_back(vertices[edges[i]]);
		}
		vertices.swap(temp);
		//cout << upper << endl;
		genPerms(1);
	}

	void fill_dist()
	{
		distance.resize(vertices.size(), vector<double>(vertices.size()));
		for (size_t i = 0; i < vertices.size(); i++)
		{
			for (size_t j = 0; j < vertices.size(); j++)
			{
				distance[i][j] = find_dist(vertices[i], vertices[j]);
				//cout << distance[i][j] << " ";
			}
			//cout << endl;
		}
	}

	void genPerms(size_t permLength) {
		cout << "Current Path" << endl;
		for (size_t i = 0; i < permLength; i++)
		{
			cout << vertices[i].entry << " ";
		}
		cout << endl;
		if (permLength == vertices.size()) { // Do something with the vertices
			runningTotal += distance[vertices[0].entry][vertices[vertices.size() - 1].entry];  // find_dist(vertices[0], vertices[vertices.size() - 1]);
			//cout << "End of solution. Total is " << runningTotal << endl;
			//cout << "Current best is " << upper << endl;
			if (runningTotal < upper)
			{
				//cout << "Upper changed to " << runningTotal << endl;
				upper = runningTotal;
				edges.clear();
				edges.reserve(vertices.size());
				for (size_t i = 0; i < vertices.size(); i++)
				{
					edges.push_back(vertices[i].entry);
				}
			}
			runningTotal -= distance[vertices[0].entry][vertices[vertices.size() - 1].entry];
			return;
		} // if
		if (!promising(permLength))
			return;
		for (size_t i = permLength; i < vertices.size(); ++i) 
		{
			swap(vertices[permLength], vertices[i]);
			runningTotal += distance[vertices[permLength - 1].entry][vertices[permLength].entry]; //find_dist(vertices[permLength - 1], vertices[permLength]);
			genPerms(permLength + 1); // recursive call
			runningTotal -= distance[vertices[permLength - 1].entry][vertices[permLength].entry]; //find_dist(vertices[permLength - 1], vertices[permLength]);
			swap(vertices[permLength], vertices[i]);
		} // for
	} // genPerms()

	bool promising(size_t permLength) // 
	{
		double mst = find_mst(permLength);
		double min = std::numeric_limits<double>::infinity();
		//double min1 = std::numeric_limits<double>::infinity();
		for (size_t i = permLength; i < vertices.size(); i++)
		{
			double temp = distance[vertices[0].entry][vertices[i].entry]; //find_dist(vertices[0], vertices[i]);
			if (temp < min)
			{
				min = temp;
			}
		}
		mst += min;
		//cout << "Arm 1: " << min << endl;
		min = std::numeric_limits<double>::infinity();
		for (size_t i = permLength; i < vertices.size(); i++)
		{
			double temp = distance[vertices[permLength - 1].entry][vertices[i].entry]; //find_dist(vertices[permLength - 1], vertices[i]);
			if (temp < min)
			{
				min = temp;
			}
		}
		mst += min;
		double lower = mst + runningTotal;
		/*cout << "Arm 2: " << min << endl;
		cout << "Upper is " << upper << endl;шоө 
		cout << "Running total is " << runningTotal << endl;
		cout << "Lower is " << lower << endl;*/
		return lower < upper;
	}

	double find_dist(Node &a, Node &b)
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
		Node temp;
		int count = 0;
		double min = std::numeric_limits<double>::infinity();
		while (cin >> temp.x >> temp.y)
		{
			temp.entry = count;
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
		return distance[i][k] + distance[j][k] - distance[i][j]; //find_dist(vertices[i], vertices[k]) + find_dist(vertices[j], vertices[k]) - find_dist(vertices[i], vertices[j]);
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
		upper += distance[edges[index - 1]][a]; //find_dist(vertices[edges[index - 1]], vertices[a]);
		upper += distance[edges[index]][a]; //find_dist(vertices[a], vertices[edges[index]]);
		upper -= distance[edges[index - 1]][edges[index]]; //find_dist(vertices[edges[index]], vertices[edges[index - 1]]);
		edges.insert(edges.begin() + index, a);
		//cout << "inserted " << a << '\n';
		//print_result();
	}

	void find_fast()
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
		upper += distance[0][minIndex]; //find_dist(vertices[0], vertices[minIndex]);
		upper += distance[0][minIndex]; //find_dist(vertices[0], vertices[minIndex]);
		//cout << total << '\n';
		for (size_t i = 1; i < vertices.size(); i++)
		{
			if (!vertices[i].visited)
			{
				insert_vertex(i);
				vertices[i].visited = true;
			}
		}
	}

	double find_mst(size_t permLength) // edge case, start from sea location 212.15
	{
		/*cout << "Taking MST of: ";
		for (size_t i = 0; i < test.size(); i++)
		{
			cout << i << " ";
		}*/
		for (size_t i = permLength; i < vertices.size(); i++)
		{
			vertices[i].visited = false;
			vertices[i].d = std::numeric_limits<double>::infinity();
		}
		vertices[permLength].d = 0;
		double total = 0;
		int current = int(permLength);
		//cout << "Taking MST of: ";
		for (size_t i = permLength; i < vertices.size(); i++)
		{
			//cout << vertices[i].entry << " ";
			
			double min = std::numeric_limits<double>::infinity();
			for (size_t j = permLength; j < vertices.size(); j++)
			{
				if (!vertices[j].visited && vertices[j].d < min)
				{
					min = vertices[j].d;
					current = int(j);
				}
			}
			//cout << "Current: " << current << '\n';
			vertices[current].visited = true;
			total += vertices[current].d;
			for (size_t k = permLength; k < vertices.size(); k++)
			{
				if (!vertices[k].visited)
				{
					double temp = distance[vertices[current].entry][vertices[k].entry]; //find_dist(vertices[current], vertices[k])
					if (temp < vertices[k].d)
					{
						vertices[k].d = temp;
					}
				}
			}
		}
		//cout << endl;
		//cout << "total MST is " << total << endl;
		return total;
	}

	void print_result()
	{
		cout << upper << '\n';
		//cout << path.size() << endl;
		for (size_t i = 0; i < edges.size(); i++)
		{
			cout << edges[i] << " ";
		}
		cout << '\n';
	}

};