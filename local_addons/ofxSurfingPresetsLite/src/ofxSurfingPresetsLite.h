#pragma once
#include "ofMain.h"

#include "SurfingFilesManager.h"
#include "ofxSurfingHelpersLite.h"
#include "ofxSurfingHelpersParameters.h"

//--

/*

	BUGS

	check deleting some presets wrongly!
		add backup kit button
	saving a preset on exit?
	in presets lite enter key breaks removing files! add modifier comand key

	--

	TODO

	allow create folder.
	select other folder, if has files, load first preset.
	FIX set reset allowing colors that seems disabled!

	FIX init start when no settings.
		set default path ex: /bin/data/kit/
		improve default workflow
			kit path empty
			set default /kit/
			populate

	add new index and from/to copy preset

	FIX some crashes

	simplify path and refresh

	FIX global path for settings

	FIX clean not required pathSettings, pathGlobal..

	FIX key triggers

	smooth params ?

	--

    add auto saver when changes.
		using autoSaver?
		avoid exit save.
	add multiple ofParameterGroup/s
	in the imgui matrix: 
		fix colors on flipping 
		fix direction
	add rename/custom names presets?

	re populate misc unsorted files with correlative names 01-02-etc
*/

//----

class SurfingPresetsLite {
public:
	SurfingPresetsLite() {
		ofSetLogLevel("SurfingPresetsLite", OF_LOG_NOTICE);

		ofLogVerbose("SurfingPresetsLite") << "Constructor()";

		addListeners();

		dir.allowExt("JSON");
		dir.allowExt("json");
	}

	~SurfingPresetsLite() {
		ofLogVerbose("SurfingPresetsLite") << "Destructor()";

		removeListeners();

		destructUI();

		if (!bDoneExit) {
			ofLogWarning("SurfingPresetsLite") << "Call exit() forced on destructor!";
			exit();
		}
	}

protected:
	void addListeners() {
		ofLogVerbose("SurfingPresetsLite") << "addListeners()";

		ofAddListener(parameters.parameterChangedE(), this, &SurfingPresetsLite::Changed);
		ofAddListener(ofEvents().update, this, &SurfingPresetsLite::update);
		ofAddListener(ofEvents().exit, this, &SurfingPresetsLite::exit);

		addKeysListeners();
	}

	void removeListeners() {
		ofLogVerbose("SurfingPresetsLite") << "removeListeners()";

		ofRemoveListener(parameters.parameterChangedE(), this, &SurfingPresetsLite::Changed);
		ofRemoveListener(ofEvents().update, this, &SurfingPresetsLite::update);
		ofRemoveListener(ofEvents().exit, this, &SurfingPresetsLite::exit);

		removeKeysListeners();
	}

	virtual void destructUI() {
		ofLogNotice("SurfingPresetsLite") << "destructUI() empty"; // To be filled by derived classes..
	}

private:
	void exit(ofEventArgs & args) {
		ofLogNotice("SurfingPresetsLite") << "exit(args)";

		exit();
	}

	void exit() {
		ofLogNotice("SurfingPresetsLite") << "exit()";

		// Save session settings
		std::string s;
		if (pathGlobal == "")
			s = pathSettings;
		else
			s = ofFilePath::join(pathGlobal, pathSettings);
		ofxSurfing::saveGroup(parameters, s);

		// Save current preset
		if (bAutoSave) doSave(false);

		bDoneExit = true;
	}

public:
	// //TODO: fix
	// Customize name to avoid window names colliding
	// with other preset manager instances working on the same app.
	void setNameUI(std::string s) {
		ofLogNotice("SurfingPresetsLite") << "setNameUI(): " << s;

		std::string n = "";
		n += "UI ";
		n += "PRESETS ";
		n += s;
		bGui.set(n, true);
	}

private:
	std::string pathSettings = "Presets.json";

	bool bDoneStartup = false;
	bool bDoneExit = false;

	//----

protected:
	bool bModKeyControl = false;
	bool bModKeyAlt = false;

	vector<char> pChars;

	//----

public:
	ofParameter<void> vReset { "Reset" };
	ofParameter<void> vResetSetInit { "Set Reset" };
	ofParameter<void> vRandom { "Random" };

	ofParameter<int> index { "Index", -1, -1, -1 };

	ofParameter<bool> bCycled { "Cycled", true };

