#include "plugin.hpp"
#include <algorithm>


struct SATURN : Module {

	float phase1;
	float phase2;
	float phase3;
	float phase4;
	float phase5;

	float phase1a;
	float phase2a;
	float phase3a;
	float phase4a;
	float phase5a;

	float phase1b;
	float phase2b;
	float phase3b;
	float phase4b;
	float phase5b;

	bool hold = false;
	bool detune = false;

	float atk;
	float rls;

	enum ParamId {
		pitch1,
		pitch2,
		pitch3,
		pitch4,
		pitch5,
		on1,
		on2,
		on3,
		on4,
		on5,
		mod1,
		mod2,
		mod3,
		mod4,
		mod5,
		modatt,
		holdbutton,
		detunebutton,
		atkknob,
		rlsknob,
		cvbutton,
		spreadknob,
		PARAMS_LEN
	};
	enum InputId {
		modinput,
		gateinput,
		cvin,
		INPUTS_LEN
	};
	enum OutputId {
		sawOut,
		cvOut,
		gateOut,
		debugOut,
		OUTPUTS_LEN
	};
	enum LightId {
		on1L,
		on2L,
		on3L,
		on4L,
		on5L,
		mod1L,
		mod2L,
		mod3L,
		mod4L,
		mod5L,
		gateL,
		cvL,
		LIGHTS_LEN
	};

	SATURN() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(pitch1, -5, 5, 0, "pitch parameter");
		configParam(pitch2, -5, 5, 0, "pitch parameter");
		configParam(pitch3, -5, 5, 0, "pitch parameter");
		configParam(pitch4, -5, 5, 0, "pitch parameter");
		configParam(pitch5, -5, 5, 0, "pitch parameter");
		
		configParam(modatt, -1, 1, 0, "mod attenuverter");

		configParam(on1, 0.f, 1.f, 0.f, "oscillator on");
		configParam(on2, 0.f, 1.f, 0.f, "oscillator on");
		configParam(on3, 0.f, 1.f, 0.f, "oscillator on");
		configParam(on4, 0.f, 1.f, 0.f, "oscillator on");
		configParam(on5, 0.f, 1.f, 0.f, "oscillator on");

		configParam(mod1, 0.f, 1.f, 0.f, "mod oscillator");
		configParam(mod2, 0.f, 1.f, 0.f, "mod oscillator");
		configParam(mod3, 0.f, 1.f, 0.f, "mod oscillator");
		configParam(mod4, 0.f, 1.f, 0.f, "mod oscillator");
		configParam(mod5, 0.f, 1.f, 0.f, "mod oscillator");

