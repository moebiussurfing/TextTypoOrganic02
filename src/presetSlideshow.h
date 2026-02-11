#pragma once

#include <functional>
#include <string>
#include <vector>

#include "ofMain.h"

class OrganicText;

class PresetSlideshow {
public:
  void setup(OrganicText * organicText, std::function<void()> nextSceneCallback);
  void setMouseIdleChecker(std::function<bool()> fn);
  void update(float dt);
  void onSceneAdvanced();
  void triggerNow();
  void toggle();
  ofParameterGroup & getParameters();
  ofParameterGroup & getFeedbackParameters();
  bool isPresetLocked() const;
  void applyTextFromFileNow();
  ofParameter<bool> bEnabled_ { "Slideshow Play", false };

private:
  bool isReady() const;
  void resetTimer();
  void applyTextFromFile();

  OrganicText * ot_ = nullptr;
  std::function<void()> nextScene_;
  std::function<bool()> isMouseIdle_;
  float elapsed_ = 0.0f;
  float lastTriggerTime_ = 0.0f;

  ofParameterGroup params_;
  ofParameter<float> waitSeconds_ { "Interval (s)", 5.0f, 1.0f, 10.0f };
  ofParameter<bool> bReadFromFile_ { "Read From File", false };
  ofParameter<std::string> textFilePath_ { "Text File", "slideshow.txt" };
  ofParameter<bool> bLockPreset_ { "Lock Preset", false };
  ofParameterGroup paramsFeedback_;
  ofParameter<float> progressFeedback_ { "Progress", 0.0f, 0.0f, 1.0f };
  ofParameter<bool> bUserIdle_ { "User Idle", true };
  ofParameter<bool> bTimerRunning_ { "Timer Running", false };
  ofParameter<bool> bBusyTweens_ { "Busy Tweens", false };
  ofParameter<bool> bBusyLineTweaks_ { "Busy LineTweaks", false };
  ofParameter<bool> bWaitTweens_ { "Wait Tweens", true };
  ofParameter<bool> bWaitLineTweaks_ { "Wait LineTweaks", true };
  ofParameter<bool> bPauseTimerWhenBusy_ { "Pause When Busy", true };
  ofParameter<bool> bWaitUserIdle_ { "Wait User Idle", true };
  ofParameter<void> vTriggerNow_ { "Trigger Now" };

  ofEventListener eTriggerNow_;
  std::size_t currentLineIndex_ = 0;
};