	// Amount max presets allowed but only for populating functions and key commands
	ofParameter<int> numPresetsForPopulating { "Num presets", 10, 2, 32 };

public:
	ofParameter<bool> bGui { "PRESETS", true };
	ofParameter<bool> bGuiParams { "UI PARAMETERS", true };
	ofParameter<bool> bGuiClicker { "UI CLICKER", false };
	ofParameter<bool> bGuiFloating { "Floating Window", true };
	ofParameter<bool> bGuiExpand { "Expand", false };

private:
	int index_PRE = -2; // pre

public:
	void setToggleGuiVisible() { bGui = !bGui; }
	void setGuiVisible(bool b = true) { bGui = b; }
	bool getGuiVisible() { return bGui; }

	//--

public:
	ofParameter<void> vPrevious { "<" };
	ofParameter<void> vNext { ">" };

protected:
	ofParameter<void> vNew { "New" };
	ofParameter<void> vDelete { "Delete" };
	ofParameter<void> vSave { "Save" };
	ofParameter<void> vLoad { "Load" };

	ofParameter<void> vScanKit { "Scan Files" };
	ofParameter<void> vClearKit { "Clear Kit" };
	ofParameter<void> vPopulateKit { "Populate Current" };
	ofParameter<void> vPopulateRandomKit { "Populate Random" };

	ofParameter<bool> bAutoSave { "AutoSave", true }; // edit mode
	ofParameter<bool> bAutoLoad { "AutoLoad", true }; // edit mode
	ofParameter<bool> bKeys { "Keys", true };
	ofParameter<bool> bHelp { "Help", true };

private:
	SurfingFilesManager filesManager;
	ofParameter<std::string> path_Kit;

	vector<char> keyCommandsChars; // available keys to listen on keys press

private:
	void setup() {
		ofLogNotice("SurfingPresetsLite") << "setup()";

		ofSetLogLevel("SurfingOfxGuiPanelsManager", OF_LOG_SILENT);

		setupParameters();
		doRefreshKitFiles();
		setupGui();
	}

	virtual void refreshGui() {
		ofLogNotice("SurfingPresetsLite") << "refreshGui() empty"; // To be filled by derived classes..
	}

	virtual void setupParametersExtra() {
		ofLogNotice("SurfingPresetsLite") << "setupParametersExtra() empty"; // To be filled by derived classes..
	}

	//--

	void setupFilesManager() {
		ofLogNotice("SurfingPresetsLite") << "setupFilesManager()";

		filesManager.setName("Kit_Path");
		filesManager.setDisableInternalJsonSettings(true); // handle path serialization ourselves
		filesManager.setDisableExportTrigger(true); // to hide export trigger in case you dont need it
		filesManager.setup();
		if (filesManager.getPathFolder() == "")
			filesManager.setPathFolder(ofToDataPath("Kit-00", true));
		path_Kit.set(filesManager.getPathFolder());
		path_Kit.setSerializable(false); // hide from serialization bc we use surfingFilesManager to store the path

		paramsKit.add(filesManager.params);

		setupFilesManagerCallbacks();
	}

	void setupFilesManagerCallbacks() {
		ofLogNotice("SurfingPresetsLite") << "setupFilesManagerCallbacks()";

		// Custom callbacks for files manager
		// Notify ofApp when a folder is selected in the manager
		filesManager.setFolderSelectedCallback([this](const std::string & folder) {
			ofLogNotice("SurfingPresetsLite") << "Callback (SurfingFilesManager) Folder selected: " << folder;

			// store selected folder
			path_Kit.set(filesManager.getPathFolder());

			doRefreshKitFiles();
		});
	}

	//--

	virtual void setupParameters() {
		ofLogNotice("SurfingPresetsLite") << "setupParameters()";

		paramsBrowse.add(index);
		paramsBrowse.add(vNext);
		paramsBrowse.add(vPrevious);

		paramsManager.add(vLoad);
		paramsManager.add(vNew);
		paramsManager.add(vDelete);
		paramsManager.add(vResetSetInit);
		paramsManager.add(vReset);
		paramsManager.add(vRandom);

		// Setup files manager.
		// This class is used to handle kit path: folder browsing and file listing.
		setupFilesManager();

		paramsKit.add(vPopulateKit);
		paramsKit.add(vPopulateRandomKit);
		paramsKit.add(vClearKit);
		paramsKit.add(vScanKit);

		paramsAdvanced.add(bCycled);
		paramsAdvanced.add(numPresetsForPopulating);
		paramsInternal.add(bGui); // Only for serializing settings. could be hidden of the ui
		paramsAdvanced.add(paramsInternal);

		//parameters.add(bGuiParams); // Exposed also on guiManager
		parameters.add(paramsBrowse);
		parameters.add(vSave);
		parameters.add(bAutoSave);
		parameters.add(bAutoLoad);
		parameters.add(paramsManager);
		parameters.add(paramsKit);
		parameters.add(paramsAdvanced);
		parameters.add(bHelp);
		parameters.add(bKeys);

		setupParametersExtra();
	}

