#include <string>
#include <list>
#include <iostream>

std::list<double> split_d(std::string str, char separator) {
	std::list<double> returnStatement;

	for (char& character : str) {

		if (character != separator) {
			returnStatement.push_back(atof(&character));
		}
	}

	return returnStatement;
}