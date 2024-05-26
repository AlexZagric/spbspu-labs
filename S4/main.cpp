#include <cmath>
#include <iostream>

void makeHeap(int *arr, int i, int n);
void heapSort(int *arr, int n);
bool isSorted(int *arr, int size);

int main()
{
  int arr[10];

  for (int i = 0; i < 10; i++)
  {
    // arr[i] = std::rand();
    arr[i] = i * 10;
  }
  std::cout << isSorted(arr, 10) << '\n';
  heapSort(arr, 10);
  std::cout << isSorted(arr, 10) << '\n';
}

void makeHeap(int *arr, int i, int n)
{
  int min = i;
  while (1)
  {
    int left_childs = 2 * i + 1;
    int right_childs = 2 * i + 2;
    if (left_childs < n && arr[left_childs] < arr[min])
    {
      min = left_childs;
    }
    if (right_childs < n && arr[right_childs] < arr[min])
    {
      min = right_childs;
    }

    if (min == i)
    {
      break;
    }
    else
    {
      std::swap(arr[min], arr[i]);
      i = min;
    }
  }
}

void heapSort(int *arr, int n)
{
  int i = 0;
  for (i = n / 2; i >= 0; i--)
  {
    makeHeap(arr, i, n);
  }

  for (int i = n - 1; i >= 0; i--)
  {
    std::swap(arr[0], arr[i]);
    makeHeap(arr, 0, i);
  }
}

bool isSorted(int *arr, int size)
{
  for (int i = 0; i < size - 1; i++)
  {
    if (arr[i] < arr[i + 1])
    {
      return false;
    }
  }
  return true;
}
