///////////////////////////////////////////////////////////////////////////////
//
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
//
///////////////////////////////////////////////////////////////////////////////
// Main File:        p2B
// This File:        hill_climb.c
// Other Files:      hill1.txt, output.txt
// Semester:         CS 354 Fall 2019
//
// Author:           Archana Dhyani
// Email:            adhyani@wisc.edu
// CS Login:         archana
//
/////////////////////////// OTHER SOURCES OF HELP /////////////////////////////
//                   fully acknowledge and credit all sources of help,
//                   other than Instructors and TAs.
//
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the the ideas and help they provided.
//
// Online sources:   avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
///////////////////////////////////////////////////////////////////////////////

#include <stdio.h>   
#include <stdlib.h>     
#include <string.h>  

/*
 * USE THIS:
 * Structure representing the Matrix
 * numRows: number of rows
 * numCols: number of columns
 * matrix: 2D heap allocated array of integers
 */
typedef struct {    
    int numRows;
    int numCols;
    int **matrix;
} Matrix;

char* COMMA = ",";

/* TODO:
 * Get the dimensions of the matrix that are on
 * the first line of the input file.
 * 
 * infp: file pointer for input file
 * nRows: pointer to number of rows in the matrix   
 * nCols: pointer to number of columns in the matrix
 */
void get_dimensions(FILE *infp, int *nRows, int *nCols) {         
    // Read the dimensions on the first line from infp
    char *line = NULL;
    size_t len = 0;
    if (getline(&line, &len, infp) == -1) {
        printf("Error in reading the file\n");
        exit(1);
    }
    char *token = strtok(line, COMMA);
    *nRows = atoi(token);
    token = strtok(NULL, COMMA);
    *nCols = atoi(token);

}            

/* TODO:
 * Continually find and print the largest neighbor
 * that is also larger than the current position
 * until nothing larger is found.       
 * 
 * outfp: file pointer for output file  
 * mstruct: pointer to the Matrix structure
 */
void hill_climb(FILE *outfp, Matrix *mstruct) {
	 // Write the intial starting number to outfp
    // Find the largest neighbor that is also larger than the current position
    // Move to that position   
    // Write that number to outfp
    // Repeat until you can't find anything larger (you may use any loop)
	int dirX[] = {-1, -1, -1, 0, 0, 1, 1, 1};
	int dirY[] = {-1, 0, 1, -1, 1, -1, 0, 1};
	int max = -1;
	int maxIndexI = 0;
	int maxIndexJ = 0;
	int max2 = 0;
	int i=0;
	int j=0;
	fprintf(outfp, "%d ", 1);
	
	while(i>=0 && i<(mstruct -> numRows) && j>=0 && j<(mstruct -> numCols)){
		for(int a=0; a<(sizeof(dirX)/4); a++){
			int neighborX = i + dirX[a];
			int neighborY = j + dirY[a];
			
			if(neighborX >= 0 && neighborX < (mstruct -> numRows) && neighborY >=0 && neighborY < (mstruct -> numCols)){
				if(max < *(*(mstruct -> matrix+neighborX) + neighborY)){
					max = *(*(mstruct -> matrix+neighborX)+neighborY);
					maxIndexI = neighborX;
					maxIndexJ = neighborY;
				}
			}
			
	}
	if(max > max2){
			max2 = max;
			fprintf(outfp, "%d ", max);
			i = maxIndexI;
			j = maxIndexJ;
	 } else {
	 	break;
	 }
}
		
	
}    

/* TODO:
 * This program reads an m by n matrix from the input file
 * and outputs to a file the path determined from the
 * hill climb algorithm.    
 *
 * argc: CLA count
 * argv: CLA values
 */
int main(int argc, char *argv[]) {
	    // Check if number of command-line arguments is correct
	if(argc !=3) {
		printf("Error\n");
		exit(1);
	}
	//printf("%d %s %s %s\n", argc, argv[0], argv[1], argv[2]);
    // Open the input file and check if it opened successfully
    FILE *fp = fopen(*(argv + 1), "r");
    if (fp == NULL) {
        printf("Cannot open file for reading\n");
        exit(1);
    }
    // Declare local variables including the Matrix structure 
    int rows;
    int cols;
    // Call the function get_dimensions
    get_dimensions(fp, &rows, &cols);
    // Dynamically allocate a 2D array in the Matrix structure
    Matrix *m = malloc(sizeof(Matrix));

    m->numRows = rows;
    m -> numCols = cols;

    if(m==NULL){
		printf("Error\n");
		exit(1);
	}
	m->matrix = malloc(sizeof(int)*rows);
	if(m->matrix == NULL){
		printf("Error\n");
		exit(1);
	}
	for(int i=0; i<rows; i++){
		*(m->matrix+i) = malloc(sizeof(int)*cols);
		if(*(m->matrix+i) == NULL){
			printf("Error\n");
			exit(1);
		}
	}
	// for(int i=0; i<rows; i++){
	//	*(m -> matrix+i) = malloc(sizeof(int)*cols);
	//}

    // Read the file line by line base on the number of rows
    // Tokenize each line wrt comma to store the values in the matrix
    char *line = NULL;
    size_t len = 0;
    char *token = NULL;
    for (int i = 0; i < rows; i++) {

        if (getline(&line, &len, fp) == -1) {
            printf("Error while reading the file\n");
            exit(1);
        }

        token = strtok(line, COMMA);
        for (int j = 0; j < cols; j++) {
            //TODO: Complete the line of code below
            //to initialize your 2D array.
            /* ADD ARRAY ACCESS CODE HERE */
	        *(*(m->matrix+i)+j) = atoi(token);
            token = strtok(NULL, COMMA);
        }
    }

    // printf("printing the matrix\n");
    // for(int i = 0; i < rows; i++) {
    // 	for(int j = 0; j < cols; j++) {
    // 		printf("%d ", m-> matrix[i][j]);
    // 	}
    // 	printf("\n");
    // }
    // Open the output file
    FILE *ofp = fopen(*(argv + 2), "w");
    if (ofp == NULL) {
        printf("Cannot open file for writing\n");
        exit(1);
    }
    // Call the function hill_climb
    
    hill_climb(ofp, m);

    //TODO: Free all dynamically allocated memory.
	for(int i=0; i<rows; i++){
		free(*(m->matrix+i));
	}
	free(m);
	m = NULL;

    //Close the file.
    if (fclose(fp) != 0) {
        printf("Error while closing the file\n");
        exit(1);
    } 
       
    // Close the input file  
    // Close the output file
    if (fclose(ofp) != 0) {
        printf("Error while closing the file\n");
        exit(1);
    }

    return 0;
}   
