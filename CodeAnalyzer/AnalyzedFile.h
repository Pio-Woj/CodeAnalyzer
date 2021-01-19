#pragma once

#include <string>
#include <filesystem>
#include <sstream>
#include <fstream>

///////////////////////////////////////////////////////////
// This class implements a structure to obtain and later to
// store text statistics of file.
///////////////////////////////////////////////////////////

class AnalyzedFile {

	private:
		std::wstring fFilePathWstring;
		int fNumberOfLetters;
		int fNumberOfWords;
		int fNumberOfLines;

	public:
		// Default constructor
		AnalyzedFile();

		// Parametric constructor
		AnalyzedFile(std::filesystem::path filePath);

		// Function which analyzes a file and then sets all integer variables
		void setFileStatistics();

		// Getters/setters
		std::wstring getFilePathWstring();
		int getNumberOfLetters();
		int getNumberOfLines();
		int getNumberOfWords();
		void setFilePathWstring(std::filesystem::path filePath);
		void setNumberOfLetters(int letters);
		void setNumberOfLines(int lines);
		void setNumberOfWords(int words);

};
