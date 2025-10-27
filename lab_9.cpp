#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <iomanip>

void print_matrix(const std::vector<std::vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int val : row) {
            std::cout << std::setw(5) << val;
        }
        std::cout << std::endl;
    }
	std::cout << "\n" << std::endl;
}

std::pair <std::vector<std::vector<int>>, std::vector<std::vector<int>>>  read_input_file() {
	//Get file
	std::ifstream input_file("test.txt");
	std::vector<std::string> lines;
	
	if (!input_file.is_open()) {
        std::cerr << "Error: Could not open input.txt\n";
        return {};
    }
	
	std::string line;
	while (std::getline(input_file, line)) {
		lines.push_back(line);
	}
	
	input_file.close();
	
	
	//Store matrices
	int n = std::stoi(lines[0]);
	
	std::vector<std::string> matrix_1_str;
	for(int i=2; i <= 2 + (n-1); i++) {
		matrix_1_str.push_back(lines[i]);
	}
	
	std::vector<std::string> matrix_2_str;
	for(int i=2+n; i <= (2+n) + (n-1); i++) {
		matrix_2_str.push_back(lines[i]);
	}
	
	//Store elements of the matrices
	std::vector<std::vector<int>> matrix_1;

    for (std::string line : matrix_1_str) {
        std::istringstream iss(line);
        int num;
        std::vector<int> row;

        while (iss >> num) {
            row.push_back(num);
        }

        matrix_1.push_back(row);
    }
	
	std::vector<std::vector<int>> matrix_2;

    for (std::string line : matrix_2_str) {
        std::istringstream iss(line);
        int num;
        std::vector<int> row;

        while (iss >> num) {
            row.push_back(num);
        }

        matrix_2.push_back(row);
    }
	
	std::cout << "Matrix 1: " << std::endl;
	print_matrix(matrix_1);

	std::cout << "Matrix 2: " << std::endl;
	print_matrix(matrix_2);
	
	return {matrix_1, matrix_2};
}
	
void sum_matrix(const std::vector<std::vector<int>>& matrix_1, const std::vector<std::vector<int>>& matrix_2) {
	std::cout << "Sum of Matrix 1 and Matrix 2: " << std::endl;
	
	std::vector<std::vector<int>> sum(matrix_1.size(), std::vector<int>(matrix_1[0].size()));
		
	for (size_t i = 0; i < matrix_1.size(); ++i) {
        for (size_t j = 0; j < matrix_1[i].size(); ++j) {
            sum[i][j] = matrix_1[i][j] + matrix_2[i][j];
        }
    }

    print_matrix(sum);

}

void multiplication_matrix(const std::vector<std::vector<int>>& matrix_1, const std::vector<std::vector<int>>& matrix_2) {
	std::cout << "Multiplication of Matrix 1 and Matrix 2: " << std::endl;
	
	std::vector<std::vector<int>> multi(matrix_1.size(), std::vector<int>(matrix_2[0].size()));
		
	for (size_t i = 0; i < matrix_1.size(); ++i) {
        for (size_t j = 0; j < matrix_2[0].size(); ++j) {
			multi[i][j] = 0;
			for (size_t k = 0; k < matrix_1[0].size(); ++k) {
            multi[i][j] += (matrix_1[i][k] * matrix_2[k][j]);
			}
        }
    }

    print_matrix(multi);
}

void sum_diagonal(const std::vector<std::vector<int>>& matrix_1, const std::vector<std::vector<int>>& matrix_2) {
	int matrix_1_main = 0, matrix_2_main = 0;
	int matrix_1_sec = 0, matrix_2_sec = 0;
	
	for (size_t i = 0; i < matrix_1.size(); ++i) {
		matrix_1_main += matrix_1[i][i];
		matrix_2_main += matrix_2[i][i];
		matrix_1_sec += matrix_1[i][matrix_1.size() - 1 - i];
		matrix_2_sec += matrix_2[i][matrix_2.size() - 1 - i];
	}
	
	std::cout << "Sum of Matrix 1's main diagonal elements: " << matrix_1_main << std::endl;
	std::cout << "Sum of Matrix 1's secondary diagonal elements: " << matrix_1_sec << std::endl;
	std::cout << "\n" << std::endl;
	
	std::cout << "Sum of Matrix 2's main diagonal elements: " << matrix_2_main << std::endl;
	std::cout << "Sum of Matrix 2's secondary diagonal elements: " << matrix_2_sec << std::endl;
	std::cout << "\n" << std::endl;
}

void swap_rows(const std::vector<std::vector<int>>& matrix, int row_1, int row_2) {
	std::cout << "Swap rows " << row_1 << " and " << row_2 << ": " << std::endl;
	
	if (row_1 >= static_cast<int>(matrix.size()) || row_2 >= static_cast<int>(matrix.size()) || row_1 < 0 || row_2 < 0) {
		std::cout << "Invalid Input: invalid row indices." << std::endl;
		std::cout << "\n" << std::endl;
	}
	
	else {
		std::vector<std::vector<int>> matrix_copy = matrix;
		matrix_copy[row_1] = matrix_copy[row_2];
		matrix_copy[row_2] = matrix[row_1];
		
		print_matrix(matrix_copy);
	}
}
	
void swap_cols(const std::vector<std::vector<int>>& matrix, int col_1, int col_2) {
	std::cout << "Swap columns " << col_1 << " and " << col_2 << ": " << std::endl;
	
	if (col_1 >= static_cast<int>(matrix.size()) || col_2 >= static_cast<int>(matrix.size()) || col_1 < 0 || col_2 < 0) {
		std::cout << "Invalid Input: invalid column indices." << std::endl;
		std::cout << "\n" << std::endl;
	}
	
	else {
		std::vector<std::vector<int>> matrix_copy = matrix;
		
		for (size_t i = 0; i < matrix.size(); ++i) {
			matrix_copy[i][col_1] =  matrix[i][col_2];
			matrix_copy[i][col_2] =  matrix[i][col_1];
		}
		
		print_matrix(matrix_copy);
	}
}

