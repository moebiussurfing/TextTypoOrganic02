#pragma once
#include "ofMain.h"

#include "ofxGui.h"
#include "ofxSurfingSerializers.h" // Settings

/*
* ofxGui
* 
	ofxGui Helpers
*/

//------

// CONSTANTS

#define SURFING__OFXGUI__PAD_BETWEEN_PANELS 4
#define SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS 8

//--

// ofxGui

// Default font and sizes/colors will be used to customize ofxGui!
#define SURFING__OFXGUI__FONT_DEFAULT_SIZE 9
#define SURFING__OFXGUI__FONT_DEFAULT_SIZE_MINI 6
#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/NotoSansMono-Regular.ttf"

// testing alternatives
//#define SURFING__OFXGUI__FONT_DEFAULT_SIZE_MINI 7
//#define SURFING__OFXGUI__FONT_DEFAULT_SIZE 10
//#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/Montserrat-Regular.ttf"
//#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/Inter-Regular.ttf"
//#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/JetBrainsMonoNL-ExtraBold.ttf"
//#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/JetBrainsMonoNL-SemiBold.ttf"
//#define SURFING__OFXGUI__FONT_DEFAULT_PATH "assets/fonts/JetBrainsMono-Bold.ttf"

//----

namespace ofxSurfing {

enum SURFING_LAYOUT {
	SURFING_LAYOUT_TOP_LEFT = 0,
	SURFING_LAYOUT_TOP_CENTER,
	SURFING_LAYOUT_TOP_RIGHT,

	SURFING_LAYOUT_CENTER_LEFT,
	SURFING_LAYOUT_CENTER,
	SURFING_LAYOUT_CENTER_RIGHT,

	SURFING_LAYOUT_BOTTOM_LEFT,
	SURFING_LAYOUT_BOTTOM_CENTER,
	SURFING_LAYOUT_BOTTOM_RIGHT,

//--

#ifdef SURFING__STRING_BOX__INCLUDE_EXTRA_LAYOUTS
	SURFING_LAYOUT_MOUSE_POS,
	SURFING_LAYOUT_MOUSE_POS_CENTER,
#endif

