//
// ofxTweenLiteHelper.h
//
// Helper class created by moebiusSurfing
// for the ofxTweenLite.h originally by lukasz karluk.
//

#define USE_OFX_GUI__OFX_TWEEN_LITE_HELPER // -> comment if you won't use ofxGui in your project
#ifdef USE_OFX_GUI__OFX_TWEEN_LITE_HELPER
	#include "ofxGui.h"
#endif

#pragma once
#include "ofMain.h"
#include "ofxTweenLite.h"
#include <atomic>
#include <functional>
#include <vector>

// Helper for interpolation
// Implemented types: int, float, glm::vec2, ofColor
namespace ofxTweenLiteHelperUtils {
// Generic template
// float
template <typename T>
inline T lerp(const T & a, const T & b, float t) { return a + (b - a) * t; }
// int
template <>
inline int lerp(const int & a, const int & b, float t) {
	return static_cast<int>(std::round(a + (b - a) * t));
}
// vec2
template <>
inline glm::vec2 lerp(const glm::vec2 & a, const glm::vec2 & b, float t) { return a + (b - a) * t; }
template <>
// ofColor
inline ofColor lerp(const ofColor & a, const ofColor & b, float t) {
	return ofColor(
		ofLerp(a.r, b.r, t),
		ofLerp(a.g, b.g, t),
		ofLerp(a.b, b.b, t),
		ofLerp(a.a, b.a, t));
}
}

//--

// Main helper class
template <typename T>
class ofxTweenLiteHelper {
public:
	ofxTweenLiteHelper()
		: from(T {})
		, to(T {})
		, value(T {})
		, duration(1.0f)
		, easeMode(OF_EASE_LINEAR_IN)
		, startTime(0.0f)
		, pauseTime(0.0f)
		, finished(true)
		, paused(false)
		, onStart(nullptr)
		, onUpdate(nullptr)
		, onComplete(nullptr)
		, onCancel(nullptr)
		, tweenName_("Tween")
		, pathSettings_("settings_tween.json")
		, ap_(nullptr)
		, bIsInitialized_(false) {
		// initialize optional linked parameter pointer
		// setupParameters_();
	}

	//--

	// Fluent API
	ofxTweenLiteHelper & setFrom(const T & v) {
		from = v;
		pFrom_ = v; // sync with parameter
		return *this;
	}
	ofxTweenLiteHelper & setTo(const T & v) {
		to = v;
		pTo_ = v; // sync with parameter
		return *this;
	}
	ofxTweenLiteHelper & setDuration(float d) {
		duration = d;
		pDuration_ = d; // sync with parameter
		return *this;
	}
	ofxTweenLiteHelper & setEase(ofEaseFunction e) {
		easeMode = e;
		pEaseType_ = static_cast<int>(e); // sync with parameter
		return *this;
	}
	ofxTweenLiteHelper & setChainFromCurrentValue(bool chain) {
		pChainFromCurrent_ = chain; // sync with parameter
		return *this;
	}

	//--

	ofxTweenLiteHelper & onStartCallback(std::function<void()> cb) {
		onStart = cb;
		return *this;
	}
	ofxTweenLiteHelper & onUpdateCallback(std::function<void()> cb) {
		onUpdate = cb;
		return *this;
	}
	ofxTweenLiteHelper & onCompleteCallback(std::function<void()> cb) {
		onComplete = cb;
		return *this;
	}
	ofxTweenLiteHelper & onUserCompleteCallback(std::function<void()> cb) {
		onUserComplete = cb;
		return *this;
	}
	ofxTweenLiteHelper & onCancelCallback(std::function<void()> cb) {
		onCancel = cb;
		return *this;
	}

	//--

	// Starts the tween for a value
	void start(const T & from_, const T & to_, float duration_, ofEaseFunction easeMode_ = OF_EASE_LINEAR_IN, std::function<void()> onComplete_ = nullptr) {
		ofLogNotice("ofxTweenLiteHelper") << "start(..): " << tweenName_;
		startInternal(from_, to_, duration_, easeMode_, onComplete_);
	}

