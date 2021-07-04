//Include stdio for file input / output
#include <stdio.h>
//Include stdlib for atoi() function
#include <stdlib.h>



int main( int argc, char *argv[] ) {
	
	//If argc only contains the program name,
	//print an error.
	if (argc == 1) {printf("At least one argument is required.\n");} 
	
	//If argc has other variables besides the programs name,
	//do this:
	else {
		
		//Since we might be dealing with more than one conversion,
		//We need to have some way of iterating through all the arguments given
		for (int i = 1; i < argc; i++) {
			
			//int d gets the value of index i (i=1) in the argv[] array.
			//bin[64] initializes an empty array of 64 elements.
			//count gets set to 0 for each argument (iteration of the for loop).
			int d = atoi(argv[i]), bin[64], count=0;
			
			while (d > 0) {
				//store the remainder of the argument divided by 2
				//in the array with the index of the value count
				//bin[0] the first time
				//bin[1] the second time, etc.
				bin[count] = d%2;
				
				//divide the number by 2 and re-assign it to d
				//could also be written as d = d / 2;
				d /= 2;

				//increase count by 1 each iteration of the loop
				//to keep track of the number of values we need to print
				count++;
			}
			
			//Print this message once for each argument
			//(iteration of the for loop)
			printf("%d in binary is: 0b", atoi(argv[i]));
			
			//While count = true, ie not equal to 0,
			//do this:
			while (count) {

				//If count is on the fourth number, print a space
				//Not necessary but helps with readability as
				//binary numbers are typically split up by groups of 4.
				if (count % 4 == 0)
					printf(" ");
				
				//print each element in the array backwards, 
				//starting at the last element in the array
				printf("%d", bin[--count]);
			}
			
			//Print a new line for each result for clarity.
			printf("\n");
		}
	}
	//Exit the program
	return 0;
}
