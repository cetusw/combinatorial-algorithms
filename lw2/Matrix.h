//
// Created by cetus on 3/24/25.
//

#ifndef MATRIX_H
#define MATRIX_H
#include <vector>

class Matrix
{
	std::vector<std::vector<int>> data;
	std::vector<size_t> rowIndices;
	std::vector<size_t> colIndices;
	size_t lastRemovedRow = static_cast<size_t>(-1);
	size_t lastRemovedCol = static_cast<size_t>(-1);

public:
	explicit Matrix(const std::vector<std::vector<int>>& matrix);
	void RemoveRowColumn(size_t row, size_t col);
	size_t RowIndex(size_t currentRow) const;
	size_t ColumnIndex(size_t currentCol) const;
	int& operator()(size_t row, size_t col);
	const int& operator()(size_t row, size_t col) const;
	size_t FindCurrentRowIndex(size_t originalRow) const;
	size_t FindCurrentColumnIndex(size_t originalCol) const;
	size_t GetLastRemovedRow() const;
	size_t GetLastRemovedColumn() const;
	size_t GetSize() const;
};

#endif // MATRIX_H