	SURFING_LAYOUT_AMOUNT
};

//------

/*
	SURFING_LAYOUT_TOP_LEFT = 0,
	SURFING_LAYOUT_TOP_CENTER,
	SURFING_LAYOUT_TOP_RIGHT,

	SURFING_LAYOUT_CENTER_LEFT,
	SURFING_LAYOUT_CENTER,
	SURFING_LAYOUT_CENTER_RIGHT,

	SURFING_LAYOUT_BOTTOM_LEFT,
	SURFING_LAYOUT_BOTTOM_CENTER,
	SURFING_LAYOUT_BOTTOM_RIGHT,
*/

//--------------------------------------------------------------
inline void setGuiPositionToLayout(ofxPanel & gui, int layout /* = 0*/) {

	// Move gui panel window to:
	glm::vec2 p;
	int pad = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS; // to borders

	// top-left
	if (layout == SURFING_LAYOUT_TOP_LEFT) {
		int x = pad;
		int y = pad;
		p = glm::vec2(x, y);
	}
	// top-center
	else if (layout == SURFING_LAYOUT_TOP_CENTER) {
		int x = ofGetWindowWidth() / 2 - gui.getShape().getWidth() / 2;
		int y = pad;
		p = glm::vec2(x, y);
	}
	// top-right
	else if (layout == SURFING_LAYOUT_TOP_RIGHT) {
		int x = ofGetWindowWidth() - gui.getShape().getWidth() - pad;
		int y = pad;
		p = glm::vec2(x, y);
	}

	// center-left
	else if (layout == SURFING_LAYOUT_CENTER_LEFT) {
		int x = pad;
		int y = ofGetWindowHeight() / 2 - gui.getShape().getHeight() / 2;
		p = glm::vec2(x, y);
	}
	// center-center
	else if (layout == SURFING_LAYOUT_CENTER) {
		int x = ofGetWindowWidth() / 2 - gui.getShape().getWidth() / 2;
		int y = ofGetWindowHeight() / 2 - gui.getShape().getHeight() / 2;
		p = glm::vec2(x, y);
	}
	// center-right
	else if (layout == SURFING_LAYOUT_CENTER_RIGHT) {
		int x = ofGetWindowWidth() - gui.getShape().getWidth() - pad;
		int y = ofGetWindowHeight() / 2 - gui.getShape().getHeight() / 2;
		p = glm::vec2(x, y);
	}

	// bottom-left
	else if (layout == SURFING_LAYOUT_BOTTOM_LEFT) {
		int x = pad;
		int y = ofGetWindowHeight() - gui.getShape().getHeight() - pad;
		p = glm::vec2(x, y);
	}
	// bottom-center
	else if (layout == SURFING_LAYOUT_BOTTOM_CENTER) {
		int x = ofGetWindowWidth() / 2 - gui.getShape().getWidth() / 2;
		int y = ofGetWindowHeight() - gui.getShape().getHeight() - pad;
		p = glm::vec2(x, y);
	}
	// bottom-right
	else if (layout == SURFING_LAYOUT_BOTTOM_RIGHT) {
		int x = ofGetWindowWidth() - gui.getShape().getWidth() - pad;
		int y = ofGetWindowHeight() - gui.getShape().getHeight() - pad;
		p = glm::vec2(x, y);
	}

	else {
		int x = pad;
		int y = pad;
		p = glm::vec2(x, y);
	}

	gui.setPosition(p.x, p.y);
}

//--------------------------------------------------------------
inline void setGuiPositionToLayout(ofxPanel & gui, SURFING_LAYOUT layout) {
	setGuiPositionToLayout(gui, (int)layout);
}

// Set position of guiAnchor at the window bottom and centered
// (gui2 must be externally linked to guiAnchor with the correct padding).
//TODO: other layouts
//--------------------------------------------------------------
inline void setGuiPositionToLayoutBoth(ofxPanel & gui1, ofxPanel & gui2, SURFING_LAYOUT layout = SURFING_LAYOUT_BOTTOM_CENTER, bool bDoubleSpace = false) {
	//TODO: ADD OTHER LAYOUTS

	float d = float(SURFING__OFXGUI__PAD_BETWEEN_PANELS);
	if (bDoubleSpace) d *= 2;

	if (layout == SURFING_LAYOUT_BOTTOM_CENTER) { // both bottom-center
		int gw = gui1.getShape().getWidth() + gui2.getShape().getWidth() + d;
		int gh = std::max(gui1.getShape().getHeight(), gui2.getShape().getHeight());
		gh += SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
		int x = ofGetWidth() / 2 - gw / 2;
		int y = ofGetHeight() - gh;
		y = std::max(y, 0);
		gui1.setPosition(x, y);
	}

	else if (layout == SURFING_LAYOUT_TOP_CENTER) { // both top-center
		int gw = gui1.getShape().getWidth() + gui2.getShape().getWidth() + d;
		int x = ofGetWidth() / 2 - gw / 2;
		int y = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
		y = std::max(y, 0);
		gui1.setPosition(x, y);
	}

	else {
		ofLogWarning("SurfingOfxGuiPanelsManager") << "Layout not implemented for setGuiPositionToLayoutBoth(" + ofToString(layout) + ")";
	}
}

//--------------------------------------------------------------
inline void setGuiPositionToLayoutPanelsCentered(ofxPanel & guiAnchor, size_t amount, SURFING_LAYOUT layout) {
	//TODO: add other layouts?
	// to be used for a landscape layout
	// each panel right to the previous.

	//SURFING_LAYOUT_BOTTOM_CENTER
	//SURFING_LAYOUT_TOP_CENTER

	float d = float(SURFING__OFXGUI__PAD_BETWEEN_PANELS);

	float w = guiAnchor.getWidth();
	float h = guiAnchor.getHeight();

	float x;
	float y;

	x = ofGetWidth() / 2 - (w * amount + d) / 2 - d;

	if (layout == SURFING_LAYOUT_BOTTOM_CENTER) { // bottom-center
		y = ofGetHeight() - (h + SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS);
	}

	else if (layout == SURFING_LAYOUT_TOP_CENTER) { // top-center
		y = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
	}

	else {
		ofLogWarning("ofxSurfing") << "Layout not implemented for setGuiPositionToLayoutPanelsCentered(" + ofToString(layout) + ")";

		x = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
		y = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS;
	}

	guiAnchor.setPosition(x, y);
}

//--------------------------------------------------------------
inline void setGuiPositionRightTo(ofxPanel & guiTarget, ofxPanel & guiAnchor, bool bDoubleSpace = false) {
	auto bb = guiAnchor.getShape();
	float d = float(SURFING__OFXGUI__PAD_BETWEEN_PANELS);
	if (bDoubleSpace) d *= 2;
	auto p = bb.getTopRight() + glm::vec3{d, 0, 0};
	guiTarget.setPosition(glm::vec3(p));
}
//--------------------------------------------------------------
inline void setGuiPositionBelowTo(ofxPanel & guiTarget, ofxPanel & guiAnchor, bool bDoubleSpace = false) {
	auto bb = guiAnchor.getShape();
	float d = float(SURFING__OFXGUI__PAD_BETWEEN_PANELS);
	if (bDoubleSpace) d *= 2;
	auto p = bb.getBottomLeft() + glm::vec3 { 0, d, 0 };
	guiTarget.setPosition(p);
}

//--------------------------------------------------------------
inline void setOfxGuiTheme(bool bMini = 0, std::string pathFont = "") {

	bool bDebugDefault = 0;

	bool bColors = 1;
	bool bSizes = 1;

	bool bFont = 1;
	int size = bMini ? SURFING__OFXGUI__FONT_DEFAULT_SIZE_MINI : SURFING__OFXGUI__FONT_DEFAULT_SIZE;

	if (pathFont == "") pathFont = SURFING__OFXGUI__FONT_DEFAULT_PATH;

	if (bFont) {
		ofFile file(pathFont);
		bool b = file.exists();
		if (b) {
			ofxGuiSetFont(pathFont, size);
		} else {
			ofLogError("ofxSurfing") << "Font file " + pathFont + " not found!";
			ofLogError("ofxSurfing") << "Unable to customize the ofxGui theme font.";
		}
	}

	if (bColors) {
		ofColor cHeadBg;
		ofColor cBg;
		ofColor cBorder;
		ofColor cText;
		ofColor cFill;

#if bDebugDefault
		//Default
		/*
		ofxBaseGui::headerBackgroundColor(80),
		ofxBaseGui::backgroundColor(0),
		ofxBaseGui::borderColor(120, 100),
		ofxBaseGui::textColor(255),
		ofxBaseGui::fillColor(128);
		*/
		cHeadBg = ofColor(80);
		cBg = ofColor(0);
		cBorder = ofColor(120, 100);
		cText = ofColor(255);
		cFill = ofColor(128);
#else
	//TODO
	#if 0
		//Default
		cHeadBg = ofColor(80);
		cBg = ofColor(0);
		cBorder = ofColor(120, 100);
		cText = ofColor(255);
		cFill = ofColor(128);
	#else
		cHeadBg = ofColor(70);
		//cHeadBg = ofColor(80);
		cBg = ofColor(50, 210);
		cBorder = ofColor(120, 100);
		cText = ofColor(255);
		cFill = ofColor(100, 210);
			//cFill = ofColor(120, 210);
	#endif
#endif
		ofxGuiSetHeaderColor(cHeadBg);
		ofxGuiSetBackgroundColor(cBg);
		ofxGuiSetBorderColor(cBorder);
		ofxGuiSetFillColor(cFill);
		ofxGuiSetTextColor(cText);
	}

	if (bSizes) {
		int textPadding;
		int defaultWidth;
		int defaultHeight;

#if bDebugDefault
		// Default
		/*
		int ofxBaseGui::defaultWidth = 200;
		int ofxBaseGui::textPadding = 4;
		int ofxBaseGui::defaultHeight = 18;
		*/
		defaultWidth = 200;
		textPadding = 4;
		defaultHeight = 18;
#else
		if (bMini) {
			defaultWidth = 150;
			textPadding = 4;
			defaultHeight = 14;
			//textPadding = 6;
			//defaultHeight = 17;
		} else {
			defaultWidth = 200;
			textPadding = 6;
			defaultHeight = 18;
		}
#endif
		ofxGuiSetTextPadding(textPadding);
		ofxGuiSetDefaultWidth(defaultWidth);
		ofxGuiSetDefaultHeight(defaultHeight);
	}
}
};