	// Starts the tween using previously set parameters
	void start() {
		ofLogNotice("ofxTweenLiteHelper") << "start(): " << tweenName_;
		// If tween is currently running, honor e_pChainFromCurrent_: start from current value if chain enabled,
		// otherwise start from the original from.
		if (isRunning()) {
			if (pChainFromCurrent_) {
				startInternal(value, to, duration, easeMode, onComplete);
			} else {
				startInternal(from, to, duration, easeMode, onComplete);
			}
		} else {
			// If tween is stopped (not running), always start from the original from regardless of chain flag
			startInternal(from, to, duration, easeMode, onComplete);
		}
	}

	/// @brief Stops the tween and resets to initial 'from' value
	void stop() {
		ofLogNotice("ofxTweenLiteHelper") << "stop(): " << tweenName_;
		finished = true;
		paused = false;
		pCurrentProgress_.set(0.0f);
		value = from;

		// Auto-update linked parameter if available
		if (ap_ != nullptr) {
			auto typedParam = dynamic_cast<ofParameter<T> *>(ap_);
			if (typedParam) {
				typedParam->set(value);
			}
		}

		if (onCancel) onCancel();
	}

	// Cancels the tween (alias for stop)
	void cancel() {
		ofLogNotice("ofxTweenLiteHelper") << "cancel()";
		stop();
	}

	// Pauses the tween
	void pause() {
		ofLogNotice("ofxTweenLiteHelper") << "pause()";
		paused = true;
		pauseTime = ofGetElapsedTimef();
	}

	// Resumes the tween
	void resume() {
		ofLogNotice("ofxTweenLiteHelper") << "resume()";
		if (paused) {
			float pausedDuration = ofGetElapsedTimef() - pauseTime;
			startTime += pausedDuration;
			paused = false;
		}
	}

	// Updates the tween and calculates the value
	void update() {
		if (paused) {
			// When paused, don't update but keep current value
			return;
		}
		if (finished) {
			// When finished, keep the final calculated value, don't force it to 'to'
			return;
		}
		float elapsed = ofGetElapsedTimef() - startTime;
		pCurrentProgress_.set(ofClamp(elapsed / duration, 0.0f, 1.0f));
		value = ofxTweenLiteHelperUtils::lerp(from, to, ofxTweenLite::tween(0.0f, 1.0f, pCurrentProgress_.get(), easeMode));

		// Auto-update linked parameter if available
		if (ap_ != nullptr) {
			auto typedParam = dynamic_cast<ofParameter<T> *>(ap_);
			if (typedParam) {
				typedParam->set(value);
			}
		}

		if (onUpdate) onUpdate();
		if (pCurrentProgress_.get() >= 1.0f && !finished) {
			//TODO: must fix situation when value not arrives (lower) to target (to) value too!
			// Fix workaround: When tween completes and overshoots target (to) value,
			// ensure exact final value regardless of framerate/timing precision
			value = to;
			pCurrentProgress_.set(1.0f);
			finished = true;
			from = pFrom_.get(); // sync from parameter to fix chaining mode

			// Internal callback (always runs to ensure exact final value)
			if (onComplete) onComplete();
			// User callback (runs after internal callback for state machine/workflow)
			if (onUserComplete) onUserComplete();
		}
	}

	// Returns the current tweened value
	T getValue() const {
		return value;
	}
	// Returns normalized progress (0 to1)
	float getProgress() {
		return pCurrentProgress_.get();
	}

	// Check if finished
	bool isFinished() const {
		return finished;
	}
	bool isPaused() const {
		return paused;
	}
	bool isRunning() const {
		return !finished && !paused;
	}

	//--

