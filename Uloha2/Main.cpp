#include <iostream>
#include "sudoku.h"

int main() {
	Sudoku s("075090006023080040800003001500702000040806020000901003900400007060070580700010390");
	/*Sudoku s;
	s.SetNumber(1, 1, 5);
	s.SetNumber(1, 2, 3);
	s.SetNumber(1, 5, 7);
	s.SetNumber(2, 1, 6);
	s.SetNumber(2, 4, 1);
	s.SetNumber(2, 5, 9);
	s.SetNumber(2, 6, 5);
	s.SetNumber(3, 2, 9);
	s.SetNumber(3, 3, 8);
	s.SetNumber(3, 8, 6);
	s.SetNumber(4, 1, 8);
	s.SetNumber(4, 5, 6);
	s.SetNumber(4, 9, 3);
	s.SetNumber(5, 1, 4);
	s.SetNumber(5, 4, 8);
	s.SetNumber(5, 6, 3);
	s.SetNumber(5, 9, 1);
	s.SetNumber(6, 1, 7);
	s.SetNumber(6, 5, 2);
	s.SetNumber(6, 9, 6);
	s.SetNumber(7, 2, 6);
	s.SetNumber(7, 7, 2);
	s.SetNumber(7, 8, 8);
	s.SetNumber(8, 4, 4);
	s.SetNumber(8, 5, 1);
	s.SetNumber(8, 6, 9);
	s.SetNumber(8, 9, 5);
	s.SetNumber(9, 5, 8);
	s.SetNumber(9, 8, 7);
	s.SetNumber(9, 9, 9);*/
	std::cout << s << std::endl;
	s.Solve();
	std::cout << s << std::endl;
}