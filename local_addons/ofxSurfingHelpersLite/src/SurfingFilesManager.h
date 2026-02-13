// file: SurfingFilesManager.h
#pragma once

/*

	TODO:

	- allow create a new folder/kit
	- add option to open the folder after export
	- save favorite folder/kit to a list to select them using index or dropdown

*/


#include "ofMain.h"

#include "SurfingFilesManager.h"
#include <functional>

class SurfingFilesManager {
public:
	SurfingFilesManager();
	~SurfingFilesManager();

	void setup();
	// To hide the export button trigger for cases that only need the path setling.
	void setDisableExportTrigger(bool b) { bHideExportTrigger = b; }

	void exit(); // Auto-save settings

	// Callback for custom export logic (e.g., FBO → PNG)
	// Return: filename saved (empty if failed)
	using ExportCallback = std::function<std::string(const std::string & folder)>;
	void setExportCallback(ExportCallback cb) { exportCallback = cb; }

	// Callback when user selects a folder via the dialog
	using FolderSelectedCallback = std::function<void(const std::string & folder)>;
	void setFolderSelectedCallback(FolderSelectedCallback cb) { folderSelectedCallback = cb; }

	// Public API
	void doExport();
	void doChooseFolder();
	void doOpenExportFolder();

	void setPathFolder(const std::string & path) { pathFolder = path; }
	std::string getPathFolder() const { return pathFolder.get(); }

	// For GUI Integration
	ofParameterGroup params;

private:
	void setupParams();
	void setupCallbacks();

	// Parameters
	ofParameter<std::string> pathFolder;
	ofParameter<void> vChoosePathFolder;
	ofParameter<void> vOpenPathFolder;

	// Listeners
	ofEventListener e_vChooseFolder;

	// Export
	ofEventListener e_vExport;
	ofEventListener e_vOpenExportFolder;
	ofParameter<void> vExport;

	// Export logic injected by user
	ExportCallback exportCallback;

	// Folder selected callback injected by user
	FolderSelectedCallback folderSelectedCallback;

	bool bDoneExit = false;
	bool bHideExportTrigger = false;

	bool bDisableInternalJsonSettings = false;
	
	std::string name = "Export";
	
	public:
	void setDisableInternalJsonSettings(bool b) { bDisableInternalJsonSettings = b; }	
	void setName(const std::string & name_) { name = name_; }
};
