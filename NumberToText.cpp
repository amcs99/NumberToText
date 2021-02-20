#include<string>
#include<vector>
#include<algorithm>

using namespace std;

#pragma once
class NumberToText {
private:
	// name of digit from 0 -> 9
	// e.g in english we have: zero, one, two, three, four, five, six, seven, eight, nine
	// this vector must have exactly 10 elements
	vector<string> digitName;

	// name of teen part, i.e from 10 -> 19
	// this vector must have exactly 10 elements
	vector<string> teenPartName;

	// name of tens part, i.e 20, 30, 40, 50, 60, 70, 80, 90
	// this vector must have exactly 8 elements
	vector<string>  tensPartName;

	// name of the last digit of tens part
	// note: in English, this is same as digitName
	// but in some languagues such as Vietnamese, this is different 
	// in some digit
	// e.g in "24", "4" is read as "tư" not "bốn"
	// this vector must have exactly 10 elements
	vector<string> digitTensPartName;

	// for number with 3 digit and the midle digit is "0"
	// e.g "103" , in English it is nothin, just "one hundred three"
	// but in some languagues it has a name, such as in Vietnamese
	// "0" is "lẻ", "103" is "một trăm lẻ ba"
	string zeroTensPartName;

	// hyphen between ten part and digit
	// e.g in English: 23 is read as "Twenty-three", the hyphen is "-"
	string hyphenBetweenTenPartAndDigit;

	// hyphen between hundred part and ten part
	// e.g in US English, we don't have hyphen between hundred part and ten part
	// but in UK English we have "and"
	string hyphenBetweenHundredPartAndTenPart;

	// name of hundreds part
	// this vector must have exactly 10 elements
	// note: in English we don't have "zero hundred",
	// i.e 1023 is just "one thousand twenty-three"
	// but in some languages such as Vietnamese
	// 1023 is "mot nghin khong tram hai muoi ba"
	vector<string> hundredsPartName;

	// hundred name
	// e.g in English is "hundred" and Vietnamese is "trăm"
	string hundredName;

	

	// name of the dot(in case number is real number)
	// e.g "point" in English and "chấm" in Vietnamese
	string dotName; 

	// for read negative number
	string negativeRead;
	
	// name of number class
	// i.e in English, it can be {"", "thousand", "million", "billion", "trillion"}
	vector<string> numberClassName;

protected:
	// check if a input string is valid number
	bool isValid(string num) {
		int cntDot = 0;
		for (int i = 0; i < num.size(); ++i) {
			if (num[i] >= '0' && num[i] <= '9') continue;
			if (num[i] == '.') {
				if (i == 0 || i == num.size() - 1 || cntDot > 0) {
					return false;
				}
				else {
					++cntDot;
					continue;
				}
			}
			if (num[i] == '-' && i == 0) {
				continue;
			}
			return false;
		}
		return true;
	}

	// convert integer number to text in case length of number is less than or equal to 3
	string smallIntegerNumberToText(string num) {
		if (num == "000") {
			// in case a part of "1000003"
			return "";
		}
		if (num.size() == 1) {
			return digitName[num[0] - '0'];
		}
		else if (num.size() == 2) {
			if (num[0] == '0') {
				// case "00", it must be call from some thing like: 100, 200, ..., 900
				if (num[1] == '0') {
					return "";
				}
				return zeroTensPartName + (zeroTensPartName.size() > 0?" ":"") + digitName[num[1] - '0'];
			} else if (num[0] == '1') {
				return teenPartName[stoi(num) - 10];
			}
			else {
				if (num[1] == '0') {
					return tensPartName[num[0] - '2'];
				}
				return tensPartName[num[0] - '2']
					+ hyphenBetweenTenPartAndDigit
					+ digitTensPartName[num[1] - '0'];
			}
		}
		else {
			return hundredsPartName[num[0] - '0'] + " " + (hundredsPartName[num[0] - '0'].size() > 0?hundredName:"") + " "
				+ hyphenBetweenHundredPartAndTenPart + " "
				+ smallIntegerNumberToText(num.substr(1, 2));
		}
	}

	// convert integer number to text, the integer is non negative 
	// and must be valid input
	string integerNumberToText(string num) {
		// normalize the input
		// i.e "0000123" should be "123", "0000" should be "0"
		int pos = -1;
		while (pos + 1 < num.size() - 1 && num[pos + 1] == '0') ++pos;
		num = num.substr(pos + 1, num.size() - pos - 1);
		if (num.size() <= 3) {
			// just read small int
			return smallIntegerNumberToText(num);
		}
		else {
			// split for each block with ((numberClassName.size()-1) * 3) digit
			// this can read very very large number
			int szOfLargeBlock = (numberClassName.size()-1) * 3;
			int numberOfLargeBlock = (num.size() + szOfLargeBlock - 1) / szOfLargeBlock;
			string resultText = "";
			// name of large block
			// first block has no name
			// for i > 0 
			string curLargeBlockName = "";
			for (int _i = 1; _i <= numberOfLargeBlock; ++_i) {
				string curLargeBlock = num.substr(max(0, (int) num.size() - szOfLargeBlock), min(szOfLargeBlock, (int) num.size()));
				num.erase(num.begin() + num.size() - curLargeBlock.size(), num.end());
				int idxClassName = 0;
				// read each small block with 3 digit
				string curLargeBlockText = "";
				while (curLargeBlock.size() > 0) {
					string curSmallBlock = curLargeBlock.substr(max(0, (int)curLargeBlock.size() - 3)), min(3, curLargeBlock.size());
					string curSmallBlockText = smallIntegerNumberToText(curSmallBlock);
					curLargeBlockText = curSmallBlockText + (curSmallBlockText.size() > 0 ? (" " + numberClassName[idxClassName] + " ") : "") + curLargeBlockText;
					curLargeBlock.erase(curLargeBlock.begin() + curLargeBlock.size() - curSmallBlock.size(), curLargeBlock.end());
					idxClassName++;
				}
				resultText = curLargeBlockText + (_i > 1 ? (" " + numberClassName.back()) : "") + " " + resultText;
			}

			return resultText;
		}
		
	}