	virtual void setupGui() { // To be filled by derived classes..
		ofLogNotice("SurfingPresetsLite") << "setupGui() empty";
	}

	void refreshIndexRanges() {
		ofLogNotice("SurfingPresetsLite") << "refreshIndexRanges()";

		bool bEmpty = (dir.size() == 0);
		if (!bEmpty) {
			index.setMin(0);
			index.setMax(dir.size() - 1);
		} else {
			index.setMin(-1);
			index.setMax(-1);
			index.set(-1);
		}

		// Clamp index ofParameter
		if (index < index.getMin())
			index.set(index.getMin());
		else if (index > index.getMax())
			index.set(index.getMax());
	}

	void startup() {
		ofLogNotice("SurfingPresetsLite") << "startup()";

		doRefreshKitFiles();

		index_PRE = -2;

		// Load session settings
		std::string s;
		if (pathGlobal == "")
			s = pathSettings;
		else
			s = ofFilePath::join(pathGlobal, pathSettings);
		ofxSurfing::loadGroup(parameters, s);

		// Workflow
		// Must set some init states to avoid exceptions on reset!
		ofxSurfing::doResetSetInit(paramsPreset);

		// Fix if index range is out of range or not correlated to dir files!
		refreshIndexRanges();

		// Flag to create help info
		bFlagBuildHelp = true;

		// Define some standard key strokes to trig presets
		pChars.clear();
		pChars = {
			'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
			'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
			'z', 'x', 'c', 'v', 'b', 'n', 'm'
		};
		ofLogNotice("SurfingPresetsLite") << "pChars.size(): " << pChars.size();

		// Prepare key commands vector according to numPresetsForPopulating
		numPresetsForPopulating = ofClamp(numPresetsForPopulating.get(),
			0, numPresetsForPopulating.getMax());
		keyCommandsChars.clear();
		for (size_t i = 0; i < numPresetsForPopulating.get(); i++) {
			keyCommandsChars.push_back(pChars[i]);
		}

		//--

		// Auto populate if there's no preset files found!

		if (getNumPresets() == 0) {
			ofLogWarning("SurfingPresetsLite") << "No file presets found. Populating a kit of random presets.";
			doPopulateRandomKit();
		}

		//--

		bDoneStartup = true;
	}

	void update(ofEventArgs & args) {
		if (!bDoneStartup) {
			startup();
		}

		if (bFlagBuildHelp) {
			bFlagBuildHelp = false;
			buildHelp();
		}
	}

protected:
	std::string sHelp = "";
	bool bFlagBuildHelp = false;

public:
	void buildHelp() {
		sHelp = "";
		sHelp += "PRESETS\nMANAGER\n";
		sHelp += "\n";
		if (bKeys) {
			sHelp += "KEYS\n";
			sHelp += "\n";
			sHelp += "g           UI\n";
			sHelp += "h           Help\n";
			sHelp += "\n";
			sHelp += "BACKSPACE   Random\n";
			sHelp += "+Ctrl       Reset\n";
			sHelp += "\n";
			sHelp += "n           New preset\n";
			sHelp += "r           Populate\n";
			sHelp += "            Random Kit\n";
			sHelp += "\n";
			sHelp += "< >         Browse\n";
#ifdef SURFING__OFX_PRESETS_LITE__USING__IM_GUI
			sHelp += "UP/DOWN     Row\n";
#endif
		} else {
			sHelp += "\n";
			sHelp += "KEYS DISABLED\n";
		}
		sHelp += "Preset      ";
		sHelp += ofToString(getPresetIndex()) + " / " + ofToString(getPresetIndexLast()) + "\n";
		sHelp += "File        ";
		if (index < dir.size()) sHelp += getPresetFileName() + "\n";
		sHelp += "Kit         ";
		sHelp += getKitName() + "\n";
		sHelp += "\n";
		sHelp += "Kit Path: \n";
		sHelp += getPathSplitIntoLines(getKitPath()) + "\n";
		sHelp += "\n";
		sHelp += "Files: \n";
		if (dir.size() > 0) sHelp += ofToString(getListFiles()) + "\n";
		if (bKeys) {
			sHelp += "F5          Scan\n";
		}
	}

