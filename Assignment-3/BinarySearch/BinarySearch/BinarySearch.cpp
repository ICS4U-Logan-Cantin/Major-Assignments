#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <algorithm>
#include <deque>

using namespace std;
typedef vector<int> vi;

// Utility function to print vectors
void print_vector(const vi& v, int start = 0, int count = INT_MAX) {
	int i = 0;
	while (i < count && start + i < (int)v.size()) {
		cout << v[start + i] << " ";
		i++;
	}
	cout << endl;
}

// Generates a random number from one to 100
inline int random_number() {
	return rand() % 1000 + 1;
}


///BINARY SEARCH

// Binary Search Function
template <class T>
int binary_search(T target, const vector<T>& input, int low, int high) {	
	// Base case: only one element in the array
	if (low + 1 == high) {
		return (input[low] == target) ? low : -1;
	}

	// Dividing the array segment into two
	int middleIndex = (low + high) / 2;
	int middleValue = input[middleIndex];

	// Element in the middle is equal to the target, so return the middle index
	if (middleValue == target) {
		return middleIndex;
	}

	// target is less than the middle value, so check the array to the left
	if (target < middleValue) {
		return binary_search(target, input, low, middleIndex);
	}

	// Target is greater than the middle value, so check the array to the right
	else {
		return binary_search(target, input, middleIndex + 1, high);
	}
}

// Ultility function to automatically calculate the parameters
template <class T>
int binary_search(T value, const vector<T>& input) {
	return binary_search(value, input, 0, input.size());
}

/// MERGE SORT

// In-place merge
void merge(vi& v, int low, int middle, int high) {

	// Queues representing the values from the left and the right
	deque<int> L, R;

	// Adding all the values from both arrays to the queues
	for (int i = low; i < middle; i++) {
		L.push_back(v[i]);
	}
	for (int j = middle; j < high; j++) {
		R.push_back(v[j]);
	}

	// Adding sentinel values to the back of each list
	L.push_back(INT_MAX);
	R.push_back(INT_MAX);

	// Merging the vectors
	for (int i = low; i < high; i++) {

		// front of left array is less than or equal to front of right array
		// so place it in the vector and pop the value from the queue
		if (L.front() <= R.front()) {
			v[i] = L.front();
			L.pop_front();
		}

		// Same as above, just with the right front value instead
		else {
			v[i] = R.front();
			R.pop_front();
		}
	}
}


// In-place, stable merge sort
void merge_sort(vi& v, int low, int high) {

	// Dividing the array into two
	int middle = (high - low) / 2 + low;

	// If the size of the array is greater than two, divide it further
	if (high - low > 2) {
		merge_sort(v, low, middle);
		merge_sort(v, middle, high);
	}
	
	// Merge the left and right sides
	merge(v, low, middle, high);
}

// Utility function to automatically calculate parameters
void merge_sort(vi& v) {
	merge_sort(v, 0, v.size());
}


int main() {
	// Setting the random seed
	srand(time(NULL));

	// Array of values
	vi values;
	for (int i = 0; i < 250; i++) {
		values.push_back( random_number() );
	}
	
	// The value to search for
	const int SEARCH_TERM = random_number();

	// I want there to be a 75% chance that the number is in the array.
	// Since there is already a 25% chance that the number is in the array,
	// I will add the number with a 50% chance if it doesnt exist already.
	if (find(values.begin(), values.end(), SEARCH_TERM) == values.end()
		&& random_number() > 500) {
		values.push_back(SEARCH_TERM);
	}
	
	// Unsorted array
	cout << "Unsorted array:" << endl;
	print_vector(values);

	// Sort array
	merge_sort(values);

	// Sorted Array
	cout << "Sorted array:" << endl;
	print_vector(values);

	// Binary search and print the result.
	// 75% chance is will be the index of the result
	// 25% chance it will be -1
	cout << "Index of " << SEARCH_TERM << ": " << binary_search(SEARCH_TERM, values) << endl;

}
