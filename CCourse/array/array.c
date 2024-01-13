#include <stdio.h>

void sort(int arr[], int size);
void sort2(int arr[], int size);
void print(int arr[], int size);
void printMultiArray();

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
  sort2(source, size);
  print(source, size);

  printMultiArray();

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
      if (arr[j] > arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
      }
    }
  }
}
void sort2(int arr[], int size)
{
  printf("arr size: %d\n", size);
  int temp;
  for (size_t i = 0; i < size - 1; i++)
  {
    for (size_t j = 0; j < size - 1 - i; j++)
    {
      if (arr[j] < arr[j + 1])
      {
        temp = arr[j];
        arr[j] = arr[j + 1];
        arr[j + 1] = temp;
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
void printMultiArray()
{
  int row = 3, col = 3;
  // 二维数组定义时 列数不能省 error
  int arr[3][3] = {
      {1, 1, 1},
      {2, 2, 2},
      {3, 3, 3}};
  for (int i = 0; i < row; i++)
  {
    for (int j = 0; j < col; j++)
    {
      printf("arr[%d][%d]: %d address:%#x\n", i, j, arr[i][j], &arr[i][j]);
    }
  }
}