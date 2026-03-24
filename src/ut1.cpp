#include "plugin.hpp"


struct UT1 : Module {
	enum ParamId {
		attknob,
		offknob,
		g1,
		g2,
		g3,
		ENUMS(cv, 3),
		cvs1,
		cvs2,
		cvs3,
		PARAMS_LEN
	};
	enum InputId {
		attin,
		offin,
		INPUTS_LEN
	};
	enum OutputId {
		attout,
		offout,
		g1out,
		g2out,
		g3out,
		cvout,
		OUTPUTS_LEN
	};
	enum LightId {
		g1L,
		g2L,
		g3L,
		ENUMS(cvLs, 3),
		LIGHTS_LEN
	};

	UT1() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(attknob, -1.f, 1.f, 0.f, "Attenuversion Knob");
		configParam(offknob, -5.f, 5.f, 0.f, "Offset Knob");
		configParam(g1, 0.f, 1.f, 0.f, "gate 1");
		configParam(g2, 0.f, 1.f, 0.f, "gate 1");
		configParam(g3, 0.f, 1.f, 0.f, "gate 1");
		configParam(cv + 0, -5, 5, 0);
		configParam(cv + 1, -5, 5, 0);
		configParam(cv + 2, -5, 5, 0);
	}


	void process(const ProcessArgs& args) override {
		//att
		outputs[attout].setVoltage(inputs[attin].getVoltage() * params[attknob].getValue());
		//off
		outputs[offout].setVoltage(inputs[offin].getVoltage() + params[offknob].getValue());

		//gates
		makeGate(g1, g1L, g1out);
		makeGate(g2, g2L, g2out);
		makeGate(g3, g3L, g3out);

		//3-supply
		if(buttonTrue(cvs3)){
			channel = 2;
		} else if (buttonTrue(cvs2)) {
			channel = 1;
		} else if (buttonTrue(cvs1)) {
			channel = 0;
		}

		for (int i = 0; i<3; i++){
			lightvals[i] = 0.f;
		}
		lightvals[channel] = 1.f;
		for (int i = 0; i<3; i++){
			lights[cvLs + i].setBrightness(lightvals[i]); 
		}

		outputs[cvout].setVoltage(params[cv+channel].getValue());
		



		
		
	}

	int channel;

	float lightvals[3] = {0.f, 0.f, 0.f};

	//int state;

	void makeGate(int param, int light, int out){
		float paramval = params[param].getValue();
		lights[light].setBrightness(paramval);
		if( paramval == 1.f){
			outputs[out].setVoltage(10.f);
		} else {
			outputs[out].setVoltage(0.f);
		}
	}

	void buttonOn(int param, int light){
		lights[light].setBrightness(params[param].getValue());
	}
	
	bool buttonTrue(int param){
		if(params[param].getValue() == 1.f){
			return true;
		} else {
			return false;
		}
	}
};


struct UT1Widget : ModuleWidget {
	UT1Widget(UT1* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/UT1.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		//attenuverter
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 19)), module, UT1::attin));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 19)), module, UT1::attout));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 10)), module, UT1::attknob));
	
		//offset
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.08, 41.5)), module, UT1::offin));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 41.5)), module, UT1::offout));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 32.5)), module, UT1::offknob));


		// gate generator
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(5.08, 55)), module, UT1::g1, UT1::g1L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(5.08, 64)), module, UT1::g2, UT1::g2L));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(5.08, 73)), module, UT1::g3, UT1::g3L));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 55)), module, UT1::g1out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 64)), module, UT1::g2out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(15.24, 73)), module, UT1::g3out));

		//cv generator
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(15.24, 86.5)), module, UT1::cv+0));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(15.24, 95.5)), module, UT1::cv+1));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(15.24, 104.5)), module, UT1::cv+2));

		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.08, 86.5)), module, UT1::cvs1, UT1::cvLs + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.08, 95.5)), module, UT1::cvs2, UT1::cvLs + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.08, 104.5)), module, UT1::cvs3, UT1::cvLs + 2));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 113.5)), module, UT1::cvout));


	}
};


Model* modelUT1 = createModel<UT1, UT1Widget>("UT1");