//----

/*
	SurfingOfxGuiPanelsManager class

	Layout and group ofxPanel panels.
	
	This class stores the ofxPanel position for the main anchor panel.
	First panel added is used as anchor.
	but also queues many other added ofxPanels. 
	it will create or allows passing their visible toggles (bGui),
	It will auto handle their minimized state.
	There are two layouts too: centered top and bottom.
	to link and to set the position for the others linked.
	Default mode is SURFING__OFXGUI__MODE_FULL, 
	but we can only draw without forcing the panel position,
	or only settings position without drawing etc..
*/


/*
	TODO
	create a main gui? 
		to avoid add toggles 
		to first/anchor added gui?
	allow add/chain many guiManager`s
	add solo`s
	add keys F1-F2-F3 etc
		bKeys
	add ofRectangles/shape to measure text boxes too...?
	check other ofxGui related addons
*/

//--

/*

SIMPLE EXAMPLE:

ofxPanel gui1;
ofxPanel gui2;
ofxPanel gui3;
SurfingOfxGuiPanelsManager guiManager;
	
void setup() {
	gui1.setup(params1);
	gui2.setup(params2);
	gui2.setup(params3);

	guiManager.setup(&gui1);
	guiManager.add(&gui1);
	guiManager.add(&gui2);
	guiManager.add(&gui3);
}

void draw() {
	guiManager.draw();
}

*/

