#include <iostream>
using namespace std;

int binary_search(int*, int, int); // 二分查找d

int main(int argc, char *argv[]) {
	// 二分查找
	int arr[] = {5,21,13,19,37,75,56,64,88 ,80,92};
	int len = sizeof(arr)/sizeof(int);
	cout<<"input the key you wanna search: ";
	int key;
	cin>>key;
	int res = binary_search(arr, len, key);
	cout<<"result: "<<res<<endl;
	
	return 0;
}

int binary_search(int *arr, int len, int key) {
	int mid, low = 0, high = len-1;
	while(low<=high) { // 二分思想
		mid = (low+high)/2;
		if (key == arr[mid]) {
			return mid;
		} else if (key > arr[mid]) {
			low = mid+1;
		} else if (key < arr[mid]) {
			high = mid-1;
		}
	}
	return -1;
}