	virtual void drawHelp() {
		if (!bHelp) return;

		ofxSurfing::ofDrawBitmapStringBox(sHelp, ofxSurfing::SURFING_LAYOUT_BOTTOM_RIGHT);
	}

	//--

private:
	void doSave(bool bRefreshFiles = true) {
		// Note: Here, fileBaseName is or must be already named and ready to be used here!
		if (getNumFiles() == 0) fileBaseName = "00"; // prepare name for first preset

		// Note that saves the previously settled file name when picking the index!
		ofLogNotice("SurfingPresetsLite") << "doSave(" << ofToString(bRefreshFiles ? "true" : "false") << "): " << fileBaseName;

		// Save preset
		ofxSurfing::saveGroup(paramsPreset, getPresetPath());

		//--

		if (bRefreshFiles) {
			// Scan files
			doRefreshKitFiles();
		}
	}

	void doLoad(int index_) {
		ofLogVerbose("SurfingPresetsLite") << "doLoad(" << index_ << ")";

		if (index_ != index) {
			index_PRE = index_;
			index = index_;
		}

		if (index < dir.size() && index >= 0) {
			fileBaseName = dir[index].getBaseName();
			doLoad(fileBaseName);
		} else {
			ofLogError("SurfingPresetsLite") << "Preset Index out of files range!";
		}
	}

	void doLoad(std::string baseName = "") {
		ofLogNotice("SurfingPresetsLite") << "doLoad(" << baseName << ")";

		if (baseName != "") {
			if (fileBaseName != baseName)
				fileBaseName = baseName;
		}
		ofLogNotice("SurfingPresetsLite") << "doLoad(): " << fileBaseName;

		// Load preset
		ofxSurfing::loadGroup(paramsPreset, getPresetPath());
	}

	//--

public:
	void setup(ofParameterGroup & group) {
		ofLogNotice("SurfingPresetsLite") << "setup(): " << group.getName();

		addGroup(group);
	}

private:
	//TODO: allow more than one group...
	// Separated and recursive or multiple addGroup calls?
	void addGroup(ofParameterGroup & group) {
		ofLogNotice("SurfingPresetsLite") << "addGroup(): " << group.getName();

		//TODO: make a pointer, bc maybe that `=` not work well or safe...
		auto ptype = group.type();
		bool isGroup = ptype == typeid(ofParameterGroup).name();
		if (isGroup) {
			paramsPreset = group;
		}

		name = group.getName();

		setNameUI(name); //rename bGui param
		parameters.setName(ofToString("PRESET_") + name); //used for gui panel title

		pathSettings = name + ofToString("_Presets.json");

		setup();
	}

public:
	std::string getName() const {
		return name;
	}

public:
	void setPathGlobal(const std::string & p) {
		pathGlobal = p;
		ofLogNotice("SurfingPresetsLite") << "setPathGlobal(): " << pathGlobal;
	}

private:
	void setFileBaseName(const std::string & p) {
		fileBaseName = p;
		ofLogNotice("SurfingPresetsLite") << "setFileBaseName(): " << fileBaseName;
	}

public:
	void doLoadPrevious() {
		ofLogNotice("SurfingPresetsLite") << "doLoadPrevious()";

		if (index.getMax() == -1) return;
		int i = index;

		if (index > index.getMin())
			i--;
		else if (i == index.getMin())
			if (bCycled)
				i = index.getMax();
		//else
		//i = index.getMin();
		index.set(i);
	}

	void doLoadNext() {
		ofLogNotice("SurfingPresetsLite") << "doLoadNext()";

		if (index.getMax() == -1) return;
		int i = index;
		if (i < index.getMax())
			i++;
		else if (i == index.getMax())
			if (bCycled)
				i = index.getMin();
		//else
		//i = index.getMax();
		index.set(i);
	}

