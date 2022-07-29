#include <stdio.h>
#include <omp.h>

/***** Begin *****/
void sort(int a[], int start, int end);
int main(void)
{
	int n;
	scanf("%d", &n);
	int a[1000];
	for (int i = 0; i < n; i++) scanf("%d", &a[i]);
	sort(a, 0, n - 1);
	for (int i = 0; i < n; i++) printf("%d ", a[i]);
	return 0;
}

void sort(int a[], int start, int end)
{
	if (end == start + 1 && a[start] < a[end]) return;
	if (start < end) {
		int left = start, right = end;
		int pivot = a[start];
		int index = left;
		while (start < end) {
			while (a[end] >= pivot && start < end) end--;
			if (a[end] < pivot && start < end)
			{
				a[index] = a[end];
				index = end;
				start++;
			}
			while (a[start] <= pivot && start < end) start++;
			if (a[start] > pivot && start < end)
			{
				a[index] = a[start];
				index = start;
				end--;
			}
		}
		a[index] = pivot;
		#pragma omp parallel sections
		{
			#pragma omp section
			sort(a, left, index-1);
			#pragma omp section
			sort(a, index + 1, right);
		}
	}
	return;
}
/***** End *****/