//----

#define SURFING__GUI_MANAGER__DEBUG 0
#define SURFING__GUI_MANAGER__FORCE_REFRESH_GUI 1

namespace ofxSurfing {
enum SURFING__OFXGUI__MODE {
	SURFING__OFXGUI__MODE_FULL = 1 << 0, // 1
	SURFING__OFXGUI__MODE_DRAW = 1 << 1, // 2
	SURFING__OFXGUI__MODE_POSITION = 1 << 2, // 4
	SURFING__OFXGUI__MODE_OF_RECTANGLE = 1 << 3, // 8//TODO: to handle text boxes and other windows
	SURFING__OFXGUI__MODE_AMOUNT
};

enum SURFING__OFXGUI__LAYOUT_ALIGN {
	SURFING__OFXGUI__LAYOUT_ALIGN_HORIZONTAL = 0,
	SURFING__OFXGUI__LAYOUT_ALIGN_VERTICAL
};
}

//--------------------------------------------------------------
class SurfingOfxGuiPanelsManager {
public:
	SurfingOfxGuiPanelsManager() {
		name = "";
		path = "";
#if 1
		//ofxGui_3D_TEXT.json
		filenamePreffix = "ofxGui_";
		filenameSuffix = ".json";
#else
		//3D_TEXT_ofxGui.json
		filenamePreffix = "";
		filenameSuffix = "_ofxGui.json";
#endif

		paramsGuiManager.add(bAutoLayout);
		paramsGuiManager.add(indexAlign);
		paramsGuiManager.add(nameAlign);
		paramsGuiManager.add(indexLayout);
		paramsGuiManager.add(nameLayout);

		listenerIndexAlign = indexAlign.newListener([this](int & i) {
			switch (i) {
			case 0:
				nameAlign.set("HORIZONTAL");
				break;
			case 1:
				nameAlign.set("VERTICAL");
				break;
			default:
				nameAlign.set("NONE");
				break;
			}

#if (SURFING__GUI_MANAGER__FORCE_REFRESH_GUI == 0)
			refreshGui();
#endif
		});

		listenerIndexLayout = indexLayout.newListener([this](int & i) {
			switch (i) {
			case 0:
				nameLayout.set("A"); //bottom when horizontal
				break;
			case 1:
				nameLayout.set("B"); //top when horizontal
				break;
			default:
				nameLayout.set("NONE");
				break;
			}

#if (SURFING__GUI_MANAGER__FORCE_REFRESH_GUI == 0)
			refreshGui();
#endif
		});

		indexAlign.set(0);
		indexLayout.set(0);

		bDoneStartup = false;
	}

	~SurfingOfxGuiPanelsManager() {
		exit(); //TODO: kind of bad practice saving on exit..
	}

private:
	ofxPanel * guiAnchorPtr; //act as anchor main panel (left)

