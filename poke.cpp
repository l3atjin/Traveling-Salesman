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
//#include "fast.h"
#include "opt.h"

using namespace std;

string getMode(int argc, char * argv[]) {
	bool modeSpecified = false;
	string mode;

	// These are used with getopt_long()
	opterr = true; // Give us help with errors
	int choice;
	int option_index = 0;
	option long_options[] = {
		// TODO: Fill in two lines, for the "mode" ('m') and
		// the "help" ('h') options.
		{ "mode", required_argument, nullptr, 'm' },
		{ "help", no_argument, nullptr, 'h' },
		{ nullptr, 0,                 nullptr, '\0' }
	};

	// TODO: Fill in the double quotes, to match the mode and help options.
	while ((choice = getopt_long(argc, argv, "m:h", long_options, &option_index)) != -1) {
		switch (choice) {
		case 'h':
			cout << "Allowed options: -m" << "\n";
			exit(1);
			break;
		case 'm':
			mode = optarg;
			modeSpecified = true;
			break;

		default:
			cerr << "Error: invalid option" << '\n';
			exit(1);
		} // switch
	} // while

	if (!modeSpecified) {
		cerr << "Error: no mode specified" << '\n';
		exit(1);
	} // if

	return mode;
} // getMode()





int main(int argc, char * argv[])
{
	std::ios_base::sync_with_stdio(false);
	cout << std::setprecision(2); //Always show 2 decimal places
	cout << std::fixed; //Disable scientific notation for large numbers

	string mode = getMode(argc, argv);
	if (mode == "MST")
	{
		MSTree mst;
		mst.read_input();
		mst.find_path();
		//mst.print_vertices();
		mst.print_result();
	}
	else if (mode == "FASTTSP")
	{
		Fast fast;
		fast.read_input();
		fast.find_path();
		fast.print_result();
	}
	else if (mode == "OPTTSP")
	{
		Opt optimal;
		optimal.read_input();
		optimal.solve();
		optimal.print_result();
	}
	

}