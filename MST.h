// Project Identifier: 5949F553E20B650AB0FB2266D3C0822B13D248B0

#include <vector>
#include <stack>
#include <queue>
#include <deque>
#include <string>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <getopt.h>
#include <limits>


using namespace std;


struct Point
{
	double d = std::numeric_limits<double>::max();
	char type;
	int x;
	int y;
	int prev = -1;
	bool visited = false;
};

class MSTree
{
private:
	double total;

public:
	vector<Point> vertices;
	MSTree() {}

	double find_dist(Point &a, Point &b)
	{
		if (a.type == 's' && b.type == 'l') // a is a sea tile
		{
			return std::numeric_limits<double>::max();
		}
		if (b.type == 's' && a.type == 'l') // b is a sea tile
		{
			return std::numeric_limits<double>::max();
		}
		double dist = sqrt((double(a.x) - double(b.x)) * (double(a.x) - double(b.x)) + 
			(double(a.y) - double(b.y)) * (double(a.y) - double(b.y)));
		return dist;
	}

	void find_path() // edge case, start from sea location
	{
		//cout << "entered find path" << '\n';
		int current = 0;
		vertices[0].d = 0;
		//cout << "before big loop" << '\n';
		for (size_t i = 0; i < vertices.size(); i++)
		{
			double min = std::numeric_limits<double>::max();
			for (size_t j = 0; j < vertices.size(); j++)
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
			for (size_t k = 0; k < vertices.size(); k++)
			{
				if (!vertices[k].visited)
				{
					double temp = find_dist(vertices[current], vertices[k]);
					if (temp < vertices[k].d)
					{
						vertices[k].d = temp;
						vertices[k].prev = current;
						//cout << "distance: " << temp << '\n';
					}
				}
			}
		}
	}

	void print_result()
	{
		//cout << std::setprecision(2); //Always show 2 decimal places
		//cout << std::fixed; //Disable scientific notation for large numbers
		cout << total << '\n';
		for (size_t i = 1; i < vertices.size(); i++)
		{
			if (int(i) < vertices[i].prev)
			{
				cout << i << " " << vertices[i].prev << '\n';
			}
			else
			{
				cout << vertices[i].prev << " " << i << '\n';
			}
		}

	}

	void print_vertices()
	{
		for (size_t i = 0; i < vertices.size(); i++)
		{
			cout << vertices[i].x << " " << vertices[i].y << " " << vertices[i].type << '\n';
		}
	}

	void read_input()
	{
		int size;
		cin >> size;
		vertices.reserve(size);
		Point temp;
		int count = 0;
		int count1 = 0;
		int count2 = 0;
		while (cin >> temp.x >> temp.y)
		{
			if ((temp.x == 0 && temp.y <= 0) || (temp.y == 0 && temp.x <= 0))
			{
				temp.type = 'c';
				count++;
			}
			else if (temp.x < 0 && temp.y < 0)
			{
				temp.type = 's';
				count1++;
			}
			else
			{
				temp.type = 'l';
				count2++;
			}
			vertices.push_back(temp);
		}
		if (count1 > 0 && count2 > 0 && count == 0)
		{
			cerr << "Cannot construct mst" << '\n';
			exit(1);
		}
	}
	
};