// primenumberanalysis.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
// DESCRIPTION:
//
//			This toy program is a tool for A) testing whether a number is prime and B) generating prime numbers.
//
//			It displays 4 options for the user to select from:
//				1) Test whether a specific [input] number is prime.
//				2) Output the largest prime number below an [input] number.
//				3) Output the smallest prime number above an [input] number.
//				4) Display all the prime numbers between [input1] and [input2].
//	
//			After selecting one of the options, the user is directed to provide the relevant input(s),
//			after which the corresponding output is immediately displayed.
//
//			The user then has the option of repeating the analysis for a new set of inputs or terminating the program.
//
//			Positive integers are the only intended numeric inputs from the user. However, as this is merely
//			a toy program meant to showcase basic logic and programming competence, input validation is largely
//			ignored. Accordingly, please only enter positive integers when prompted for numeric inputs.


#include "pch.h"
#include <iostream>
#include "windows.h" // to clear the screen using system("cls")

// function prototypes
bool isPrime(unsigned long long testNum);
void testSpecificNumber();
void displayLargest();
void displaySmallest();
void displayRange();


int main()
{
	char menuSelection;

	do
	{
		system("cls");
		std::cout << "       PRIME NUMBER ANALYSIS PROGRAM by Chris Bryant, Created January 2019\n\n"
			<< "Please select one of the following options:\n\n"
			<< "1) Test whether a specific [input] number is prime.\n"
			<< "2) Output the largest prime number below an [input] number.\n"
			<< "3) Output the smallest prime number above an [input] number.\n"
			<< "4) Display all the prime numbers between [input1] and [input2].\n"
			<< "5) QUIT\n\n"
			<< "Enter 1, 2, 3, 4, or 5: ";
		std::cin >> menuSelection;
		system("cls");

		switch (menuSelection)
		{
		case '1':
			testSpecificNumber();
			break;
		case '2':
			displayLargest();
			break;
		case '3':
			displaySmallest();
			break;
		case '4':
			displayRange();
			break;
		case '5':
			break;
		default:
			std::cout << "INVALID SELECTION. ";
		}

	} while (menuSelection == '1' || menuSelection == '2' || menuSelection == '3' || menuSelection == '4');

	std::cout << "PROGRAM TERMINATED.\n\nCreated by Chris Bryant. clb372@cornell.edu\n";

	return 0;

}

bool isPrime(unsigned long long testNum)
// This function returns TRUE if the integer testNum is a prime number.
// It returns FALSE if it's not a prime number.
// The function also returns FALSE if testNum is negative or > 18,446,744,073,709,551,615
// (The data type 'unsigned long long' cannot handle a number larger than 18,446,744,073,709,551,615.)
{
	// variable declarations
	unsigned long long denominator;

	// If testNum equals 2, then it is, by definition, prime. No other analysis necessary.
	if (testNum == 2)
	{
		return true;
	}
	// If testNum is less than 2, it cannot be prime. Same if it's even. So,
	// return FALSE for those cases, as well as if it's larger than the upper bound
	// of 18,446,744,073,709,551,615 for the 'unsigned long long' C++ data type.
	else if (testNum < 2 || testNum % 2 == 0 || testNum > 18446744073709551615)
	{
		return false;
	}
	else
	{
		// Initialize the denominator to half of testNum because it will be impossible
		// for testNum to be divisible by a number that's more than half of testNum. Add
		// 1 to it to ensure it rounds up in the case of a fractional result.
		denominator = (testNum / 2) + 1;

		// If denominator is even, decrement it by 1. We're testing for prime numbers, and
		// no prime number can be divisible by an even number (except in the case of testNum=2,
		// which was already handled by the first If statement in this function).
		if (denominator % 2 == 0)
		{
			denominator--;
		}

		// Test every odd divisor for testNum, starting at 'denominator', then
		// denominator minus 2, then denominator minus 4, then denominator minus 6,
		// and so on, until denominator is no longer greater than 2. If testNum is divisible
		// by any of these divisors, return FALSE. Otherwise, return TRUE.
		while (denominator > 2)
		{
			// If testNum is divisible by denominator at any point during this loop, return FALSE
			if (testNum % denominator == 0)
			{
				return false;
			}

			// If testNum was not divisible by denominator, deduct 2 from
			// denominator and execute the loop again, except if denominator <= 2.
			denominator = denominator - 2;
		}

		// If the function did not return false in the previous loop, then testNum
		// must be prime. Return TRUE.
		return true;

	}
}


void testSpecificNumber()
// This function tests whether a specific number is prime.
{
	unsigned long long x;
	char loop;
	int inputcount;

	do
	{
		std::cout << "Enter a positive integer to test: ";

		// get user input, with some minimal input validation
		do
		{
			inputcount = 0;
			if (inputcount > 0)
			{
				std::cout << "\n\nError: You must enter a value between 0 and 18,446,744,073,709,551,615 (no commas). Try again: ";
			}
			std::cin.clear();
			std::cin >> x;
			inputcount++;
		} while (std::cin.fail());

		std::cout << "\n\nThis number is ";

		// test whether the input number is prime and display the result to the user
		if (isPrime(x))
		{
			std::cout << "PRIME.\n\nTest another number? (type Y or N) ";
		}
		else
		{
			std::cout << "NOT PRIME.\n\nTest another number? (type Y or N) ";
		}
		std::cin >> loop;
		std::cout << "\n\n";
		system("cls");
	} while (loop == 'Y' || loop == 'y');
}