	// Only useful for matrix clicker ui as ImGui not ofxGui
	virtual void doLoadNextRow() {
		ofLogNotice("SurfingPresetsLite") << "doLoadNextRow()";

		int i = index;
		if (bCycled)
			if (i > index.getMax()) i = index.getMin() + i;
		index = ofClamp(i, index.getMin(), index.getMax());
	}
	virtual void doLoadPreviousRow() {
		ofLogNotice("SurfingPresetsLite") << "doLoadPreviousRow()";

		int i = index;
		if (bCycled)
			if (i < index.getMin()) i = index.getMax() - i;
		index = ofClamp(i, index.getMin(), index.getMax());
	}

private:
	void Changed(ofAbstractParameter & e) {
		std::string name = e.getName();
		ofLogNotice("SurfingPresetsLite") << "Changed: " << name;

		bFlagBuildHelp = true; // update help info when any parameter changes

		if (name == index.getName()) {
			doProcessIndexCallback();
		}

		else if (name == vLoad.getName()) {
			doLoad();
		}

		else if (name == vSave.getName()) {
			doSave(false);
		}

		else if (name == vDelete.getName()) {
			doDelete();
		}

		else if (name == vNew.getName()) {
			doNewPreset();
		}

		else if (name == vPrevious.getName()) {
			doLoadPrevious();
		}

		else if (name == vNext.getName()) {
			doLoadNext();
		}

		else if (name == vScanKit.getName()) {
			doRefreshKitFiles();
		}

		else if (name == vClearKit.getName()) {
			doClearKit(); // autocreates a new preset
		}

		else if (name == vPopulateKit.getName()) {
			doPopulateKit(numPresetsForPopulating);
		}

		else if (name == vPopulateRandomKit.getName()) {
			doPopulateRandomKit(numPresetsForPopulating);
		}

		else if (name == vReset.getName()) {
			doResetInit();
		}

		else if (name == vResetSetInit.getName()) {
			doResetSetInit();
		}

		else if (name == vRandom.getName()) {
			doRandomize();
		}
	}

	void doProcessIndexCallback() {
		if (dir.size() == 0) return;

		// Changed index selector?
		if (index != index_PRE) {
			ofLogNotice("SurfingPresetsLite") << ofToString(index_PRE) << " > " << ofToString(index);
			bIsChangedIndex = true;

			// log the index/files changes from->to
			if ((index_PRE < fileBaseNames.size() && index < fileBaseNames.size()) && (index_PRE < dir.size() && index < dir.size())) {
				ofLogVerbose("SurfingPresetsLite: Names: ") << ofToString(fileBaseNames[index_PRE]) << " > "
															<< ofToString(fileBaseNames[index]);
				ofLogNotice("SurfingPresetsLite: Filenames: ") << ofToString(dir[index_PRE].getFileName()) << " > "
															   << ofToString(dir[index].getFileName());
			}

			//--

			// 1. Common load.
			//
			// Also will save the previous index preset if AutoSave enabled.

			if (!bModKeyControl && !bModKeyAlt) // Ctrl nor Alt not pressed.
			{
				// 1.1 save if enabled AutoSave

				if (bAutoSave) {
					if (index_PRE < fileBaseNames.size()) {
						fileBaseName = fileBaseNames[index_PRE];
						doSave(false);
					} else {
						ofLogVerbose("SurfingPresetsLite") << "Preset Index out of files range!";
					}
				}

				//--

				// 1.2 Load
				if(bAutoLoad){
					ofLogNotice("SurfingPresetsLite") << index.getName() + ": " << ofToString(index);

					if (index < fileBaseNames.size()) {
						fileBaseName = fileBaseNames[index];
						doLoad();
					} else {
						ofLogError("SurfingPresetsLite") << "File out of range";
					}
				}

				index_PRE = index;
			}

			//--

			// 2. Save / Copy

			// Save to clicked preset index
			// Ctrl pressed. Alt not pressed.

			else if (bModKeyControl && !bModKeyAlt) {
				if (index < fileBaseNames.size()) {
					fileBaseName = fileBaseNames[index];
					doSave(false);
					ofLogNotice("SurfingPresetsLite") << "Preset Copy!";

					index_PRE = index;
				}
			}

			//--

			//TODO:

			// 3. Swap between current/previous

			// (from/to) pre/current index
			// Ctrl not pressed. Alt pressed.

			else if (!bModKeyControl && bModKeyAlt) {
				if (index < fileBaseNames.size() && index_PRE < fileBaseNames.size()) {

					// Rename target to source
					std::string nFrom = fileBaseNames[index_PRE];
					std::string nTo = fileBaseNames[index];
					ofFile f;

					nTo = ofFilePath::join(path_Kit.get(), (nTo + ".json"));
					nFrom = ofFilePath::join(path_Kit.get(), (nFrom + ".json"));

					bool bf = f.open(nTo);
					bool bt = f.renameTo(nFrom, true, true);

					// Save current to
					fileBaseName = nTo;
					doSave(false);

					if (bf && bt) {
						ofLogNotice("SurfingPresetsLite") << "Preset Swap!";
						ofLogNotice("SurfingPresetsLite") << nFrom << " <-> " << nTo;
					} else {
						ofLogError("SurfingPresetsLite") << "Wrong Swap!";
					}

					index_PRE = index;
				}
			}
		}
	}

