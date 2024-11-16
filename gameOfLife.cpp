#include <iostream>
#include <array>
#include <vector>
#include <fstream>


const int rowCol = 30;                                         // 30x30 2D Binary Martix
std::array<std::array<bool, rowCol>, rowCol> Matrix();
void display(std::array<std::array<bool, rowCol>, rowCol>& matrix);
void checkPos(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos);
void checkCell(std::array<std::array<bool, rowCol>, rowCol> matrix, int& counter, int i, int j, bool toCheck);
void update(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos);



int main()
{					  
	int gen;
	std::vector<std::vector<int>> pos = {};     // to store (i, j) position of cells that fullfull the conditions of the game
	
	auto matrix = Matrix();
	
	std::cout << "No of Generations: ";
	std::cin >> gen;                     // no of iterations basically
	
	display(matrix);                               
	                              
	for (int x = 0; x <= gen; x++) {                                 // Main Loop \\
		system("cls");                      // clear console 
		std::cout << "Current Generation: " << x << "\n\n";
		display(matrix);                     // display the current matrix
		checkPos(matrix, pos);              //  check each cell (alive or dead) and apply the conditions of the game and if they are satisfied,
		update(matrix, pos);                // store that (i,j) value to update the matrix at end of each iteration
	}
	return 0;
}


std::array<std::array<bool, rowCol>, rowCol> Matrix() {       // get Matrix from a .txt file 
	std::array<std::array<bool, rowCol>, rowCol> matrix;

	std::string file;
    std::cout << "Enter file name: ";
    std::cin >> file;    
    std::ifstream File(file);

    for (int i = 0; i < rowCol; i++) {
        for (int j = 0; j < rowCol; j++) {
            File >> matrix[i][j];
        }
    }
	return matrix;	
}


void display(std::array<std::array<bool, rowCol>, rowCol>& matrix) {   // display the matrix on the console
	int population = 0;
	for (int i = 0; i < rowCol; i++) {
        for (int j = 0; j < rowCol; j++) {
        	if (matrix[i][j] == 0)
            	std::cout << '.' << ' ';            // dead cell = 0 = '.'
            else {
            	std::cout << 'o' << ' ';           // alive cell = 1 = 'o'
            	population++;
            }
		}
        std::cout << '\n';
    }
    std::cout << '\n';                                                
    std::cout << "Current Population: " << population << '\n';            // current no of alive cells
}


void checkPos(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos) {
	pos = {};
	int counter = 0;                                                        
	for (int i = 0; i < rowCol; i++) {                  // loop through each cell
		for (int j = 0; j < rowCol; j++) {                   
			if (matrix[i][j] == 1) {                         // if cell is alive then check conditions and if fullfilled, store position    
				checkCell(matrix, counter, i, j, 1);
				if (counter < 2 || counter > 3) {
					pos.push_back({i, j});
				}
				counter = 0;
			}
			else {
				checkCell(matrix, counter, i, j, 1);          // same with each dead cell
				if (counter == 3) {
					pos.push_back({i, j});
				}
				counter = 0;
			}
		}
	}
}

                                             // checking all possible neighbors of a cell
void checkCell(std::array<std::array<bool, rowCol>, rowCol> matrix, int& counter, int i, int j, bool toCheck) {
	
    if (i - 1 >= 0 && matrix[i - 1][j] == toCheck) 
        counter++;
        
    if (i + 1 < rowCol && matrix[i + 1][j] == toCheck)
        counter++;
        
    if (j - 1 >= 0 && matrix[i][j - 1] == toCheck)
        counter++;
        
    if (j + 1 < rowCol && matrix[i][j + 1] == toCheck) 
        counter++;
        
    if (i - 1 >= 0 && j + 1 < rowCol && matrix[i - 1][j + 1] == toCheck) 
        counter++;
    
    if (i - 1 >= 0 && j - 1 >= 0 && matrix[i - 1][j - 1] == toCheck)
        counter++;
        
    if (i + 1 < rowCol && j + 1 < rowCol && matrix[i + 1][j + 1] == toCheck) 
        counter++;
    
    if (i + 1 < rowCol && j - 1 >= 0 && matrix[i + 1][j - 1] == toCheck) 
        counter++;            
}

                                                 // to update the alive to dead or vice versa
void update(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos) {
	for (const auto& position : pos) {
		int i = position[0];
    	int j = position[1];
		if (matrix[i][j] == 1)
			matrix[i][j] = 0;
		else
			matrix[i][j] = 1;
	}
}








