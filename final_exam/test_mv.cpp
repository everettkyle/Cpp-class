#include <iostream>
#include <map>
using namespace std;


int main()
{
	string s2 = "abab";
	int cnt_s2 = 0;
	map<char, int> dups2;

	dups2.insert(pair<char, int>(s2[0], 1));
	for(int i=1; i<s2.size()-1; i++)
	{
		for(auto map_it = dups2.begin(); map_it != dups2.end(); map_it++)
		{
			if(map_it->first == s2[i])
			{
				cnt_s2++;
				break;
                        }
			else
				dups2.insert(pair<char, int>(s2[i], 1));
		}

	}


	cout << cnt_s2 << endl;

	return 0;

}
