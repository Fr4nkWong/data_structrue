#include <iostream>

using namespace std;

#define LEN 8

void insert_sort(int*, int); // 直接插入排序
void binary_sort(int*, int); // 折半插入排序
void shell_sort(int*, int);  // 希尔排序
void bubble_sort(int*, int); // 冒泡排序
void quick_sort(int*, int, int);  // 快速排序
void select_sort(int*, int); // 简单选择排序
void heap_sort(int*, int, int);   // 堆排序
void merge_sort(int*, int, int);  // 归并排序

int main(int argc, char *argv[]) {
	int arr[] = {65,38,21,49,97,76,13,27};
	int len = sizeof(arr)/sizeof(int);
	bubble_sort(arr, len);
	// insert_sort(arr, len);
	// binary_sort(arr, len);
	// quick_sort(arr, 0, len-1);
	// select_sort(arr, len);
	// heap_sort(arr, len, 1);
	// binary_sort(arr, len);
}

void insert_sort(int *arr, int len) {
	cout<<"插入排序"<<endl;
	int i,j;
	for(i=1; i<len; i++) { // 趟数
		if(arr[i]<arr[i-1]) {
			int p = arr[i];
			for (j=i-1; p<arr[j] && j>=0; j=j-1) arr[j+1] = arr[j];
			arr[j+1] = p; // 注意j--的后处理
		}
		
		printf("第%d趟：", i);
		for(int j=0; j<len; j++) {
			cout<<arr[j]<<" ";
		}
		cout<<endl;
	}
}

void binary_sort(int* arr, int len) {
	cout<<"二分插入排序"<<endl;
	for(int i=1; i<len; i++) { // 趟数
		int mid, low=0, high= i-1;
		int key = arr[i];
		while(low<=high) { // 二分思想 low,high指针的变化
			mid = (low+high)/2;
			if(key < arr[mid]) high = mid-1;
			else low = mid+1;
		}
		for(int j=i-1; j>high; j--) { // 大于上界
			arr[j+1] = arr[j];
		}
		arr[high+1] = key;
		
		printf("第%d趟：", i);
		for(int j=0; j<len; j++) {
			cout<<arr[j]<<" ";
		}
		cout<<endl;
	}
}

