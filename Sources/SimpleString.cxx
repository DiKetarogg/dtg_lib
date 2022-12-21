#include <dtg/Utilities.hpp>
#include <iostream>
#include <vector>
int main () {
	{
	std::cout << "sizeof = " << sizeof(dtg::SimpleString) << '\n';
	dtg::SimpleString string = "Test1";
	std::cout << string << '\n';//
	string.Append(".Test2");
	std::cout << string << '\n';
	string.Append(".","T","e","s","t","3");
	std::cout << string << '\n';
	dtg::SimpleString string1 = "Te";
	dtg::SimpleString string2 = "4";
	string.Append(".", string1, "st", string2);
	std::cout << string << '\n';
	//////Test1.Test2.Test3.Test4.TeStFive.
	dtg::SimpleString strings[] = {".Te", "St", "Five."};
	string.Append(strings, strings + 3);
	std::cout << string << '\n';
	const char* strings1[] = {"Te", "St", "Six."};
	string.Append(strings1, strings1 + 3);
	std::cout << string << '\n';
	std::vector<dtg::SimpleString> vec = {string, string1, string2, strings[0], strings[1], strings[2]};
	dtg::SimpleString iteratorConstructor{vec.begin(), vec.end()};
	std::cout << "final: " << iteratorConstructor << '\n';
	}//append test
	{
	
	std::string test_std = "test_str";
	dtg::SimpleString test_dtg = "test_str";
	if (std::hash<std::string>()(test_std) == std::hash<dtg::SimpleString>()(test_dtg))
		std::cout << "Passed\n";
	else
		std::cout << "Failed\n";
	}//hash test
}