	//TODO: could make a data struct..?
	vector<ofxPanel *> guis;
	vector<ofParameter<bool>> bGuis;
	ofParameterGroup paramsTogglesUI { "UI" };
	ofParameterGroup paramsTogglesSettings { "UI" };
	vector<ofParameter<bool>> bMinimizeds;
	ofParameterGroup paramsMinimizeds { "Minimizeds" };
	vector<ofxSurfing::SURFING__OFXGUI__MODE> modes;
	ofParameterGroup parameters { "GuiManager" };

private:
	ofParameter<glm::vec2> position { "Position",
		glm::vec2(SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS, SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS),
		glm::vec2(0, 0),
		glm::vec2(3840, 2160) }; //4k

public:
	ofParameterGroup paramsGuiManager { "GuiManager" };

public:
	ofParameter<bool> bAutoLayout { "AutoLayout", false };
	ofParameter<int> indexAlign { "Align", 0, 0, 1 };
	ofParameter<string> nameAlign { "Mode", "NONE" };
	ofParameter<int> indexLayout { "Layout", 0, 0, 1 };
	ofParameter<string> nameLayout { "Name", "NONE" };

	// Horizontal
	// A bottom
	// B top
	// Vertical
	// A left
	// B right

private:
	ofEventListener listenerIndexLayout;
	ofEventListener listenerIndexAlign;

	bool bAutoAddInternalParamasToMainPanel = true;
	bool bAutoHideFirstToggleVisibleForAnchorPanel = true;

public:
	void setAutoAddInternalParamasToMainPanel(bool b) {
		bAutoAddInternalParamasToMainPanel = b;
	}
	void setAutoHideFirstToggleVisibleForAnchorPanel(bool b) {
		bAutoHideFirstToggleVisibleForAnchorPanel = b;
	}

private:
	string name;
	string path;
	string filenameSuffix;
	string filenamePreffix;
	bool bDoneStartup;

public:
	void setup(ofxPanel * guiAnchorPtr_) {
		guiAnchorPtr = guiAnchorPtr_;
		name = guiAnchorPtr->getName();

		ofLogNotice("SurfingOfxGuiPanelsManager") << "setup(" << name << ")";

		path = filenamePreffix + name + filenameSuffix;

		parameters.setName(name);
		parameters.add(position);
		parameters.add(bAutoLayout);
		parameters.add(indexLayout);
		parameters.add(nameLayout);
		parameters.add(indexAlign);
		parameters.add(nameAlign);

		nameAlign.setSerializable(false);
		nameLayout.setSerializable(false);
	}

	//--

	void add(ofxPanel * g, ofParameter<bool> & b, ofxSurfing::SURFING__OFXGUI__MODE mode) {
		bGuis.emplace_back(b);

		guis.push_back(g);
		modes.push_back(mode);

		ofParameter<bool> bm;
		bm.set(g->getName() + "_minimized", false);
		bMinimizeds.push_back(bm);
	}

	void add(ofxPanel * g, ofParameter<bool> & b) {
		bGuis.emplace_back(b);

		guis.push_back(g);
		modes.push_back(ofxSurfing::SURFING__OFXGUI__MODE_FULL);

		ofParameter<bool> bm;
		bm.set(g->getName() + "_minimized", false);
		bMinimizeds.push_back(bm);
	}

	void add(ofxPanel * g, ofxSurfing::SURFING__OFXGUI__MODE mode) {
		ofParameter<bool> b;
		string n = "";
		n += "UI ";
		n += g->getName();
		b.set(n, true);
		bGuis.emplace_back(b);

		guis.push_back(g);
		modes.push_back(ofxSurfing::SURFING__OFXGUI__MODE_FULL);

		ofParameter<bool> bm;
		bm.set(g->getName() + "_minimized", false);
		bMinimizeds.push_back(bm);
	}

	void add(ofxPanel * g) {
		ofParameter<bool> b;
		string n = "";
		n += "UI ";
		n += g->getName();
		b.set(n, true);
		bGuis.emplace_back(b);

		guis.push_back(g);
		modes.push_back(ofxSurfing::SURFING__OFXGUI__MODE_FULL);

		ofParameter<bool> bm;
		bm.set(g->getName() + "_minimized", false);
		bMinimizeds.push_back(bm);
	}

	//--

