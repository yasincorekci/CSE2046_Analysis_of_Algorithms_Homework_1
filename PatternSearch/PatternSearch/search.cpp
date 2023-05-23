
#include "search.h"

#include <iostream>

std::vector<int> BruteForceSearch::search(const std::string& text, const std::string& pattern, int& totalCompares)
{
    std::vector<int> foundIndexes;
    totalCompares = 0;

	if (text.length() < pattern.length() || pattern.empty())
		return foundIndexes;

    for (int i = 0; i <= (int) (text.length() - pattern.length()); i++) {
        int k;

        for (k = 0; k < (int) pattern.length(); k++) {
            ++totalCompares;

            if (text[i + k] != pattern[k])
                break;
        }

        if (k == (int) pattern.length()) {
            foundIndexes.push_back(i);
        }
    }

    return foundIndexes;
}

std::vector<int> BoyerMooreSearch::search(const std::string& text, const std::string& pattern, int& totalCompares)
{
	std::vector<int> foundIndexes;
	totalCompares = 0;

	if (text.length() < pattern.length() || pattern.empty())
		return foundIndexes;

	int* borders = new int[pattern.length()+1]();
	int* shifts = new int[pattern.length()+1]();
	int badCharacterTable[CHARACTERS_COUNT];
	
	createBadCharacterTable(pattern, badCharacterTable, CHARACTERS_COUNT);
	createGoodSuffix(pattern, borders, shifts);
	createPartialGoodSuffix(borders, shifts, pattern.length());
	
	int i = 0;
	int j;

	while (i <= (int) (text.length() - pattern.length())) {
		j = (int) (pattern.length() - 1);

		while (j >= 0) {
			++totalCompares;

			if (pattern[j] != text[i + j])
				break;
			
			--j;
		}

		if (j < 0) {
			foundIndexes.push_back(i);

			if ((i + pattern.length()) < text.length()) {
				i += std::max(shifts[0], (int) pattern.length() - badCharacterTable[(uint8_t) text[i + pattern.length()]]);
			}
			else {
				i += shifts[0];
			}
		}
		else {
			i = i + std::max(shifts[j+1], j - badCharacterTable[(uint8_t) text[i+j]]);
		}
	}

	delete[] borders;
	delete[] shifts;

	return foundIndexes;
}

void BoyerMooreSearch::createBadCharacterTable(const std::string& pattern, int* table, int len)
{
    for (int i = 0; i < len; ++i)
        table[i] = -1;

    for (int i = 0; i < (int) pattern.length(); ++i) {
        table[(uint8_t) pattern[i]] = i;
    }

	std::string delim = "";

	std::cout << "Bad character heuristic: " << std::endl;

	for (int i = 0; i < len; ++i) {
		if (table[i] != -1) {
			std::cout << delim << (char)i << ": " << table[i];

			if (delim.empty())
				delim = ", ";
		}
	}

	std::cout << std::endl;
}

void BoyerMooreSearch::createGoodSuffix(const std::string& pattern, int* borders, int* shifts)
{
    int i = (int) pattern.length();
    int j = (int) (pattern.length() + 1);

	borders[i] = j;

	while (i > 0) {
		while ((j <= (int) pattern.length()) && (pattern[i-1] != pattern[j-1])) {
			if (shifts[j] == 0) {
				shifts[j] = j-i;
			}

			j = borders[j];
		}

		--i;
		--j;
		borders[i] = j;
	}
}

void BoyerMooreSearch::createPartialGoodSuffix(int* borders, int* shifts, size_t len)
{
	int j = borders[0];

	for (int i = 0; i <= (int) len; i++) {
		if (shifts[i] == 0) {
			shifts[i] = j;
		}

		if (i == j) {
			j = borders[j];
		}
	}

	std::string delim = "";

	std::cout << "Good character heuristic: " << std::endl;

	for (int i = 0; i <= (int) len; ++i) {
		if (shifts[i] != -1) {
			std::cout << delim << shifts[i];

			if (delim.empty())
				delim = ", ";
		}
	}

	std::cout << std::endl;
}

std::vector<int> HorspoolSearch::search(const std::string& text, const std::string& pattern, int& totalCompares)
{
	std::vector<int> foundIndexes;
	totalCompares = 0;

	if ((text.length() < pattern.length()) || pattern.empty())
		return foundIndexes;

	int i;

	int m = pattern.length();
	int n = text.length();

	int shifts[CHARACTERS_COUNT];

	for (i = 0; i < CHARACTERS_COUNT; ++i)
		shifts[i] = -1;

	for (i = 0; i < m; ++i)
		shifts[(uint8_t) pattern[i]] = i;

	i = 0;

	while (i <= (n - m)) {
		int j = m - 1;

		while (j >= 0) {
			++totalCompares;

			if (pattern[j] != text[i + j])
				break;

			--j;
		}
		
		if (j < 0) {
			foundIndexes.push_back(i);

			if ((i + pattern.length()) < text.length()) {
				i += (int) (pattern.length() - shifts[(uint8_t) text[i + pattern.length()]]);
			}
			else {
				++i;
			}
		}
		else {
			i += std::max(1, j - shifts[(uint8_t) text[i + j]]);
		}
	}

	return foundIndexes;
}
