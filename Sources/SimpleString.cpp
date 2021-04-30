#include <dtg/Utilities.hpp>
#include <iostream>
int main () {
	std::cout << "sizeof = " << sizeof(dtg::SimpleString) << '\n';
	dtg::SimpleString string = "Test1";
	std::cout << string << '\n';
	string.Append(".Test2");
	std::cout << string << '\n';
	string.Append(".","T","e","s","t","3");
	std::cout << string << '\n';
	dtg::SimpleString string1 = "Te";
	dtg::SimpleString string2 = "4";
	string.Append(".", string1, "st", string2);
	std::cout << string << '\n';
	dtg::SimpleString strings[] = {".Te", "St", "Five."};
	string.Append(strings, strings + 3);
	std::cout << string << '\n';
	const char* strings1[] = {"Te", "St", "Six."};
	string.Append(strings1, strings1 + 3);
	std::cout << string;
}