	void startup(bool bSkipSettings = false) { //pass true to load default settings!
		ofLogNotice("SurfingOfxGuiPanelsManager") << "startup()";

		//--

		//don't add anchor main toggle!
		for (size_t i = 0; i < bGuis.size(); i++) {
			paramsTogglesSettings.add(bGuis[i]);
			if (i == 0 && bAutoHideFirstToggleVisibleForAnchorPanel) continue;

			paramsTogglesUI.add(bGuis[i]);
			ofLogNotice("SurfingOfxGuiPanelsManager") << "add bGui: " << bGuis[i].getName() << " " << (bGuis[i].get() ? "True" : "False");
		}

		for (size_t i = 0; i < bMinimizeds.size(); i++) {
			paramsMinimizeds.add(bMinimizeds[i]);
			ofLogNotice("SurfingOfxGuiPanelsManager") << "added minimized state for:" << guis[i]->getName();
		}

		//--

		//add to groups
		paramsTogglesUI.add(paramsGuiManager);

		if (bAutoAddInternalParamasToMainPanel) {
			guis[0]->add(paramsTogglesUI);

			//minimize some groups
			//guis[0]->getGroup(paramsTogglesUI.getName()).minimize();//workflow
			// useful when not using/exposed external bGui. So using auto populated/internal bGui's!

			guis[0]->getGroup(paramsTogglesUI.getName()).getGroup(paramsGuiManager.getName()).minimize();
		}

		//--

		//for the settings only
		parameters.add(paramsTogglesSettings);
		parameters.add(paramsMinimizeds);

		//--

		if (!bSkipSettings) load();

		//--

		bDoneStartup = true;
	}

	void refreshGui() {
		if (guiAnchorPtr == nullptr) return;
		if (bGuis.size() == 0) return;

		if (bAutoLayout) {
			//force anchor panel position

			int x = 0;
			int y = 0;
			int pad = SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS; //to borders
			float wPanel = guis[0]->getWidth();

			if (indexAlign == 0) //horizontal
			{
#if 0
				int count = guis.size();//count all
#else
				int count = 0; //count visible panels to center correctly
				for (size_t i = 0; i < bGuis.size(); i++) {
					if (bGuis[i]) count++;
				}
#endif

				int w = count * wPanel;
				x = ofGetWidth() / 2 - w / 2;

				//bottom
				if (indexLayout == 0) { //SURFING_LAYOUT_BOTTOM_CENTER
					float hmax = 0;
					for (auto g : guis) {
						if (hmax < g->getHeight()) hmax = g->getHeight();
					}
					y = ofGetHeight() - hmax - pad;
				}
				//top center
				else if (indexLayout == 1) { //SURFING_LAYOUT_TOP_CENTER
					y = pad;
				}
			}

			else if (indexAlign == 1) //vertical
			{
				//top left
				if (indexLayout == 0) {
					x = pad;
					y = pad;
				}

				//right
				else if (indexLayout == 1) {
#if 1
					//top
					x = ofGetWidth() - pad - wPanel;
					y = pad;
#else
					//bottom. fails when any group is minimized or UI hidden...
					float htotal = 0;
					size_t i = 0;
					for (auto g : guis) {
						if (!bGuis[i]) continue;
						//if (g->isMinimized()) {
						//	htotal += g->getShape().getHeight();
						//	//htotal += g->isHeaderEnabled();
						//	continue;
						//}
						//htotal += g->getHeight();
						htotal += g->getShape().getHeight();
						htotal += float(SURFING__OFXGUI__PAD_BETWEEN_PANELS);
						i++;
					}
					y = ofGetHeight() - htotal - pad;
#endif
				}

				else { //default
					x = pad;
					y = pad;
				}
			}

			guis[0]->setPosition(x, y);
		}
	}

	inline void setGuiAnchorPositionToLayout(ofxSurfing::SURFING_LAYOUT layout) {
		if (guiAnchorPtr == nullptr) return;
		if (bGuis.size() == 0) return;

		ofxSurfing::setGuiPositionToLayout(*guis[0], (int)layout);
	}

	const bool getGuiVisible(int i) {
		if (i > bGuis.size() - 1) return false;
		return bGuis[i].get();
	}

