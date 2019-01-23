#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>

// is the number z allowed at M[x][y]
int is_allowed(int **M, int x, int y, int z)
{
	int p, q; // loop counters

	// check for duplicates in 3-by-3 box
	int m, n; // 3-by-3 box location
	m = x - x % 3;
	n = y - y % 3;
	for(p = m; p < m + 3; p++)
	{
		for(q = n; q < n + 3; q++)
		{
			if(M[p][q] == z)
			{
				return 0;
			}
		}
	}

	// check for duplicates in row (x = constant)
	for(q = 0; q < 9; q++) // column location
	{
		if(M[x][q] == z)
		{
			return 0;
		}
	}

	// check for duplicates in column (y = constant)
	for(p = 0; p < 9; p++) // row location
	{
		if(M[p][y] == z)
		{
			return 0;
		}
	}

	// maybe z is allowed
	return 1;
}

// is the Sudoku solved or not
int is_solved(int **M)
{
	int x, y;
	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			if(M[x][y] == 0)
			{
				return 0;
			}
		}
	}
	return 1;
}

int main(int argc, char **argv)
{
	printf("-----\n");
	printf("Disclaimer: I cannot solve SuDokus that require guessing.\n\n");

	// check the arguments
	if(argc != 2)
	{
		printf("usage:");
		printf("\n\tsolve_sudoku.out <input file name>");
		printf("\n-----\n");
		return 1;
	}

	// allocate space for matrix
	// I don't know why I like dynamic memory allocation
	int **M;
	M = (int **)malloc(9 * sizeof(int *));
	int count;
	for(count = 0; count < 9; count++)
	{
		M[count] = (int *)malloc(9 * sizeof(int));
	}

	// load and study question
	FILE *question;
	question = fopen(argv[1], "r");
	int x, y; // loop counters
	int zeros; // number of cells to be filled
	zeros = 0;
	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			fscanf(question, "%d", *(M + x) + y);
			zeros += !M[x][y];
		}
	}
	fclose(question);

	// open a file to write the solution
	char *out_file;
	out_file = malloc(64 * sizeof(*out_file));
	strcat(strcpy(out_file, "solution_"), argv[1]);
	FILE *answer;
	answer = fopen(out_file, "w");
	free(out_file);
	fprintf(answer, "question:\n\n");
	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			fprintf(answer, "%d ", M[x][y]);
			if(y % 3 == 2)
			{
				fprintf(answer, " ");
			}
		}
		fprintf(answer, "\n");
		if(x % 3 == 2)
		{
			fprintf(answer, "\n");
		}
	}

	// calculate density of the matrix
	int ones; // ridiculous name, I understand
	ones = 81 - zeros;
	fprintf(answer, "number of filled cells\t= %2d\n", ones);
	fprintf(answer, "number of empty cells\t= %2d\n", zeros);
	fprintf(answer, "\ndensity of matrix\t= %.2f%%\n", (float)ones / 81 * 100);

	// some variables to use in the loop
	int r, s, t; // used to analyse results of is_allowed
	int p, q; // counters to traverse 3-by-3 boxes

	// time variables
	clock_t start, stop;

	// start time: just before analysis starts
	start = clock();

	// main loop
	// I know that time is wasted in checking is_solved
	while(!is_solved(M))
	{
		// traverse one cell at a time
		for(x = 0; x < 9; x++)
		{
			for(y = 0; y < 9; y++)
			{
				// if M[x][y] is already filled, continue
				if(M[x][y])
				{
					continue;
				}

				// how many numbers from 1 to 9 are allowed in M[x][y]
				r = 0;
				for(count = 1; count <= 9; count++)
				{
					if(is_allowed(M, x, y, count))
					{
						s = count;
						r += 1;
					}
				}
				// if only one number is allowed, fill it here
				if(r == 1)
				{
					M[x][y] = s;
				}
			}
		}

		// traverse one number at a time
		for(count = 1; count <= 9; count++)
		{
			// filling by row
			for(x = 0; x < 9; x++)
			{
				// in this row, how many cells will allow count
				r = 0;
				for(y = 0; y < 9; y++)
				{
					// if M[x][y] is already filled, continue
					if(M[x][y])
					{
						continue;
					}

					if(is_allowed(M, x, y, count))
					{
						r += 1;
						s = y;
					}
				}
				// if only one possible place for count exists, write it there
				if(r == 1)
				{
					M[x][s] = count;
				}
			}

			// filling by column
			for(x = 0; x < 9; x++)
			{
				// in this column, how many cells will allow count
				r = 0;
				for(y = 0; y < 9; y++)
				{
					// if M[y][x] is already filled, continue
					if(M[y][x])
					{
						continue;
					}

					if(is_allowed(M, y, x, count))
					{
						r += 1;
						s = y;
					}
				}
				// if only one possible place for count exists, write it there
				if(r == 1)
				{
					M[s][x] = count;
				}
			}

			// filling by 3-by-3 box
			for(p = 0; p < 3; p++)
			{
				for(q = 0; q < 3; q++)
				{
					// in this box, how many cells will allow count
					r = 0;
					for(x = 3 * p; x < 3 * p + 3; x++)
					{
						for(y = 3 * q; y < 3 * q + 3; y++)
						{
							// if M[y][x] is already filled, continue
							if(M[x][y])
							{
								continue;
							}

							if(is_allowed(M, x, y, count))
							{
								r += 1;
								s = x;
								t = y;
							}
						}
					}
					// if only one possibile place for count exists, write it there
					if(r == 1)
					{
						M[s][t] = count;
					}
				}
			}
		}
	}

	// stop the clock after the analysis ends
	// some comments are actually unnecessary
	stop = clock();

	// show what the computer has laboured over
	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			printf("%d %c", M[x][y], !((y + 1) % 3) * ' ');
		}
		printf("\n%c", '\n' * !((x + 1) % 3));
	}

	// write the solution to the file
	fprintf(answer, "\n-----\n\nsolution:\n\n");
	for(x = 0; x < 9; x++)
	{
		for(y = 0; y < 9; y++)
		{
			fprintf(answer, "%d ", M[x][y]);
			if(y % 3 == 2)
			{
				fprintf(answer, " ");
			}
		}
		fprintf(answer, "\n");
		if(x % 3 == 2)
		{
			fprintf(answer, "\n");
		}
	}

	// find the appropriate unit prefix for the time
	int prefix; // prefix--duh
	double T; // time taken
	T = (double)(stop - start) / CLOCKS_PER_SEC; // number of seconds

	// see how many times 1000 has to be multiplied
	prefix = 0;
	while(!(int)T)
	{
		T *= 1e3;
		prefix++;
	}

	// write the time taken with the correct prefix
	fprintf(answer, "time taken = %.2lf", T);
	switch(prefix)
	{
		case 1:
		{
			fprintf(answer, " milliseconds\n");
			break;
		}
		case 2:
		{
			fprintf(answer, " microseconds\n");
			break;
		}
		case 3:
		{
			fprintf(answer, " nanoseconds\n");
			break;
		}
		default:
		{
			// too bad--your processor is too fast
			fprintf(answer, "e-%d seconds\n", 3 * prefix);
		}
	}

	// finally, close the file
	fclose(answer);

	// clear the memory
	free(M);

	printf("Solved successfully.\n-----\n");
	return 0;
}
