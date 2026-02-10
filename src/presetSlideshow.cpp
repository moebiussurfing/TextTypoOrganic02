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
  progressFeedback_.setSerializable(false);
  bUserIdle_.setSerializable(false);
  bTimerRunning_.setSerializable(false);
  bBusyTweens_.setSerializable(false);
  bBusyLineTweaks_.setSerializable(false);
  paramsFeedback_.add(progressFeedback_);
  paramsFeedback_.add(bUserIdle_);
  paramsFeedback_.add(bTimerRunning_);
  paramsFeedback_.add(bBusyTweens_);
  paramsFeedback_.add(bBusyLineTweaks_);
  params_.add(paramsFeedback_);
  params_.add(bWaitTweens_);
  params_.add(bWaitLineTweaks_);
  params_.add(bPauseTimerWhenBusy_);
  params_.add(bWaitUserIdle_);
  params_.add(vTriggerNow_);

  eTriggerNow_ = vTriggerNow_.newListener([this](const void *) { triggerNow(); });

  // Start with text hidden so the first slide appears via writeIn tween.
  if (ot_ != nullptr) {
    ot_->writeOut();
  }

  resetTimer();
}

void PresetSlideshow::setMouseIdleChecker(std::function<bool()> fn) {
  isMouseIdle_ = std::move(fn);
}

void PresetSlideshow::update(float dt) {
  if (!bEnabled_.get() || !nextScene_) {
    progressFeedback_.set(0.0f);
    bUserIdle_.set(true);
    bTimerRunning_.set(false);
    bBusyTweens_.set(false);
    bBusyLineTweaks_.set(false);
    return;
  }

  const bool busyTweens = bWaitTweens_.get() && ot_ != nullptr && ot_->isTweening();
  const bool busyLineTweaks = bWaitLineTweaks_.get() && ot_ != nullptr && ot_->isLineTweaksRunning();
  bBusyTweens_.set(busyTweens);
  bBusyLineTweaks_.set(busyLineTweaks);

  const bool ready = !busyTweens && !busyLineTweaks;
  const bool timerRunning = ready || !bPauseTimerWhenBusy_.get();
  bTimerRunning_.set(timerRunning);

  const bool userIdle = isMouseIdle_ ? isMouseIdle_() : true;
  bUserIdle_.set(userIdle);

  // Only block while waiting between slides (timer advancing) and system is ready.
  if (ready && timerRunning && bWaitUserIdle_.get() && !userIdle) {
    bTimerRunning_.set(false);
    return;
  }

  if (timerRunning) {
    const float step = (dt > 0.0f) ? dt : ofGetLastFrameTime();
    elapsed_ += step;
  }

  if (waitSeconds_.get() > 0.0f) {
    const float progress = ofClamp(elapsed_ / waitSeconds_.get(), 0.0f, 1.0f);
    progressFeedback_.set(progress);
  } else {
    progressFeedback_.set(0.0f);
  }

  //TODO:
  // if(ot_->isMouseIdle())

  if (elapsed_ >= waitSeconds_.get() && ready) {
    triggerNow();
  }
}

void PresetSlideshow::onSceneAdvanced() {
  resetTimer();
}

void PresetSlideshow::toggle() {
  bEnabled_.set(!bEnabled_.get());
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
  progressFeedback_.set(0.0f);
  bUserIdle_.set(true);
  bTimerRunning_.set(false);
  bBusyTweens_.set(false);
  bBusyLineTweaks_.set(false);
}
