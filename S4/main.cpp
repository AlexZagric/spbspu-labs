#include <cmath>
#include <iostream>

void makeHeap(int *arr, int i, int n);
void heapSort(int *arr, int n);

int main()
{
  int arr[10];

  for (int i = 0; i < 10; i++)
  {
    // arr[i] = std::rand();
    arr[i] = i * 10;
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';

  heapSort(arr, 10);

  for (int i = 0; i < 10; i++)
  {
    std::cout << arr[i] << " ";
  }
  std::cout << '\n';
}

void makeHeap(int *arr, int i, int n)
{
  int min = i;
  while (1)
  {
    int child = 2 * i + 1;
    if (child < n && arr[child] < arr[min])
    {
      min = child;
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
