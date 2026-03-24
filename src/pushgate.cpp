#include "plugin.hpp"


struct PUSHGATE : Module {
	enum ParamId {
		ENUMS(push, 8),
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		upout,
		downout,
		OUTPUTS_LEN
	};
	enum LightId {
		ENUMS(pushL, 8),
		LIGHTS_LEN
	};

	PUSHGATE() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
	}

	

	void process(const ProcessArgs& args) override {
	
		outputs[upout].setChannels(8);
		outputs[downout].setChannels(8);

		for(int i = 0; i <8; i++){
			float pushval = params[push + i].getValue();
			lights[pushL + i].setBrightness(pushval);
			float voltsout = 10 * pushval;
			outputs[upout].setVoltage(voltsout, i);
			outputs[downout].setVoltage(voltsout, i);
		}

	}
};


struct PUSHGATEWidget : ModuleWidget {
	PUSHGATEWidget(PUSHGATE* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PUSHGATE.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x = 5.08;
		float upy = 19;
		float downy = 118;
		float yCoords[8] = {28.5, 40, 51.5, 63, 74.5, 86, 97.5, 109};

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[0])), module, PUSHGATE::push + 0, PUSHGATE::pushL + 0));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[1])), module, PUSHGATE::push + 1, PUSHGATE::pushL + 1));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[2])), module, PUSHGATE::push + 2, PUSHGATE::pushL + 2));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[3])), module, PUSHGATE::push + 3, PUSHGATE::pushL + 3));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[4])), module, PUSHGATE::push + 4, PUSHGATE::pushL + 4));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[5])), module, PUSHGATE::push + 5, PUSHGATE::pushL + 5));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[6])), module, PUSHGATE::push + 6, PUSHGATE::pushL + 6));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x, yCoords[7])), module, PUSHGATE::push + 7, PUSHGATE::pushL + 7));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, upy)), module, PUSHGATE::upout));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, downy)), module, PUSHGATE::downout));
	}
};


Model* modelPUSHGATE = createModel<PUSHGATE, PUSHGATEWidget>("PUSHGATE");