	//--

public:
	ofParameterGroup parameters { "PRESETS MANAGER" };

protected:
	ofParameterGroup paramsPreset { "Preset" };
	ofParameterGroup paramsBrowse { "Browse" };
	ofParameterGroup paramsManager { "Manager" };
	ofParameterGroup paramsKit { "Kit" };
	ofParameterGroup paramsAdvanced { "Advanced" };
	ofParameterGroup paramsInternal { "Internal" };

	//ofParameterGroup paramsUI { "UI" };

protected:
	std::string name = ""; // Only for instance naming.

private:
	std::string pathGlobal = ""; // Optional main folder where nested folder goes inside. bin/data/myApp/Kit/

	// Files
protected:
	ofDirectory dir;

	std::string filePath;
	std::string fileBaseName = "NONE";
	vector<std::string> fileBaseNames;

	//--

public:
	std::string getKitPath() const {
		return path_Kit.get();
	}
	std::string getPresetPath() const {
		std::string path;
		path = ofFilePath::join(path_Kit.get(), (fileBaseName + ".json"));
		return path;
	}
	std::string getPresetName() const {
		return fileBaseName;
	}
	std::string getKitName() const {
		string n = ofFilePath::getFileName(ofFilePath::removeTrailingSlash(path_Kit.get()));
		return n;
	}
	std::string getPresetFileName() const {
		return ofToString(fileBaseName + ".json");
	}
	int getNumPresets() const {
		return index.getMax() + 1;
	}
	int getPresetIndexLast() const {
		return index.getMax();
	}
	int getPresetIndex() const {
		return index.get();
	}

protected:
	int getNumFiles() const {
		return fileBaseNames.size();
	}

	bool doReorganizeKitFiles() {
		ofLogNotice("SurfingPresetsLite") << "doReorganizeKitFiles() Found " << dir.size() << " files.";

		bool bSomeFileRequiredRename = false;
		for (int i = 0; i < dir.size(); i++) {
			std::string n = dir[i].getBaseName(); // current name
			std::string n_ = std::string((i < 10) ? "0" : "") + ofToString(i); // expected name
			if (n_ != n) {
				std::string pf; // from
				std::string pt; // to
				pf = ofFilePath::join(path_Kit.get(), (n + ".json"));
				pt = ofFilePath::join(path_Kit.get(), (n_ + ".json"));

				ofLogNotice("SurfingPresetsLite") << "Rename file #" << i;
				ofLogNotice("SurfingPresetsLite") << pf << " > " << pt;
				ofFile file(pf);
				if (file.exists()) {
					file.renameTo(pt);

					bSomeFileRequiredRename = true;
				}
			}
		}

		bFlagBuildHelp = true;

		return bSomeFileRequiredRename;
	}

	bool doRefreshKitFiles() {
		// Must call for reading folder, when deleting or creating a new preset.
		ofLogNotice("SurfingPresetsLite") << "doRefreshKitFiles(): " << path_Kit.get();

		dir.listDir(path_Kit.get());
		dir.sort();

		bool bEmpty = (dir.size() == 0);
		if (bEmpty) {
			ofLogWarning("SurfingPresetsLite") << "doRefreshKitFiles(): " << path_Kit.get() << " directory is empty.";
		} else {
			doReorganizeKitFiles();
		}

		// Log files on folder
		fileBaseNames.clear();
		for (int i = 0; i < dir.size(); i++) {
			ofLogNotice("SurfingPresetsLite") << "file #" << ofToString(i) << ": " << dir.getName(i);
			fileBaseNames.push_back(dir[i].getBaseName());
		}

		refreshIndexRanges();

		// Returns true if there's some file/s!
		return (!bEmpty);
	}

protected:
	void doListFiles() {
		ofLogNotice("SurfingPresetsLite") << "doListFiles()";

		for (auto f : dir) {
			ofLogNotice("SurfingPresetsLite") << "doListFiles(): getAbsolutePath: " << f.getAbsolutePath();
		}
	}
	std::string getListFiles() const {
		ofLogNotice("SurfingPresetsLite") << "getListFiles()";

		std::string l;
		size_t i = 0;
		for (auto f : dir) {
			l += f.getFileName();
			//l += f.path();
			if (i == index) l += " *";
			l += "\n";
			i++;
		}
		return l;
	}

