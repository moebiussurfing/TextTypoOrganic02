#include <utility>

#include "presetSlideshow.h"

#include "organicText.h"

void PresetSlideshow::setup(OrganicText * organicText, std::function<void()> nextSceneCallback) {
  ofLogNotice("PresetSlideshow") << "setup()";
  ot_ = organicText;
  nextScene_ = std::move(nextSceneCallback);

  params_.setName("Slideshow");
  params_.add(bEnabled_);
  params_.add(waitSeconds_);
  paramsFeedback_.setName("Feedback");
  paramsFeedback_.add(feedback_);
  params_.add(paramsFeedback_);
  params_.add(bWaitTweens_);
  params_.add(bWaitLineTweaks_);
  params_.add(bPauseTimerWhenBusy_);
  params_.add(vTriggerNow_);

  eTriggerNow_ = vTriggerNow_.newListener([this](const void *) { triggerNow(); });

  resetTimer();
}

void PresetSlideshow::update(float dt) {
  if (!bEnabled_.get()) return;
  if (!nextScene_) return;

  const bool ready = isReady();

  if (!ready && bPauseTimerWhenBusy_) {
    return;
  }

  const float step = (dt > 0.0f) ? dt : ofGetLastFrameTime();
  elapsed_ += step;

  if (elapsed_ >= waitSeconds_.get() && ready) {
    triggerNow();
  }
}

void PresetSlideshow::onSceneAdvanced() {
  resetTimer();
}

void PresetSlideshow::triggerNow() {
  if (!nextScene_) return;
  if (!isReady()) return;

  nextScene_();
  resetTimer();
  lastTriggerTime_ = ofGetElapsedTimef();
}

ofParameterGroup & PresetSlideshow::getParameters() {
  return params_;
}

bool PresetSlideshow::isReady() const {
  bool tweensReady = true;
  bool lineTweaksReady = true;

  if (ot_ != nullptr) {
    if (bWaitTweens_.get()) {
      tweensReady = !ot_->isTweening();
    }
    if (bWaitLineTweaks_.get()) {
      lineTweaksReady = !ot_->isLineTweaksRunning();
    }
  }

  return tweensReady && lineTweaksReady;
}

void PresetSlideshow::resetTimer() {
  elapsed_ = 0.0f;
}