	// Static: get all ease modes
	static const std::vector<ofEaseFunction> & getAllEaseModes() {
		static std::vector<ofEaseFunction> modes = {
			OF_EASE_BACK_IN, OF_EASE_BACK_OUT, OF_EASE_BACK_INOUT,
			OF_EASE_BOUNCE_IN, OF_EASE_BOUNCE_OUT, OF_EASE_BOUNCE_INOUT,
			OF_EASE_CIRC_IN, OF_EASE_CIRC_OUT, OF_EASE_CIRC_INOUT,
			OF_EASE_CUBIC_IN, OF_EASE_CUBIC_OUT, OF_EASE_CUBIC_INOUT,
			OF_EASE_ELASTIC_IN, OF_EASE_ELASTIC_OUT, OF_EASE_ELASTIC_INOUT,
			OF_EASE_EXPO_IN, OF_EASE_EXPO_OUT, OF_EASE_EXPO_INOUT,
			OF_EASE_LINEAR_IN, OF_EASE_LINEAR_OUT, OF_EASE_LINEAR_INOUT,
			OF_EASE_QUAD_IN, OF_EASE_QUAD_OUT, OF_EASE_QUAD_INOUT,
			OF_EASE_QUART_IN, OF_EASE_QUART_OUT, OF_EASE_QUART_INOUT,
			OF_EASE_QUINT_IN, OF_EASE_QUINT_OUT, OF_EASE_QUINT_INOUT,
			OF_EASE_SINE_IN, OF_EASE_SINE_OUT, OF_EASE_SINE_INOUT
		};
		return modes;
	}

	// Static: get all ease names
	static const std::vector<std::string> & getAllEaseNames() {
		static std::vector<std::string> names = {
			"BackIn", "BackOut", "BackInOut",
			"BounceIn", "BounceOut", "BounceInOut",
			"CircIn", "CircOut", "CircInOut",
			"CubicIn", "CubicOut", "CubicInOut",
			"ElasticIn", "ElasticOut", "ElasticInOut",
			"ExpoIn", "ExpoOut", "ExpoInOut",
			"LinearIn", "LinearOut", "LinearInOut",
			"QuadIn", "QuadOut", "QuadInOut",
			"QuartIn", "QuartOut", "QuartInOut",
			"QuintIn", "QuintOut", "QuintInOut",
			"SineIn", "SineOut", "SineInOut"
		};
		return names;
	}

	/// @brief Get next ease type and restart tween
	void nextEaseType() {
		int current = static_cast<int>(pEaseType_.get());
		int numModes = static_cast<int>(getAllEaseModes().size());
		int next = (current + 1) % numModes;
		pEaseType_.set(next);
		// start(); // Restart with new ease type
	}
	/// @brief Get previous ease type and restart tween
	void previousEaseType() {
		int current = static_cast<int>(pEaseType_.get());
		int numModes = static_cast<int>(getAllEaseModes().size());
		int prev = (current - 1 + numModes) % numModes;
		pEaseType_.set(prev);
		// start(); // Restart with new ease type
	}
	/// @brief Get the name of the current ease type
	std::string getCurrentEaseName() const {
		int current = static_cast<int>(pEaseType_.get());
		const auto & names = getAllEaseNames();
		if (current >= 0 && current < static_cast<int>(names.size())) {
			return names[current];
		}
		return "Unknown";
	}

	//--

private:
	T from, to, value;
	float duration;
	ofEaseFunction easeMode;
	float startTime;
	float pauseTime;
	bool finished;
	bool paused;

	std::function<void()> onStart;
	std::function<void()> onUpdate;
	std::function<void()> onComplete;
	std::function<void()> onUserComplete;
	std::function<void()> onCancel;

	// Parameters and settings
	std::string tweenName_;
	std::string pathSettings_;

public:
	ofParameterGroup params_;
	ofParameterGroup paramsAdvanced_;
	ofParameter<T> pFrom_;
	ofParameter<T> pTo_;
	ofParameter<float> pDuration_;
	ofParameter<float> pCurrentProgress_;
	ofParameter<int> pEaseType_;
	ofParameter<std::string> pEaseName_;
	ofParameter<bool> pChainFromCurrent_;
	ofParameter<void> vStart_;
	ofParameter<void> vStop_;
	ofParameter<void> vPause_;
	ofParameter<void> vResume_;

private:
	ofEventListener e_pFrom_;
	ofEventListener e_pTo_;
	ofEventListener e_pDuration_;
	ofEventListener e_pEaseType_;
	ofEventListener e_pChainFromCurrent_;
	ofEventListener e_vStart_;
	ofEventListener e_vStop_;
	ofEventListener e_vPause_;
	ofEventListener e_vResume_;

