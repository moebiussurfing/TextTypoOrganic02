
#pragma once
#include "ofMain.h"

namespace ofxSurfing {

//----

// Resets and random engines

/*
	TODO
	- bSilent is not full implemented... 
		not sure how could be useful..
*/

// Random simple

//--------------------------------------------------------------
static inline void doRandomize(ofParameterGroup & paramsGroup/*, bool bSilent = false*/) {
	ofLogNotice("ofxSurfing") << "doRandomizeParamsGroup():" << paramsGroup.getName();
	bool bSilent = false;

	for (auto ap : paramsGroup) {
		// Param Group
		auto pg = std::dynamic_pointer_cast<ofParameterGroup>(ap);
		if (pg) {
			// Recurse through contents.
			doRandomize(*pg/*, bSilent*/);
			continue;
		}

		for (int i = 0; i < paramsGroup.size(); i++) {
			auto & p = paramsGroup[i];

			//float
			if (p.type() == typeid(ofParameter<float>).name()) {
				ofParameter<float> pr = p.cast<float>();
				if (!pr.isSerializable()) continue;
				float v = ofRandom(pr.getMin(), pr.getMax());
				if (bSilent)
					pr.setWithoutEventNotifications(v);
				else
					pr.set(v);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//int
			else if (p.type() == typeid(ofParameter<int>).name()) {
				ofParameter<int> pr = p.cast<int>();
				if (!pr.isSerializable()) continue;
				int v = ofRandom(pr.getMin(), pr.getMax());
				if (bSilent)
					pr.setWithoutEventNotifications(v);
				else
					pr.set(v);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//booleans
			else if (p.type() == typeid(ofParameter<bool>).name()) {
				ofParameter<bool> pr = p.cast<bool>();
				if (!pr.isSerializable()) continue;
				bool b = (ofRandom(1.f) >= 0.5f);
				if (bSilent)
					pr.setWithoutEventNotifications(b);
				else
					pr.set(b);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//colors
			else if (p.type() == typeid(ofParameter<ofColor>).name()) {
				ofParameter<ofColor> pr = p.cast<ofColor>();
				if (!pr.isSerializable()) continue;
				ofColor c;
				c.setBrightness(255);
				c.setSaturation(255);
				c.setHue(ofRandom(255));

				if (bSilent)
					pr.setWithoutEventNotifications(c);
				else
					pr.set(c);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			////TODO: add multi dim
			//auto pVec3f = std::dynamic_pointer_cast<ofParameter<glm::vec3>>(p);
			//if (pVec3f) {
			//	//ofxImGuiSurfing::AddParameter(*pVec3f);
			//	continue;
			//}
		}
	}
}

// Reset Simple

//--------------------------------------------------------------
static inline void doReset(ofParameterGroup & paramsGroup/*, bool bSilent = false*/) {//TODO: to min value!
	ofLogNotice("ofxSurfing") << "doResetParamsGroup():" << paramsGroup.getName();
	bool bSilent = false;
	for (auto ap : paramsGroup) {
		// Param Group
		auto pg = std::dynamic_pointer_cast<ofParameterGroup>(ap);
		if (pg) {
			// Recurse through contents.
			doReset(*pg/*, bSilent*/);
			continue;
		}

		for (int i = 0; i < paramsGroup.size(); i++) {
			auto & p = paramsGroup[i];

			//float
			if (p.type() == typeid(ofParameter<float>).name()) {
				ofParameter<float> pr = p.cast<float>();
				if (!pr.isSerializable()) continue;
				if (bSilent)
					pr.setWithoutEventNotifications(pr.getMin());
				else
					pr.set(pr.getMin());
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//int
			else if (p.type() == typeid(ofParameter<int>).name()) {
				ofParameter<int> pr = p.cast<int>();
				if (!pr.isSerializable()) continue;
				if (bSilent)
					pr.setWithoutEventNotifications(pr.getMin());
				else
					pr.set(pr.getMin());
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//booleans
			else if (p.type() == typeid(ofParameter<bool>).name()) {
				ofParameter<bool> pr = p.cast<bool>();
				if (!pr.isSerializable()) continue;
				bool b = false;
				if (bSilent)
					pr.setWithoutEventNotifications(b);
				else
					pr.set(b);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

#if 0 // Disable to avoid all colors the same.
	//colors
				else if (p.type() == typeid(ofParameter<ofColor>).name()) {
					ofParameter<ofColor> pr = p.cast<ofColor>();
					if (!pr.isSerializable()) continue;
					ofColor c;
					c.setBrightness(64);
					c.setSaturation(0);
					c.setHue(0);

					if (bSilent)
						pr.setWithoutEventNotifications(c);
					else
						pr.set(c);
					ofLogNotice("ofxSurfing") << pr.getName() << ":" << pr.get();
					continue;
				}
#endif
		}
	}
}

//--------------------------------------------------------------
static inline void doResetSetInit(ofParameterGroup & paramsGroup) {
	ofLogNotice("ofxSurfing") << "doResetSetInit(): " << paramsGroup.getName();

	for (auto ap : paramsGroup) {
		// Param Group
		auto pg = std::dynamic_pointer_cast<ofParameterGroup>(ap);
		if (pg) {
			// Recurse through contents.
			doResetSetInit(*pg);
			continue;
		}

		for (int i = 0; i < paramsGroup.size(); i++) {
			auto & p = paramsGroup[i];

			//float
			if (p.isOfType<float>()) { //new api
				//if (p.type() == typeid(ofParameter<float>).name()) {
				ofParameter<float> pr = p.cast<float>();
				//pr.setInit(pr.get());
				auto v = pr.get();
				pr.setInit(v);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//int
			else if (p.isOfType<int>()) { //new api
				//else if (p.type() == typeid(ofParameter<int>).name()) {
				ofParameter<int> pr = p.cast<int>();
				//pr.setInit(pr.get());
				auto v = pr.get();
				pr.setInit(v);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//booleans
			else if (p.isOfType<bool>()) { //new api
				//else if (p.type() == typeid(ofParameter<bool>).name()) {
				ofParameter<bool> pr = p.cast<bool>();
				//pr.setInit(pr.get());
				auto v = pr.get();
				pr.setInit(v);
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

#if 0 // Disable to avoid all colors the same. \
	//colors
				else if (p.type() == typeid(ofParameter<ofColor>).name()) {
					ofParameter<ofColor> pr = p.cast<ofColor>();
					//pr.setInit(pr.get());
					auto v = pr.get();
					pr.setInit(v);
					ofLogNotice("ofxSurfing") << pr.getName() << ":" << pr.get();
					continue;
				}
#endif
		}
	}
}

//--------------------------------------------------------------
static inline void doResetInit(ofParameterGroup & paramsGroup) {
	ofLogNotice("ofxSurfing") << "doResetInit():" << paramsGroup.getName();

	for (auto ap : paramsGroup) {
		// Param Group
		auto pg = std::dynamic_pointer_cast<ofParameterGroup>(ap);
		if (pg) {
			// Recurse through contents.
			doResetInit(*pg);
			continue;
		}

		for (int i = 0; i < paramsGroup.size(); i++) {
			auto & p = paramsGroup[i];

			//float
			if (p.type() == typeid(ofParameter<float>).name()) {
				ofParameter<float> pr = p.cast<float>();
				//pr.getInit();
				pr.reInit();
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//int
			else if (p.type() == typeid(ofParameter<int>).name()) {
				ofParameter<int> pr = p.cast<int>();
				//pr.getInit();
				pr.reInit();
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

			//booleans
			else if (p.type() == typeid(ofParameter<bool>).name()) {
				ofParameter<bool> pr = p.cast<bool>();
				//pr.getInit();
				pr.reInit();
				ofLogVerbose("ofxSurfing") << pr.getName() << ":" << pr.get();
				continue;
			}

#if 0 // Disable to avoid all colors the same. \
	//colors
				else if (p.type() == typeid(ofParameter<ofColor>).name()) {
					ofParameter<ofColor> pr = p.cast<ofColor>();
					//pr.getInit();
					pr.reInit();
					ofLogNotice("ofxSurfing") << pr.getName() << ":" << pr.get();
					continue;
				}
#endif
		}
	}
}

//----

//TODO:
// An improved randomizer. center value + power %
/*
    enum ResetPramsType
    {
        RESET_PARAM_MIN = 0,
        RESET_PARAM_FULL_CENTER,
        RESET_PARAM_RANGE_CENTER,
        RESET_PARAM_MAX,
        RESET_RANGE_MIN,
        RESET_RANGE_MAX,
    };

    //--------------------------------------------------------------
    void doResetParamsFull(ResetPramsType MS_type) {
        ofLogNotice("ofxSurfing") << (__FUNCTION__);


        for (int i = 0; i < paramsPreset.size(); i++)
            //for (auto p : editorEnablers)
        {
            auto p = true;//only reset this iterated param if it's enabled

            //-

            //string name = p.getName();//name
            string name = paramsPreset[i].getName();//name
            //auto& g = paramsPreset.getGroup(name);//ofParameterGroup
            //auto& g = paramsPreset.getGroup(name);//ofParameterGroup
            auto& g = paramsPreset;//ofParameterGroup
            auto& e = g.get(name);//ofAbstractParameter
            //auto& e = paramsPreset.get(name);//ofAbstractParameter

            auto type = e.type();
            bool isFloat = type == typeid(ofParameter<float>).name();
            bool isInt = type == typeid(ofParameter<int>).name();

            bool isVec2 = type == typeid(ofParameter<glm::vec2>).name();
            bool isVec3 = type == typeid(ofParameter<glm::vec3>).name();
            bool isVec4 = type == typeid(ofParameter<glm::vec4>).name();

            if (isFloat)
            {
                auto pmin = g.getFloat("Min").get();
                auto pmax = g.getFloat("Max").get();
                ofParameter<float> p0 = e.cast<float>();

                if (0) {}
                else if (MS_type == RESET_PARAM_MIN) p0.set(p0.getMin());//reset to param min
                else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set((p0.getMax() - p0.getMin()) / 2);
                else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set((pmax - pmin) / 2);
                else if (MS_type == RESET_PARAM_MAX) p0.set(p0.getMax());//reset to param max
                else if (MS_type == RESET_RANGE_MIN) p0.set(pmin);//reset to range min
                else if (MS_type == RESET_RANGE_MAX) p0.set(pmax);//reset to range max
            }

            else if (isInt)
            {
                auto pmin = g.getInt("Min").get();
                auto pmax = g.getInt("Max").get();
                ofParameter<int> p0 = e.cast<int>();

                if (0) {}
                else if (MS_type == RESET_PARAM_MIN) p0.set(p0.getMin());//reset to param min
                else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set((p0.getMax() - p0.getMin()) / 2);
                else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set((pmax - pmin) / 2);
                else if (MS_type == RESET_PARAM_MAX) p0.set(p0.getMax());//reset to param max
                else if (MS_type == RESET_RANGE_MIN) p0.set(pmin);//reset to range min
                else if (MS_type == RESET_RANGE_MAX) p0.set(pmax);//reset to range max
            }

            else if (isVec2)
            {
                auto pmin = g.getVec2f("Min").get();
                auto pmax = g.getVec2f("Max").get();
                ofParameter<glm::vec2> p0 = e.cast<glm::vec2>();

                if (0) {}
                else if (MS_type == RESET_PARAM_MIN) p0.set(p0.getMin());//reset to param min
                else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set((p0.getMax() - p0.getMin()) / 2);
                else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set((pmax - pmin) / 2);
                else if (MS_type == RESET_PARAM_MAX) p0.set(p0.getMax());//reset to param max
                else if (MS_type == RESET_RANGE_MIN) p0.set(pmin);//reset to range min
                else if (MS_type == RESET_RANGE_MAX) p0.set(pmax);//reset to range max

                //for (int dim = 0; dim < 2; dim++) {
                //	if (dim == 0) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec2(p0.getMin().x, p0.get().y));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec2(p0.getMax().x - p0.getMin().x / 2, p0.get().y));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec2(pmax.x - pmin.x / 2, p0.get().y));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec2(p0.getMax().x, p0.get().y));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec2(pmin.x, p0.get().y));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec2(pmax.x, p0.get().y));//reset to range max
                //	}
                //	else if (dim == 1) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec2(p0.get().x, p0.getMin().y));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec2(p0.get().x,p0.getMax().y - p0.getMin().y / 2));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec2(p0.get().x,pmax.y - pmin.y / 2));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec2(p0.getMax().x, p0.get().y));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec2(p0.get().x, pmin.y));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec2(p0.get().x, pmax.y));//reset to range max
                //	}
                //}
            }
            else if (isVec3)
            {
                auto pmin = g.getVec3f("Min").get();
                auto pmax = g.getVec3f("Max").get();
                ofParameter<glm::vec3> p0 = e.cast<glm::vec3>();

                if (0) {}
                else if (MS_type == RESET_PARAM_MIN) p0.set(p0.getMin());//reset to param min
                else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set((p0.getMax() - p0.getMin()) / 2);
                else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set((pmax - pmin) / 2);
                else if (MS_type == RESET_PARAM_MAX) p0.set(p0.getMax());//reset to param max
                else if (MS_type == RESET_RANGE_MIN) p0.set(pmin);//reset to range min
                else if (MS_type == RESET_RANGE_MAX) p0.set(pmax);//reset to range max

                //for (int dim = 0; dim < 3; dim++) {
                //	if (dim == 0) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec3(p0.getMin().x, p0.get().y, p0.get().z));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec3(p0.getMax().x - p0.getMin().x / 2, p0.get().y, p0.get().z));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec3(pmax.x - pmin.x / 2, p0.get().y, p0.get().z));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec3(p0.getMax().x, p0.get().y, p0.get().z));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec3(pmin.x, p0.get().y, p0.get().z));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec3(pmax.x, p0.get().y, p0.get().z));//reset to range max
                //	}
                //	else if (dim == 1) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec3(p0.get().x, p0.getMin().y, p0.getMin().z));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec3(p0.get().x, p0.getMax().y - p0.getMin().y / 2, p0.getMin().z));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec3(p0.get().x, pmax.y - pmin.y / 2, p0.getMin().z));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec3(p0.getMax().x, p0.get().y, p0.getMin().z));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec3(p0.get().x, pmin.y, p0.getMin().z));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec3(p0.get().x, pmax.y, p0.getMin().z));//reset to range max
                //	}
                //	else if (dim == 2) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec3(p0.get().x, p0.get().y, p0.getMin().z));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec3(p0.get().x, p0.get().y, p0.getMax().z - p0.getMin().z / 2));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec3(p0.get().x, p0.get().y, pmax.z - pmin.z / 2));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec3(p0.getMax().x, p0.get().y, p0.get().z));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec3(p0.get().x, p0.get().y, pmin.z));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec3(p0.get().x, p0.get().y, pmax.z));//reset to range max
                //	}
                //}
            }
            else if (isVec4)
            {
                auto pmin = g.getVec4f("Min").get();
                auto pmax = g.getVec4f("Max").get();
                ofParameter<glm::vec4> p0 = e.cast<glm::vec4>();

                if (0) {}
                else if (MS_type == RESET_PARAM_MIN) p0.set(p0.getMin());//reset to param min
                else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set((p0.getMax() - p0.getMin()) / 2);
                else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set((pmax - pmin) / 2);
                else if (MS_type == RESET_PARAM_MAX) p0.set(p0.getMax());//reset to param max
                else if (MS_type == RESET_RANGE_MIN) p0.set(pmin);//reset to range min
                else if (MS_type == RESET_RANGE_MAX) p0.set(pmax);//reset to range max

                //for (int dim = 0; dim < 4; dim++) {
                //	if (dim == 0) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec4(p0.getMin().x, p0.get().y, p0.get().z, p0.get().w));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec4((p0.getMax().x - p0.getMin().x) / 2, p0.get().y, p0.get().z, p0.get().w));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec4((pmax.x - pmin.x) / 2, p0.get().y, p0.get().z, p0.get().w));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec4(p0.getMax().x, p0.get().y, p0.get().z, p0.get().w));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec4(pmin.x, p0.get().y, p0.get().z, p0.get().w));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec4(pmax.x, p0.get().y, p0.get().z, p0.get().w));//reset to range max
                //	}
                //	else if (dim == 1) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec4(p0.get().x, p0.getMin().y, p0.get().z, p0.get().w));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec4(p0.get().x, (p0.getMax().y - p0.getMin().y) / 2, p0.get().z, p0.get().w));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec4(p0.get().x, (pmax.y - pmin.y) / 2, p0.get().z, p0.get().w));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec4(p0.getMax().x, p0.get().y, p0.get().z, p0.get().w));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec4(p0.get().x, pmin.y, p0.get().z, p0.get().w));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec4(p0.get().x, pmax.y, p0.get().z, p0.get().w));//reset to range max
                //	}
                //	else if (dim == 2) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.getMin().z, p0.get().w));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec4(p0.get().x, p0.get().y, (p0.getMax().z - p0.getMin().z) / 2, p0.get().w));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec4(p0.get().x, p0.get().y, (pmax.z - pmin.z) / 2, p0.get().w));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, p0.get().w));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec4(p0.get().x, p0.get().y, pmin.z, p0.get().w));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec4(p0.get().x, p0.get().y, pmax.z, p0.get().w));//reset to range max
                //	}
                //	else if (dim == 3) {
                //		if (0) {}
                //		else if (MS_type == RESET_PARAM_MIN) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, p0.getMin()));//reset to param min
                //		else if (MS_type == RESET_PARAM_FULL_CENTER) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, (p0.getMax().w - p0.getMin().w) / 2));
                //		else if (MS_type == RESET_PARAM_RANGE_CENTER) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, (pmax.w - pmin.w) / 2));
                //		else if (MS_type == RESET_PARAM_MAX) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, p0.getMax().w));//reset to param max
                //		else if (MS_type == RESET_RANGE_MIN) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, pmin));//reset to range min
                //		else if (MS_type == RESET_RANGE_MAX) p0.set(glm::vec4(p0.get().x, p0.get().y, p0.get().z, pmax));//reset to range max
                //	}
                //}
            }
        }
    }
    */

}
