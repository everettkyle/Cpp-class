#include <iostream>
#include <string>
#include <filesystem>
#include <vector>
#include <stack>
#include <fstream>
#include <map>
#include <algorithm>
#include <cmath>
#include <regex>


//Compile -> g++-8 final_pro.cpp -lstdc++fs -std=c++17

using namespace std;

bool sortbysec(const pair<string, int> &a, const pair<string, int> &b)
{
    return a.second>b.second;
}


int sw_count(string file_name, string sword)
{
	string data;
	int count = 0;
	ifstream infile;

	infile.open(file_name);
	if(infile.is_open())
		while(!infile.eof())
		{
			infile >> data;
			if(data == sword)
				count++;
		}

	infile.close();
	return count;
}

bool sen_compare(string str, string search_w)
{
        string word = "";
        vector<string> words;
        for(auto x : str)
        {
                if(x == ' ')
                {
                        words.push_back(word);
                        word = "";
                }

                else
                        word = word + x;
        }

        words.push_back(word);

        for(int i=0; i<words.size(); i++)
                if(words[i] == search_w)
                        return true;

        return false;
}


void sw_line(string file_name, string search_w)
{
	map<int, string> line_pair;
        string data;
        int line_num = 1;


	ifstream file(file_name);
        while(getline(file,data))
        {
                line_pair.insert(make_pair(line_num, data));
                line_num++;
        }


	 string tmpStr;

        //printing out the mapping
        for(auto &lp1: line_pair)
        {
                tmpStr = lp1.second;
                string word = "";

                if(sen_compare(tmpStr, search_w))
                        cout << "Occurences of search word on line number:" << lp1.first << "   " << "\"" << lp1.second << "\"" << "   Filename:" << file_name << endl;
	}

}



bool brac(char open, char close)
{
	if(open == '(' && close == ')')
		return true;

	else if (open == '[' && close == ']')
		return true;

	else if (open == '{' && close == '}')
		return true;

	return false;
}

bool balancedPara(string str)
{
	stack<char> sk;
	for(int i = 0; i < str.length(); i++)
	{
		if(str[i] == '(' || str[i] == '{' || str[i] == '[')
			sk.push(str[i]);
		else if(str[i] == ')' || str[i] == '}' || str[i] == ']')
		{
			if(sk.empty() || !brac(sk.top(), str[i]))
				return false;
			else
				sk.pop();
		}
	}
	return sk.empty();
}



int term_total(string search_w)
{

        string path_x = filesystem::current_path();
        vector<string> file_names;
        int total = 0;
	string data;

        for(auto& p: filesystem::directory_iterator(path_x))
        {
                string path_y = p.path();
                if(path_y[path_y.length() - 1] == 't' && path_y[path_y.length() - 2] == 'x')
                        file_names.push_back(path_y);
        }


        for(int i=0; i<file_names.size(); i++)
	{

		ifstream infile;
        	infile.open(file_names[i]);
        	if(infile.is_open())
                	while(!infile.eof())
                	{
                        	infile >> data;
                        	if(data == search_w)
				{
                                	total++;
					break;
                		}
			}
		infile.close();
	}

        return total;
}


float tf_idf(string search_w, string file_name, int doc_count)
{

	string data;
        float W_count = 0.0;
	float T_count = 0.0;
        float tt_count = 0.0;
	float tf_weight = 0.0;
	float tf = 0.0;
	float idf = 0.0;

	ifstream infile;
        infile.open(file_name);
        if(infile.is_open())
                while(!infile.eof())
                {
                        infile >> data;
                        if(data == search_w)
                                W_count++;
			T_count++;
                }
        infile.close();

	tt_count = term_total(search_w);
	tf = W_count/T_count;
	idf = log(doc_count/tt_count);

	tf_weight = tf*idf;

	return tf_weight;
}

void sub_direct(vector<string> &file_names, string path_x)
{
	for(auto& p: filesystem::directory_iterator(path_x))
	{
		string path_y = p.path();
		if(path_y[path_y.length() - 1] == 't' && path_y[path_y.length() - 2] == 'x' && path_y[path_y.length() - 4] == '.')
			file_names.push_back(path_y);

		if(path_y[path_y.length() - 4] != '.')
			sub_direct(file_names, path_y);

	}
}


