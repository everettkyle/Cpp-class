#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <regex>

using namespace std;


int main()
{
	string str = "hello world ratherhave";

	string part_1 = "w";
	string part_2 = "d";

	string reg_one_m = "[a-zA-Z ,]+";
	string reg_zero_m = "[a-zA-Z ,]*";

	regex reg("hello[a-zA-Z ,]*world");

	smatch matches;

	regex_search(str, matches, reg);

	if(matches.empty())
		cout << "None" << endl;

	if(matches.size() > 0)
		cout << matches.str() << endl;


}


