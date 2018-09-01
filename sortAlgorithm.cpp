#include <iostream>
#include <ctime>
#include <vector>
#include <stack>

using namespace std;

#define N 100
#define MOD 100
#define SORT lsdRadixSort

void swap(int &a, int &b);


// 内部排序算法
/*
冒泡排序：用一个标记变量判断是否发生交换，不发生交换时就可以退出函数。已有序的数组经过一次遍历后即可退出。
平均时间复杂度：O(n²)
最好时间复杂度：O(n)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：稳定
*/
void bubbleSort(vector<int> &vec);

/*
选择排序：无论是否排好序，每次都会进行遍历，无法在循环过程中判断是否有序，除非每次循环操作后，再遍历一遍判断是否已有序。
平均时间复杂度：O(n²)
最好时间复杂度：O(n²)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：不稳定
*/
void selectionSort(vector<int> &vec);

/*
插入排序：有序情况下，相当于只遍历了一次，最差时是完全逆序。
平均时间复杂度：O(n²)
最好时间复杂度：O(n)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：稳定
*/
void insertionSort(vector<int> &vec);

/*
希尔排序：有序情况下，内层循环遍历O(n),外层次数循环与gap值有关。
平均时间复杂度：O(nlogn)到O(n²)
最好时间复杂度：O(n的1.3次方)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：不稳定
*/
void shellSort(vector<int> &vec);

/*
归并排序：分治思想，时间复杂度与数据排列无关，合并时需要开辟额外空间。
平均时间复杂度：O(nlogn)
最好时间复杂度：O(nlogn)
最差时间复杂度：O(nlong)
所需辅助空间：O(n)
稳定性：稳定
*/
void MergeSort(vector<int> &vec);
void mergeSort(vector<int> &vec, int left, int right);
void merge(vector<int> &vec, int left, int mid, int right);

/*
非递归归并排序：分治思想，时间复杂度与数据排列无关，合并时需要开辟额外空间。
平均时间复杂度：O(nlogn)
最好时间复杂度：O(nlogn)
最差时间复杂度：O(nlong)
所需辅助空间：O(n)
稳定性：稳定
*/
void merge_sort(vector<int> &vec);

/*
快速排序：分治思想，取一个数字作为左右的分界点，每次排序后，对排序部分再分左右进行排序。
取最左值作为key，则key值属于左半部分；取最右值作为key，则key值属于右半部分。
最差情况下，每次取的值刚好是最大或最小值，则退化为选择排序。
平均时间复杂度：O(nlogn)
最好时间复杂度：O(nlogn)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：不稳定
*/
void QuickSort(vector<int> &vec);
void quickSort(vector<int> &vec, int left, int right);
int partitionSort(vector<int> &vec, int left, int right);

/*
非递归快速排序：分治思想，取一个数字作为左右的分界点，每次排序后，对排序部分再分左右进行排序。
取最左值作为key，则key值属于左半部分；取最右值作为key，则key值属于右半部分。
最差情况下，每次取的值刚好是最大或最小值，则退化为选择排序。
平均时间复杂度：O(nlogn)
最好时间复杂度：O(nlogn)
最差时间复杂度：O(n²)
所需辅助空间：O(1)
稳定性：不稳定
*/
void quick_sort(vector<int> &vec);

/*
堆排序：从0开始的最后一个非叶节点是 n / 2 - 1。 升序排列时，构建大顶堆，每次将其移到最后，继而调整剩下的元素。
构建堆时，从最后一个非叶子节点开始，知道堆顶，如发生交换，则继续以发生交换的子节点为起点向下比较。
平均时间复杂度：O(nlogn)
最好时间复杂度：O(nlogn)
最差时间复杂度：O(nlogn)
所需辅助空间：O(1)
稳定性：不稳定
*/
void heapSort(vector<int> &vec);
void buildHeap(vector<int> &vec);
void adjustHeap(vector<int> &vec, int i, int n);

/*
计数排序
平均时间复杂度：O(n + k)
最好时间复杂度：O(n + k)
最差时间复杂度：O(n + k)
所需辅助空间：O(n + k)
稳定性：稳定
*/
void countSort(vector<int> &vec);

/*
基数排序：可以从左，也可以从右
平均时间复杂度：O(n * dn)
最好时间复杂度：O(n * dn)
最差时间复杂度：O(n * dn)
所需辅助空间：O(n * dn)
稳定性：稳定
*/
void lsdRadixSort(vector<int> &vec);