string buildReg(string search_p)
{
	string reg = "";

	string reg_one_m = "[a-zA-Z ,0-9!.]+";
        string reg_zero_m = "[a-zA-Z ,0-9!.]*";

	string tmpStr = "";


	for(int i=0; i<search_p.length(); i++)
	{
		if(search_p[i] == '*')
		{
			tmpStr = tmpStr + reg_zero_m;
			continue;
		}

		if(search_p[i] == '?')
		{
			tmpStr = tmpStr + reg_one_m;
			continue;
		}

		else
			tmpStr = tmpStr + search_p[i];

	}

	reg = tmpStr;

	return reg;
}




bool matchLine(string search_p, string str)
{
	string reg_b = "";

	reg_b = buildReg(search_p);
	regex reg(reg_b);
	smatch matches;

	regex_search(str, matches, reg);

	if(matches.empty())
		return false;

	if(matches.size() > 0)
		return true;
}


int main()
{
	string search_w = "";
	string search_p = "";
	map<string, int> freq;
	string data;
	string tmpStr;
	int doc_count = 0;
	int para_count = 0;

	cout << "Enter a search word: " << endl;
	cin >> search_w;

	cout << "Enter a search phrase (include a \"*\" or \"?\"):" << endl;
	cin >> search_p;


	string path_x = filesystem::current_path();
	vector<string> file_names;
	for(auto& p: filesystem::directory_iterator(path_x))
	{
		string path_y = p.path();
		if(path_y[path_y.length() - 1] == 't' && path_y[path_y.length() - 2] == 'x' && path_y[path_y.length() - 4] == '.')
			file_names.push_back(path_y);

		if(path_y[path_y.length() - 4] != '.')
			sub_direct(file_names, path_y);
	}

	for(int i=0; i<file_names.size(); i++)
		doc_count++;

	cout << endl;
	for(int i=0; i<file_names.size(); i++)
	{
		cout << "Search Results: " << endl;
		int cnt = sw_count(file_names[i], search_w);
        	cout << "Frequency of search word:" << cnt <<"   Filename:" << file_names[i] << endl;

		ifstream infile;
		//opens a file and finds the freq of all words in that file
        	infile.open(file_names[i]);
        	if(infile.is_open())
                	while(!infile.eof())
                	{
                        	infile >> data;
                        	//check if data is inside of map
				map<string, int>::iterator it = freq.find(data);

				if(it != freq.end())
					it->second++;
				else
					freq.insert(make_pair(data, 1));
			}
		infile.close();

		//paraenthesis balanced
		map<int, string> line_para;
        	string para_data;
        	int line_num = 1;

        	ifstream file(file_names[i]);
        	while(getline(file,para_data))
        	{
                	line_para.insert(make_pair(line_num, para_data));
                	line_num++;
        	}

		for(auto &pb1: line_para)
        	{
                	tmpStr = pb1.second;
                	if(balancedPara(tmpStr))
				continue;
			else
				cout << "Line number:" << pb1.first << " is not balanced.  Filename:" << file_names[i] << " Line:" << tmpStr << endl;
		}

		sw_line(file_names[i], search_w);

		for(auto &sp1: line_para)
		{
			if(matchLine(search_p, sp1.second))
				cout << "Search phrase match - Line number:" << sp1.first << " Line:" << sp1.second << " Filename:" << file_names[i] << endl;
		}
		cout << endl;


	}

	cout << endl;
	vector< pair <string, int> > sort_vec;
        cout<<"Total frequency of all words:" << endl;

	//Mapping frequency map to pair vec and then sorted in descending order
        for(auto &e : freq)
		sort_vec.push_back(make_pair(e.first, e.second));
	sort(sort_vec.begin(), sort_vec.end(), sortbysec);

        //prints out sorted vec with freq count of words
        for(int i=0; i<sort_vec.size(); i++)
                cout << sort_vec[i].first << " " << sort_vec[i].second << ", ";

	//vector<float> tf_weights;
	map<string, float> tf_weights;
	for(int i=0; i<file_names.size(); i++)
		tf_weights.insert(make_pair(file_names[i], tf_idf(search_w, file_names[i], doc_count)));

	float tmpVal = 0.0;
	cout << endl;
	cout << endl;

	for(auto &pb1: tf_weights)
        {
        	tmpVal = pb1.second;
                if(tmpVal > 0.0)
                	cout << "TF-IDF weight:" << pb1.second << "  Filename:" << pb1.first << endl;
	}
	cout << endl;

	//for(int i=0; i<tf_weights.size(); i++)
	//	cout << tf_weights[i] << endl;


	return 0;

}


