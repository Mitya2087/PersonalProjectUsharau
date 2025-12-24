#ifndef SORTER_H
#define SORTER_H

#include <string>
#include <vector>

class Sorter {
public:
  static std::vector<int> loadFromFile(const std::string &filename);
  static void saveToFile(const std::string &filename,
                         const std::vector<int> &data);

  static void bubbleSort(std::vector<int> &arr);
  static void quickSort(std::vector<int> &arr, int low, int high);
  static void mergeSort(std::vector<int> &arr, int left, int right);

  static void runInteractive();

private:
  static int partition(std::vector<int> &arr, int low, int high);
  static void merge(std::vector<int> &arr, int left, int mid, int right);
};

#endif