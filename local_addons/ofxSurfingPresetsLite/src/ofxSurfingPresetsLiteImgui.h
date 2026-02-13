#pragma once
#include "ofMain.h"

/*

TODO
	add kit selector and naming
	add custom names ?
*/

//--

#include "ofxSurfingPresetsLite.h"

#include "ofxSurfingImGui.h"

#define SURFING__OFX_PRESETS_LITE__USING__IM_GUI

//----

class SurfingPresetsLiteImGui : public SurfingPresetsLite {
protected:
	void destructUI() override {
		ofLogNotice("SurfingPresetsLiteImGui") << "destructUI()";

		delete ui;
		ui = nullptr;
	}

private:
	ofxSurfingGui * ui = nullptr;

public:
	void setUiPtr(ofxSurfingGui * _ui) {
		ui = _ui;

		//setupParametersExtra();
	}

	void setupParameters() override {
		ofLogNotice("SurfingPresetsLiteImGui") << "setupParameters()";

		//indexName.setSerializable(false);
		paramsKit.setSerializable(false);

		paramsBrowse.add(index);
		paramsBrowse.add(vNext);
		paramsBrowse.add(vPrevious);

		paramsManager.add(vSave);
		paramsManager.add(vLoad);
		paramsManager.add(vNew);
		paramsManager.add(vDelete);
		paramsManager.add(vRandom);
		paramsManager.add(vReset);
		paramsManager.add(bAutoSave);

		paramsKit.add(vScanKit);
		paramsKit.add(vClearKit);
		paramsKit.add(vPopulateKit);
		paramsKit.add(vPopulateRandomKit);

		paramsInternal.add(bGuiParams);
		paramsInternal.add(bGuiClicker);
		paramsInternal.add(bGuiFloating);
		paramsInternal.add(bGuiExpand);
		paramsInternal.add(numPresetsForPopulating);
		paramsInternal.add(numColumnsPerRow);
		paramsInternal.add(bFlip);
		paramsInternal.add(bCycled);
		paramsInternal.add(bGuiColorized);
		paramsInternal.add(bMinimalMode);
		paramsInternal.add(bGui);

		parameters.add(paramsBrowse);
		parameters.add(paramsManager);
		parameters.add(paramsKit);
		parameters.add(paramsInternal);
		parameters.add(bHelp);
		parameters.add(bKeys);

		setupParametersExtra();
	}

	void setupParametersExtra() override {
		ofLogNotice("SurfingPresetsLiteImGui") << "setupParametersExtra()";

		e_guiNumColumnsPerRow = numColumnsPerRow.newListener([this](int & i) {
			buildColorizer();
		});

		e_bGuiColorized = bGuiColorized.newListener([this](bool & b) {
			buildColorizer();
		});

		buildColorizer();
	}

	void buildColorizer() {
		ofLogNotice("SurfingPresetsLiteImGui") << "buildColorizer()";

		// For colorize buttons on matrix preset colors
		if (bGuiColorized) {

			int numRows = 1;
			int numPresets = getNumPresets();
			if (numPresets > 1)
				numRows = numPresets / numColumnsPerRow;

			colors.clear();

			for (size_t i = 0; i < numPresets; i++) {
				// Calculate the row number
				int row = i / numColumnsPerRow;
				// Use the row number to index into colors_
				ofColor c = colors_[row % colors_.size()];
				colors.push_back(c);
			}
		}
	}

	void doLoadNextRow() override {
		ofLogNotice("SurfingPresetsLiteImGui") << "doLoadNextRow()";

		if (index > index.getMax() - numColumnsPerRow) return;
		int i = index;
		i = i + numColumnsPerRow;
		if (bCycled)
			if (i > index.getMax()) i = index.getMin() + i;
		index = ofClamp(i, index.getMin(), index.getMax());
	}

	void doLoadPreviousRow() override {
		ofLogNotice("SurfingPresetsLiteImGui") << "doLoadPreviousRow()";

		if (index < numColumnsPerRow) return;
		int i = index;
		i = i - numColumnsPerRow;
		if (bCycled)
			if (i < index.getMin()) i = index.getMax() - i;
		index = ofClamp(i, index.getMin(), index.getMax());
	}

