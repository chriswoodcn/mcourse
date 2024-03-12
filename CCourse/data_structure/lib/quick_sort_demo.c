#include <stdio.h>
#include <stdlib.h>
#define N 15

void show(int data[], int len)
{
  printf("show data:\n");
  for (int i = 0; i < N; i++)
  {
    printf(" %d ", data[i]);
  }
  puts("");
}
int partion(int data[], int low, int high)
{
  int temp = data[low];
  while (low < high)
  {
    while (low < high && temp <= data[high])
    {
      high--;
    }
    data[low] = data[high];
    while (low < high && temp >= data[low])
    {
      low++;
    }
    data[high] = data[low];
  }
  data[low] = temp;
  return low;
}
int quick_sort(int data[], int low, int high)
{
  if (data == NULL)
  {
    printf("data is NULL\n");
    return -1;
  }
  if (low >= high)
  {
    return 0;
  }
  int t = partion(data, low, high);
  quick_sort(data, low, t - 1);
  quick_sort(data, t + 1, high);
  return 0;
}
int compare(const void *a, const void *b)
{
  return (*(const int *)a) - (*(const int *)b);
}
int main()
{
  int data[N] = {0};
  int r;
  srand(100);
  for (int i = 0; i < N; i++)
  {
    r = rand() % 100;
    data[i] = r;
  }
  show(data, N);
  // quick_sort(data, 0, N - 1);
  // 使用库函数快排
  qsort(data, N, sizeof(int), compare);
  show(data, N);
  return 0;
}