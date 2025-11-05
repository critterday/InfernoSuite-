#include "plugin.hpp"


struct FORK : Module {
	enum ParamId {
		DIAL1_PARAM,
		BUTTON2_PARAM,
		DIAL2_PARAM,
		BUTTON3_PARAM,
		DIAL3_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		CVIN_INPUT,
		GATEIN_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		CVOUT1_OUTPUT,
		GATEOUT1_OUTPUT,
		CVOUT2_OUTPUT,
		GATEOUT2_OUTPUT,
		CVOUT3_OUTPUT,
		GATEOUT3_OUTPUT,
		CVOUT4_OUTPUT,
		GATEOUT4_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHT2_LIGHT,
		LIGHT3_LIGHT,
		LIGHTS_LEN
	};

	FORK() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(DIAL1_PARAM, -5.f, 5.f, 0.f, "1/2 split");
		configParam(BUTTON2_PARAM, 0.f, 1.f, 0.f, "Tine 3 toggle");
		configParam(DIAL2_PARAM, -5.f, 5.f, 0.f, "2/3 split");
		configParam(BUTTON3_PARAM, 0.f, 1.f, 0.f, "Tine 4 toggle");
		configParam(DIAL3_PARAM, -5.f, 5.f, 0.f, "3/4 split");
		configInput(CVIN_INPUT, "CV");
		configInput(GATEIN_INPUT, "Gate");
		configOutput(CVOUT1_OUTPUT, "CV #1");
		configOutput(GATEOUT1_OUTPUT, "Gate #1");
		configOutput(CVOUT2_OUTPUT, "CV #2");
		configOutput(GATEOUT2_OUTPUT, "Gate #2");
		configOutput(CVOUT3_OUTPUT, "CV #3");
		configOutput(GATEOUT3_OUTPUT, "Gate #3");
		configOutput(CVOUT4_OUTPUT, "CV #4");
		configOutput(GATEOUT4_OUTPUT, "Gate #4");
	}
	
	//sets states of last 2 tines
	bool twostate = false;
	bool threestate = false;
	
	void process(const ProcessArgs& args) override {

		//maintains last 2 tine states
		if(params[BUTTON2_PARAM].getValue() == 1.f){
			
			// turn on tine 3
			lights[LIGHT2_LIGHT].setBrightness(1.f);
			twostate = true;

			// check tine 4
			if(params[BUTTON3_PARAM].getValue() > 0.f){

				// turn on tine 4
				lights[LIGHT3_LIGHT].setBrightness(1.f);
				threestate = true;

			}else { 
				// turn off tine 4
				lights[LIGHT3_LIGHT].setBrightness(0.f);
				threestate = false;
			}
		} else {
			//turn off tine 3
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			twostate = false;

			//turn off tine 4
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			threestate = false;
			params[BUTTON3_PARAM].setValue(0.f);
		}

		//checks how many channels there are connected to CV Input and sets output channels
		int channelcount = std::max(1, inputs[CVIN_INPUT].getChannels());

		outputs[CVOUT1_OUTPUT].setChannels(channelcount);
		outputs[GATEOUT1_OUTPUT].setChannels(channelcount);
		outputs[CVOUT2_OUTPUT].setChannels(channelcount);
		outputs[GATEOUT2_OUTPUT].setChannels(channelcount);
		outputs[CVOUT3_OUTPUT].setChannels(channelcount);
		outputs[GATEOUT3_OUTPUT].setChannels(channelcount);
		outputs[CVOUT4_OUTPUT].setChannels(channelcount);
		outputs[GATEOUT4_OUTPUT].setChannels(channelcount);

		//establishes div points
		float divone = params[DIAL1_PARAM].getValue();
		float divtwo = params[DIAL2_PARAM].getValue();
		float divthree = params[DIAL3_PARAM].getValue();
		

		//iterates through channels
		for (int c = 0; c < channelcount; c++) {

			float cvvolts = inputs[CVIN_INPUT].getPolyVoltage(c);
			float gatevolts = inputs[GATEIN_INPUT].getPolyVoltage(c);

			if(cvvolts >= divone){
				outputs[CVOUT1_OUTPUT].setVoltage(cvvolts, c);
				outputs[GATEOUT1_OUTPUT].setVoltage(gatevolts, c);

				outputs[GATEOUT2_OUTPUT].setVoltage(0.f, c);
				outputs[GATEOUT3_OUTPUT].setVoltage(0.f, c);
				outputs[GATEOUT4_OUTPUT].setVoltage(0.f, c);
			} else {
				if (cvvolts < divtwo and twostate == true){
					if (cvvolts < divthree and threestate == true){
						outputs[CVOUT4_OUTPUT].setVoltage(cvvolts, c);
						outputs[GATEOUT4_OUTPUT].setVoltage(gatevolts, c);

						outputs[GATEOUT1_OUTPUT].setVoltage(0.f, c);
						outputs[GATEOUT2_OUTPUT].setVoltage(0.f, c);
						outputs[GATEOUT3_OUTPUT].setVoltage(0.f, c);
					} else {
						outputs[CVOUT3_OUTPUT].setVoltage(cvvolts, c);
						outputs[GATEOUT3_OUTPUT].setVoltage(gatevolts, c);

						outputs[GATEOUT1_OUTPUT].setVoltage(0.f, c);
						outputs[GATEOUT2_OUTPUT].setVoltage(0.f, c);
						outputs[GATEOUT4_OUTPUT].setVoltage(0.f, c);
					}
				} else {
					outputs[CVOUT2_OUTPUT].setVoltage(cvvolts, c);
					outputs[GATEOUT2_OUTPUT].setVoltage(gatevolts, c);

					outputs[GATEOUT1_OUTPUT].setVoltage(0.f, c);
					outputs[GATEOUT3_OUTPUT].setVoltage(0.f, c);
					outputs[GATEOUT4_OUTPUT].setVoltage(0.f, c);
				}
			}
			
		}

	}
};


struct FORKWidget : ModuleWidget {
	FORKWidget(FORK* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/FORK.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 52.5)), module, FORK::DIAL1_PARAM));
		addParam(createParamCentered<VCVLatch>(mm2px(Vec(5.62, 77.5)), module, FORK::BUTTON2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 77.5)), module, FORK::DIAL2_PARAM));
		addParam(createParamCentered<VCVLatch>(mm2px(Vec(5.62, 102.5)), module, FORK::BUTTON3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 102.5)), module, FORK::DIAL3_PARAM));

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10.16, 22.5)), module, FORK::CVIN_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(20.32, 22.5)), module, FORK::GATEIN_INPUT));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 40)), module, FORK::CVOUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.32, 40)), module, FORK::GATEOUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 65)), module, FORK::CVOUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.32, 65)), module, FORK::GATEOUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 90)), module, FORK::CVOUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.32, 90)), module, FORK::GATEOUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 115)), module, FORK::CVOUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(20.32, 115)), module, FORK::GATEOUT4_OUTPUT));

		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(26.86, 77.5)), module, FORK::LIGHT2_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(26.86, 102.5)), module, FORK::LIGHT3_LIGHT));
	}
};


Model* modelFORK = createModel<FORK, FORKWidget>("FORK");