	//----

	// Draw UI
	// main draw will all nodes/windows combined.
	// you could use more specialized window,
	// like for example only the preset clicker,
	// while editing the preset parameters into their own UI.
	void drawGui() {
		if (!bGui) return;
		drawHelp();

		if (ui == nullptr) return;
		//TODO: fix multi instance
		//ui->Begin();

		if (bMinimalMode) {
			drawImGuiMinimal();
			return;
		}

		if (bGuiParams) drawImGuiParameters();
		if (bGuiFloating) drawImGuiManager(true);

		//ui->End();
	}

	//----

	// Presets clicker with different layout/styles:
	// - windowed
	// - foldered
	// - only widgets to insert in other windows
	// - minimal required widgets
	//TODO: need fixing some combinations..
	void drawImGuiClicker(bool bWindowed = false, bool bMinimal = false) {

		bool bOpen_ = true;
		if (bWindowed) {
			bOpen_ = ui->BeginWindow(bGui);
		}

		//--

		if (bOpen_) {
			if (!bMinimal) {
				if (ui->isMaximized()) {
					ui->Add(bGuiClicker, OFX_IM_TOGGLE_BUTTON_ROUNDED_MINI);
					//ui->Add(bGuiClickerMini, OFX_IM_TOGGLE_ROUNDED_MINI_XS);
					ui->AddSpacing();
				}
			} else {
				if (!bGuiClicker) bGuiClicker = true;
			}

			if (bGuiClicker) {
				if (ui->isMinimized() && !bMinimal) ui->AddSpacingSeparated();

				float _h2 = ui->getWidgetsHeightUnit();
				_h2 *= 1.5f;

				bool bResponsiveButtonsClicker = true;

				string sTip = "";
				if (bModKeyControl)
					sTip = "Copy to...";
				else if (bModKeyAlt)
					sTip = "Swap between..";
				else if (bHelp)
					sTip = "Press Ctrl/Alt\nto copy/swap";

				if (bGuiColorized) {
					ofxImGuiSurfing::AddMatrixClickerLabels(index, keyCommandsChars, colors, bResponsiveButtonsClicker,
						numColumnsPerRow, true, _h2, sTip, bFlip);
				} else {
					ofxImGuiSurfing::AddMatrixClickerLabels(index, keyCommandsChars, bResponsiveButtonsClicker,
						numColumnsPerRow, true, _h2, sTip, bFlip);
				}
			}

			if (bGuiExpand) {
				if (index.getMax() > -1) {
					if (!bMinimal && ui->isMaximized()) {
						//ui->AddSpacing();
						ui->AddSpacingSeparated();

						ui->Add(ui->bAdvanced, OFX_IM_TOGGLE_ROUNDED_MINI);
						if (ui->bAdvanced) {
							ui->AddSpacing();
							ui->AddLabel(numColumnsPerRow.getName());
							ui->Add(numColumnsPerRow, OFX_IM_STEPPER_NO_LABEL);
							ui->AddTooltip("Buttons per row.");
							ui->AddLabel(numPresetsForPopulating.getName());
							ui->Add(numPresetsForPopulating, OFX_IM_STEPPER_NO_LABEL);
							ui->AddTooltip("Amount populating presets.");
							ui->Add(bFlip);
							ui->Add(bCycled);
							ui->Add(bGuiColorized);
							ui->Add(bMinimalMode);
							//ui->AddToggle("Foldered", bFoldered, OFX_IM_CHECKBOX);
							ui->Add(bKeys);
							ui->Add(bHelp);
						}
					}
				}
			}
		}

		//--

		if (bWindowed) {
			if (bOpen_) {
				ui->EndWindow();
			}
		}
	}

	//----