std::vector<std::vector<int>> update_matrix_value(std::vector<std::vector<int>> matrix, int row_index, int col_index, int new_val) {
	std::cout << "Updated matrix: " << std::endl;
	
	if (row_index >= static_cast<int>(matrix.size()) || row_index < 0) {
		std::cout << "Invalid Input: invalid row index." << std::endl;
		std::cout << "\n" << std::endl;
	}
	
	else if (col_index >= static_cast<int>(matrix.size()) || col_index < 0) {
		std::cout << "Invalid Input: invalid column index." << std::endl;
		std::cout << "\n" << std::endl;
	}
	
	else {
		matrix[row_index][col_index] = new_val;
		print_matrix(matrix);
	}

	return matrix;
}

int main() {
	std::pair <std::vector<std::vector<int>>, std::vector<std::vector<int>>> matrices = read_input_file();
	
	std::vector<std::vector<int>> matrix_1 = matrices.first;
    std::vector<std::vector<int>> matrix_2 = matrices.second;
	
	
	std::cout << "Options: \n" << "1) Add two matrices \n" << "2) Multiply two matrices \n" 
	<< "3) Sum of matrix diagonal elements \n" << "4) Swap matrix rows \n" 
	<< "5) Swap matrix columns \n" << "6) Update a matrix \n" << "7) Display matrices \n" 
	<< "8) Display options \n" << "9) Exit \n" << std::endl;
	
	int option, matrix_num, row_1, row_2, col_1, col_2, row_index, col_index, new_val;
	
	std::cout << "Select an option: " << std::endl;
	std::cin >> option;
	std::cout << "\n" << std::endl;
	
	while (true) {
		if (option == 1) {
			sum_matrix(matrix_1, matrix_2);
		}
		
		else if (option == 2) {
			multiplication_matrix(matrix_1, matrix_2);
		}
		
		else if (option == 3) {
			sum_diagonal(matrix_1, matrix_2);
		}
		
		else if (option == 4) {
			std::cout << "Which matrix (1 or 2)?: " << std::endl;
			std::cin >> matrix_num;
			std::cout << "\n" << std::endl;
			
			std::cout << "Enter the first row index (indices start at 0): " << std::endl;
			std::cin >> row_1;
			std::cout << "\n" << std::endl;
			std::cout << "Enter the second row index (indices start at 0): " << std::endl;
			std::cin >> row_2;
			std::cout << "\n" << std::endl;
			
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Invalid input\n" << std::endl;
			}
			
			else if (matrix_num == 1) {
				swap_rows(matrix_1, row_1, row_2);
			}
			
			else if (matrix_num == 2) {
				swap_rows(matrix_2, row_1, row_2);
			}
			
		}
		
		else if (option == 5) {
			std::cout << "Which matrix (1 or 2)?: " << std::endl;
			std::cin >> matrix_num;
			std::cout << "\n" << std::endl;
			
			std::cout << "Enter the first column index (indices start at 0): " << std::endl;
			std::cin >> col_1;
			std::cout << "\n" << std::endl;
			std::cout << "Enter the second column index (indices start at 0): " << std::endl;
			std::cin >> col_2;
			std::cout << "\n" << std::endl;
			
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Invalid input\n" << std::endl;
			}
			
			else if (matrix_num == 1) {
				swap_cols(matrix_1, col_1, col_2);
			}
			
			else if (matrix_num == 2) {
				swap_cols(matrix_2, col_1, col_2);
			}
			
		}
		
		else if (option == 6) {
			std::cout << "Which matrix (1 or 2)?: " << std::endl;
			std::cin >> matrix_num;
			std::cout << "\n" << std::endl;
			
			std::cout << "Enter a row index (indices start at 0): " << std::endl;
			std::cin >> row_index;
			std::cout << "\n" << std::endl;
			std::cout << "Enter a column index (indices start at 0): " << std::endl;
			std::cin >> col_index;
			std::cout << "\n" << std::endl;
			
			std::cout << "Enter the new value: " << std::endl;
			std::cin >> new_val;
			std::cout << "\n" << std::endl;
			
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
				std::cout << "Invalid input\n" << std::endl;
			}
			
			else if (matrix_num == 1) {
				matrix_1 = update_matrix_value(matrix_1, row_index, col_index, new_val);
			}
			
			else if (matrix_num == 2) {
				matrix_2 = update_matrix_value(matrix_2, row_index, col_index, new_val);
			}
			
		}
		
		else if (option == 7) {
			std::cout << "Matrix 1: " << std::endl;
			print_matrix(matrix_1);

			std::cout << "Matrix 2: " << std::endl;
			print_matrix(matrix_2);
		}
		
		else if (option == 8) {
			std::cout << "Options: \n" << "1) Add two matrices \n" << "2) Multiply two matrices \n" 
			<< "3) Sum of matrix diagonal elements \n" << "4) Swap matrix rows \n" 
			<< "5) Swap matrix columns \n" << "6) Update a matrix \n" << "7) Display matrices \n" 
			<< "8) Display options \n" << "9) Exit \n" << std::endl;
		}
		
		else if (option == 9) {
			break;
		}
		
		else {
			std::cout << "Invalid Input: Not an option. Input must be a number. \n" << std::endl;
			
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(10000, '\n');
			}
		}
		
		std::cout << "Select an option: " << std::endl;
		std::cin >> option;
		std::cout << "\n" << std::endl;
	}
	
	return 0;
}