		configParam(spreadknob, 0.f, 1.f, 0.f, "saw spread control");
	}

	void process(const ProcessArgs& args) override {

		// control button lights
		lights[on1L].setBrightness(params[on1].getValue());
		lights[on2L].setBrightness(params[on2].getValue());
		lights[on3L].setBrightness(params[on3].getValue());
		lights[on4L].setBrightness(params[on4].getValue());
		lights[on5L].setBrightness(params[on5].getValue());

		lights[mod1L].setBrightness(params[mod1].getValue());
		lights[mod2L].setBrightness(params[mod2].getValue());
		lights[mod3L].setBrightness(params[mod3].getValue());
		lights[mod4L].setBrightness(params[mod4].getValue());
		lights[mod5L].setBrightness(params[mod5].getValue());

		//hold button light
		lights[gateL].setBrightness(params[holdbutton].getValue());

		//set cv and gate outputs
		outputs[cvOut].setChannels(5);
		outputs[gateOut].setChannels(5);

		outputs[cvOut].setVoltage(params[pitch1].getValue(), 0);
		outputs[cvOut].setVoltage(params[pitch2].getValue(), 1);
		outputs[cvOut].setVoltage(params[pitch3].getValue(), 2);
		outputs[cvOut].setVoltage(params[pitch4].getValue(), 3);
		outputs[cvOut].setVoltage(params[pitch5].getValue(), 4);

		outputs[gateOut].setVoltage(params[on1].getValue() * 10, 0);
		outputs[gateOut].setVoltage(params[on2].getValue() * 10, 1);
		outputs[gateOut].setVoltage(params[on3].getValue() * 10, 2);
		outputs[gateOut].setVoltage(params[on4].getValue() * 10, 3);
		outputs[gateOut].setVoltage(params[on5].getValue() * 10, 4);

		//calculate mod amount
		float modvolt = params[modatt].getValue() * inputs[modinput].getVoltage() * 0.25;

		//set pitch cv channels
		float pitchoff1 = 0.f;
		float pitchoff2 = 0.f;
		float pitchoff3 = 0.f;
		float pitchoff4 = 0.f;
		float pitchoff5 = 0.f;

		if(params[cvbutton].getValue() == 1.f){
			pitchoff1 = inputs[cvin].getVoltage(0);
			pitchoff2 = inputs[cvin].getVoltage(1);
			pitchoff3 = inputs[cvin].getVoltage(2);
			pitchoff4 = inputs[cvin].getVoltage(3);
			pitchoff5 = inputs[cvin].getVoltage(4);
		} else {
			pitchoff1 = inputs[cvin].getVoltage(0);
			pitchoff2 = inputs[cvin].getVoltage(0);
			pitchoff3 = inputs[cvin].getVoltage(0);
			pitchoff4 = inputs[cvin].getVoltage(0);
			pitchoff5 = inputs[cvin].getVoltage(0);
		}

		lights[cvL].setBrightness(params[cvbutton].getValue());

		float spreadmax = 0.0208;
		float spread = params[spreadknob].getValue() * spreadmax;

		outputs[debugOut].setVoltage(spread);

		//calculate frequencies based on knob input
		float freq1 = dsp::FREQ_C4 * std::pow(2.f, params[pitch1].getValue() + modvolt * params[mod1].getValue() + pitchoff1);
		float freq2 = dsp::FREQ_C4 * std::pow(2.f, params[pitch2].getValue() + modvolt * params[mod2].getValue() + pitchoff2);
		float freq3 = dsp::FREQ_C4 * std::pow(2.f, params[pitch3].getValue() + modvolt * params[mod3].getValue() + pitchoff3);
		float freq4 = dsp::FREQ_C4 * std::pow(2.f, params[pitch4].getValue() + modvolt * params[mod4].getValue() + pitchoff4);
		float freq5 = dsp::FREQ_C4 * std::pow(2.f, params[pitch5].getValue() + modvolt * params[mod5].getValue() + pitchoff5);

		float freq1a = dsp::FREQ_C4 * std::pow(2.f, params[pitch1].getValue() + modvolt * params[mod1].getValue() + pitchoff1 + spread);
		float freq2a = dsp::FREQ_C4 * std::pow(2.f, params[pitch2].getValue() + modvolt * params[mod2].getValue() + pitchoff2 + spread);
		float freq3a = dsp::FREQ_C4 * std::pow(2.f, params[pitch3].getValue() + modvolt * params[mod3].getValue() + pitchoff3 + spread);
		float freq4a = dsp::FREQ_C4 * std::pow(2.f, params[pitch4].getValue() + modvolt * params[mod4].getValue() + pitchoff4 + spread);
		float freq5a = dsp::FREQ_C4 * std::pow(2.f, params[pitch5].getValue() + modvolt * params[mod5].getValue() + pitchoff5 + spread);

		float freq1b = dsp::FREQ_C4 * std::pow(2.f, params[pitch1].getValue() + modvolt * params[mod1].getValue() + pitchoff1 - spread);
		float freq2b = dsp::FREQ_C4 * std::pow(2.f, params[pitch2].getValue() + modvolt * params[mod2].getValue() + pitchoff2 - spread);
		float freq3b = dsp::FREQ_C4 * std::pow(2.f, params[pitch3].getValue() + modvolt * params[mod3].getValue() + pitchoff3 - spread);
		float freq4b = dsp::FREQ_C4 * std::pow(2.f, params[pitch4].getValue() + modvolt * params[mod4].getValue() + pitchoff4 - spread);
		float freq5b = dsp::FREQ_C4 * std::pow(2.f, params[pitch5].getValue() + modvolt * params[mod5].getValue() + pitchoff5 - spread);

		//phases stuff i dont understand at all
		phase1 += freq1 * args.sampleTime;
		if (phase1 >= 1.f){
			phase1 -= 1.f;
		}
		phase2 += freq2 * args.sampleTime;
		if (phase2 >= 1.f){
			phase2 -= 1.f;
		}
		phase3 += freq3 * args.sampleTime;
		if (phase3 >= 1.f){
			phase3 -= 1.f;
		}
		phase4 += freq4 * args.sampleTime;
		if (phase4 >= 1.f){
			phase4 -= 1.f;
		}
		phase5 += freq5 * args.sampleTime;
		if (phase5 >= 1.f){
			phase5 -= 1.f;
		}

		//a

		phase1a += freq1a * args.sampleTime;
		if (phase1a >= 1.f){
			phase1a -= 1.f;
		}
		phase2a += freq2a * args.sampleTime;
		if (phase2a >= 1.f){
			phase2a -= 1.f;
		}
		phase3a += freq3a * args.sampleTime;
		if (phase3a >= 1.f){
			phase3a -= 1.f;
		}
		phase4a += freq4a * args.sampleTime;
		if (phase4a >= 1.f){
			phase4a -= 1.f;
		}
		phase5a += freq5a * args.sampleTime;
		if (phase5a >= 1.f){
			phase5a -= 1.f;
		}

		//b

		phase1b += freq1b * args.sampleTime;
		if (phase1b >= 1.f){
			phase1b -= 1.f;
		}
		phase2b += freq2b * args.sampleTime;
		if (phase2b >= 1.f){
			phase2b -= 1.f;
		}
		phase3b += freq3b * args.sampleTime;
		if (phase3b >= 1.f){
			phase3b -= 1.f;
		}
		phase4b += freq4b * args.sampleTime;
		if (phase4b >= 1.f){
			phase4b -= 1.f;
		}
		phase5b += freq5b * args.sampleTime;
		if (phase5b >= 1.f){
			phase5b -= 1.f;
		}


		// saw waves
		float saw1 = ((sawgen(phase1) + sawgen(phase1a) + sawgen(phase1b))/3);
		float saw2 = ((sawgen(phase2) + sawgen(phase2a) + sawgen(phase2b))/3);
		float saw3 = ((sawgen(phase3) + sawgen(phase3a) + sawgen(phase3b))/3);
		float saw4 = ((sawgen(phase4) + sawgen(phase4a) + sawgen(phase4b))/3);
		float saw5 = ((sawgen(phase5) + sawgen(phase5a) + sawgen(phase5b))/3);

		//mixer section
		float oscs = params[on1].getValue() + params[on2].getValue() + params[on3].getValue() + params[on4].getValue() + params[on5].getValue();

		float mix = ((saw1 * params[on1].getValue()) + (saw2 * params[on2].getValue()) + (saw3 * params[on3].getValue()) + (saw4 * params[on4].getValue()) + (saw5 * params[on5].getValue()));
		
		//check for hold button or gate input
		if((params[holdbutton].getValue() == 1.f) || (inputs[gateinput].getVoltage() > 5.f)){
			hold = true;
		} else{
			hold = false;
		}

		// prototype volume limiter
		float boost = 0.5;
		if((oscs == 0) || !hold){
			mix = 0.f;
		} else{
			mix = (mix/oscs) + (boost * oscs);
		}
		
		outputs[sawOut].setVoltage(mix);
	}

	float sawgen(float phase){
		return (10 * phase) - 5;
	}
};