	// Parameters for the preseted group
	void drawImGuiParameters() {
#if 1
		string n = "PARAMETERS " + name;
		if (ui->BeginWindow(n))
#else
		if (ui->BeginWindow(bGuiParams))
#endif
		{
			ui->Add(ui->bMinimize, OFX_IM_TOGGLE_ROUNDED_SMALL);
			ui->Add(bGuiFloating, OFX_IM_TOGGLE_ROUNDED_MINI);

			ui->AddSpacingSeparated();

			if (!bGuiFloating && ui->isMaximized())
				ui->AddLabelBig("Parameters");
			ui->AddSpacing();

			ui->AddGroup(paramsPreset);

			// Integrated inside another panel
			if (!bGuiFloating) {
				ui->AddSpacingBigSeparated();

				drawImGuiManager();
			}

			ui->EndWindow();
		}
	}

	//----

#if 1
	// test bFoldered_
	// Some windows panels also combined
	void drawImGuiManager(bool bWindowed = false, bool bMinimized_ = false, bool bFoldered_ = false, bool bOpen = true) {
		if (!bGui) return;

		string sTip = "";

		bool bOpen_ = true;
		if (bWindowed) {
			IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_SMALL_LOCKED_RESIZE;
			bOpen_ = ui->BeginWindow(bGui);
		} else if (bFoldered_) {
			bOpen_ = true;
		}

		if (bOpen_) {
			string s = fileBaseName;
			string sn = "Presets";

			bool b;
			if (!bFoldered_) {
				b = true;
				if (!bWindowed && ui->isMaximized()) ui->AddLabelBig(sn);
			} else {
				b = ui->BeginTree(sn, bOpen);
				if (b) ui->AddSpacing();
			}

			if (bGuiFloating) {
				ui->Add(ui->bMinimize, OFX_IM_TOGGLE_ROUNDED_MINI);
			}
			ui->AddSpacing();

			if (b) {
				if (ui->isMaximized()) {
					if (bGuiFloating) ui->Add(bGuiParams, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui->Add(bGuiExpand, OFX_IM_TOGGLE_ROUNDED_MINI);
					ui->AddSpacing();
				}

				// expanded
				if (bGuiExpand) {
					// maximized
					if (ui->isMaximized()) {
						ui->Add(vLoad, OFX_IM_BUTTON_SMALL, 2, true);
						ui->AddTooltip("Discard changes\nand reload file");
						ui->Add(vSave, (bAutoSave ? OFX_IM_BUTTON_SMALL : OFX_IM_BUTTON_SMALL_BORDER_BLINK), 2);
						ui->AddTooltip("Save changes\nto file");

						ui->Add(bAutoSave, OFX_IM_TOGGLE_SMALL_BORDER_BLINK);
						//ui->Add(vRename, OFX_IM_BUTTON_SMALL, 2, true);
						//ui->AddTooltip("Change file name");
						if (bAutoSave) {
							sTip = "Edit Mode";
						} else {
							sTip = "Manual save Mode";
						}
						ui->AddTooltip(sTip);

	//#if 0
	//					if (!bOverInputText) {
	//						ui->Add(vNew, OFX_IM_BUTTON_SMALL, 2);
	//						if (bModKeyControl) {
	//							sTip = "Release control\nto rename";
	//						} else {
	//							sTip = "Press control\nto create";
	//						}
	//						ui->AddTooltip(sTip);
	//					} else {
	//						if (ui->AddButton("Cancel", OFX_IM_BUTTON_SMALL_BORDER_BLINK, 2)) {
	//							bOverInputText = false;
	//							bDoingNew = false;
	//						}}
	//#else
						ui->Add(vNew, OFX_IM_BUTTON_SMALL, 2);
						if (bModKeyControl) {
							sTip = "Release control\nto rename";
						} else {
							sTip = "Press control\nto create";
						}
						ui->AddTooltip(sTip);
	//#endif

						ui->SameLine();
						ui->Add(vDelete, OFX_IM_BUTTON_SMALL, 2);
						ui->AddTooltip("Remove preset file");

						ui->Add(vReset, OFX_IM_BUTTON_SMALL, 2, true);
						ui->AddTooltip("Preset reset");
						ui->Add(vRandom, OFX_IM_BUTTON_SMALL, 2);
						ui->AddTooltip("Preset random");

						//--

						ui->refreshLayout();
						float _w2 = getWidgetsWidth(2);
						float _h = getWidgetsHeightUnit();

						if (ImGui::Button("Clear", ImVec2(_w2, _h))) {
							ImGui::OpenPopup("CLEAR KIT?");
						}
						ui->AddTooltip("Remove all \nfile presets!");

						if (ImGui::BeginPopupModal("CLEAR KIT?", NULL, ImGuiWindowFlags_AlwaysAutoResize)) {
							ui->AddLabelBig("Presets kit \nwill be erased.", true, true);
							ui->AddSpacing();
							ui->AddLabelBig("This operation \ncannot be undone!", true, true);
							ui->AddSpacingBig();

							static bool dont_ask_me_next_time = false;
							ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(0, 0));
							ImGui::Checkbox("Don't ask me next time", &dont_ask_me_next_time);
							ImGui::PopStyleVar();

							ui->AddSpacing();

							if (!dont_ask_me_next_time) {
								if (ImGui::Button("OK", ImVec2(120, 2 * _h))) {
									ofLogNotice("SurfingPresetsLiteImGui") << "CLEAR";
									doClearKit();
									ImGui::CloseCurrentPopup();
								}
								ImGui::SetItemDefaultFocus();
								ImGui::SameLine();
								if (ImGui::Button("Cancel", ImVec2(120, 2 * _h))) {
									ImGui::CloseCurrentPopup();
								}
							} else {
								ofLogNotice("SurfingPresetsLiteImGui") << "CLEAR";
								doClearKit(false);
								ImGui::CloseCurrentPopup();

								//if (bOverInputText) bOverInputText = false;
							}

							ImGui::EndPopup();
						}

						ui->SameLine();
						ui->Add(vScanKit, OFX_IM_BUTTON_SMALL, 2);
						ui->AddTooltip("Reload folder files");

						//if (ui->Add(vPopulateKit, OFX_IM_BUTTON_SMALL, 2)) {
						//	//if (bOverInputText) bOverInputText = false;
						//}
						ui->Add(vPopulateKit, OFX_IM_BUTTON_SMALL, 2);
						ui->AddTooltip("Clear kit and create \n" + ofToString(numPresetsForPopulating) + " new presets copying current");
						ui->SameLine();
						ui->Add(vPopulateRandomKit, OFX_IM_BUTTON_SMALL, 2);
						ui->AddTooltip("Clear kit and populate \n" + ofToString(numPresetsForPopulating) + "new randomized presets ");
					}
				}

				// minimized
				else {
	//#if 0
	//					if (ui->Add(vSave,
	//							(bOverInputText ? OFX_IM_BUTTON_SMALL_BORDER_BLINK : OFX_IM_BUTTON_SMALL), 2, true)) {
	//						bOverInputText = false;
	//						indexName = s;
	//					}

	//					if (!bOverInputText) {
	//						ui->Add(vNew, OFX_IM_BUTTON_SMALL, 2);
	//					} else {
	//						if (ui->AddButton("Cancel", OFX_IM_BUTTON_SMALL_BORDER_BLINK, 2)) {
	//							bOverInputText = false;
	//							bDoingNew = false;
	//						}
	//#else
					ui->Add(vSave, OFX_IM_BUTTON_SMALL, 2, true);
					ui->Add(vNew, OFX_IM_BUTTON_SMALL, 2);
	//#endif
				}
			}

			//--

	//#if 0
	//	if (bOverInputText) {

	//				if (ui->isMaximized()) ui->AddSpacing();
	//				//TODO: use string params
	//				int _w = ui->getWidgetsWidth() * 0.9f;
	//				ImGui::PushItemWidth(_w);
	//				{
	//					bool b = ImGui::InputText("##NAME", &s);
	//					if (b) {
	//						ofLogNotice("SurfingPresetsLiteImGui") << "InputText:" << s.c_str();
	//						setFileBaseName(s);
	//					}
	//					if (ImGui::IsItemDeactivated() && ImGui::IsKeyPressed(ImGui::GetKeyIndex(ImGuiKey_Escape)))
	//						bOverInputText = false;
	//				}
	//				ImGui::PopItemWidth();
	//	}
	//#endif
			if (ui->bMinimize && !bGuiExpand) {
				ui->PushButtonRepeat();
				ui->Add(vPrevious, OFX_IM_BUTTON_MEDIUM, 2, true);
				ui->Add(vNext, OFX_IM_BUTTON_MEDIUM, 2);
				ui->PopButtonRepeat();
			}

			//--

			if (ui->isMaximized() && index.getMax() > -1) ui->AddSpacingSeparated();

			if (bGuiExpand) // expanded
			{
				ui->PushButtonRepeat();
				ui->Add(vPrevious, OFX_IM_BUTTON_MEDIUM, 2, true);
				ui->Add(vNext, OFX_IM_BUTTON_MEDIUM, 2);
				ui->PopButtonRepeat();
				ui->AddCombo(index, fileBaseNames);
			}

			else { // not expanded
				if (ui->isMaximized()) {
					ui->PushButtonRepeat();
					ui->Add(vPrevious, OFX_IM_BUTTON_MEDIUM, 2, true);
					ui->Add(vNext, OFX_IM_BUTTON_MEDIUM, 2);
					ui->PopButtonRepeat();
					ui->AddCombo(index, fileBaseNames);

					ui->Add(vLoad, OFX_IM_BUTTON_SMALL, 2, true);
					ui->Add(vSave, (bAutoSave ? OFX_IM_BUTTON_SMALL : OFX_IM_BUTTON_SMALL_BORDER_BLINK), 2);
				}
			}

			//--

			if (ui->isMaximized()) ui->AddSpacingSeparated();

			//--

			drawImGuiClicker();

			//--

			if (b && bFoldered_) ui->EndTree();
		}

		if (bWindowed && bOpen_) {
			ui->EndWindow();
		}
	}
#else
	void drawImGuiManager(bool b = 0) {};
#endif

