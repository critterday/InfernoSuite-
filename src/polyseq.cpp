#include "plugin.hpp"


struct POLYSEQ : Module {
	enum ParamId {
		s1t1,
		s1t2,
		s1t3,
		s1t4,
		s2t1,
		s2t2,
		s2t3,
		s2t4,
		r1,
		r2,
		r3,
		r4,
		s1r1,
		s1r2,
		s1r3,
		s1r4,
		s2r1,
		s2r2,
		s2r3,
		s2r4,
		tempo,
		start,
		reset,
		trig,
		next,
		PARAMS_LEN
	};
	enum InputId {
		extclock,
		INPUTS_LEN
	};
	enum OutputId {
		cv1,
		cv2,
		gate1,
		gate2,
		sharegate,
		tempout,
		OUTPUTS_LEN
	};
	enum LightId {
		s1L1,
		s1L2,
		s1L3,
		s1L4,
		s2L1,
		s2L2,
		s2L3,
		s2L4,
		s1r1L,
		s1r2L,
		s1r3L,
		s1r4L,
		s2r1L,
		s2r2L,
		s2r3L,
		s2r4L,
		LIGHTS_LEN
	};

	POLYSEQ() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(tempo, 0.5, 30, 0.75);
	}

	int seq1state = 1;
	int seq2state = 1;

	float thisprocess;
	float lastprocess;

	void process(const ProcessArgs& args) override {

		float thisprocess = clockGen(args);

		fixlights();

		outputs[tempout].setVoltage(clockGen(args));




		float lastprocess = clockGen(args);
	}

	void fixlights(){
		lights[s1r1L].setBrightness(params[s1r1].getValue());
		lights[s1r2L].setBrightness(params[s1r2].getValue());
		lights[s1r3L].setBrightness(params[s1r3].getValue());
		lights[s1r4L].setBrightness(params[s1r4].getValue());
		lights[s2r1L].setBrightness(params[s2r1].getValue());
		lights[s2r2L].setBrightness(params[s2r2].getValue());
		lights[s2r3L].setBrightness(params[s2r3].getValue());
		lights[s2r4L].setBrightness(params[s2r4].getValue());
	}

	void advance(int state){
		state <4 ? state += 1 : state = 1;
	}

	float phase = 0.f;

	float clockGen(const ProcessArgs& args){
		float speed = params[tempo].getValue();
		float tempo = 1 * std::pow(2.f, speed);

		phase += tempo * args.sampleTime;
		if (phase >= 1.f)
			phase -= 1.f;

		float sine = std::sin(2.f * M_PI * phase);
		float clock;
		sine > 0 ? clock = 5 : clock = -5;

		return clock;

	}

	bool detectRisingEdge(float now, float then){
		if (now > then){
			return true;
		} else {
			return false;
		}
	}

	void rhythms (Trimpot knob, VCVLatch b1, VCVLatch b2){

	}
};


struct POLYSEQWidget : ModuleWidget {
	POLYSEQWidget(POLYSEQ* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/POLYSEQ.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x1 = 6.32;
		float x2 = 15.78;
		float x3 = 25.22;
		float x4 = 34.64;

		float y1 = 15;
		float y2 = 25;
		float y3 = 35;
		float y4 = 45;
		float y5 = 60;
		float y6 = 70;
		float y7 = 80;

		// seq 1
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x1, y1)), module, POLYSEQ::s1t1));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x2, y1)), module, POLYSEQ::s1t2));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x3, y1)), module, POLYSEQ::s1t3));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x4, y1)), module, POLYSEQ::s1t4));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x1, y2)), module, POLYSEQ::s1L1));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x2, y2)), module, POLYSEQ::s1L2));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x3, y2)), module, POLYSEQ::s1L3));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x4, y2)), module, POLYSEQ::s1L4));

		// seq 2
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x1, y3)), module, POLYSEQ::s2t1));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x2, y3)), module, POLYSEQ::s2t2));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x3, y3)), module, POLYSEQ::s2t3));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x4, y3)), module, POLYSEQ::s2t4));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x1, y4)), module, POLYSEQ::s2L1));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x2, y4)), module, POLYSEQ::s2L2));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x3, y4)), module, POLYSEQ::s2L3));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x4, y4)), module, POLYSEQ::s2L4));

		// rhythm
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x1, y5)), module, POLYSEQ::r1));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x2, y5)), module, POLYSEQ::r2));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x3, y5)), module, POLYSEQ::r3));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x4, y5)), module, POLYSEQ::r4));

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x1, y6)), module, POLYSEQ::s1r1, POLYSEQ::s1r1L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x2, y6)), module, POLYSEQ::s1r2, POLYSEQ::s1r2L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y6)), module, POLYSEQ::s1r3, POLYSEQ::s1r3L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x4, y6)), module, POLYSEQ::s1r4, POLYSEQ::s1r4L));

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x1, y7)), module, POLYSEQ::s2r1, POLYSEQ::s2r1L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x2, y7)), module, POLYSEQ::s2r2, POLYSEQ::s2r2L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y7)), module, POLYSEQ::s2r3, POLYSEQ::s2r3L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x4, y7)), module, POLYSEQ::s2r4, POLYSEQ::s2r4L));

		// bottom controls
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10, 99.25)), module, POLYSEQ::tempo));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(25, 95)), module, POLYSEQ::start));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(32.5, 95)), module, POLYSEQ::reset));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(25, 102.5)), module, POLYSEQ::trig));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(32.5, 102.5)), module, POLYSEQ::next));

		//outputs
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(8, 115.24)), module, POLYSEQ::cv1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(16, 115.24)), module, POLYSEQ::gate1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(24, 115.24)), module, POLYSEQ::cv2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(32, 115.24)), module, POLYSEQ::gate2));


		//temp output for testing purposes
		//addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20, 115.24)), module, POLYSEQ::tempout));
	}

};


Model* modelPOLYSEQ = createModel<POLYSEQ, POLYSEQWidget>("POLYSEQ");