	void doDelete(bool bSetIndexToLast = false) {
		if (dir.size() == 0) return;

		ofLogNotice("SurfingPresetsLite") << "doDelete() Index: " << index;

		fileBaseName = fileBaseNames[index];
		//fileBaseName = dir[index].getBaseName();

		ofLogNotice("SurfingPresetsLite") << "doDelete() Filename: " << fileBaseName;

		std::string p = getPresetPath();
		ofLogNotice("SurfingPresetsLite") << "doDelete() Look for: " << p;
		bool b = ofFile::removeFile(p);

		if (b) {
			ofLogNotice("SurfingPresetsLite") << "Successfully deleted: " << p;
			doRefreshKitFiles();
#if 1
			// workflow
			if (bSetIndexToLast) // load last
				index.set(index.getMax());
			else // load current
				doLoad(index); // refresh current selected
#endif
			ofLogNotice("SurfingPresetsLite") << "Done delete";
		} else {
			ofLogError("SurfingPresetsLite") << "Unable to delete: " << p;
		}

		// fix correct list
		doRefreshKitFiles();
	}

	void doNewPreset() {
		ofLogNotice("SurfingPresetsLite") << "doNewPreset()";

		std::string n;
		if (dir.size() == 0) {
			n = "00"; // at first
		} else {
			// at last
			int sz = dir.size();
			n = std::string((sz < 10) ? "0" : "") + ofToString(sz);
		}
		setFileBaseName(n);

		doSave(true);

		// workflow: select last preset
		index.set(dir.size() - 1);
	}

	void doClearKit(bool createOne = true) {
		ofLogNotice("SurfingPresetsLite") << "doClearKit(" << createOne << ")";

		// Remove all files
		for (int i = 0; i < dir.size(); i++) {
			ofFile file = dir[i];
			file.remove();
		}

		doRefreshKitFiles();

		// workflow: create a new preset
		if (createOne) {
			doNewPreset();
		}
	}

	void doPopulateRandomKit() {
		ofLogNotice("SurfingPresetsLite") << "doPopulateRandomKit() " << numPresetsForPopulating;

		doPopulateRandomKit(numPresetsForPopulating);
	}

	void doPopulateRandomKit(int amount) { // pass -1 to overwrite/use the same amount of presets.
		ofLogNotice("SurfingPresetsLite") << "doPopulateRandomKit() " << amount;

		doPopulateKit(amount, true);
	}

	void doPopulateKit(int amount, bool bRandom = false) { // pass -1 to overwrite/use the same amount of presets.
		ofLogNotice("SurfingPresetsLite") << "doPopulateKit() " << amount;

		doClearKit(false);

		// will create the same amount files on folder
		if (amount == -1) {
			amount = dir.size();
		}

		bool b = false;
		for (int i = 0; i < amount; i++) {
			doNewPreset();
			if (bRandom) doRandomize();
			doSave(true);
		}

		if (b) index = 0; //workflow
	}

	//----

	//--------------------------------------------------------------
	void keyPressed(ofKeyEventArgs & eventArgs) {
		if (!bKeys) return;

		const int & key = eventArgs.key;
		ofLogVerbose("SurfingPresetsLite") << "keyPressed: " << (char)key;

		// Modifiers
		bool bModKeyControl_ = eventArgs.hasModifier(OF_KEY_CONTROL);
		bool bModKeyAlt_ = eventArgs.hasModifier(OF_KEY_ALT);

		if (bModKeyControl_) bModKeyControl = true;
		if (bModKeyAlt_) bModKeyAlt = true;

		if (key == OF_KEY_DEL) {
			doDelete();
			return;
		}

		if (key == OF_KEY_LEFT) {
			doLoadPrevious();
			return;
		}

		if (key == OF_KEY_RIGHT) {
			doLoadNext();
			return;
		}

		if (key == OF_KEY_F5) {
			doRefreshKitFiles();
			//doRefreshKitFiles(); //TODO: doubled to fix
			return;
		}

#ifdef SURFING__OFX_PRESETS_LITE__USING__IM_GUI
		if (key == OF_KEY_UP) {
			doLoadPreviousRow();
			return;
		}

		if (key == OF_KEY_DOWN) {
			doLoadNextRow();
			return;
		}
#endif

		//		if (key == OF_KEY_RETURN && !bModKeyControl) {
		if (key == 'n' && !bModKeyControl) {
			doNewPreset();
			return;
		}

		//		if (key == OF_KEY_RETURN && bModKeyControl) {
		if (key == 'r' && !bModKeyControl) {
			doPopulateRandomKit();
			return;
		}

		if (key == OF_KEY_BACKSPACE && bModKeyControl) {
			doResetInit();
			//doReset();
			return;
		}

		if (key == OF_KEY_BACKSPACE && !bModKeyControl) {
			doRandomize();
			return;
		}

		if (key == 'h') {
			bHelp = !bHelp;
			return;
		}

		if (key == 'g') {
			setToggleGuiVisible();
			return;
		}

		if (key == 'G') {
			bGuiClicker = !bGuiClicker;
			return;
		}

		else {
			for (size_t i = 0; i < numPresetsForPopulating; i++) {
				if (i >= keyCommandsChars.size()) return;
				if ((char)key == keyCommandsChars[i]) {
					index.set(i);
					return;
				}
			}
		}
	}

