#pragma once

#include <set>
#include <string>
#include <filesystem>
#include <vector>
#include <map>
#include "AnalyzedFile.h"

///////////////////////////////////////////////////////////
// This class implements the structure which starts analyze
// for each file in main folder selected by user and holds
// obtained statistics in map. In this version of class, it
// is capable of storing statistics form different folders
// in one map.
///////////////////////////////////////////////////////////

class AnalyzedFolder {

	private:
		// Key - path to file given by wstring, Value - file given by AnalyzedFile  
		std::map <std::wstring,AnalyzedFile> fMapOfAnalyzedFiles{};
		AnalyzedFile fFolderInfo{};
		// Flags below specify which files are expected in analysis 
		bool fTxtExtension{};
		bool fHExtension{};
		bool fCppExtension{};

	public:
		// Default constructor
		AnalyzedFolder();

		// Parametric constructor
		AnalyzedFolder(std::filesystem::path folderPath);

		// Necessary getters/setters
		std::wstring getFolderPathWstring(void);
		std::map <std::wstring, AnalyzedFile> getMapOfAnalyzedFiles(void);
		AnalyzedFile getFolderInfo(void);
		void setFolderPathWstring(std::filesystem::path folderPath);
		void setTxtExtension(bool validExtension);
		void setHExtension(bool validExtension);
		void setCppExtension(bool validExtension);

		// Function which updates the fMapOfAnalyzedFiles by adding or removing keys with values
		void updateMapOfAnalyzedFiles(void);

		// Function which sums statistics from all files in the folder
		// and sets them in folder statistic
		void sumUpStatisticsForFolder(std::wstring folderPath);

		// Function which starts analysis for each file in fMapOfAnalyzedFiles
		void fillStatisticsForMapOfAnalyzedFiles(void);

		// Function which deletes all keys and values from fMapOfAnalyzedFiles
		void clearMapOfAnalyzedFiles(void);

		// Function which adds folder statistic to fMapOfAnalyzedFiles
		void addFolderInfoToMap(void);

};