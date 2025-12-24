#include "Sorter.h"
#include <fstream>
#include <iostream>

std::vector<int> Sorter::loadFromFile(const std::string &filename) {
  std::vector<int> data;
  std::ifstream file(filename);

  if (!file) {
    std::cout << "Failed to open file: " << filename << std::endl;
    return data;
  }

  int num;
  while (file >> num) {
    data.push_back(num);
  }

  std::cout << "Loaded " << data.size() << " elements from " << filename
            << std::endl;
  return data;
}

void Sorter::saveToFile(const std::string &filename,
                        const std::vector<int> &data) {
  std::ofstream file(filename);

  if (!file) {
    std::cout << "Failed to open file for writing: " << filename << std::endl;
    return;
  }

  for (const auto &num : data) {
    file << num << " ";
  }

  std::cout << "Saved " << data.size() << " elements to " << filename
            << std::endl;
}

void Sorter::bubbleSort(std::vector<int> &arr) {
  int n = arr.size();
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (arr[j] > arr[j + 1]) {
        std::swap(arr[j], arr[j + 1]);
      }
    }
  }
}

int Sorter::partition(std::vector<int> &arr, int low, int high) {
  int pivot = arr[high];
  int i = low - 1;

  for (int j = low; j < high; ++j) {
    if (arr[j] < pivot) {
      ++i;
      std::swap(arr[i], arr[j]);
    }
  }
  std::swap(arr[i + 1], arr[high]);
  return i + 1;
}

void Sorter::quickSort(std::vector<int> &arr, int low, int high) {
  if (low < high) {
    int pi = partition(arr, low, high);
    quickSort(arr, low, pi - 1);
    quickSort(arr, pi + 1, high);
  }
}

void Sorter::merge(std::vector<int> &arr, int left, int mid, int right) {
  int n1 = mid - left + 1;
  int n2 = right - mid;

  std::vector<int> L(n1), R(n2);

  for (int i = 0; i < n1; ++i)
    L[i] = arr[left + i];
  for (int i = 0; i < n2; ++i)
    R[i] = arr[mid + 1 + i];

  int i = 0, j = 0, k = left;

  while (i < n1 && j < n2) {
    if (L[i] <= R[j]) {
      arr[k++] = L[i++];
    } else {
      arr[k++] = R[j++];
    }
  }

  while (i < n1)
    arr[k++] = L[i++];
  while (j < n2)
    arr[k++] = R[j++];
}

void Sorter::mergeSort(std::vector<int> &arr, int left, int right) {
  if (left < right) {
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
  }
}

void Sorter::runInteractive() {
  std::cout << "--- Array Sorter ---\n";
  std::cout << "1. Load from file\n";
  std::cout << "Enter filename: ";

  std::string filename;
  std::cin >> filename;

  auto data = loadFromFile(filename);
  if (data.empty()) {
    std::cout << "No data to sort.\n";
    return;
  }

  std::cout << "Choose sorting algorithm:\n";
  std::cout << "1. Bubble Sort\n";
  std::cout << "2. Quick Sort\n";
  std::cout << "3. Merge Sort\n";
  std::cout << "> ";

  int choice;
  std::cin >> choice;

  switch (choice) {
  case 1:
    bubbleSort(data);
    std::cout << "Sorted with Bubble Sort.\n";
    break;
  case 2:
    quickSort(data, 0, data.size() - 1);
    std::cout << "Sorted with Quick Sort.\n";
    break;
  case 3:
    mergeSort(data, 0, data.size() - 1);
    std::cout << "Sorted with Merge Sort.\n";
    break;
  default:
    std::cout << "Invalid choice.\n";
    return;
  }

  std::cout << "Save to file (filename): ";
  std::cin >> filename;
  saveToFile(filename, data);
}
