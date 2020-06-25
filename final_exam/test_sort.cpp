#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

bool sortbydup(string s1, string s2)
{
	int cnt_s1 = 0;
	int cnt_s2 = 0;

	map<char, int> dups2;
	dups2.insert(pair<char, int>(s2[0], 1));
	for(int i=0; i<s2.size(); i++)
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


	map<char, int> dups;
	dups.insert(pair<char, int>(s1[0], 1));
        for(int i=0; i<s1.size(); i++)
        {
                for(auto map_it = dups.begin(); map_it != dups.end(); map_it++)
                {
                        if(map_it->first == s1[i])
                        {
                                cnt_s1++;
                                break;
                        }
                        else
                                dups.insert(pair<char, int>(s1[i], 1));
                }

        }

	return cnt_s1 > cnt_s2;
}

int main()

{

vector<string> sort_vec = {"aaabbcc", "bc", "ddd", "abab"};

sort(sort_vec.begin(), sort_vec.end(), sortbydup);


for(int i=0; i<sort_vec.size(); i++)
	cout << sort_vec[i] << endl;


return 0;

}
