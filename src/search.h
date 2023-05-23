
#ifndef __SEARCH_H
#define __SEARCH_H

#include <string>
#include <vector>

#define CHARACTERS_COUNT		256

class Search {
public:
	virtual std::vector<int> search(const std::string& text, const std::string& pattern, int& totalCompares) = 0;
};

class BruteForceSearch : public Search {
public:
	std::vector<int> search(const std::string& text, const std::string& pattern, int& totalCompares);
};

class HorspoolSearch : public Search {
public:
	std::vector<int> search(const std::string& text, const std::string& pattern, int& totalCompares);
};

class BoyerMooreSearch : public Search {
public:
	std::vector<int> search(const std::string& text, const std::string& pattern, int& totalCompares);

private:
	void createBadCharacterTable(const std::string& pattern, int* table, int len);
	void createGoodSuffix(const std::string& pattern, int* borders, int* shifts);
	void createPartialGoodSuffix(int* borders, int* shifts, size_t len);
};

#endif