// 外部排序算法
/*
对于大数据小内存的情况，根据内存大小对数据进行分组，组内使用内部排序算法进行排序。
各大组再根据内存大小进行划分为小组，使得每个大组都有一个小组的数据放入内存(留出一部分内存的情况下)。
各小组进行归并排序，将排序后的数据放入输出缓冲区，当缓冲区满时，将数据输出到硬盘，清空输出缓冲区。
每当一个小组数据为空时，从其大组在想内存中装入一个小组数据。
*/

int main() {
	srand((unsigned)time(NULL));

	vector<int> vec;
	for (int i = 0; i < N; ++i) {
		vec.push_back(rand() % MOD);
	}

	void(*fun)(vector<int> &) = SORT;

	fun(vec);

	for (int i : vec) {
		cout << i << " ";
	}
	cout << endl;
	return 0;
}

void swap(int &a, int &b) {
	int tmp = a;
	a = b;
	b = tmp;
}

void bubbleSort(vector<int> &vec) {
	cout << "bubble sort" << endl;

	int size = static_cast<int>(vec.size());
	bool swapFlag = false;  /* 判断本次遍历是否发生交换，若未发生，则说明已经有序 */
	// int cnt = 0;   /* 外层循环遍历次数 */

	for (int i = 0; i < size; ++i) {
		// ++cnt;
		swapFlag = false;

		for (int j = size - 1; j > i; --j) {
			if (vec[j] < vec[j - 1]) {
				swap(vec[j], vec[j - 1]);
				swapFlag = true;
			}
		}

		if (!swapFlag) {
			// cout << cnt << endl;
			return;
		}
	}
}

void selectionSort(vector<int> &vec) {
	cout << "selection sort" << endl;

	int size = static_cast<int>(vec.size());

	for (int i = 0; i < size; ++i) {
		int minIndex = i;
		for (int j = i + 1; j < size; ++j) {
			if (vec[minIndex] > vec[j]) {
				minIndex = j;
			}
		}

		if (minIndex != i) {
			swap(vec[minIndex], vec[i]);
		}
	}
}

void insertionSort(vector<int> &vec) {
	cout << "insertion sort" << endl;

	int size = static_cast<int>(vec.size());

	for (int i = 1; i < size; ++i) {
		int tmp = vec[i];
		int j = i - 1;
		while (j >= 0 && vec[j] > tmp) {
			vec[j + 1] = vec[j];
			--j;
		}

		vec[++j] = tmp;
	}
}

void shellSort(vector<int> &vec) {
	cout << "shell sort" << endl;

	int size = static_cast<int>(vec.size());

	for (int gap = size / 2; gap > 0; gap /= 2) {
		for (int i = gap; i < size; i++) {
			int tmp = vec[i];
			int j = i - gap;
			while (j >= 0 && vec[j] > tmp) {
				vec[j + gap] = vec[j];
				j -= gap;
			}
			vec[j + gap] = tmp;
		}
	}
}

void MergeSort(vector<int> &vec) {
	cout << "merge sort" << endl;
	mergeSort(vec, 0, static_cast<int>(vec.size()) - 1);
}

void mergeSort(vector<int> &vec, int left, int right) {
	if (left < right) {
		int mid = (left + right) >> 1;
		mergeSort(vec, left, mid);
		mergeSort(vec, mid + 1, right);
		merge(vec, left, mid, right);
	}
}

void merge(vector<int> &vec, int left, int mid, int right) {
	int ll = left, rl = mid + 1;
	vector<int> tmp;
	while (ll <= mid && rl <= right) {
		if (vec[ll] <= vec[rl]) {
			tmp.push_back(vec[ll]);
			++ll;
		}
		else {
			tmp.push_back(vec[rl]);
			++rl;
		}
	}

	while (ll <= mid) {
		tmp.push_back(vec[ll]);
		++ll;
	}

	while (rl <= right) {
		tmp.push_back(vec[rl]);
		++rl;
	}

	for (int i : tmp) {
		vec[left] = i;
		++left;
	}
}

void merge_sort(vector<int> &vec) {
	cout << "non-recursive merge sort" << endl;

	int size = static_cast<int>(vec.size());

	for (int gap = 1; gap < size; gap *= 2) {
		for (int left = 0, right = gap; left < size; left = right + 1, right = left + gap) {
			int mid = right - 1;
			int ll = left, rl = right;
			right = right + gap - 1 >= size ? size - 1 : right + gap - 1;

			vector<int> tmp;

			while (ll <= mid && rl <= right) {
				if (vec[ll] <= vec[rl]) {
					tmp.push_back(vec[ll]);
					++ll;
				}
				else {
					tmp.push_back(vec[rl]);
					++rl;
				}
			}

			while (ll <= mid) {
				tmp.push_back(vec[ll]);
				++ll;
			}

			while (rl <= right) {
				tmp.push_back(vec[rl]);
				++rl;
			}

			for (int i : tmp) {
				vec[left] = i;
				++left;
			}
		}
	}
}