	// Optional link to an external parameter.
	// Pointer keeps this helper default-constructible.
	ofAbstractParameter * ap_;

	// Flag to prevent callbacks during initialization
	bool bIsInitialized_;

public:
	/// @brief Setup tween without linked ofParameter (auto-generates unique name)
	/// Call this in ofApp::setup() for standalone tweens
	void setup() {
		ofLogNotice("ofxTweenLiteHelper") << "setup()";
		std::string autoName = generateUniqueName_();
		setName(autoName);
	}

	/// @brief Setup tween with custom name (without linked ofParameter)
	/// Call this in ofApp::setup() for standalone tweens with custom naming
	void setup(const std::string & customName) {
		ofLogNotice("ofxTweenLiteHelper") << "setup(" << customName << ")";
		setName(customName);
	}

public:
	void setup(ofAbstractParameter & aParameter) {
		ofLogNotice("ofxTweenLiteHelper") << "setup()";
		setupParameter(aParameter);
	}

private:
	/// @brief Setup link parameter
	/// @warning The parameter must outlive this helper instance.
	///          Typically safe when both are members of the same class.
	void setupParameter(ofAbstractParameter & aParameter) {
		ap_ = &aParameter;
		ofLogNotice("ofxTweenLiteHelper") << "setupParameter() name: " << ap_->getName();

		bool bValidType = false;

		// Verify supported types and print type info

		// int
		auto parameterInt = dynamic_cast<ofParameter<int> *>(ap_);
		if (parameterInt) {
			ofLogNotice("ofxTweenLiteHelper") << "type int";
			bValidType = true;
		}
		// float
		auto parameterFloat = dynamic_cast<ofParameter<float> *>(ap_);
		if (parameterFloat) {
			ofLogNotice("ofxTweenLiteHelper") << "type float";
			bValidType = true;
		}
		// vec2
		auto parameterVec2f = dynamic_cast<ofParameter<glm::vec2> *>(ap_);
		if (parameterVec2f) {
			ofLogNotice("ofxTweenLiteHelper") << "type glm::vec2";
			bValidType = true;
		}
		// ofColor
		auto parameterColor = dynamic_cast<ofParameter<ofColor> *>(ap_);
		if (parameterColor) {
			ofLogNotice("ofxTweenLiteHelper") << "type ofColor";
			bValidType = true;
		}

		if (bValidType) {
			setName(ap_->getName());
		} else {
			ofLogError("ofxTweenLiteHelper") << "Unsupported parameter type for tweening.";
		}
	}

private:
	/// @brief Set the name of this tween (used for parameter group and JSON filename)
	void setName(const std::string & name) {
		ofLogNotice("ofxTweenLiteHelper") << "setName() " << name;

		tweenName_ = "Tween_" + name;
		pathSettings_ = "settings_" + tweenName_ + ".json";

		setupParameters_();
		params_.setName(tweenName_);
		
		setupCallbacks_(); // Setup callbacks after parameters are fully initialized

		// Autoload settings so the user doesn't need to call it from ofApp
		if(!bDisableInternalJsonSettings) loadSettings();
		
		// Mark as fully initialized after all setup is complete
		bIsInitialized_ = true;
	}

public:
	/// @brief Get the current name of this tween
	std::string getName() const {
		return tweenName_;
	}

private:
	/// @brief Setup parameters and group
	void setupParameters_() {
		ofLogNotice("ofxTweenLiteHelper") << "setupParameters_()";
		params_.setName(tweenName_);
		params_.add(pCurrentProgress_.set("Progress", 0.0f, 0.0f, 1.0f));

		if (ap_ != nullptr) {
			// Cast to the templated type T
			auto typedParam = dynamic_cast<ofParameter<T> *>(ap_);
			if (typedParam) {
				T minVal = typedParam->getMin();
				T maxVal = typedParam->getMax();

				// Use min as default for From, max as default for To
				params_.add(pFrom_.set("From", minVal, minVal, maxVal));
				params_.add(pTo_.set("To", maxVal, minVal, maxVal));

				// Sync internal values with parameter defaults
				from = minVal;
				to = maxVal;
			} else {
				// Fallback if cast fails (type mismatch)
				setupDefaultParams_();
			}
		} else { // No linked ofParameter, use default construction
			// No linked ofParameter, use type-appropriate defaults
			setupDefaultParams_();
		}

		params_.add(pDuration_.set("Duration", 1.0f, 0.1f, 10.0f));
		params_.add(pEaseType_.set("EaseType", OF_EASE_LINEAR_IN, 0, 32));
		params_.add(pEaseName_.set("EaseName", "LinearIn"));
		params_.add(vStart_.set("Start"));
		paramsAdvanced_.setName("Advanced");
		paramsAdvanced_.add(pChainFromCurrent_.set("Chain", false));
		paramsAdvanced_.add(vPause_.set("Pause"));
		paramsAdvanced_.add(vResume_.set("Resume"));
		paramsAdvanced_.add(vStop_.set("Stop"));
		params_.add(paramsAdvanced_);

		// Make EaseName non-serializable (read-only display)
		pCurrentProgress_.setSerializable(false);
		pEaseName_.setSerializable(false);
	}

private:
	/// @brief Setup default parameters based on type T
	// int
	template <typename U = T>
	typename std::enable_if<std::is_same<U, int>::value>::type
	setupDefaultParams_() {
		// int: 0 to 100
		params_.add(pFrom_.set("From", 0, 0, 100));
		params_.add(pTo_.set("To", 100, 0, 100));
	}
	// float
	template <typename U = T>
	typename std::enable_if<std::is_same<U, float>::value>::type
	setupDefaultParams_() {
		// float: 0.0 to 1.0
		params_.add(pFrom_.set("From", 0.0f, 0.0f, 1.0f));
		params_.add(pTo_.set("To", 1.0f, 0.0f, 1.0f));
	}
	// vec2
	template <typename U = T>
	typename std::enable_if<std::is_same<U, glm::vec2>::value>::type
	setupDefaultParams_() {
		// vec2: (0,0) to (1,1)
		params_.add(pFrom_.set("From", glm::vec2(0, 0), glm::vec2(0, 0), glm::vec2(1, 1)));
		params_.add(pTo_.set("To", glm::vec2(1, 1), glm::vec2(0, 0), glm::vec2(1, 1)));
	}
	// ofColor
	template <typename U = T>
	typename std::enable_if<std::is_same<U, ofColor>::value>::type
	setupDefaultParams_() {
		// ofColor: black to white
		params_.add(pFrom_.set("From", ofColor(0), ofColor(0), ofColor(255)));
		params_.add(pTo_.set("To", ofColor(255), ofColor(0), ofColor(255)));
	}

