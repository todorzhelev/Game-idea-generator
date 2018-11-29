//Combinations without repetition generator with O(n) complexity
//the algorithm is written by Dennis Clarke dclarke@blastwave.org
//Standard algorithms would have nested loops, which is not feasible for more than 5 elements I would say
//another approach is to have random elements generation with hash, which can be checked if it exists already
//Is there O(logN)? May be with recursion and parallelization.


#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <unordered_map>

std::vector<std::vector<int>> g_combinations;

 /* Prints out a combination like {1, 2} */
void printc(int *comb, int k) {

	int j;
	//std::string res;
	//res.append("{ ");

	//printf("{ ");
	std::vector<int> elements;

	for (j = 0; j < k; ++j)
	{
		elements.push_back(*(comb + j) + 1);
		//res.append(std::to_string(*(comb + j) + 1));
		//res.append(" , ");
	}
		
		//printf("%d , ", *(comb + j) + 1);

	//res.append("\b\b}\n");
	//printf("\b\b}\n");

	//g_combinations.push_back(res);
	g_combinations.push_back(elements);
} /* printc */

/**********************************************************************
	next_comb(int comb[], int k, int n)
	Generates the next combination of n elements as k after comb

	comb => the previous combination ( use (0, 1, 2, ..., k) for first)
	k => the size of the subsets to generate
	n => the size of the original set

	Returns: 1 if a valid combination was found
	0, otherwise
**********************************************************************/

int next_comb(int *comb, int k, int n) {

	int i = k - 1;
	++*(comb + i);
	while ((i >= 0) && (*(comb + i) >= n - k + 1 + i)) 
	{
		--i;
		++*(comb + i);
	}

	if (*comb > n - k) /* Combination (n-k, n-k+1, ..., n) reached */
	{
		return 0; /* No more combinations can be generated */
	}

	/* comb now looks like (..., x, n, n, n, ..., n).
	 * Turn it into (..., x, x + 1, x + 2, ...) */
	for (i = i + 1; i < k; ++i)
	{
		*(comb + i) = *(comb + (i - 1)) + 1;
	}

	return 1;

} /* next_comb */

int main() {

	int *comb, i, n, k;

	n = 20; /* The size of the set; for {1, 2, 3, 4} it's 4 */
	k = 11; /* The size of the subsets; for {1, 2}, {1, 3}, .. it's 2 */

	if (k > n) {
		printf("invalid input \n");
		return 0;
	}

	comb = new int[k];

	for (i = 0; i < k; ++i)
	{
		*(comb + i) = i;
	}

	/* Print the first combination */
	printc(comb, k);

	/* Generate and print all the other combinations */
	while (next_comb(comb, k, n))
	{
		printc(comb, k);
	}

	delete comb;

	std::unordered_map<int, std::string> ideasMap;

	std::fstream infile;
	infile.open("ideas.txt");
	std::string line;
	int j = 1;
	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		ideasMap[j] = line;
		++j;
	}

	std::vector<std::string> finalIdeasVec;

	for (const auto& el : g_combinations)
	{
		std::string finalStr;

		for (const auto& subEl : el)
		{
			finalStr += ideasMap[subEl] + " , ";
		}

		finalIdeasVec.push_back(finalStr);
	}

	std::ofstream outfile;
	outfile.open("output_ideas.txt");
	for (const auto& el : finalIdeasVec)
	{
		outfile << el << std::endl << std::endl;
	}
	outfile.close();

	system("pause");

	return 0;

}