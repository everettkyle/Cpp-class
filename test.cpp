#include <iostream>
#include <experimental/filesystem>
#include <string>

namespace fs = std::experimental::filesystem;
using namespace std;

int main()
{
	string path = fs::current_path();
	for(const auto & entry : fs::directory_iterator(path))
	{
		string path = entry.path();
		int length = path.length();
		int n_length = length - 3;
		cout << path[n_length] << endl;
	}

	return 0;

}
