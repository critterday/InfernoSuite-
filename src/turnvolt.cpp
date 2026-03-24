#include "plugin.hpp"


struct TURNVOLT : Module {
	enum ParamId {
		ENUMS(turn, 8),
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
		LIGHTS_LEN
	};

	TURNVOLT() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(turn + 0, -5, 5, 0);
		configParam(turn + 1, -5, 5, 0);
		configParam(turn + 2, -5, 5, 0);
		configParam(turn + 3, -5, 5, 0);
		configParam(turn + 4, -5, 5, 0);
		configParam(turn + 5, -5, 5, 0);
		configParam(turn + 6, -5, 5, 0);
		configParam(turn + 7, -5, 5, 0);
	}



	void process(const ProcessArgs& args) override {

		outputs[upout].setChannels(8);
		outputs[downout].setChannels(8);

		for(int i = 0; i<8; i++){
			float voltsout = params[turn + i].getValue();
			outputs[upout].setVoltage(voltsout, i);
			outputs[downout].setVoltage(voltsout, i);
		}
	}
};


struct TURNVOLTWidget : ModuleWidget {
	TURNVOLTWidget(TURNVOLT* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/TURNVOLT.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x = 5.08;
		float upy = 19;
		float downy = 118;
		float yCoords[8] = {28.5, 40, 51.5, 63, 74.5, 86, 97.5, 109};

		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[0])), module, TURNVOLT::turn + 0));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[1])), module, TURNVOLT::turn + 1));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[2])), module, TURNVOLT::turn + 2));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[3])), module, TURNVOLT::turn + 3));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[4])), module, TURNVOLT::turn + 4));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[5])), module, TURNVOLT::turn + 5));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[6])), module, TURNVOLT::turn + 6));
		addParam(createParamCentered<Trimpot>(mm2px(Vec(x, yCoords[7])), module, TURNVOLT::turn + 7));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, upy)), module, TURNVOLT::upout));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, downy)), module, TURNVOLT::downout));
	}
};


Model* modelTURNVOLT = createModel<TURNVOLT, TURNVOLTWidget>("TURNVOLT");