#include "Matrix.h"

#include <stdexcept>

Matrix::Matrix(const std::vector<std::vector<int>>& matrix)
	: data(matrix)
	, rowIndices(matrix.size())
	, colIndices(matrix.empty() ? 0 : matrix[0].size())
{
	for (size_t i = 0; i < rowIndices.size(); ++i)
	{
		rowIndices[i] = i;
	}
	for (size_t j = 0; j < colIndices.size(); ++j)
	{
		colIndices[j] = j;
	}
}

void Matrix::RemoveRowColumn(const size_t row, const size_t col)
{
	lastRemovedRow = rowIndices[row];
	lastRemovedCol = colIndices[col];
	rowIndices.erase(rowIndices.begin() + static_cast<int>(row));
	colIndices.erase(colIndices.begin() + static_cast<int>(col));
}

size_t Matrix::RowIndex(const size_t currentRow) const
{
	if (currentRow >= rowIndices.size())
	{
		throw std::out_of_range("Некорректный индекс строки");
	}
	return rowIndices[currentRow];
}

size_t Matrix::ColumnIndex(const size_t currentCol) const
{
	if (currentCol >= colIndices.size())
	{
		throw std::out_of_range("Некорректный индекс столбца");
	}
	return colIndices[currentCol];
}

int& Matrix::operator()(const size_t row, const size_t col)
{
	if (row >= rowIndices.size() || col >= colIndices.size())
	{
		throw std::out_of_range("Несуществующие строки или столбцы");
	}
	return data[rowIndices[row]][colIndices[col]];
}

const int& Matrix::operator()(const size_t row, const size_t col) const
{
	if (row >= rowIndices.size() || col >= colIndices.size())
	{
		throw std::out_of_range("Несуществующие строки или столбцы");
	}
	return data[rowIndices[row]][colIndices[col]];
}

size_t Matrix::FindCurrentRowIndex(const size_t originalRow) const
{
	for (size_t i = 0; i < rowIndices.size(); ++i)
	{
		if (rowIndices[i] == originalRow)
			return i;
	}
	return static_cast<size_t>(-1);
}

size_t Matrix::FindCurrentColumnIndex(const size_t originalCol) const
{
	for (size_t j = 0; j < colIndices.size(); ++j)
	{
		if (colIndices[j] == originalCol)
			return j;
	}
	return static_cast<size_t>(-1);
}

size_t Matrix::GetLastRemovedRow() const { return lastRemovedRow; }
size_t Matrix::GetLastRemovedColumn() const { return lastRemovedCol; }

size_t Matrix::GetSize() const { return std::min(rowIndices.size(), colIndices.size()); }