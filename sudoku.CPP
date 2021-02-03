#include <stdio.h>
#include <conio.h>

#define SIZE 9
int grid[SIZE][SIZE] = { {0, 0, 0, 5, 0, 0, 0, 0, 0},
						 {1, 0, 4, 0, 0, 0, 0, 0, 0},
                         {0, 5, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 3, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0}};

bool permanentGrid[SIZE][SIZE] = {  {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0},
                                    {0, 0, 0, 0, 0, 0, 0, 0, 0} };

/*
* This Function Displays the sudoku grid on the console 
*/
void display()
{
 	int i, j;

    printf("\n\n\n\n\n\n\n\n");
    printf("\t\t\t");
    for (i = 0; i< SIZE; i++)
    {
       if ((i % 3) == 0)
       {
           for (j = 0; j < SIZE; j++)
           {
               if (j % 3 == 0)
                   printf("* ");
               printf("* ");
               if (j == SIZE - 1)
                   printf("*");
           }
           printf("\n\t\t\t");
       }

       for (j = 0; j < SIZE; j++)
       {
           if ((j % 3) == 0)
               printf("* ");
           printf("%d ", grid[i][j]);
           if (j == SIZE - 1)
               printf("*");
       }
      printf("\n\t\t\t");
      if (i == 8)
      {
          for (j = 0; j < SIZE; j++)
          {
              if (j % 3 == 0)
                  printf("* ");
              printf("* ");
              if (j == SIZE - 1)
                  printf("*");
          }
          printf("\n\t\t\t");
      }

    }
}

/***********************************************************************************************
 ***********************************************************************************************
 *  Recursive Function which solve sudoku
 *  Parameters:
 *      i: row of the grid
 *      j: column of the grid
 *      num: The number to be inserted in ith row and jth column
 *  Explanation:
 *      The function will check the viability of 'num' to be placed at row 'i' and column 'j'.
 *  Conditions:    
 *      Always call the function from i = 0 and j = 0 to solve sudoku correctly.       
 ***********************************************************************************************
 ***********************************************************************************************/
bool solver(int i, int j, int num) 
{
  int k, sbi, sbj;
  
  if (i > 8)    // Limiting case where grid[8][8] has been successfully assigned a number
  	return 1;

  if (grid[i][j] == 0)
  {
      sbi = i / 3 * 3; //starting row for smaller 3x3 grid
      sbj = j / 3 * 3; //starting column for smaller 3x3 grid 

      for (k = 0; k < SIZE; k++)
      {

          if (grid[k][j] == num && k != i) // column check
              return 0;
          if (k != j && grid[i][k] == num) // row check
              return 0;
          if ((k / 3 + sbi) != i || (k % 3 + sbj) != j) //small box check
              if (grid[k / 3 + sbi][k % 3 + sbj] == num) 
                  return 0;
      }

      grid[i][j] = num; //assign number and move to next
  }

  if (j < (SIZE - 1)) // while there is next column move to next column
  {
      for (k = 1; k <= SIZE; k++) 
      {
          if (solver(i, j + 1, k)) // Check each number for the next column
              return 1; // This means that all next boxes have been successfully assigned
      }
      
  }
  else  // Move to next row 
  {
      for (k = 1; k <= SIZE; k++) 
      {
          if (solver(i + 1, 0, k)) // Check each number for the next column
              return 1; // This means that all next boxes have been successfully assigned
      }      
  }
  
  if (permanentGrid[i][j] == 0) // if current element is changeable
	grid[i][j] = 0; // A successful combination was not found reset it 
  return 0; // send failure back
}

int main()
{
    int starter;

    printf("Please enter a starting Integer\n");
    do
    {
        printf("Allowed Range 1 - %d : ", SIZE);
        scanf_s("%d", &starter);
    } while (starter < 1 || starter > 9);


    if (solver(0, 0, starter))
        printf("\n\n\nSUCCESS");
    else
        printf("\n\n\nFAILURE");
	display();

 getchar();
 return 0;
}