	//--

	/// @brief Setup parameter callbacks
	void setupCallbacks_() {
		ofLogNotice("ofxTweenLiteHelper") << "setupCallbacks_()";

		// From changed
		e_pFrom_ = pFrom_.newListener([this](T & v) {
			if (!bIsInitialized_) return;
			from = v;
		});

		// To changed
		e_pTo_ = pTo_.newListener([this](T & v) {
			if (!bIsInitialized_) return;
			to = v;
		});

		// Duration changed
		e_pDuration_ = pDuration_.newListener([this](float & v) {
			if (!bIsInitialized_) return;
			if (v <= 0.0f) v = 0.1f; // Validation
			duration = v;
		});

		// Ease type changed
		e_pEaseType_ = pEaseType_.newListener([this](int & v) {
			if (!bIsInitialized_) return;
			v = ofClamp(v, 0, 32); // Validation
			easeMode = static_cast<ofEaseFunction>(v);
			// Update ease name
			const auto & names = getAllEaseNames();
			if (v >= 0 && v < static_cast<int>(names.size())) {
				pEaseName_ = names[v];
			}
		});

		// Chain from current changed
		e_pChainFromCurrent_ = pChainFromCurrent_.newListener([this](bool & v) {
			if (!bIsInitialized_) return;
			// chainFromCurrentValue = v;
		});

		// Button callbacks - ofParameter<void> signature uses const void* sender
		e_vStart_ = vStart_.newListener([this](const void *) {
			if (!bIsInitialized_) return;
			start();
		});

		e_vStop_ = vStop_.newListener([this](const void *) {
			if (!bIsInitialized_) return;
			stop();
		});

		e_vPause_ = vPause_.newListener([this](const void *) {
			if (!bIsInitialized_) return;
			pause();
		});

		e_vResume_ = vResume_.newListener([this](const void *) {
			if (!bIsInitialized_) return;
			resume();
		});
	}