	//----

	// Minimal mode. Requires to not use the other drawGui/ImGui modes
	// to avoid collide or re group windows!
	void drawImGuiMinimal(bool bWindowed = true) {
		if (bWindowed) IMGUI_SUGAR__WINDOWS_CONSTRAINTSW_LOCKED_RESIZE;
		//TODO: must fix this imgui bug...

		if (ui->isMinimized()) {
			bool bOpen = true;

			if (bWindowed) {
				bOpen = ui->BeginWindow(bGui);
			}

			if (bOpen) {
				ui->refreshLayout();
				ui->PushButtonRepeat();
				ui->Add(vPrevious, OFX_IM_BUTTON_MEDIUM, 2, true);
				ui->Add(vNext, OFX_IM_BUTTON_MEDIUM, 2);
				ui->PopButtonRepeat();
				ui->AddCombo(index, fileBaseNames);
			}

			if (bWindowed && bOpen) {
				ui->EndWindow();
			}
		} else {
			drawImGuiClicker(bWindowed, true);
		}
	}

	//----

protected:
	vector<ofColor> colors;

	// Colors for each row.
	vector<ofColor> colors_ { ofColor::green, ofColor::yellow, ofColor::red,
		ofColor::blue, ofColor::orange, ofColor::yellowGreen,
		ofColor::indianRed, ofColor::lightGreen, ofColor::violet,
		ofColor::blueViolet, ofColor::aliceBlue }; //TODO last color not applied..
	// For example: 3 columns of 11 rows for 33 presets
	// each row will have not repeated colors.

	ofParameter<bool> bGuiColorized { "Colorized", false };
	//enable to colorize per 3 rows: green, yellow, red.

	ofParameter<int> numColumnsPerRow { "Num columns", 3, 1, 5 };
	//num colors per row for the matrix clicker

	ofParameter<bool> bFlip { "Flip", false };
	ofParameter<bool> bMinimalMode { "Minimal Mode", false };

	//bool bFoldered = 0;//TODO

public:
	void setMinimalMode(bool b = true) {
		bMinimalMode = b;
	}
	void setToggleMinimalMode() {
		bMinimalMode = !bMinimalMode;
	}

protected:
	ofEventListener e_guiNumColumnsPerRow;
	ofEventListener e_bGuiColorized;
};
