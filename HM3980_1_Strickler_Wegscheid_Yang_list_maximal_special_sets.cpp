//Student Names: Chase Strickler, Adam Wegscheid, Paufou Yang
//Date: 3/6/2017
//Homework #: 3980-1
//Problem: list maximal special sets of (0,1) dataset
//lower bound on number of maximal special sets: 252
//The source code in this program is the work of people in my group
//and not the work of anyone else.
//Your Signatures:

#include<iostream>
#include<fstream>
#include<cstdlib>
#include<vector>
#include <algorithm>

class TransactionSet
{
	size_t* data;
	size_t at(size_t row, size_t col) const {
		return data[row * 10 + col];
	}
	bool exists(size_t row, const std::vector<size_t>& set) const {
		for (size_t i = 0; i < set.size(); i++)
		{
			if (!at(row, set[i]))
				return false;
		}
		return true;
	}


public:
	TransactionSet(size_t input[10][10]) {
		data = new size_t[100];
		for (size_t i = 0; i < 10; i++)
		{
			for (size_t j = 0; j < 10; j++)
			{
				data[i * 10 + j] = input[i][j];
			}
		}
	}
	~TransactionSet() {
		delete[] data;
	}
	bool isFrequent(const std::vector<size_t>& set) const {
		size_t count = 0;
		for (size_t i = 0; i < 10; i++)
		{
			count += exists(i, set);
		}
		return count >= 5;
	}
};



using namespace std;

const size_t numRows = 100;
const size_t numCols = 100;
const size_t OptRows = 10;
const size_t OptCols = 10;

size_t matrix2[OptRows][OptCols];

template<typename T>
bool contains(vector<T> a, T b)
{
	for (size_t i = 0; i < a.size(); i++)
		if (a[i] == b)
			return true;
	return false;
}

template<typename T>
bool isSubset(vector<T> a, vector<T> b)
{
	for (size_t i = 0; i < a.size(); i++)
		if (!contains(b, a[i]))
			return false;
	return true;
}


void maximalRecursion(const TransactionSet& ts, const vector<size_t>& current, vector<size_t> available, vector<vector<size_t> >& output)
{
	for (size_t i = 0; i < available.size(); i++)
	{
		vector<size_t> copy_current(current);
		copy_current.push_back(available[i]);

		if (!ts.isFrequent(copy_current))
			available.erase(available.begin() + i--);
	}

	if (available.size() == 0)
	{
		for (size_t i = 0; i < output.size(); i++)
		{
			if (isSubset(current, output[i]))
				return;
		}
		output.push_back(current);
	}
	else
	{
		while(available.size())
		{
			vector<size_t> copy_current(current);
			copy_current.push_back(available[available.size() - 1]);
			available.pop_back();
			maximalRecursion(ts, copy_current, available, output);
		}
	}
}


int main()
{
	vector<size_t> vCol, vRow;

	size_t matrix[numRows][numCols];
	//size_t matrix2[OptRows][OptCols];

	ifstream input;
	input.open("input.txt");
	//ofstream output("output.txt");

	//Fill matrix with input.txt file
	for (size_t n = 0; n < numRows; n++)
	{
		for (size_t i = 0; i < numCols; i++)
		{
			input >> matrix[n][i];
		}
	}

	input.close();

	size_t threshold_counter = 0;
	size_t threshold = 5;

	//Check if columns meet threshold and store them into a vector vCol
	for (size_t index = 0; index < numCols; index++)
	{
		threshold_counter = 0;

		for (size_t next = 0; next < numRows; next++)
		{

			if (matrix[next][index] == 1)
			{
				threshold_counter++;

				if (threshold_counter == threshold)
				{
					vCol.push_back(index);
					break;
				}

			}
		}
	}

	//These Loops are supposed to refine the 10x100 matrix to a 10x10
	for (size_t next = 0; next < 100; next++)
	{
		for (size_t index = 0; index < 10; index++)
		{
			size_t x = vCol[index];

			if (matrix[next][x] == 1)
			{
				vRow.push_back(next);
				break;
			}
		}
	}

	//Put the refined 10x10 matrix into a new matrix		
	for (size_t row = 0; row < vRow.size(); row++)
	{
		for (size_t col = 0; col < vCol.size(); col++)
		{
			size_t x = vCol[col];
			size_t y = vRow[row];
			matrix2[row][col] = matrix[y][x];
		}
	}

	TransactionSet ts(matrix2);
	
	vector<size_t> current_primer;
	vector<size_t> available;
	
	for (int i = 0; i < 10; i++)
		{
			available.push_back(i);
		}
	vector<vector<size_t> > output;

	maximalRecursion(ts, current_primer, available, output);
	
	int counter = 0;
	
	for (size_t i = 0; i < output.size(); i++)
	{

		cout << '{';
		for (size_t j = 0; j < output[i].size(); j++)
		{
			cout << vCol[output[i][j]];
			if (j != output[i].size() - 1)
				cout << ", ";
		}
		cout << "}\n";
		counter++;
	}
	cout<<endl;
	cout << "Total Maximal Special Sets: " <<counter<<endl;
	cout<<endl;
		
	//Just output the column numbers
	
		for (size_t i = 0; i <vCol.size(); i++)
			cout << vCol[i] << " ";
			cout << endl;



	//Output the 10x10 matrix

	for(size_t row = 0; row<vRow.size(); row++)
		{
		//cout << endl;

			for(size_t j = 0; j<vCol.size(); j++)
				{
					size_t x = vCol[j];
					size_t y = vRow[row];
				//	cout << matrix2[row][j] << "  ";

				}
		}

	cout << endl;
	cout << endl;
	
	cout << "It's interesting that the 100x100 data set reduces to a 10x10, and within" << endl;
	cout << "that 10x10, each column contains exactly one zero." << endl;
	cout << endl;
	
	char dummmy;
	cout << "Enter character to end: ";
	cin >> dummmy;
	
	return 0;
}
