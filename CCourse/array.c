#include <stdio.h>

void sort(int arr[], int size);
void print(int arr[], int size);

int main()
{
  int a[10] = {1, 2, 3, 4, 5};
  for (int i = 0; i < sizeof(a) / sizeof(int); i++)
  {
    printf("i: %d v: %d \n", i, a[i]);
  }
  printf("数组越界 c不做检查 i: %d v: %d \n", 10, a[10]);
  int source[] = {38, 49, 76, 13, 27, 30, 97};
  int size = sizeof(source) / sizeof(int);
  sort(source, size);
  print(source, size);
  return 0;
}

void sort(int arr[], int size)
{
  printf("arr size: %d\n", size);
  int temp;
  for (size_t i = 0; i < size - 1; i++)
  {
    for (size_t j = 0; j < size - 1 - i; j++)
    {
      if(arr[j] > arr[j+1])
      {
        temp = arr[j];
        arr[j] = arr[j+1];
        arr[j+1] = temp;
      }
    }
  }
}
void print(int arr[], int size)
{
  for (size_t i = 0; i < size; i++)
  {
    printf("arr %d: %d\n", i, arr[i]);
  }
}