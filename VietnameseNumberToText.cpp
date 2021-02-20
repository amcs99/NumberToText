#include "NumberToText.cpp"
 
class VietnameseNumberToText : public NumberToText {
public:
	VietnameseNumberToText() : NumberToText(
		vector<string>{ "khong ", "mot", "hai", "ba", "bon", "nam", "sau", "bay", "tam", "chin" },
		vector<string>{ "muoi", "muoi mot", "muoi hai", "muoi ba", "muoi bon", "muoi lam", "muoi sau", "muoi bay", "muoi tam", "muoi chin" },
		vector<string>{ "hai muoi", "ba muoi", "bon muoi", "nam muoi", "sau muoi", "bay muoi", "tam muoi", "chin muoi" },
		vector<string>{ "", "mot", "hai", "ba", "tu", "lam", "sau", "bay", "tam", "chin" },
		"le",
		" ",
		"",
		vector<string>{ "khong", "mot", "hai", "ba", "bon", "nam", "sau", "bay", "tam", "chin" },
		"tram",
		"cham",
		"am",
		vector<string> {"", "nghin", "trieu", "ty"}
		) {}
};