	const ofRectangle getShapePanels() { //get a rect that contains all panels shapes
		ofRectangle r;
		if (guiAnchorPtr == nullptr) return r;
		if (bGuis.size() == 0) return r;
		if (!bGuis[0]) return r;

		ofRectangle r0 = guis[0]->getShape();
		r = r0;

		for (size_t i = 1; i < guis.size(); i++) {
			if (!bGuis[i]) continue;
			r = r.getUnion(guis[i]->getShape());
		}

#if (SURFING__GUI_MANAGER__DEBUG == 1)
		ofPushStyle();
		ofSetColor(ofColor::red);
		ofNoFill();
		ofDrawRectangle(r);
		ofPopStyle();

#endif

		return r;
	}

private:
	void update() {
		if (!bDoneStartup) {
			startup();
		}

		if (guiAnchorPtr == nullptr) return;
		if (bGuis.size() == 0) return;
		if (!bGuis[0]) return;

		//clamp
		glm::vec2 p = guiAnchorPtr->getPosition();
		if (p.x < 0) {
			guiAnchorPtr->setPosition(SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS, p.y);
		}
		if (p.y < 0) {
			guiAnchorPtr->setPosition(p.x, SURFING__OFXGUI__PAD_TO_WINDOW_BORDERS);
		}

		// link all panels position to anchor/main panel
		int i_ = 0; // last visible
		for (size_t i = 1; i < guis.size(); i++) {
			if (!bGuis[i]) continue;

			bool b = (modes[i] & ofxSurfing::SURFING__OFXGUI__MODE_FULL) != 0;
			b = b || ((modes[i] & ofxSurfing::SURFING__OFXGUI__MODE_POSITION) != 0);

			if (b) {
				if (indexAlign == 0) //horizontal
					ofxSurfing::setGuiPositionRightTo(*guis[i], *guis[i_]);
				else if (indexAlign == 1) //vertical
					ofxSurfing::setGuiPositionBelowTo(*guis[i], *guis[i_]);
				else //default horizontal
					ofxSurfing::setGuiPositionRightTo(*guis[i], *guis[i_]);
			}
			i_ = i;
		}

		//--

#if (SURFING__GUI_MANAGER__FORCE_REFRESH_GUI == 1)
		//TODO
		//workflow: force layout
		refreshGui();
#endif
	}

public:
	void draw() { //draw all the panels
		if (guiAnchorPtr == nullptr) return;
		if (bGuis.size() == 0) return;
		if (!bGuis[0]) return;

		update();

		for (size_t i = 0; i < guis.size(); i++) {
			if (!bGuis[i]) continue;

			bool b = (modes[i] & ofxSurfing::SURFING__OFXGUI__MODE_FULL) != 0;
			b = b || ((modes[i] & ofxSurfing::SURFING__OFXGUI__MODE_DRAW) != 0);

			if (bGuis[i] && b) guis[i]->draw();
		}

#if (SURFING__GUI_MANAGER__DEBUG == 1)
		ofPushStyle();
		ofNoFill();
		ofSetColor(ofColor::red);
		ofDrawRectangle(getShapePanels());
		ofPopStyle();
#endif
	}

private:
	void exit() {
		ofLogNotice("SurfingOfxGuiPanelsManager") << "exit()";

		if (guiAnchorPtr == nullptr) return;

		save();
	}

	void save() { //save all settings
		ofLogNotice("SurfingOfxGuiPanelsManager") << "save()";

		position.set(guiAnchorPtr->getPosition());

		//get maximize states
		for (size_t i = 0; i < bMinimizeds.size(); i++) {
			bMinimizeds[i] = guis[i]->isMinimized();
		}

		ofxSurfing::save(parameters, path);
	}

	void load() { //load all settings
		ofLogNotice("SurfingOfxGuiPanelsManager") << "load()";

		//load settings
		ofxSurfing::load(parameters, path);

		//apply maximize states
		for (size_t i = 0; i < bMinimizeds.size(); i++) {
			if (bMinimizeds[i]) {
				guis[i]->minimize();
			} else {
				guis[i]->maximize();
			}
			ofLogNotice("SurfingOfxGuiPanelsManager") << guis[i]->getName() << ": " << (bMinimizeds[i].get() ? "minimized" : "maximized");
		}

		//clamp inside the window
		float x = position.get().x;
		float y = position.get().y;
		float xmax = ofGetWidth() - guiAnchorPtr->getWidth();
		float ymax = ofGetHeight() - guiAnchorPtr->getHeight();
		bool b = false;
		if (x > xmax) {
			x = xmax;
			b = true;
		}
		if (y > ymax) {
			y = ymax;
			b = true;
		}
		if (b) position.set(glm::vec2(x, y));

		guiAnchorPtr->setPosition(position.get().x, position.get().y);
	}
};
