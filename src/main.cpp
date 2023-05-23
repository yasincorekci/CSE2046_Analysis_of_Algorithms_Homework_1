
#include <iostream>
#include <sstream>
#include <fstream>

#include "search.h"
#include "util.h"
#include "timer.h"

#define FILE_OUT

std::string markHtml(const std::string& html, const std::string& pattern, std::vector<int>& positions)
{
	std::stringstream markedHtml;

	int m = (int) pattern.length();

	int last = 0;
	int begin = -1;
	bool cont = false;

	if (positions.size() == 0)
		return "";

	for (int i = 0; i < (int) (positions.size() - 1); ++i) {
		if (positions[i] + m > positions[i + 1]) {
			if (!cont) {
				begin = positions[i];
			}
			cont = true;
		}
		else {
			if (cont) {
				markedHtml << html.substr(last, begin - last);
				markedHtml << "<mark>";
				markedHtml << html.substr(begin, positions[i] + m - begin);
				markedHtml << "</mark>";
			}
			else {
				markedHtml << html.substr(last, positions[i] - last);
				markedHtml << "<mark>";
				markedHtml << html.substr(positions[i], m);
				markedHtml << "</mark>";
			}

			last = positions[i] + m;
			cont = false;
		}
	}

	if (!positions.empty()) {
		if (cont) {
			markedHtml << html.substr(last, begin - last);
			markedHtml << "<mark>";
			markedHtml << html.substr(begin, positions[positions.size()-1] + m - begin);
			markedHtml << "</mark>";
		}
		else {
			markedHtml << html.substr(last, positions[positions.size() - 1] - last);
			markedHtml << "<mark>";
			markedHtml << html.substr(positions[positions.size() - 1], m);
			markedHtml << "</mark>";
		}

		last = positions[positions.size() - 1] + m;
	}

	if (last < (int) html.length()) {
		markedHtml << html.substr(last, html.length() - last);
	}

	return markedHtml.str();
}

void runTest(const std::string& text, const std::string& pattern)
{
	int totalCompares = 0;

	Timer timer;

	BruteForceSearch searchBruteForce;
	HorspoolSearch searchHorspool;
	BoyerMooreSearch searchBoyerMoore;

	std::cout << "#####################################" << std::endl;
	std::cout << "              Test                   " << std::endl;
	std::cout << "#####################################" << std::endl;

	std::cout << "Brute Force: " << std::endl;
	std::cout << "-------------------------------------" << std::endl;

	timer.start();
	auto v1 = searchBruteForce.search(text, pattern, totalCompares);
	timer.stop();

	std::string bruteForcedMarked = markHtml(text, pattern, v1);
	Util::writeFile("BruteForce_" + pattern + ".html", bruteForcedMarked);

	std::cout << "Total compares: " << totalCompares << ", " << "Found: " << v1.size() << ", Elapsed: " << timer.elapsedInSeconds() << std::endl;
	std::cout << std::endl;

	std::cout << "Horspool: " << std::endl;
	std::cout << "-------------------------------------" << std::endl;

	timer.start();
	auto v2 = searchHorspool.search(text, pattern, totalCompares);
	timer.stop();

	std::string horspoolMarked = markHtml(text, pattern, v2);
	Util::writeFile("Horspool_" + pattern + ".html", horspoolMarked);

	std::cout << "Total compares: " << totalCompares << ", " << "Found: " << v2.size() << ", Elapsed: " << timer.elapsedInSeconds() << std::endl;
	std::cout << std::endl;

	std::cout << "Boyer Moore: " << std::endl;
	std::cout << "-------------------------------------" << std::endl;

	timer.start();
	auto v3 = searchBoyerMoore.search(text, pattern, totalCompares);
	timer.stop();

	std::string boyerMooreMarked = markHtml(text, pattern, v3);
	Util::writeFile("BoyerMoore_" + pattern + ".html", boyerMooreMarked);

	std::cout << "Total compares: " << totalCompares << ", " << "Found: " << v3.size() << ", Elapsed: " << timer.elapsedInSeconds() << std::endl;
	std::cout << std::endl;

	std::cout << "Searched pattern: '" << pattern << "', Pattern length: " << pattern.length() << std::endl;

	std::cout << std::endl;
}

int main()
{
	std::string text = Util::readFile("CrimeAndPunishment.html");
	std::string pattern = "";

#ifdef FILE_OUT
	std::ofstream out("output.txt");
	std::streambuf* coutbuf = std::cout.rdbuf();
	std::cout.rdbuf(out.rdbuf());
#endif

	pattern = "ee";
	runTest(text, pattern);

	pattern = "the";
	runTest(text, pattern);

	pattern = "serve";
	runTest(text, pattern);

	pattern = "Raskolnikov";
	runTest(text, pattern);

	pattern = "Later on, when he recalled that time and all that happened to him during";
	runTest(text, pattern);

	std::cout << "*********************************************" << std::endl;

	text = Util::createRandomHtml();

	for (int i = 1; i <= 20; ++i) {
		pattern = text.substr(text.length() / 2 + 5, 5*i);
		runTest(text, pattern);
	}

#ifdef FILE_OUT
	std::cout.rdbuf(coutbuf);
#endif

	return 0;
}