struct SATURNWidget : ModuleWidget {
	SATURNWidget(SATURN* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SATURN.svg")));

		float x1 = 10;
		float x2 = 20;
		float x3 = 30;

		float initY = 15;
		float ySpacing = 11.5;
		
		float y1 = initY;
		float y2 = initY + ySpacing;
		float y3 = initY + 2*ySpacing;
		float y4 = initY + 3*ySpacing;
		float y5 = initY + 4*ySpacing;


		//screws
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		//on buttons
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y1)), module, SATURN::on1, SATURN::on1L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y2)), module, SATURN::on2, SATURN::on2L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y3)), module, SATURN::on3, SATURN::on3L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y4)), module, SATURN::on4, SATURN::on4L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(x3, y5)), module, SATURN::on5, SATURN::on5L));
		
		//pitch knobs
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(x2, y1)), module, SATURN::pitch1));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(x2, y2)), module, SATURN::pitch2));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(x2, y3)), module, SATURN::pitch3));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(x2, y4)), module, SATURN::pitch4));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(x2, y5)), module, SATURN::pitch5));
		
		//mod buttons
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y1)), module, SATURN::mod1, SATURN::mod1L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y2)), module, SATURN::mod2, SATURN::mod2L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y3)), module, SATURN::mod3, SATURN::mod3L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y4)), module, SATURN::mod4, SATURN::mod4L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y5)), module, SATURN::mod5, SATURN::mod5L));

		//mod input and knob
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(11.5, 92.5)), module, SATURN::modinput));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(11.5, 85)), module, SATURN::modatt));

		
		
		//output (deprecated, uses debug out for main out now)
		//addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2, 110)), module, SATURN::sawOut));
		
		//gate input and hold button
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(27, 87.5)), module, SATURN::gateinput));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(34.5, 87.5)), module, SATURN::holdbutton, SATURN::gateL));

		//cv and gate outputs
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35, 103)), module, SATURN::cvOut));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(35, 112.5)), module, SATURN::gateOut));

		// cv input and selector
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(9, 115.5)), module, SATURN::cvin));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(9, 108)), module, SATURN::cvbutton, SATURN::cvL));

		//spread
		addParam(createParamCentered<Trimpot>(mm2px(Vec(31.64, 75)), module, SATURN::spreadknob));

		//final out 
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2, 120)), module, SATURN::sawOut));


	}
};


Model* modelSATURN = createModel<SATURN, SATURNWidget>("SATURN");