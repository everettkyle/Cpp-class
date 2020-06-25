#include <map>
#include <iostream>
#include <list>

using namespace std;

void Printout(multimap<string, string> &names_str)
{
multimap<string, string> :: iterator it1;
multimap<string, string> :: iterator it2;
string prev = "";


for(it1 = names_str.begin(); it1 != names_str.end(); it1++)
{
	if(prev == it1->first)
		continue;

	cout << it1->first << " ";

	for(it2 = names_str.begin(); it2 != names_str.end(); it2++)
	{
		if(it1->first == it2->first)
		{
			cout << it2->second << " ";
			prev = it1->first;
		}
	}
	cout << endl;
}

}



int main()
{
multimap<string, string> names_str;
names_str.insert(pair <string, string> ("eric", "mp5"));
names_str.insert(pair <string, string> ("eric", "thompson"));
names_str.insert(pair <string, string> ("eric", "m39"));
names_str.insert(pair <string, string> ("patty", "m92"));
names_str.insert(pair <string, string> ("kyle", "l96"));
names_str.insert(pair <string, string> ("robbie", "ak"));
names_str.insert(pair <string, string> ("chaca", "rock"));

Printout(names_str);

return 0;
}
