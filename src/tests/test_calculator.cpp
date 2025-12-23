#include "../backend/ExpressionEvaluator.h"
#include "../backend/History.h"
#include "../backend/MathUtils.h"
#include "../backend/Sorter.h"
#include <cmath>
#include <fstream>
#include <gtest/gtest.h>

// ==================== MathUtils Tests ====================

TEST(MathUtilsTest, Sqrt) {
  EXPECT_NEAR(MathUtils::my_sqrt(4.0), 2.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_sqrt(9.0), 3.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_sqrt(2.0), std::sqrt(2.0), 1e-9);
  EXPECT_NEAR(MathUtils::my_sqrt(100.0), 10.0, 1e-9);
  EXPECT_THROW(MathUtils::my_sqrt(-1.0), std::invalid_argument);
}

TEST(MathUtilsTest, Pow) {
  EXPECT_NEAR(MathUtils::my_pow(2.0, 3.0), 8.0, 1e-6);
  EXPECT_NEAR(MathUtils::my_pow(5.0, 2.0), 25.0, 1e-6);
  EXPECT_NEAR(MathUtils::my_pow(2.0, 0.5), std::sqrt(2.0), 1e-6);
  EXPECT_NEAR(MathUtils::my_pow(10.0, -1.0), 0.1, 1e-6);
}

TEST(MathUtilsTest, Exp) {
  EXPECT_NEAR(MathUtils::my_exp(0.0), 1.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_exp(1.0), MathUtils::E, 1e-9);
  EXPECT_NEAR(MathUtils::my_exp(2.0), std::exp(2.0), 1e-6);
  EXPECT_NEAR(MathUtils::my_exp(-1.0), std::exp(-1.0), 1e-6);
}

TEST(MathUtilsTest, Log) {
  EXPECT_NEAR(MathUtils::my_log(1.0), 0.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_log(MathUtils::E), 1.0, 1e-6);
  EXPECT_NEAR(MathUtils::my_log(10.0), std::log(10.0), 1e-6);
  EXPECT_THROW(MathUtils::my_log(0.0), std::invalid_argument);
  EXPECT_THROW(MathUtils::my_log(-5.0), std::invalid_argument);
}

TEST(MathUtilsTest, TrigonometricFunctions) {
  // Test sin
  EXPECT_NEAR(MathUtils::my_sin(0.0), 0.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_sin(MathUtils::PI / 2), 1.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_sin(MathUtils::PI), 0.0, 1e-9);

  // Test cos
  EXPECT_NEAR(MathUtils::my_cos(0.0), 1.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_cos(MathUtils::PI / 2), 0.0, 1e-6);
  EXPECT_NEAR(MathUtils::my_cos(MathUtils::PI), -1.0, 1e-9);

  // Test tan
  EXPECT_NEAR(MathUtils::my_tan(0.0), 0.0, 1e-9);
  EXPECT_NEAR(MathUtils::my_tan(MathUtils::PI / 4), 1.0, 1e-6);
}

TEST(MathUtilsTest, Abs) {
  EXPECT_EQ(MathUtils::my_abs(5.0), 5.0);
  EXPECT_EQ(MathUtils::my_abs(-5.0), 5.0);
  EXPECT_EQ(MathUtils::my_abs(0.0), 0.0);
}

TEST(MathUtilsTest, ToRadians) {
  EXPECT_NEAR(MathUtils::to_radians(0.0), 0.0, 1e-9);
  EXPECT_NEAR(MathUtils::to_radians(180.0), MathUtils::PI, 1e-9);
  EXPECT_NEAR(MathUtils::to_radians(90.0), MathUtils::PI / 2, 1e-9);
}

// ==================== ExpressionEvaluator Tests ====================

TEST(ExpressionEvaluatorTest, BasicArithmetic) {
  EXPECT_NEAR(ExpressionEvaluator::evaluate("2 + 3"), 5.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("10 - 4"), 6.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("3 * 4"), 12.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("15 / 3"), 5.0, 1e-9);
}

TEST(ExpressionEvaluatorTest, OrderOfOperations) {
  EXPECT_NEAR(ExpressionEvaluator::evaluate("2 + 3 * 4"), 14.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("(2 + 3) * 4"), 20.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("10 - 2 * 3"), 4.0, 1e-9);
}

TEST(ExpressionEvaluatorTest, PowerOperation) {
  EXPECT_NEAR(ExpressionEvaluator::evaluate("2 ^ 3"), 8.0, 1e-6);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("5 ^ 2"), 25.0, 1e-6);
}

