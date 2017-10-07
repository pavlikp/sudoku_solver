#include "sudoku.h"
#include <string>
#include <regex>
#include <vector>

const size_t SUDOKU_SIZE = 9;

std::vector<char> Sudoku::LineValues(const size_t& index) const {
	std::vector<char> result;
	for (int i = index * SUDOKU_SIZE; i < index * SUDOKU_SIZE + SUDOKU_SIZE; i++) {
		if (m_values[i] != '0') {
			result.push_back(m_values[i]);
		}
	}
	return result;
}

std::vector<char> Sudoku::ColumnValues(const size_t& index) const {
	std::vector<char> result;
	for (int i = index; i <= SUDOKU_SIZE * (SUDOKU_SIZE - 1) + index; i += SUDOKU_SIZE) {
		if (m_values[i] != '0') {
			result.push_back(m_values[i]);
		}
	}
	return result;
}

std::vector<char> Sudoku::SquareValues(const size_t& index) const {
	std::vector<char> result;
	const size_t SQUARE_SIZE = sqrt(SUDOKU_SIZE);
	for (size_t i = 0; i < SQUARE_SIZE; i++) {
		size_t start = (index % SQUARE_SIZE) * SQUARE_SIZE + (index / SQUARE_SIZE) * SQUARE_SIZE * SUDOKU_SIZE + i * SUDOKU_SIZE;
		for (size_t j = start; j < start + SQUARE_SIZE; j++) {
			if (m_values[j] != '0') {
				result.push_back(m_values[j]);
			}
		}
	}
	return result;
}

Sudoku::Sudoku() {
	for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
		m_values[i] = '0';
	}
}

Sudoku::Sudoku(const std::string& serialized) {
	const std::regex SERIALIZATION_STRING("[0-9]{81}");
	if (std::regex_match(serialized, SERIALIZATION_STRING)) {
		for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
			m_values[i] = serialized[i];
		}
	}
	else {
		for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
			m_values[i] = '0';
		}
	}
}

bool Sudoku::IsValid() const {
	for (size_t i = 0; i < SUDOKU_SIZE ; i++) {
		{
			auto line = LineValues(i);
			std::sort(line.begin(), line.end());
			if (std::adjacent_find(line.begin(), line.end()) != line.end()) {
				return false;
			}
		}

		{
			auto column = ColumnValues(i);
			std::sort(column.begin(), column.end());
			if (std::adjacent_find(column.begin(), column.end()) != column.end()) {
				return false;
			}
		}

		{
			auto square = SquareValues(i);
			std::sort(square.begin(), square.end());
			if (std::adjacent_find(square.begin(), square.end()) != square.end()) {
				return false;
			}
		}
	}
	return true;
}

bool Sudoku::Solve() {
	bool is_full = true;
	size_t first_empty;
	for (size_t i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
		if (m_values[i] == '0') {
			is_full = false;
			first_empty = i;
			break;
		}
	}
	if (is_full) {
		return true;
	}
	else {
		for (uint32_t j = 1; j <= SUDOKU_SIZE; j++) {
			m_values[first_empty] = j + '0';
			if (!IsValid())
			{
				m_values[first_empty] = '0';
			}
			else {
				if (Solve()) {
					return true;
				}
				else {
					m_values[first_empty] = '0';
				}
			}
		}
	}
	return false;
}

uint32_t Sudoku::operator()(size_t i, size_t j) const {
	return GetNumber(i, j);
}

uint32_t Sudoku::GetNumber(size_t i, size_t j) const {
	if ((i - 1) * SUDOKU_SIZE + j > SUDOKU_SIZE * SUDOKU_SIZE) {
		return 0;
	}
	return m_values[(i - 1) * SUDOKU_SIZE + j - 1] - '0';
}

bool Sudoku::SetNumber(size_t i, size_t j, uint32_t number) {
	if ((i - 1) * SUDOKU_SIZE + j > SUDOKU_SIZE * SUDOKU_SIZE || number < 1 || number > 9) {
		return false;
	}
	m_values[(i - 1) * SUDOKU_SIZE + j - 1] = number + '0';
	return true;
}

std::string Sudoku::Serialize() const {
	std::string result;
	for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
		result += m_values[i];
	}
	return result;
}

std::ostream& operator<<(std::ostream& lhs, const Sudoku& rhs) {
	for (int i = 0; i < SUDOKU_SIZE * 4 + 5; i++) {
		lhs << '=';
	}
	lhs << std::endl;
	for (int i = 0; i < SUDOKU_SIZE * SUDOKU_SIZE; i++) {
		std::string column_divider = i % 3 == 0 ? "||" : "|";
		if (rhs.m_values[i] == '0') {
			lhs << column_divider << "   ";
		}
		else {
			lhs << column_divider << ' ' << rhs.m_values[i] << ' ';
		}
		if (i % SUDOKU_SIZE == SUDOKU_SIZE - 1) {
			lhs << "||" << std::endl;
			char line_divider = i % (SUDOKU_SIZE * 3) == (SUDOKU_SIZE * 3) - 1 ? '=' : '-';
			for (int j = 0; j < SUDOKU_SIZE * 4 + 5; j++) {
				lhs << line_divider;
			}
			lhs << std::endl;
		}
	}
	return lhs;
}