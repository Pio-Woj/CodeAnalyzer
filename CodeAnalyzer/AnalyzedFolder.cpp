#include "AnalyzedFolder.h"

// Default constructor
AnalyzedFolder::AnalyzedFolder()
	:fMapOfAnalyzedFiles{},
	fFolderInfo{ L"" },
	fTxtExtension{ true },
	fHExtension{ true },
	fCppExtension{ true }{

}

// Parametric constructor -> initializing object of folder with fixed path
// which affect in calling default contructor of AnalyzedFile fFolderInfo
AnalyzedFolder::AnalyzedFolder(std::filesystem::path folderPath)
	:fMapOfAnalyzedFiles{},
	fFolderInfo{ folderPath.wstring() },
	fTxtExtension{ true },
	fHExtension{ true },
	fCppExtension{ true }{

}

// Necessary getters/setters
std::wstring AnalyzedFolder::getFolderPathWstring() {
	return fFolderInfo.getFilePathWstring();
}

std::map <std::wstring, AnalyzedFile> AnalyzedFolder::getMapOfAnalyzedFiles(void) {
	return fMapOfAnalyzedFiles;
}

AnalyzedFile AnalyzedFolder::getFolderInfo() {
	return fFolderInfo;
}

void AnalyzedFolder::setFolderPathWstring(std::filesystem::path folderPath) {
	fFolderInfo.setFilePathWstring(folderPath);
}

void AnalyzedFolder::setTxtExtension(bool validExtension) {
	fTxtExtension = validExtension;
}

void AnalyzedFolder::setHExtension(bool validExtension) {
	fHExtension = validExtension;
}

void AnalyzedFolder::setCppExtension(bool validExtension) {
	fCppExtension = validExtension;
}

////////////////////////////////////////////////////////////////////////////////////////
// This function updates the fMapOfAnalyzedFiles by adding or removing keys with values
////////////////////////////////////////////////////////////////////////////////////////
//		
// INPUT: void
// OUTPUT: void
// REMARKS: Function adds or removes keys with values depends on bool value of 
//			f*Extension fields and path of folder being currently analyzed		
//		
void AnalyzedFolder::updateMapOfAnalyzedFiles() {
	
	// Initializing vectors of filters (file extensions; case of addition keys
	// with values), antiFilters (file extensions; case of removal keys with values)
	// and filesToDelete (paths used as keys to erase them with values from map)
	std::vector<std::wstring> filtersOfFiles{};
	std::vector<std::wstring> antiFiltersOfFiles{};
	std::vector<std::wstring> filesToDelete{};
	
	if (fTxtExtension == true)
		filtersOfFiles.push_back(L".txt");
	else {
		antiFiltersOfFiles.push_back((L".txt"));
	}
	
	if (fCppExtension == true)
		filtersOfFiles.push_back(L".cpp");
	else {
		antiFiltersOfFiles.push_back((L".cpp"));
	}
	
	if (fHExtension == true)
		filtersOfFiles.push_back(L".h");
	else {
		antiFiltersOfFiles.push_back((L".h"));
	}

	// Loops which go through entire folder, subfolders (omitting directories 
	// that would otherwise result in permission denied errors) and add files
	// to map that meet the extension requirement
	for (const auto file : std::filesystem::recursive_directory_iterator(fFolderInfo.getFilePathWstring(), std::filesystem::directory_options::skip_permission_denied)) {
		for (const auto filter : filtersOfFiles)
			if (file.path().extension().wstring() == filter) {
				fMapOfAnalyzedFiles.insert(std::pair<std::wstring, AnalyzedFile>(file.path().wstring(), AnalyzedFile{ file.path() }));
			}
	}

	// Loops which go through map`s keys (paths to files) and check
	// if its extensions match any of antiFilters then add path to 
	// vector filesToDelete. By checking current folder`s path,
	// records removal doesn`t affect previously analyzed folder.
	for (auto& [path, file] : fMapOfAnalyzedFiles) {
		for (const auto antiFilter : antiFiltersOfFiles)
			if (std::filesystem::path(path).extension() == antiFilter && path.find(getFolderPathWstring())!=std::wstring::npos) {
				filesToDelete.push_back(path);
			}
	}

	// Deleting from map all invalid files 
	for (const auto path : filesToDelete)
		fMapOfAnalyzedFiles.erase(path);
	
	// If map keys contain path to being currently analyzed folder,
	// delete this folder from this map
	if (fMapOfAnalyzedFiles.count(getFolderPathWstring()) == 1)
		fMapOfAnalyzedFiles.erase(getFolderPathWstring());

}

//////////////////////////////////////////////////////////////
// This function sums statistics from all files in the folder
// and sets them in folder statistic
//////////////////////////////////////////////////////////////
//		
// INPUT: folderPath - path to folder whose statistic will
//		  be set
// OUTPUT: void
// REMARKS: Before calling this method, 
//			fillStatisticsForMapOfAnalyzedFiles() should be  
//			called, otherwise statistics of folder will be 0
//			Ofc folder can have statistics set to 0, but it
//			should mean that any file with specified extension
//			has been found 
//		
void AnalyzedFolder::sumUpStatisticsForFolder(std::wstring folderPath) {
	
	int letters{ 0 }, words{ 0 }, lines{ 0 };
	
	// Checking in map whether any file occurs in folder from 
	// input. If yes, get file`s statistic and add it to
	// folder statistic
	for (auto& [path, file] : fMapOfAnalyzedFiles) {
		if (path.find(folderPath) != std::wstring::npos) {
			letters += file.getNumberOfLetters();
			lines += file.getNumberOfLines();
			words += file.getNumberOfWords();
		}
	}
	
	fFolderInfo.setNumberOfLetters(letters);
	fFolderInfo.setNumberOfLines(lines);
	fFolderInfo.setNumberOfWords(words);

}

//////////////////////////////////////////////////////////////////////
// This function starts analysis for each file in fMapOfAnalyzedFiles
//////////////////////////////////////////////////////////////////////
//		
// INPUT: void
// OUTPUT: void
// REMARKS:
//		
void AnalyzedFolder::fillStatisticsForMapOfAnalyzedFiles() {

	for (auto& [path, file] : fMapOfAnalyzedFiles)
		file.setFileStatistics();

}

//////////////////////////////////////////////////////////////////////
// This function deletes all keys and values from fMapOfAnalyzedFiles
//////////////////////////////////////////////////////////////////////
//		
// INPUT: void
// OUTPUT: void
// REMARKS:
//		
void AnalyzedFolder::clearMapOfAnalyzedFiles() {

	fMapOfAnalyzedFiles.clear();

}

//////////////////////////////////////////////////////////////
// This function adds folder statistic to fMapOfAnalyzedFiles
//////////////////////////////////////////////////////////////
//		
// INPUT: void
// OUTPUT: void		
// REMARKS:
//		
void AnalyzedFolder::addFolderInfoToMap() {

	fMapOfAnalyzedFiles.insert(std::pair<std::wstring, AnalyzedFile>(getFolderPathWstring(), getFolderInfo()));

}