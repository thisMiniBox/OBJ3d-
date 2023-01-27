#pragma once
#include"LinkList.h"
int Paritition1(LinkList<int> A, int low, int high) {
	int pivot = A[low];
	while (low < high) {
		while (low < high && A[high] >= pivot) {
			--high;
		}
		A.FindNode(low)->data = A[high];
		while (low < high && A[low] <= pivot) {
			++low;
		}
		A.FindNode(high)->data = A[low];
	}
	A.FindNode(low)->data = pivot;
	return low;
}
void QuickSort(LinkList<int> A, int low, int high) //快排母函数
{
	if (low < high) {
		int pivot = Paritition1(A, low, high);
		QuickSort(A, low, pivot - 1);
		QuickSort(A, pivot + 1, high);
	}
}
int TParitition1(TriFLink* A, int low, int high) {
	TriFLink* L = nullptr;
	TriFLink* R = nullptr;
	int pivot = SearchTLink(A, low)->distance;
	while (low < high) {
		while (low < high && SearchTLink(A, high)->distance >= pivot) {
			--high;
		}
		L = SearchTLink(A, low);
		R = SearchTLink(A, high);
		L->data = R->data;
		L->distance = R->distance;
		while (low < high && L->distance <= pivot) {
			++low;
			L = L->NEXT;
		}
		R = SearchTLink(A, high);
		R->data = L->data;
		R->distance = L->distance;
	}
	SearchTLink(A, low)->distance = pivot;
	return low;
}
void TQuickSort(TriFLink* A, int low, int high) //快排母函数
{
	if (low < high) {
		int pivot = TParitition1(A, low, high);
		TQuickSort(A, low, pivot - 1);
		TQuickSort(A, pivot + 1, high);
	}
}