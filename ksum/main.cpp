#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <functional>
#include <unordered_map>

// Compare two lists to see if they're the same group; in most
// circumstances we should check for the equality of their sizes
// and early out with a false return if they weren't equal;
// however, this function is only called if the lists
// to be compared are equal to the prerequisite size anyway.
// It's provided for completeness and flexibility for other use-cases


/*
 * as it turns out, this function isn't necessary because the nature of the combinations algorithm
   prevents this via sequentially chopping off every member
   from the given numbers list
 * it's here for documentation purposes.
 *
static bool isSameUnordered(const std::vector<int>& a, const std::vector<int>& b) {
	std::unordered_map<int, int> m;

	if (a.size() != b.size())
		return false;

	// if m[x] does not exist yet,
	// the increment will first initialize it to 0
	// and then add 1 accordingly;
	// i.e., if m[x] does not exist,
	// even simply reading its value
	// will cause it to be zero-initialized
	// (on GCC)
	for (int x: a)
		m[x]++;

	for (int x: b) {
		if (m[x] == 0)
			return false;
		m[x]++;
	}

	return true;
}
*/


// This is a recursive function designed to find
// all possible sum combinations for a given list of numbers.

// For a particular size of numbers of k, and a tuple of
// distinct integers t (which is always required and given size k),
// if the sum of t is equivalent to the target sum s,
// we have a winning value. Correspondingly, we print this winning value
// ( in addition to its sequence ) into an output file corresponding
// to the input file the sum value stems from.

// The running time of this function n and k is the following combination formula (where order doesn't matter):
// O(n! / k!(n - k)!) or O(nCk)

// The implementation of this function was originally in Python,
// and can be found here: http://stackoverflow.com/a/4633515
static void sum(std::ofstream& stream,
				const int targetSum,
				const int targetAmount,
				const std::vector<int>& numbers,
				const std::vector<int>& partial = std::vector<int>()) {

	if (partial.size() == (uint32_t) targetAmount)
	{
		// Compute the sum for this current group
		int s = 0;
		std::for_each(partial.begin(), partial.cend(), [&s](const int& x) -> void {
			s += x;
		});

		// If we're valid, provide an output which shows the expression
		if (s == targetSum) {
			std::stringstream ss;

			size_t c = 0;

			for (int i: partial) {
				ss << i;

				if (++c != partial.size())
					ss << " + ";
			}
			ss << " = " << targetSum << "\n";
			stream << ss.str();
		}

		// There is no point in continuing if either of these are true,
		// since we'll only be increasing the value/partial size if
		// recurse down the tree further.
		if (s >= targetSum)
			return;
	}

	// Same principle with the sum check in the above block^^^
	if (partial.size() >= (size_t)targetAmount)
		return;

	// For us to evaluate all possible combinations (up to the desired target amount)
	// we develop a chain of values for every single value
	// which individually inspects it self with every other possible
	// sum in every list

	// Each iteration successively creates a new variant of the given partial list,
	// by taking the value in numbers corresponding to the current iteration,
	// chopping off every value up to (inclusive) that iteration from the numbers list
	// and creating a copy of that list with which we can use to evaluate within the next depth.

	// So, if I have abcdefg numbers, all of the partial combinations for first level will be:
	// ab, ac, ad, ae, af, ag

	// And in the next level:
	// abc, abd, abe, abf, abg;
	// acd, ace, acf, acg;
	// ade, adf, adg;
	// aef, aeg;
	// afg

	// (and so on and so forth)
	for (auto i = numbers.begin(); i != numbers.end(); ++i) {
		int x = *i;

		std::vector<int> remaining;
		int index = std::distance(numbers.begin(), i);
		remaining.reserve(numbers.size() - index);

		for (auto j = i + 1; j != numbers.end(); ++j)
			remaining.push_back(*j);

		std::vector<int> newPartial(partial.begin(), partial.end());
		newPartial.push_back(x);

		sum(stream, targetSum, targetAmount, remaining, newPartial);
	}
}

static bool parseInput(const std::string& inputPath, const std::string& outputPath) {
	std::ifstream f;
	f.open(inputPath);

	std::ofstream output;
	output.open(outputPath);

	int targetSum = 0;
	int targetAmount = 0;

	std::vector<int> numbers;

	if (f.is_open()) {
		// Get the current line,
		// evaluate its function accordingly,
		// depending on the current line number
		std::string line;
		int lineNum = 0;

		while (std::getline(f, line)) {
			std::istringstream toInteger(line);
			switch (lineNum) {
				case 1: toInteger >> targetSum; break;
				case 0: toInteger >> targetAmount; break;
				default:  {
					int value;
					toInteger >> value;
					numbers.push_back(value);
				} break;
			}

			lineNum++;
		}

		// Compute the sum.
		output << "BEGIN " << inputPath << "\n\n";
		output << "number count: " << numbers.size() << "\n";
		output << "target amount: " << targetAmount << "\n";
		output << "target sum: " << targetSum << "\n";

		sum(output, targetSum, targetAmount, numbers);

		output << "END input\n\n";

		output.close();

	} else {
		return false;
	}

	return true;
}

int main()
{
	// Must be <= the amount of test files generated via input_gen.py
	int numTests = 3;

	for (int i = 0; i < numTests; ++i) {
		std::string inpath("input" + std::to_string(i) + ".txt");
		if (!parseInput(inpath, "result_input" + std::to_string(i) + ".txt")) {
			std::cout << "Could not read file \"" << inpath << '\"' << std::endl;
		}
	}

	return 0;
}

