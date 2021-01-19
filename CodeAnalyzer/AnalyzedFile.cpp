#include <iostream>
#include "AnalyzedFile.h"


// Default constructor
AnalyzedFile::AnalyzedFile()
	:fFilePathWstring{ L"" },
	fNumberOfLetters{ 0 },
	fNumberOfWords{ 0 },
	fNumberOfLines{ 0 } {

}

// Parametric constructor -> initializing object of file with fixed path
// statistics set to zero, because analyze hasn`t happened
AnalyzedFile::AnalyzedFile(std::filesystem::path filePath)
	:fFilePathWstring{ filePath.wstring() },
	fNumberOfLetters{ 0 },
	fNumberOfWords{ 0 },
	fNumberOfLines{ 0 } {

}
//////////////////////////////////////////////////////////////////////
// Function which analyzes a file and then sets all integer variables
//////////////////////////////////////////////////////////////////////
//
// INPUT: void
// OUTPUT: void
// REMARKS: Function saves results of file analyze in private 
//			variables of class by setters
//
void AnalyzedFile::setFileStatistics() {
	
	// Checking whether file path points to folder
	// If yes, skip the analysis
	// Statistics for folder are set by different method in AnalyzedFolder class
	if (std::filesystem::is_directory(getFilePathWstring()))
		return;

	int numberOfLetters = 0;
	int numberOfLines = 0;
	int numberOfWords = 0;

	// Trying to open file
	std::wifstream fileHandler(getFilePathWstring());

	// Checking whether file is open
	// If yes, start analysis
	if (fileHandler.good()) {
		std::wstring line{};

		// Reading line by line from the file being currently analyzed
		while (std::getline(fileHandler, line)) {
			numberOfLines++;
			numberOfLetters += line.length();

			// Initializing empty wstring and wstringstream with buffer 
			// filled by one line from file  
			std::wstring ws;
			std::wstringstream wss(line);

			// Cleaning buffer of wstringstream word by word and counting them
			// White spaces are omitted by this method.
			while (wss >> ws)
				numberOfWords++;
		}
		// Closing file
		fileHandler.close();
	}
	
	setNumberOfLetters(numberOfLetters);
	setNumberOfLines(numberOfLines);
	setNumberOfWords(numberOfWords);
}



// Getters/setters
std::wstring AnalyzedFile::getFilePathWstring() {
	return fFilePathWstring;
}

int AnalyzedFile::getNumberOfLetters() {
	return fNumberOfLetters;
}

int AnalyzedFile::getNumberOfWords() {
	return fNumberOfWords;
}

int AnalyzedFile::getNumberOfLines() {
	return fNumberOfLines;
}

void AnalyzedFile::setFilePathWstring(std::filesystem::path filePath) {
	fFilePathWstring = filePath.wstring();
}

void AnalyzedFile::setNumberOfLetters(int letters) {
	fNumberOfLetters = letters;
}

void AnalyzedFile::setNumberOfLines(int lines) {
	fNumberOfLines = lines;
}

void AnalyzedFile::setNumberOfWords(int words) {
	fNumberOfWords = words;
}

