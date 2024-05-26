#include <cmath>
#include <iomanip>
#include <iostream>

void makeHeap(int *arr, int i, int n);
void heapSort(int *arr, int n);
bool isSorted(int *arr, int size);
void testSort(int size);

int main()
{
  testSort(1000);
  testSort(10000);
  testSort(10000);
  testSort(50000);
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

void testSort(int size)
{
  std::cout << "== Starting test for " << size << " elements ==\n";
  int *arr = new int[size];
  std::cout << "Running tests for the best situation:\n";
  for (int i = 0; i < size; i++)
  {
    arr[i] = i;
  }
  heapSort(arr, size);
  std::cout << " - Check if array was sorted: " << std::boolalpha << isSorted(arr, size) << "\n";

  std::cout << "Running tests for medium situation:\n";
  for (int i = 0; i < size; i++)
  {
    arr[i] = std::rand();
  }
  heapSort(arr, size);
  std::cout << " - Check if array was sorted: " << std::boolalpha << isSorted(arr, size) << "\n";

  std::cout << "Running tests for the worst situation:\n";
  for (int i = size - 1; i >= 0; i--)
  {
    arr[i] = i;
  }
  heapSort(arr, size);
  std::cout << " - Check if array was sorted: " << std::boolalpha << isSorted(arr, size) << "\n\n";
}
