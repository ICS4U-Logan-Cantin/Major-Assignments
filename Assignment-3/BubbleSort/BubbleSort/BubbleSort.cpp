#include <iostream>
#include <vector>
#include <time.h>
#include <cstdlib>

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

// Stable, in-place bubble sort
void bubble_sort(vi &v) {
	while (true) {

		// Variable to see if there have been any swaps
		bool sorted = true;

		// For each pair of consecutive elements
		for (int i = 0; i < v.size() - 1; i++) {

			// If the element on the left is greater than the element on the right
			if (v[i] > v[i + 1]) {

				// Swap the elements and change sorted to false
				sorted = false;
				swap(v[i], v[i + 1]);
			}
		}

		// This array is sorted so break out of the loop.
		if (sorted) {
			break;
		}
	}
}

int main()
{
	// Setting the random seed
	srand(time(NULL));

	// Array of values
	vi values;
	for (int i = 0; i < 250; i++) {
		values.push_back(random_number());
	}

	// Array before sorting
	cout << "Pre-sorting: " << endl;
	print_vector(values);

	// Sorting values
	bubble_sort(values);

	// Array post sorting
	cout << "Post-sorting: " << endl;
	print_vector(values);
}

