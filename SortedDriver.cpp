//Huy Tran
//Lab 6
//Oct 26 2017
// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that 
//   process the sorted sequences.


#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "winTimer.h"
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using std::vector;
using std::sort;


// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty; 
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double
mostIsolated(vector<double> & number)
{
	int size = number.size();
	int currentIndexOfResult = 0;
	double currentMaximumDifference = DBL_MIN;
	double tmp;
	for (int i = 0; i < size; i++) {
		if (i == (size - 1)) {
			tmp = number.at(i) - number.at(i - 1);
		}
		else if (i == 0) {
			tmp = number.at(i + 1) - number.at(i);
		}
		else {
			double difGreater = number.at(i + 1) - number.at(i);
			double difLess = number.at(i) - number.at(i - 1);
			if (difGreater < difLess) { 
				tmp = difGreater; 
			}
			else { tmp = difLess; }
		}

		if (tmp > currentMaximumDifference) { // if i is more isolated than the current most isolated
			currentIndexOfResult = i;
			currentMaximumDifference = tmp;
		}
	}

	return number.at(currentIndexOfResult);
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int
unmatched(list<string> & A, list<string> & B)
{
	int result = 0;
	string last = "";
	bool lastNotInB = false;
	std::list<string>::iterator iterA = A.begin();
	std::list<string>::iterator iterB = B.begin();
	
	while (iterA != A.end() && iterB != B.end()) {
		if (*iterA == *iterB) { // if A == B, increment both, set last = A and last is in B.
			lastNotInB = false;
			last = *iterA;
			iterA++;
			iterB++;
		}
		else if (*iterA < *iterB) {
			if (*iterA != last) {
				result++;
				last = *iterA;
				lastNotInB = true;
			}
			else { // A = last
				if (lastNotInB) { // and last is not in B, so A is not in B
					result++;
				}
			}
			iterA++;//since A < B, we increment A
		}
		else { // A > B
			iterB++;
			if (iterB == B.end()) {
				result++;
			}
		}
	}
	return result;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}