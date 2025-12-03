#include "plugin.hpp"


struct DEPOT : Module {
	enum ParamId {
		knob,
		b1,
		b2,
		b3,
		b4,
		b5,
		b6,
		PARAMS_LEN
	};
	enum InputId {
		INPUTS_LEN
	};
	enum OutputId {
		out,
		OUTPUTS_LEN
	};
	enum LightId {
		b1L,
		b2L,
		b3L,
		b4L,
		b5L,
		b6L,
		LIGHTS_LEN
	};

	DEPOT() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(knob, -10.f, 10.f, 0.f, "");
		configParam(b1, 0.f, 1.f, 0.f, "");
		configParam(b2, 0.f, 1.f, 0.f, "");
		configParam(b3, 0.f, 1.f, 0.f, "");
		configParam(b4, 0.f, 1.f, 0.f, "");
		configParam(b5, 0.f, 1.f, 0.f, "");
		configParam(b6, 0.f, 1.f, 0.f, "");
	}

	int state = 0;

	void process(const ProcessArgs& args) override {

		//check buttons
		if (params[b1].getValue() == 1.f){
			state = 0;
		} else if (params[b2].getValue() == 1.f){
			state = 1;
		} else if (params[b3].getValue() == 1.f){
			state = 2;
		} else if (params[b4].getValue() == 1.f){
			state = 3;
		} else if (params[b5].getValue() == 1.f){
			state = 4;
		} else if (params[b6].getValue() == 1.f){
			state = 5;
		}

		//set lights
		if (state == 0){
			lights[b1L].setBrightness(1.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
		} else if (state == 1){
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(1.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
		} else if (state == 2){
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(1.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
		} else if (state == 3){
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(1.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
		} else if (state == 4){
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(1.f);
			lights[b6L].setBrightness(0.f);
		} else if (state == 5){
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(1.f);
		}

		//assign bounds
		if (state == 0){
			outputs[out].setVoltage(params[knob].getValue());
		} else if (state == 1){
			outputs[out].setVoltage((params[knob].getValue() / 2));
		} else if (state == 2){
			outputs[out].setVoltage((params[knob].getValue() /10));
		} else if (state == 3){
			outputs[out].setVoltage(((params[knob].getValue() /2) + 5));
		} else if (state == 4){
			outputs[out].setVoltage(((params[knob].getValue()/4)+2.5));
		} else if (state == 5){
			outputs[out].setVoltage(((params[knob].getValue()/20)+.5));
		}
	}
};


struct DEPOTWidget : ModuleWidget {
	DEPOTWidget(DEPOT* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/DEPOT.svg")));

		//screws and panel

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// knob
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 20)), module, DEPOT::knob));

		// buttons
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.773, 40)), module, DEPOT::b1, DEPOT::b1L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.773, 65)), module, DEPOT::b2, DEPOT::b2L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(5.773, 90)), module, DEPOT::b3, DEPOT::b3L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(14.547, 40)), module, DEPOT::b4, DEPOT::b4L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(14.547, 65)), module, DEPOT::b5, DEPOT::b5L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(14.547, 90)), module, DEPOT::b6, DEPOT::b6L));

		//output
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 115)), module, DEPOT::out));
	}
};


Model* modelDEPOT = createModel<DEPOT, DEPOTWidget>("DEPOT");