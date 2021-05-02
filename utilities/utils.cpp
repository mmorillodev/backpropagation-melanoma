#include <string>
#include <cstring>
#include <list>
#include <iostream>

std::list<double> split_d(std::string str, char separator) {
	std::list<double> splitted;
	std::cout << str << std::endl;
	
	int i = 0, j = 0;
	for ( ; i < str.size(); i++) {
		std::string::iterator it = str.begin();
		std::advance(it, i);
		if (*it == separator) {
			splitted.push_back(atof(str.substr(j, i - j).c_str()));
			j = i + 1;
		}
	}

	if (j < str.size()) {
		splitted.push_back(atof(str.substr(i, i - j).c_str()));
	}
	
	return splitted;
}