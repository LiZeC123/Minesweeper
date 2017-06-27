#include "Minesweeper.h"
#include "acllib.h"
#include <cstdlib>


void CharDeque::push(char one)
{
	content.push_back(one);
	if (content.size() > MaxSize) {
		content.pop_front();
	}
}

void CharDeque::show()
{
	for (const auto &i : content) {
		std::cout << (char)i;
	}
	std::cout << std::endl;
}

bool CharDeque::operator==(const std::string & rs)
{
	auto sit = rs.crbegin();
	auto dit = content.crbegin();
	while (sit != rs.crend() && dit != content.crend()) {
		if (*sit != *dit) {
			return false;
		}
		++sit;
		++dit;
	}
	return true;
}
