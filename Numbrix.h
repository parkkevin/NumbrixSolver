
#ifndef Numbrix_h
#define Numbrix_h

#include <vector>
#include <string>

/**
 * This class finds solution to the given Numbrix board.
 */
class Numbrix
{
private:
	std::string fileName;	//Stores the name of the data file.
	int n;		//Size of the row or column (row and column are the same size in Numbrix).
	bool done;		//This becomes true when the solution is found.
	int** numbArr;		//2D array to store the numbers.
	std::vector<int> presets;	//Stores the predefined numbers that come with the board initially.
	int** cpyArr;	//Deep copy array.
	
	/**
	 * Taks the name of the input file from user as well as reading the predefined numbers
	 * on the board.
	 */
	void readInput();
	
	/**
	 * Initializes 2D array to zero before storing predefined numbers.
	 */
	void initializeArr(int n);
	
	/**
	 * This functions finds the lowest value from the predefined numbers on the board, which is used
	 * to decide the starting value.
	 */
	int findFirstNum();
	
	/**
	 * This function performs recursion to find the solution for the game.
	 */
	void findSol(int i, int j, int num);
	
	/**
	 * This functions checks whether number being tried is one of the predefined values.
	 */
	bool isPreset(int val);
	
	/**
	 * This function redraws the Numbrix board back to the initial state with the predefined numbers
	 * in order to prepare the board to check if there's another solution.
	 */
	void redrawGrid(std::string name);
	
	/**
	 * This function draws the horizontal lines in the board.
	 */
	void drawHLine();
	
	/**
	 * This function converts user inputs and validates.
	 */
	void convertStr(std::string* str, int* val, bool* isPass);
	
	/**
	 * This function checks user inputs for array bounds.
	 */
	bool checkBounds(int val);
	
public:
	
	/**
	 * This is the default constructor that calls readInput() and sets done to false;
	 */
	Numbrix();
	
	/**
	 * This is the destructor that deletes numbArr.
	 */
	~Numbrix();
	
	/**
	 * This function is called from main() and in return is calls the other overloaded findSol().
	 */
	void findSol();
	
	/**
	 * This function prints the Numbrix board.
	 */
	void print();
	
};


#endif /* Numbrix_h */
