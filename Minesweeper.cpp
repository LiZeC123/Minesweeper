#include "Minesweeper.h"
#include "acllib.h"
#include <cstdlib>

using namespace std;


CharDeque::CharDeque() : cheatString("LIZECISMYDADDY"), MaxSize(cheatString.size())
{ }

void CharDeque::push(char one)
{
	content.push_back(one);
	if (content.size() > MaxSize) {
		content.pop_front();
	}
}

bool CharDeque::canCheat()
{
	if (content.size() != cheatString.size()) {
		return false;
	}

	auto sit = cheatString.crbegin();
	auto dit = content.crbegin();
	while (sit != cheatString.crend() && dit != content.crend()) {
		std::cout << "sit=" << *sit << ",dit=" << *dit << std::endl;
		if (*sit++ != *dit++) {
			return false;
		}
	}

	return true;
}