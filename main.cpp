//This is main program to test whether the program work correctly

#include <iostream>
#include "NumberToText.cpp"
#include "VietnamesenumberToText.cpp"

using namespace std;

int main()
{
	// default language is English
	NumberToText *num = new NumberToText();
	cout << "========English========" << endl;
	cout << "1123: " << num->toText("1123") << endl;
	cout << "-102: " << num->toText("-102") << endl;
	cout << "3.14159: " << num->toText("3.14159") << endl;
	cout << "1000000000: " << num->toText("1000000000") << endl;
	cout << "1000000000000: " << num->toText("1000000000000") << endl;
	cout << "11234456000001: " << num->toText("11234456000001") << endl;

	// convert number to Vietnamese text
	num = new VietnameseNumberToText();
	cout << "========Vietnamese========" << endl;
	cout << "1123: " << num->toText("1123") << endl;
	cout << "-102: " << num->toText("-102") << endl;
	cout << "3.14159: " << num->toText("3.14159") << endl;
	cout << "1000000000: " << num->toText("1000000000") << endl;
	cout << "1000000000000: " << num->toText("1000000000000") << endl;
	cout << "11234456000001: " << num->toText("11234456000001") << endl;
	system("pause");
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started:
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