void shell_sort(int* arr, int len) {
	cout<<"希尔排序"<<endl;
	int count = 1;
	for(int d=len/2; d>=1; d=d/2) { // 增量
		for(int i=d; i<len; i++) {
			int key = arr[i];
			if(key<arr[i-d]) {
				int j;
				for(j=i-d; key<arr[j] && j>=0; j=j-d) arr[j+d] = arr[j]; // 与直接插入排序比较
				arr[j+d] = key;
			}
		}
		
		printf("第%d躺：", count++);
		for(int i=0; i<len; i++) {
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
	
} 

void bubble_sort(int *arr, int len) {
	cout<<"冒泡排序"<<endl;
	for(int j=1; j<len; j++) { // 趟数
		int flag = 0;
		for(int i=0; i<len-1; i++) {
			if (arr[i] > arr[i+1]) {
				int temp = arr[i+1];
				arr[i+1] = arr[i];
				arr[i] = temp;
				flag = 1;
			}
		}
		if (!flag) break;
		printf("第%d躺：", j);
		for(int i=0; i<len; i++) {
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
}

int partition(int* arr, int low, int high) {
	int pivot = arr[low];
	while(low<high) {
		while(low<high && arr[high]>pivot) --high;
		arr[low] = arr[high]; // 右边小于等于基准关键字的移动到左边
		while(low<high && arr[low]<=pivot) ++low;
		arr[high] = arr[low]; // 左边大于基准关键字的移动到右边
	}
	arr[low] = pivot;
	return low;
}

void quick_sort(int* arr, int low, int high) {
	if(low<high) {
		int pivotIndex = partition(arr, low, high); // 根据基准点，划分区间
		printf("快速排序	基准：%d	%d->%d\n", arr[pivotIndex], low, pivotIndex);
		for(int i=0; i<8; i++) {
			cout<<" "<<arr[i];
		}
		cout<<endl;
		quick_sort(arr, low, pivotIndex-1);
		quick_sort(arr, pivotIndex+1, high);
	}
}

void select_sort(int* arr, int len) {
	cout<<"简单选择排序"<<endl;
	for(int i=0; i<len-1; i++) {
		int minIndex = i;
		for(int j=i; j<len; j++) { // 无序序列中选择最小关键字
			if(arr[j]<=arr[minIndex]) minIndex = j;
		}
		if(minIndex!=i) {
			int temp = arr[minIndex];
			arr[minIndex] = arr[i];
			arr[i] = temp;
		}
		printf("第%d趟: ", i+1);
		for(int i=0; i<8; i++) {
			cout<<arr[i]<<" ";
		}
		cout<<endl;
	}
}

void heap_adjust_down(int* arr, int len, int k, int type) {
	arr[0] = arr[k]; // 暂存根节点的值
	if(type) { // 大顶堆
		for(int i=2*k; i<=len; i=i*2) {
			if(i<len && arr[i]<arr[i+1]) i++; // 取左右子节点的最大值
			if(arr[0]>=arr[i]) break;
			else {
				arr[k] = arr[i];
				k=i; // 修改k值，以便继续向下筛选
			}
		}
	} else { // 小顶堆
		for(int i=2*k; i<=len; i=i*2) {
			if(i<len && arr[i]>arr[i+1]) i++; // 取左右子节点的最大值
			if(arr[0]<=arr[i]) break;
			else {
				arr[k] = arr[i];
				k=i; // 保存前堆顶节点的位置
			}
		}
	}
	arr[k] = arr[0];
}

void heap_adjust_up(int* arr, int len, int k, int type) { // 应用于堆的插入操作，插入节点在最末位
	arr[0] = arr[k];
	int i=k/2;
	if(type) { // 大根堆
		while(i>0 && arr[0]>arr[i]) {
			arr[k] = arr[i];
			k = i;
			i = k/2;
		}
	} else { // 小根堆
		while(i>0 && arr[0]<arr[i]) {
			arr[k] = arr[i];
			k = i;
			i = k/2;
		}
	}
	arr[k] = arr[0];
}

/*
	@param	len	线性表里的元素个数
*/
void heap_sort(int* arr, int len, int type) {
	int list[9] = {0}; // list[0]作为哨兵
	for(int i=0; i<len; i++) list[i+1] = arr[i];
	
	for(int i=len/2; i>0; i--) { // 构建堆
		heap_adjust_down(list, len, i, type);
	}
	
	for(int i=len; i>1; i--) {	// 交换堆顶和堆底
		int temp = list[1];
		list[1] = list[i];
		list[i] = temp;
		heap_adjust_down(list, i-1, 1, type); // 把剩下的元素整理成堆
		for(int j=1; j<i; j++) {
			printf("%d ", list[j]);
		}
		cout<<endl;
	}
	for(int j=1; j<=len; j++) {
		printf("%d ", list[j]);
	}
}

int* list = new int[LEN];
void merge(int* arr, int low, int mid, int high) {
	int i,j,k;
	for(i=low; i<=high; i++) list[i] = arr[i]; // 辅助空间赋值
	for(i=low, j=mid+1, k=i; i<=mid && j<=high; k++) { // 比较两个序列
		if(list[i]<list[j]) arr[k] = list[i++];
		else arr[k] = list[j++];
	}
	while(i<=mid) arr[k++] = list[i++];
	while(j<=high) arr[k++] = list[j++];
	
	cout<<"low:"<<low<<"\thigh:"<<high<<"\t";
	for(int j=low; j<=high; j++) {
		printf("%d ", arr[j]);
	}
	printf("\n");
}

void merge_sort(int* arr, int low, int high) {
	if(low<high) {
		int mid = (low+high)/2; // 划分序列
		merge_sort(arr, low, mid);
		merge_sort(arr, mid+1, high);
		merge(arr, low, mid, high); // 合并序列
	}
}
