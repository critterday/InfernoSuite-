#include "plugin.hpp"


struct PUSHSYNC : Module {
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

	PUSHSYNC() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
	}

	int channel = 0;
	float voltsout = 1;
	bool lightvals[8] = {false, false, false, false, false, false, false, false};

	void process(const ProcessArgs& args) override {

		for (int i = 0; i < 8; i++){
			if(params[push + i].getValue() == 1.f){
				channel = i;
			}
			lightvals[i] = false;
		}

		lightvals[channel] = true;

		for(int i = 0; i < 8; i++){
			if(lightvals[i]){
				lights[pushL + i].setBrightness(1.f);
			} else {
				lights[pushL + i].setBrightness(0.f);
			}
		}

		voltsout = (float)(channel + 1);

		outputs[upout].setVoltage(voltsout);
		outputs[downout].setVoltage(voltsout);

	}
};


struct PUSHSYNCWidget : ModuleWidget {
	PUSHSYNCWidget(PUSHSYNC* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/PUSHSYNC.svg")));

		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x = 5.08;
		float upy = 19;
		float downy = 118;
		float yCoords[8] = {28.5, 40, 51.5, 63, 74.5, 86, 97.5, 109};

		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[0])), module, PUSHSYNC::push + 0, PUSHSYNC::pushL + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[1])), module, PUSHSYNC::push + 1, PUSHSYNC::pushL + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[2])), module, PUSHSYNC::push + 2, PUSHSYNC::pushL + 2));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[3])), module, PUSHSYNC::push + 3, PUSHSYNC::pushL + 3));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[4])), module, PUSHSYNC::push + 4, PUSHSYNC::pushL + 4));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[5])), module, PUSHSYNC::push + 5, PUSHSYNC::pushL + 5));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[6])), module, PUSHSYNC::push + 6, PUSHSYNC::pushL + 6));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x, yCoords[7])), module, PUSHSYNC::push + 7, PUSHSYNC::pushL + 7));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, upy)), module, PUSHSYNC::upout));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x, downy)), module, PUSHSYNC::downout));
	}
};


Model* modelPUSHSYNC = createModel<PUSHSYNC, PUSHSYNCWidget>("PUSHSYNC");