void QuickSort(vector<int> &vec) {
	cout << "quick sort" << endl;

	quickSort(vec, 0, static_cast<int>(vec.size()) - 1);
}

void quickSort(vector<int> &vec, int left, int right) {
	if (left < right) {
		int mid = partitionSort(vec, left, right);
		quickSort(vec, left, mid - 1);
		quickSort(vec, mid + 1, right);
	}
}

int partitionSort(vector<int> &vec, int left, int right) {
	/*
	int key = right;

	while (left < right) {
		while (left < right && vec[left] < vec[key]) {
			++left;
		}
		while (left < right && vec[right] >= vec[key]) {
			--right;
		}
		swap(vec[left], vec[right]);
	}

	swap(vec[key], vec[right]);
	return left;
	*/

	int key = left;

	while (left < right) {
		while (left < right && vec[right] > vec[key]) {
			--right;
		}

		while (left < right && vec[left] <= vec[key]) {
			++left;
		}

		swap(vec[left], vec[right]);
	}

	swap(vec[key], vec[right]);
	return right;
}

void quick_sort(vector<int> &vec) {
	cout << "non-recursive quick sort" << endl;

	stack<int> st;
	st.push(static_cast<int>(vec.size()) - 1);
	st.push(0);
	int left = 0, right = 0, mid;

	while (!st.empty()) {
		left = st.top();
		st.pop();
		right = st.top();
		st.pop();

		if (left < right) {
			mid = partitionSort(vec, left, right);

			st.push(right);
			st.push(mid + 1);

			st.push(mid - 1);
			st.push(left);
		}
	}
}

void heapSort(vector<int> &vec) {
	cout << "heap sort" << endl;

	int n = static_cast<int>(vec.size()) - 1;

	buildHeap(vec);

	while (n > 0) {
		swap(vec[0], vec[n]);
		--n;
		adjustHeap(vec, 0, n);
	}
}

void buildHeap(vector<int> &vec) {
	int n = static_cast<int>(vec.size()) - 1;
	for (int i = n / 2 - 1; i >= 0; --i) {
		adjustHeap(vec, i, n);
	}
}

void adjustHeap(vector<int> &vec, int i, int n) {
	int tmp = vec[i];
	for (int j = 2 * i + 1; j <= n; j = 2 * j + 1) {
		if (j + 1 <= n && vec[j] < vec[j + 1]) {
			++j;
		}

		if (vec[j] > tmp) {
			vec[i] = vec[j];
			i = j;
		}
		else {
			break;
		}
	}

	vec[i] = tmp;

	/*
	int maxIndex = 2 * i + 1;
	if (maxIndex <= n) {
		if (maxIndex + 1 <= n) {
			if (vec[maxIndex] < vec[maxIndex + 1]) {
				++maxIndex;
			}
		}

		if (vec[maxIndex] > vec[i]) {
			swap(vec[maxIndex], vec[i]);
			adjustHeap(vec, maxIndex, n);
		}
	}
	*/
}

void countSort(vector<int> &vec) {
	cout << "count sort" << endl;

	int cnt[MOD];
	memset(cnt, 0, sizeof(cnt));

	for (int i : vec) {
		++cnt[i];
	}
	vec.clear();

	for (int i = 0; i < MOD; ++i) {
		for (int j = 0; j < cnt[i]; ++j) {
			vec.push_back(i);
		}
	}
}

void lsdRadixSort(vector<int> &vec) {
	cout << "radix sort" << endl;

	vector<int> tmp[10];

	int dn = 0, max = MOD - 1;
	while (max > 0) {
		++dn;
		max /= 10;
	}

	for (int i = 0; i < dn; ++i) {
		for (int v : vec) {
			int vTmp = v;
			for (int j = 0; j < i; ++j) {
				vTmp /= 10;
			}
			vTmp %= 10;
			tmp[vTmp].push_back(v);
		}

		vec.clear();
		for (int j = 0; j < 10; ++j) {
			for (int t : tmp[j]) {
				vec.push_back(t);
			}
			tmp[j].clear();
		}
	}
}