	//--------------------------------------------------------------
	void keyReleased(ofKeyEventArgs & eventArgs) {
		if (!bKeys) return;

		const int & key = eventArgs.key;
		ofLogVerbose("SurfingPresetsLite") << "keyReleased: " << (char)key /*<< " [" << key << "]"*/;

		// Modifiers
		bool bModControl_ = eventArgs.hasModifier(OF_KEY_CONTROL);
		bool bModAlt_ = eventArgs.hasModifier(OF_KEY_ALT);

		if (!bModControl_) bModKeyControl = false;
		if (!bModAlt_) bModKeyAlt = false;
	}

	//--------------------------------------------------------------
	void addKeysListeners() {
		ofLogVerbose("SurfingPresetsLite") << "addKeysListeners()";

		ofAddListener(ofEvents().keyPressed, this, &SurfingPresetsLite::keyPressed);
		ofAddListener(ofEvents().keyReleased, this, &SurfingPresetsLite::keyReleased);
	}

	//--------------------------------------------------------------
	void removeKeysListeners() {
		ofLogNotice("SurfingPresetsLite") << "removeKeysListeners()";

		ofRemoveListener(ofEvents().keyPressed, this, &SurfingPresetsLite::keyPressed);
		ofRemoveListener(ofEvents().keyReleased, this, &SurfingPresetsLite::keyReleased);
	}

	// Easy callback to know when the preset index/selector changed from the parent class
private:
	bool bIsChangedIndex = false;

public:
	bool isChangedIndex() {
		if (bIsChangedIndex) {
			bIsChangedIndex = false;
			return true;
		} else
			return false;
	}

	//----

	//--------------------------------------------------------------
	void doResetSetInit() { // set current state as init/default
		ofLogNotice("SurfingPresetsLite") << "doResetSetInit()";

		ofxSurfing::doResetSetInit(paramsPreset);
	}

	//--------------------------------------------------------------
	void doResetInit() { // resetore init state
		ofLogNotice("SurfingPresetsLite") << "doResetInit()";

		ofxSurfing::doResetInit(paramsPreset);
	}

	//--------------------------------------------------------------
	void doReset() { // resets to each params mins
		ofLogNotice("SurfingPresetsLite") << "doReset()";

		ofxSurfing::doReset(paramsPreset);
	}

	//--------------------------------------------------------------
	void doRandomize() { // andomize each params
		ofLogNotice("SurfingPresetsLite") << "doRandomize()";

		ofxSurfing::doRandomize(paramsPreset);
	}

private:
	// Helper function to split a long path into multiple lines to beautify help display
	string getPathSplitIntoLines(const string & path, int segmentsPerLine = 3, int maxCharsPerLine = 40) {
		if (path.empty()) return string();

		// Normalize path separators to forward slashes (cross-platform)
		string normalizedPath = path;
		ofStringReplace(normalizedPath, "\\", "/");

		vector<string> segments = ofSplitString(normalizedPath, "/");
		string result;
		string currentLine;
		int segCount = 0;

		for (size_t i = 0; i < segments.size(); i++) {
			string segmentToAdd = (i > 0 ? "/" : "") + segments[i];

			bool exceedsChars = (!currentLine.empty() && (int)(currentLine.length() + segmentToAdd.length()) > maxCharsPerLine);
			bool exceedsSegments = (segCount >= segmentsPerLine);

			// Add newline if we exceed either limit (but not at the very end)
			if ((exceedsChars || exceedsSegments) && i < segments.size() - 1) {
				result += currentLine + "/\n";
				currentLine = segments[i]; // Start new line without leading slash
				segCount = 1;
			} else {
				currentLine += segmentToAdd;
				segCount++;
			}
		}

		// Add remaining content
		if (!currentLine.empty()) {
			result += currentLine;
		}

		return result;
	}
};
