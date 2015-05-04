#include <iostream>
#include <vector>

bool yeah(const std::string &s,std::vector<std::string> &vec);

int main()
{
	std::vector<std::string> v;
	v.reserve(4);
	
	v.push_back("hi");
	v.push_back("how");
	v.push_back("are");
	v.push_back("you");
	/*v.insert(v.begin(),106);
	std::cout << v[0] << "\n";
	std::cout << v[1] << "\n";
	std::cout << v.capacity() << "," << v.size() << "," << v.front() << "," << v.back() << "\n";
	std::cout << 1/2 << "\n";*/
	
	std::string s="doing";
	yeah(s,v);
	std::cout << v.back() << "\n";
	s="no";
	std::cout << v.back() << "\n";
	
	return 0;
}

bool yeah(const std::string &str,std::vector<std::string> &vec) {
	vec.push_back(str);
}