void displayLargest()
// This function displays the largest prime number less than [input].
{

	unsigned long long input;
	char loop;

	do
	{
		// get user input
		std::cout << "LARGEST PRIME LESS THAN [input]. Enter your [input] number (must be 3 or greater): ";
		std::cin >> input;

		// decrement input by 1 at the outset because we're looking for the largest prime LESS THAN input
		// (in other words, the prime test is non-inclusive of the value entered by the user)
		input--;

		// if at this point the number is even (but not 2), decrement it by 1 more to get to the next odd number below it
		if (input % 2 == 0 && input != 2)
		{
			input--;
		}

		// if the user enters a 10-digit number or larger, warn that this may take a long time
		if (input > 999999999)
		{
			std::cout << "\n\nHEAVY DUTY PROCESSING IN PROGRESS...please be patient...";
		}

		// if input is not prime, decrease it by 2 over and over until it is (decrease it by 2 rather than 1 because
		// we can skip all even values other than 2, as they will never be prime)
		while (not isPrime(input))
		{
			input = input - 2;
		}

		// output the result to the user and offer to repeat the analysis with a new input value
		std::cout << "\n\nRESULT: " << input << "\n\nTry a new [input] number? (Y or N) ";
		std::cin >> loop;
		std::cout << "\n\n";
		system("cls");

	} while (loop == 'Y' || loop == 'y');

}



void displaySmallest()
// This function displays the smallest prime number greater than [input].
{

	unsigned long long input;
	char loop;
	bool error;

	do
	{
		// get user input
		std::cout << "SMALLEST PRIME GREATER THAN [input]. \n\nEnter your [input] number (this number must be greater than 2): ";
		std::cin >> input;
		input++;

		// if the user entered a number that is not greater than 2, set 'error' to TRUE and skip processing
		// -- notifies the user at the end rather than displaying the numeric result
		error = false;
		if (input < 4)
		{
			error = true;
		}

		// if the number is even, increment it by 1 to get it to the next odd number
		if (input % 2 == 0 && !error)
		{
			input++;
		}

		// if the user enters an 11-digit number or larger, warn that this may take a long time
		if (input > 9999999999)
		{
			std::cout << "\n\nHEAVY DUTY PROCESSING IN PROGRESS...please be patient...";
		}

		// keep incrementing 'input' by 2 until it becomes a prime number
		if (!error)
		{
			while (not isPrime(input))
			{
				input = input + 2;
			}
		}


		// display the result to the user, and offer to repeat the function using a new input
		std::cout << "\n\nRESULT: ";
		if (error)
		{
			std::wcout << "*ERROR* You entered a number that isn't greater than 2. Please try again.";
		}
		else
		{
			std::cout << input;
		}
		std::cout << "\n\nTry a new [input] number? (Y or N) ";
		std::cin >> loop;
		std::cout << "\n\n";
		system("cls");

	} while (loop == 'Y' || loop == 'y');

}



void displayRange()
// This function displays all the prime numbers between [input1] and [input2].
{
	unsigned long long input1;
	unsigned long long input2;
	unsigned long long tempVar;
	bool error;
	char loop;

	do
	{
		// get user input
		std::cout << "ALL PRIMES BETWEEN [input1] and [input2], inclusive.\nEnter your [input1]: ";
		std::cin >> input1;
		std::cout << "Enter your [input2]: ";
		std::cin >> input2;
		std::cout << "\n\nRESULTS:\n";

		// detect whether the user has entered a number less than 2 -- if so, notify the user
		// -- the program will not calculate primes when the boolean variable 'error' equals TRUE
		error = false;
		if (input1 < 2 || input2 < 2)
		{
			std::cout << "ERROR: You entered a number less than 2. Please retry.";
			error = true;
		}

		// orient the user's inputs such that input1 <= input2
		if (input1 > input2)
		{
			tempVar = input2;
			input2 = input1;
			input1 = tempVar;
		}


		// if input1 is even, it's not equal to 2, it's more than 1 away from input2, and the user
		// did not input any numbers less than 2, then increment input1 by 1 to bring it up to the
		// next odd number because, from there, the program will increment it by 2 to evaluate each
		// possible prime, skipping every even number because it's impossible for an even number other
		// than 2 to be prime
		if (input1 % 2 == 0 && input1 != 2 && input2 - input1 > 1 && !error)
		{
			input1++;
		}

		// evaluate every odd number starting from input1, going up to input2, and display
		// the number to the user if it's prime
		for (unsigned long long i = input1; i <= input2 && !error; i = i + 2)
		{
			if (isPrime(i))
			{
				std::cout << i << "\n";
			}

			// for the special case where input1 = 2, allow the number to be displayed as
			// a prime (the previous 'if' statement achieves this), and now decrement i from
			// 2 to 1, because in the next iteration of this 'for' loop, 'i' will then increment to 3, then
			// to 5, 7, 9, 11, etc. In other words, set 'i' equal to 1 so that it traverses all
			// the odd numbers between input1 and input2, rather than the even numbers
			if (i == 2)
			{
				i--;
			}
		}

		// at the conclusion, allow the user to repeat the function with a new set of inputs
		std::cout << "\n\nTry a new range? (Y or N) ";
		std::cin >> loop;
		std::cout << "\n\n";
		system("cls");

	} while (loop == 'Y' || loop == 'y');

}