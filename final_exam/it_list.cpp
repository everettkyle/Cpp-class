#include <iostream>
#include <list>
#include <iterator>
#include <set>
#include <map>
#include <tuple>


using namespace std;

tuple<float, string, string> compute_find(map<string, float> &heights)
{
	string tall = "";
	string shrt = "";
	float avg_height = 0.0;
	float sum = 0.0;
	int cnt = 0;
	string tmp_tall = "";
	float tmp_th = 0.0;
	string tmp_small = "";
	float tmp_sh = 0.0;


	map<string, float> :: iterator it1;
	//avg height
	for(it1 = heights.begin(); it1 != heights.end(); it1++)
	{
		sum = sum + it1->second;
		cnt++;
	}
	avg_height = sum / cnt;


	map<string, float> :: iterator it2;
	//tallest
	for(it2 = heights.begin(); it2 != heights.end(); it2++)
	{
		if(tmp_th < it2->second)
		{
			tmp_th = it2->second;
			tmp_tall = it2->first;
		}

	}
	tall = tmp_tall;


	map<string, float> :: iterator it3;
	//shortest
	for(it3 = heights.begin(); it3 != heights.end(); it3++)
	{
		if(tmp_sh == 0.0)
		{
			tmp_sh = it3->second;
			tmp_small = it3->first;
		}

		if(tmp_sh > it3->second)
		{
			tmp_sh = it3->second;
			tmp_small = it3->first;
		}
	}
	shrt = tmp_small;


return make_tuple(avg_height, tall, shrt);


}


int main()
{

float avg_height = 0.0;
string tall = "";
string shrt = "";

map<string, float> heights;
heights.insert(pair<string, float>("kyle", 6.4));
heights.insert(pair<string, float>("eric", 6.0));
heights.insert(pair<string, float>("robbie", 6.0));
heights.insert(pair<string, float>("patterson", 2.2));
heights.insert(pair<string, float>("chaca", 1.0));

tie(avg_height, tall, shrt) = compute_find(heights);

cout << avg_height << endl;
cout << tall << endl;
cout << shrt << endl;

return 0;
}