	// Internal start method
	void startInternal(const T & from_, const T & to_, float duration_, ofEaseFunction easeMode_, std::function<void()> onComplete_) {
		// ofLogNotice("ofxTweenLiteHelper") << "startInternal()";
		from = from_;
		to = to_;
		duration = duration_;
		easeMode = easeMode_;
		startTime = ofGetElapsedTimef();
		finished = false;
		paused = false;
		onComplete = onComplete_;
		value = from;
		if (onStart) onStart();
	}

private:
	/// @brief Generate unique name based on type T and static counter
	std::string generateUniqueName_() {
		std::string typeName = getTypeName_();
		int counter = getNextCounter_();
		return typeName + std::to_string(counter);
	}

	/// @brief Get human-readable type name for template type T
	std::string getTypeName_() {
		// Use type_traits to determine type name
		if (std::is_same<T, int>::value) return "Int";
		if (std::is_same<T, float>::value) return "Float";
		if (std::is_same<T, glm::vec2>::value) return "Vec2";
		if (std::is_same<T, ofColor>::value) return "Color";
		return "Unknown";
	}

	/// @brief Get next counter value for this type (static per-type counter)
	int getNextCounter_() {
		// Static counter per type T
		static std::atomic<int> counter(0);
		return ++counter;
	}

public:
	/// @brief Save settings to JSON file
	void saveSettings() {
		ofLogNotice("ofxTweenLiteHelper") << "saveSettings() -> " << pathSettings_;
		ofJson settings;
		ofSerialize(settings, params_);
		bool b = ofSavePrettyJson(pathSettings_, settings);
		if (b)
			ofLogNotice("ofxTweenLiteHelper") << "Settings saved: " << pathSettings_;
		else
			ofLogError("ofxTweenLiteHelper") << "Unable to save settings: " << pathSettings_;
	}

	/// @brief Load settings from JSON file
	void loadSettings() {
		ofLogNotice("ofxTweenLiteHelper") << "loadSettings() -> " << pathSettings_;
		ofFile file(pathSettings_);
		if (file.exists()) {
			ofJson settings = ofLoadJson(pathSettings_);
			ofDeserialize(settings, params_);
			ofLogNotice("ofxTweenLiteHelper") << "Settings loaded: " << pathSettings_;
		} else {
			ofLogWarning("ofxTweenLiteHelper") << "Settings file not found: " << pathSettings_;
		}
	}

public:
	/// @brief Get the parameter group for adding to GUI
	ofParameterGroup & getParameters() {
		return params_;
	}

	/// @brief Exit function to be called on app exit and save settings
	void exit() {
		ofLogNotice("ofxTweenLiteHelper") << "exit()";
		if(!bDisableInternalJsonSettings)
			saveSettings();
	}

#ifdef USE_OFX_GUI__OFX_TWEEN_LITE_HELPER
	/// @brief Refresh gui panel to minimize Advanced parameters group
	void refreshGui(ofxPanel & gui) {
		ofLogNotice("ofxTweenLiteHelper") << "refreshGui()";
		auto & g = gui.getGroup(params_.getName());
		g.getGroup(paramsAdvanced_.getName()).minimize();
	}
	/// @brief Refresh gui group to minimize Advanced parameters group
	void refreshGui(ofxGuiGroup & group) {
		ofLogNotice("ofxTweenLiteHelper") << "refreshGui()";
		auto & g = group.getGroup(params_.getName());
		g.getGroup(paramsAdvanced_.getName()).minimize();
	}
#endif
	
private:
	bool bDisableInternalJsonSettings = false;
public:
	void setDisableInternalJsonSettings(bool b) { bDisableInternalJsonSettings = b; }
};