	// convert real number to text, the integer is non negative 
	// and must be valid input
	string realNumberToText(string num) {
		int dotPos = num.find(".");
		string naturalPart = num.substr(0, dotPos);
		string decimalPart = num.substr(dotPos + 1, num.size() - dotPos - 1);
		
		string naturalText = integerNumberToText(naturalPart); // the natural part is read as integer number
		// normalize the decimalPart
		// e.g : 1.2300000 should be 1.23
		while (decimalPart.size() > 0 && decimalPart.back() == '0') {
			decimalPart.pop_back();
		}
		string decimalText = "";
		for (const auto &i : decimalPart) {
			decimalText += digitName[i - '0'] + " ";
		}
		if (decimalText.empty()) {
			// this happen in case: 1.00000
			// just return the text of natural part
			return trim(naturalText);
		}
		else {
			return trim(naturalText) + " " + dotName + " " + trim(decimalText);
		}
	}
public:
	NumberToText() {
		// default language is English
		this->digitName = vector<string>{ "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		this->teenPartName = vector<string>{ "ten", "eleven", "twelve", "thirteen", "fourteen", "fifteen", "sixteen", "seventeen", "eighteen", "nineteen" };
		this->tensPartName = vector<string>{ "twenty", "thirty", "forty", "fifty", "sixty", "seventy", "eighty", "ninety" };
		this->digitTensPartName = vector<string>{ "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		this->zeroTensPartName = "";
		this->hyphenBetweenTenPartAndDigit = "-";
		this->hyphenBetweenHundredPartAndTenPart = "";
		this->hundredsPartName = vector<string>{ "", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };
		this->hundredName = "hundred";
		this->dotName = "point";
		this->negativeRead = "negative";
		this->numberClassName = vector<string>{"", "thousand", "million", "billion", "trillion" };
	}
	NumberToText(
		vector<string> digitName,
		vector<string> teenPartName,
		vector<string> tensPartName,
		vector<string> digitTensPartName,
		string zeroTensPartName,
		string hyphenBetweenTenPartAndDigit,
		string hyphenBetweenHundredPartAndTenPart,
		vector<string> hundredsPartName,
		string hundredName,
		string dotName,
		string negativeRead,
		vector<string> numberClassName
	) {
		
		if (digitName.size() != 10 || teenPartName.size() != 10
			|| tensPartName.size() != 8 || digitTensPartName.size() != 10
			|| hundredsPartName.size() != 10) {
			throw "Arguments invalid!";
		}
		this->digitName = digitName;
		this->teenPartName = teenPartName;
		this->tensPartName = tensPartName;
		this->digitTensPartName = digitTensPartName;
		this->zeroTensPartName = zeroTensPartName;
		this->hyphenBetweenTenPartAndDigit = hyphenBetweenTenPartAndDigit;
		this->hyphenBetweenHundredPartAndTenPart = hyphenBetweenHundredPartAndTenPart;
		this->hundredsPartName = hundredsPartName;
		this->hundredName = hundredName;
		this->dotName = dotName;
		this->negativeRead = negativeRead;
		this->numberClassName = numberClassName;
	}

	// remove space at begin and end of a string
	static string trim(string s) {
		while (s.size() > 0 && s.back() == ' ') {
			s.pop_back();
		}
		if (s.empty()) {
			return s;
		}
		int p = -1;
		while (p + 1 < s.size() && s[p + 1] == ' ') ++p;
		return s.substr(p + 1, s.size() - p - 1);
	}
	// nomalize the string
	// i.e remove the unnecessary space
	static string normalize(string s) {
		s = trim(s);
		for (int i = s.size() - 1; i > 0; --i) {
			if (s[i] == ' ' && s[i - 1] == ' ') s.erase(i, 1);
		}
		return s;
	}
	
	string toText(string num) {
		num = trim(num);
		if (num.empty()) {
			return num;
		}
		if (!isValid(num)) {
			throw "Input invalid";
		}
		bool isNegative = false;
		if (num[0] == '-') {
			isNegative = true;
			num.erase(0, 1);
		}
		string numberText = "";
		if (num.find(".") == string::npos) {
			numberText = integerNumberToText(num);
		}
		else {
			numberText = realNumberToText(num);
		}
		if (isNegative) {
			return normalize((numberText != digitName[0]?negativeRead:"") + " " + numberText);
		}
		else {
			return normalize(numberText);
		}
	}
	virtual ~NumberToText() {}
};