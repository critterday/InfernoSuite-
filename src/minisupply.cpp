#include "plugin.hpp"


struct MiniSUPPLY : Module {
	enum ParamId {
		b1,
		b2,
		b3,
		b4,
		b5,
		b6,
		b7,
		b8,
		knob1,
		knob2,
		knob3,
		knob4,
		knob5,
		knob6,
		knob7,
		knob8,
		PARAMS_LEN
	};
	enum InputId {
		syncIn,
		INPUTS_LEN
	};
	enum OutputId {
		out,
		OUTPUTS_LEN
	};
	enum LightId {
		SYNC_LIGHT,
		b1L,
		b2L,
		b3L,
		b4L,
		b5L,
		b6L,
		b7L,
		b8L,
		LIGHTS_LEN
	};

	MiniSUPPLY() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(knob1, -10.f, 10.f, 0.f, "set voltage #1");
		configParam(knob2, -10.f, 10.f, 0.f, "set voltage #2");
		configParam(knob3, -10.f, 10.f, 0.f, "set voltage #3");
		configParam(knob4, -10.f, 10.f, 0.f, "set voltage #4");
		configParam(knob5, -10.f, 10.f, 0.f, "set voltage #5");
		configParam(knob6, -10.f, 10.f, 0.f, "set voltage #6");
		configParam(knob7, -10.f, 10.f, 0.f, "set voltage #7");
		configParam(knob8, -10.f, 10.f, 0.f, "set voltage #8");
		configParam(b1, 0.f, 1.f, 0.f, "");
		configParam(b2, 0.f, 1.f, 0.f, "");
		configParam(b3, 0.f, 1.f, 0.f, "");
		configParam(b4, 0.f, 1.f, 0.f, "");
		configParam(b5, 0.f, 1.f, 0.f, "");
		configParam(b6, 0.f, 1.f, 0.f, "");
		configParam(b7, 0.f, 1.f, 0.f, "");
		configParam(b8, 0.f, 1.f, 0.f, "");
	}

	float channel = 1;

	void process(const ProcessArgs& args) override {

		// check if connected
		if(inputs[syncIn].isConnected() == true){
			//if connected use sync voltage

			lights[SYNC_LIGHT].setBrightness(1.f);

			if(inputs[syncIn].getVoltage() == 1.f){
				channel = 1;
			} else if(inputs[syncIn].getVoltage() == 2.f){
				channel = 2;
			} else if(inputs[syncIn].getVoltage() == 3.f){
				channel = 3;
			} else if(inputs[syncIn].getVoltage() == 4.f){
				channel = 4;
			} else if(inputs[syncIn].getVoltage() == 5.f){
				channel = 5;
			} else if(inputs[syncIn].getVoltage() == 6.f){
				channel = 6;
			} else if(inputs[syncIn].getVoltage() == 7.f){
				channel = 7;
			} else if(inputs[syncIn].getVoltage() == 8.f){
				channel = 8;
			}

		} else {
			// if not connected use buttons

			lights[SYNC_LIGHT].setBrightness(0.f);

			if (params[b1].getValue() == 1.f){
				channel = 1;
			} else if (params[b2].getValue() == 1.f){
				channel = 2;
			} else if (params[b3].getValue() == 1.f){
				channel = 3;
			} else if (params[b4].getValue() == 1.f){
				channel = 4;
			} else if (params[b5].getValue() == 1.f){
				channel = 5;
			} else if (params[b6].getValue() == 1.f){
				channel = 6;
			} else if (params[b7].getValue() == 1.f){
				channel = 7;
			} else if (params[b8].getValue() == 1.f){
				channel = 8;
			}
		}

		// set lights and outputs
		if (channel == 1){

			outputs[out].setVoltage(params[knob1].getValue());

			lights[b1L].setBrightness(1.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 2){

			outputs[out].setVoltage(params[knob2].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(1.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 3){

			outputs[out].setVoltage(params[knob3].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(1.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 4){

			outputs[out].setVoltage(params[knob4].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(1.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 5){

			outputs[out].setVoltage(params[knob5].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(1.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 6){

			outputs[out].setVoltage(params[knob6].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(1.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 7){

			outputs[out].setVoltage(params[knob7].getValue());

			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(1.f);
			lights[b8L].setBrightness(0.f);
		} else if (channel == 8){

			outputs[out].setVoltage(params[knob8].getValue());
			
			lights[b1L].setBrightness(0.f);
			lights[b2L].setBrightness(0.f);
			lights[b3L].setBrightness(0.f);
			lights[b4L].setBrightness(0.f);
			lights[b5L].setBrightness(0.f);
			lights[b6L].setBrightness(0.f);
			lights[b7L].setBrightness(0.f);
			lights[b8L].setBrightness(1.f);
		}
	}
};


struct MiniSUPPLYWidget : ModuleWidget {
	MiniSUPPLYWidget(MiniSUPPLY* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/supplymini.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		//sync in and light
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 12.5)), module, MiniSUPPLY::syncIn));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(13.75, 12.5)), module, MiniSUPPLY::SYNC_LIGHT));

		//selection buttons

		float buttonx = 5.f;
		float knobx = 14.5f;

		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 28.5)), module, MiniSUPPLY::b1, MiniSUPPLY::b1L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 40)), module, MiniSUPPLY::b2, MiniSUPPLY::b2L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 51.5)), module, MiniSUPPLY::b3, MiniSUPPLY::b3L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 63)), module, MiniSUPPLY::b4, MiniSUPPLY::b4L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 74.5)), module, MiniSUPPLY::b5, MiniSUPPLY::b5L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 86)), module, MiniSUPPLY::b6, MiniSUPPLY::b6L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 97.5)), module, MiniSUPPLY::b7, MiniSUPPLY::b7L));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(buttonx, 109)), module, MiniSUPPLY::b8, MiniSUPPLY::b8L));

		//knobs

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 28.5)), module, MiniSUPPLY::knob1));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 40)), module, MiniSUPPLY::knob2));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 51.5)), module, MiniSUPPLY::knob3));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 63)), module, MiniSUPPLY::knob4));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 74.5)), module, MiniSUPPLY::knob5));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 86)), module, MiniSUPPLY::knob6));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 97.5)), module, MiniSUPPLY::knob7));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(knobx, 109)), module, MiniSUPPLY::knob8));

		//output
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10.16, 118.5)), module, MiniSUPPLY::out));
	}
};
Model * modelMiniSUPPLY = createModel<MiniSUPPLY, MiniSUPPLYWidget>("miniSupply");