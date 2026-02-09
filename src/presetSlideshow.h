#pragma once

#include <functional>

#include "ofMain.h"

class OrganicText;

class PresetSlideshow {
public:
  void setup(OrganicText * organicText, std::function<void()> nextSceneCallback);
  void update(float dt);
  void onSceneAdvanced();
  void triggerNow();
  ofParameterGroup & getParameters();

private:
  bool isReady() const;
  void resetTimer();

  OrganicText * ot_ = nullptr;
  std::function<void()> nextScene_;
  float elapsed_ = 0.0f;
  float lastTriggerTime_ = 0.0f;

  ofParameterGroup params_;
  ofParameter<bool> bEnabled_ { "Slideshow", false };
  ofParameter<float> waitSeconds_ { "Interval (s)", 5.0f, 1.0f, 10.0f };
  ofParameterGroup paramsFeedback_;
  ofParameter<float> feedback_ { "Feedback", 0.1f, 0.0f, 1.0f };
  ofParameter<bool> bWaitTweens_ { "Wait Tweens", true };
  ofParameter<bool> bWaitLineTweaks_ { "Wait LineTweaks", true };
  ofParameter<bool> bPauseTimerWhenBusy_ { "Pause When Busy", true };
  ofParameter<void> vTriggerNow_ { "Trigger Now" };

  ofEventListener eTriggerNow_;
};
