#include <iostream>
#include <array>
#include <vector>
#include <fstream>


const int rowCol = 30;
std::array<std::array<bool, rowCol>, rowCol> Matrix();
void display(std::array<std::array<bool, rowCol>, rowCol>& matrix);
void checkPos(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos);
void checkCell(std::array<std::array<bool, rowCol>, rowCol>& matrix, int& counter, int i, int j);
void update(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos);



int main()
{					  
	int gen;
	std::vector<std::vector<int>> pos = {};
	
	auto matrix = Matrix();
	
	std::cout << "No of Generations: ";
	std::cin >> gen;
	
	display(matrix);
	
	for (int x = 0; x <= gen; x++) {                             // MAIN LOOP 
		system("cls");                  
		std::cout << "Current Generation: " << x << "\n\n";
		display(matrix);
		checkPos(matrix, pos);
		update(matrix, pos);
	}
	return 0;
}


std::array<std::array<bool, rowCol>, rowCol> Matrix() {             // 30x30 boolean matrix with initial pattern from .txt file
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


void display(std::array<std::array<bool, rowCol>, rowCol>& matrix) {    // display matrix on console
	int population = 0;
	for (int i = 0; i < rowCol; i++) {
        for (int j = 0; j < rowCol; j++) {
        	if (matrix[i][j] == 0)
            	std::cout << '.' << ' ';               // dead cell = 0 = '.'
            else {
            	std::cout << 'o' << ' ';               // alive cell = 1 = 'o'
            	population++;
            }
		}
        std::cout << '\n';
    }
    std::cout << '\n';
    std::cout << "Current Population: " << population << '\n';  
}


void checkPos(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos) {
    pos.clear();
    int counter = 0;

    for (int i = 0; i < rowCol; i++) {                // go through each cell
        for (int j = 0; j < rowCol; j++) {
            counter = 0;                              // neighbour count reset each gen
            checkCell(matrix, counter, i, j);         // check each cell and count alive neighbours
            
            if (matrix[i][j] == 1) {                 // alive cell
                if (counter < 2 || counter > 3) {    // conditions for alive cell -> dead
                    pos.push_back({i, j});                      // if fullfilled, save position for update()
                }
            } else {                                  // dead cell
                if (counter == 3) {                   // condition for dead cell -> alive
                    pos.push_back({i, j});
                }
            }
        }
    }
}


void checkCell(std::array<std::array<bool, rowCol>, rowCol>& matrix, int& counter, int i, int j) {
    int top = (i - 1 + rowCol) % rowCol;          // wrap-around boundry
    int bottom = (i + 1) % rowCol;
    int left = (j - 1 + rowCol) % rowCol;
    int right = (j + 1) % rowCol;

    if (matrix[top][j] == 1) counter++;              // neighbour count in every direaction of current cell, even corner ones
    if (matrix[bottom][j] == 1) counter++;
    if (matrix[i][left] == 1) counter++;
    if (matrix[i][right] == 1) counter++;
    if (matrix[top][left] == 1) counter++;
    if (matrix[top][right] == 1) counter++;
    if (matrix[bottom][left] == 1) counter++;
    if (matrix[bottom][right] == 1) counter++;
}


void update(std::array<std::array<bool, rowCol>, rowCol>& matrix, std::vector<std::vector<int>>& pos) {
	for (const auto& position : pos) {   // go through all saved positions to change 
		int i = position[0];
    	int j = position[1];
    	
		matrix[i][j] = !matrix[i][j];  // dead(0) -> alive(1) or vice versa
	}
}
