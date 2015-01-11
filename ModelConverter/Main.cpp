/* 
*  Kevin Meergans, Improved Lego Editor - Model Converter, 2014
*  Main.cpp
*  Contains the entry point for the application and is responsible for getting user input and
*  forwarding the input to a previously created Converter object.
*/

#include <Windows.h>
#include <fstream>
#include <iostream>
#include <string>
#include "Converter.h"

//--------------------------------------------------------------------------------------
// Entry point to the model converter program. Creates a converter and asks the user for
// files to convert.
//--------------------------------------------------------------------------------------
int main()
{
	// add .txt for destination and include ending for source file

	// the converter
	Converter converter;

	char input;

	// was the user input successfully read
	bool done = false;

	// hold the user input
	std::string sourceFileName("");
	std::string destinationFileName("");

	// Get the source and destination file names
	done = false;
	while( !done )
	{
		// Obtain source and destination file names from the user

		std::cout << "Enter filename of the model you want to convert \n(including the file extension): ";
		std::cin >> sourceFileName;

		std::cout << "\n\nEnter a filename for the new file \n(including the extension '.txt'): ";
		std::cin >> destinationFileName;

		// todo: add more detailed feedback/error description

		if( SUCCEEDED( converter.Convert( sourceFileName, destinationFileName ) ) )
		{
			std::cout << "\nThe model was successfully converted.";
		}else
		{
			std::cout << "\nThe model could not be converted.";
		}

		std::cout << "\nDo you wish to exit (y/n)? ";
		std::cin >> input;
		if(input == 'y')
		{
			done = true;
		}else
		{
			std::cout << "\n\n\n";
		}
	}

	return 0;
}