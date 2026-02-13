#include <algorithm>
#include <cctype>
#include <utility>

#include "presetSlideshow.h"

#include "organicText.h"

namespace {
std::string trimLine(const std::string & value) {
	std::string out = value;
	out.erase(out.begin(), std::find_if(out.begin(), out.end(), [](unsigned char ch) {
		return !std::isspace(ch);
	}));
	out.erase(std::find_if(out.rbegin(), out.rend(), [](unsigned char ch) {
		return !std::isspace(ch);
	}).base(),
		out.end());
	return out;
}
} // namespace

void PresetSlideshow::setup(OrganicText * organicText, std::function<void()> nextSceneCallback) {
	ofLogNotice("PresetSlideshow") << "setup()";
	ot_ = organicText;
	nextScene_ = std::move(nextSceneCallback);

	progressFeedback_.setSerializable(false);
	bUserIdle_.setSerializable(false);
	bTimerRunning_.setSerializable(false);
	bBusyTweens_.setSerializable(false);
	bBusyLineTweaks_.setSerializable(false);

	params_.setName("Slideshow");
	params_.add(bEnabled_);
	params_.add(waitSeconds_);
	params_.add(bLockPreset_);
	params_.add(bReadFromFile_);
	params_.add(textFilePath_);

	paramsFeedback_.setName("Feedback");
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

ofParameterGroup & PresetSlideshow::getFeedbackParameters() {
	return paramsFeedback_;
}

bool PresetSlideshow::isPresetLocked() const {
	return bLockPreset_.get();
}

void PresetSlideshow::applyTextFromFileNow() {
	if (bReadFromFile_.get()) {
		applyTextFromFile();
	}
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

void PresetSlideshow::applyTextFromFile() {
	if (ot_ == nullptr) return;

	const std::string filePath = ofToDataPath(textFilePath_.get(), true);
	ofFile file(filePath);
	if (!file.exists()) {
		ofLogWarning("PresetSlideshow") << "Text file not found: " << filePath;
		return;
	}

	ofBuffer buffer = ofBufferFromFile(filePath);
	std::vector<std::string> lines;
	lines.reserve(64);
	for (const auto & line : buffer.getLines()) {
		std::string trimmed = trimLine(line);
		if (!trimmed.empty()) {
			lines.push_back(trimmed);
		}
	}

	if (lines.empty()) {
		ofLogWarning("PresetSlideshow") << "Text file is empty: " << filePath;
		return;
	}

	if (currentLineIndex_ >= lines.size()) {
		currentLineIndex_ = 0;
	}

	ot_->sText.set(lines[currentLineIndex_]);
	currentLineIndex_ = (currentLineIndex_ + 1) % lines.size();
}