TEST(ExpressionEvaluatorTest, Functions) {
  EXPECT_NEAR(ExpressionEvaluator::evaluate("sqrt(16)"), 4.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("sqrt(2) * sqrt(2)"), 2.0, 1e-6);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("exp(0)"), 1.0, 1e-9);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("log(1)"), 0.0, 1e-9);
}

TEST(ExpressionEvaluatorTest, ComplexExpressions) {
  EXPECT_NEAR(ExpressionEvaluator::evaluate("2 + 3 * sqrt(16)"), 14.0, 1e-6);
  EXPECT_NEAR(ExpressionEvaluator::evaluate("(2 + 3) * (4 - 1)"), 15.0, 1e-9);
}

TEST(ExpressionEvaluatorTest, DivisionByZero) {
  EXPECT_THROW(ExpressionEvaluator::evaluate("10 / 0"), std::runtime_error);
}

// ==================== History Tests ====================

TEST(HistoryTest, AddAndDisplay) {
  History hist;
  hist.addEntry("2 + 2", 4.0);
  hist.addEntry("5 * 3", 15.0);

  // No direct way to test display, but ensure no crash
  EXPECT_NO_THROW(hist.display());
}

TEST(HistoryTest, UndoRedo) {
  History hist;
  hist.addEntry("2 + 2", 4.0);
  hist.addEntry("5 * 3", 15.0);

  EXPECT_TRUE(hist.undo());
  EXPECT_TRUE(hist.redo());
  EXPECT_FALSE(hist.redo()); // Nothing to redo
}

TEST(HistoryTest, SaveAndLoad) {
  History hist1;
  hist1.addEntry("2 + 2", 4.0);
  hist1.addEntry("5 * 3", 15.0);

  const std::string filename = "test_history.txt";
  hist1.save(filename);

  History hist2;
  hist2.load(filename);

  // Cleanup
  std::remove(filename.c_str());
}

TEST(HistoryTest, Clear) {
  History hist;
  hist.addEntry("2 + 2", 4.0);
  hist.clear();

  EXPECT_FALSE(hist.undo()); // Should be empty
}

// ==================== Sorter Tests ====================

TEST(SorterTest, BubbleSort) {
  std::vector<int> arr = {5, 2, 8, 1, 9};
  Sorter::bubbleSort(arr);

  std::vector<int> expected = {1, 2, 5, 8, 9};
  EXPECT_EQ(arr, expected);
}

TEST(SorterTest, QuickSort) {
  std::vector<int> arr = {5, 2, 8, 1, 9};
  Sorter::quickSort(arr, 0, arr.size() - 1);

  std::vector<int> expected = {1, 2, 5, 8, 9};
  EXPECT_EQ(arr, expected);
}

TEST(SorterTest, MergeSort) {
  std::vector<int> arr = {5, 2, 8, 1, 9};
  Sorter::mergeSort(arr, 0, arr.size() - 1);

  std::vector<int> expected = {1, 2, 5, 8, 9};
  EXPECT_EQ(arr, expected);
}

TEST(SorterTest, SaveAndLoad) {
  const std::string filename = "test_array.txt";
  std::vector<int> data = {3, 1, 4, 1, 5, 9};

  Sorter::saveToFile(filename, data);
  auto loaded = Sorter::loadFromFile(filename);

  EXPECT_EQ(loaded, data);

  // Cleanup
  std::remove(filename.c_str());
}

TEST(SorterTest, EmptyArray) {
  std::vector<int> arr;
  EXPECT_NO_THROW(Sorter::bubbleSort(arr));
  EXPECT_TRUE(arr.empty());
}

TEST(SorterTest, SingleElement) {
  std::vector<int> arr = {42};
  Sorter::quickSort(arr, 0, arr.size() - 1);
  EXPECT_EQ(arr.size(), 1);
  EXPECT_EQ(arr[0], 42);
}

TEST(SorterTest, AlreadySorted) {
  std::vector<int> arr = {1, 2, 3, 4, 5};
  Sorter::mergeSort(arr, 0, arr.size() - 1);

  std::vector<int> expected = {1, 2, 3, 4, 5};
  EXPECT_EQ(arr, expected);
}

// ==================== Integration Tests ====================

TEST(IntegrationTest, MathUtilsWithExpressionEvaluator) {
  // Test that custom math functions work in expression evaluator
  double result1 = ExpressionEvaluator::evaluate("sqrt(4) + sqrt(9)");
  EXPECT_NEAR(result1, 5.0, 1e-6);

  double result2 = ExpressionEvaluator::evaluate("2 ^ 3 + sqrt(16)");
  EXPECT_NEAR(result2, 12.0, 1e-6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
