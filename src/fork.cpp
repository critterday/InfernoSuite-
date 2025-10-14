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
		configParam(DIAL1_PARAM, -5.f, 5.f, 0.f, "");
		configParam(BUTTON2_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DIAL2_PARAM, -5.f, 5.f, 0.f, "");
		configParam(BUTTON3_PARAM, 0.f, 1.f, 0.f, "");
		configParam(DIAL3_PARAM, -5.f, 5.f, 0.f, "");
		configInput(CVIN_INPUT, "");
		configInput(GATEIN_INPUT, "");
		configOutput(CVOUT1_OUTPUT, "");
		configOutput(GATEOUT1_OUTPUT, "");
		configOutput(CVOUT2_OUTPUT, "");
		configOutput(GATEOUT2_OUTPUT, "");
		configOutput(CVOUT3_OUTPUT, "");
		configOutput(GATEOUT3_OUTPUT, "");
		configOutput(CVOUT4_OUTPUT, "");
		configOutput(GATEOUT4_OUTPUT, "");
	}

	void process(const ProcessArgs& args) override {
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
		addParam(createParamCentered<VCVButton>(mm2px(Vec(5.62, 77.5)), module, FORK::BUTTON2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(15.24, 77.5)), module, FORK::DIAL2_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(5.62, 102.5)), module, FORK::BUTTON3_PARAM));
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

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.86, 77.5)), module, FORK::LIGHT2_LIGHT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(26.86, 102.5)), module, FORK::LIGHT3_LIGHT));
	}
};


Model* modelFORK = createModel<FORK, FORKWidget>("FORK");