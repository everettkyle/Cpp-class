#include <iostream>
#include <map>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

map<string, vector<pair <string, char>>> transform(map<string, vector<pair <string, char> > > &perms)
{
	vector<string> names;
	string key;
	map<string, vector<pair <string, char> > > trans_map;

	for(auto map_it = perms.begin(); map_it != perms.end(); map_it++)
	{
		for(auto vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++)
		{
			key = vec_it->first;
			if(count(names.begin(), names.end(), key))
				continue;
			else
				names.push_back(key);

		}
	}

	char tmp_c;
	for(int i=0; i<names.size(); i++)
	{
		for(auto map_it = perms.begin(); map_it != perms.end(); map_it++)
			for(auto vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++)
			{
				if(names[i] == vec_it->first){
				tmp_c = vec_it->second;
				trans_map[names[i]].push_back(make_pair(map_it->first, tmp_c));

				}

			}

	}


	return trans_map;
}


bool search_perm(map<string, vector<pair <string, char> > > &perms, string name, string n_perm, string doc_name)
{
	string map_name;
	string vec_name;
	char vec_perm;
	char c_perm;

	if(n_perm == "append")
		c_perm = 'a';
	if(n_perm == "read")
		c_perm = 'r';
	if(n_perm == "write")
		c_perm = 'w';


	auto p = make_pair(doc_name, c_perm);


	for(auto map_it = perms.begin(); map_it != perms.end(); map_it++)
	{
		if(map_it->first == name)
		{
			if(find(perms[name].begin(), perms[name].end(), p) != perms[name].end() )
				return true;
		}

	}


	return false;

}


int main()
{
	string data;
	string tmp_str;
	string p_str;
	vector<string> coll;
	vector<string> docs;
	vector<string> temp_perm;
	vector<pair<string, char>> name_prem;
	string test_str;

	map<string, vector<pair <string, char> > > perms;

	ifstream infile;
	infile.open("access_rights.txt");
	if(infile.is_open())
		while(!infile.eof())
		{
			infile >> data;
			if(data == test_str)
				break;
			test_str = data;
			coll.push_back(data);
		}

	infile.close();

	int flag = 0;
	string mp;

	for(int i=0; i<coll.size(); i++)
	{
		if(coll[i][0] != '(')
			mp = coll[i];

		if(coll[i][0] == '(')
		{
			tmp_str = coll[i];
			for(int j=1; j<tmp_str.size(); j++)
			{
				if(tmp_str[j] == ',')
				{
					perms[mp].push_back(make_pair(p_str, tmp_str[j+1]));
					p_str = "";
					tmp_str = "";
					break;
				}
				p_str = p_str + tmp_str[j];

			}
		}
	}
	cout << "Before Transform:" << endl;
	//Before transform
	for(auto map_it = perms.begin(); map_it != perms.end(); map_it++)
        {
                cout << map_it->first;
                for(auto vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++)
                        cout << " " << vec_it->first << " " << vec_it->second;
                cout << endl;

        }
	cout << endl;
	cout << endl;
	perms = transform(perms);


	cout << "After Transform:" << endl;
	//After transform
 	for(auto map_it = perms.begin(); map_it != perms.end(); map_it++)
        {
                cout << map_it->first;
                for(auto vec_it = map_it->second.begin(); vec_it != map_it->second.end(); vec_it++)
                        cout << " " << vec_it->first << " " << vec_it->second;
                cout << endl;

        }
	cout << endl;
	cout << endl;

	//testing search permissions
	string name = "Bob";
	string n_perm = "read";
	string doc_name = "doc2";

	if(search_perm(perms, name, n_perm, doc_name))
		cout << name << " " << "has that permission" << endl;
	else
		cout << "Sorry " << name << " doesnt have that permission" << endl;

	return 0;
}
