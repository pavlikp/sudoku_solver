#pragma once

#include <string>
#include <ostream>
#include <stdint.h>
#include <array>
#include <vector>

class Sudoku
{
public:
	/**
	* Creates empty 9x9 sudoku.
	*/
	Sudoku();

	/**
	* Creates sudoku from some text serialized state (created by
	* call to serialize). It should detect corruption of serialized
	* data (unexpected format) in that case empty sudoku is created.
	*/
	explicit Sudoku(const std::string& serialized);

	/**
	* Checks if current sudoku state doesn't violates the rules.
	*/
	bool IsValid() const;

	/**
	* Fill all blanks, returns true if the solution exists, otherwise false.
	*/
	bool Solve();

	/**
	* The same as GetNumber(i, j).
	*/
	uint32_t operator()(size_t i, size_t j) const;

	/**
	* Gets number on position i, j. Position is 1 based from
	* top left corner. Should return 0 if i or j is larger than
	* size of sudoku. Also it should return 0 if the square is blank.
	*/
	uint32_t GetNumber(size_t i, size_t j) const;

	/**
	* Sets number on position i, j. Position is 1 based from
	* top left corner. Should return false if i or j is larger than
	* size of sudoku. Or the number is out of range.
	*/
	bool SetNumber(size_t i, size_t j, uint32_t number);

	/**
	* Serialize sudoku do string is may not be pretty. Serialized
	* state should work with appropriate constructor.
	*/
	std::string Serialize() const;

private:
	friend std::ostream& operator<<(std::ostream& lhs, const Sudoku& rhs);
	std::array<char, 81> m_values;

	std::vector<char> Sudoku::LineValues(const size_t& index) const;
	std::vector<char> Sudoku::ColumnValues(const size_t& index) const;
	std::vector<char> Sudoku::SquareValues(const size_t& index) const;
};

/**
* Prints Sudoku board to selected output stream in pretty format.
*/
std::ostream& operator<<(std::ostream& lhs, const Sudoku& rhs);