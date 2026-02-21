#include "plugin.hpp"


struct MiniFX : Module {
	enum ParamId {
		toggle1,
		toggle2,
		togglemix,
		mix1,
		mix2,
		PARAMS_LEN
	};
	enum InputId {
		in1,
		in2,
		r1,
		r2,
		toggle1In,
		toggle2In,
		INPUTS_LEN
	};
	enum OutputId {
		s1,
		s2,
		out1,
		out2,
		toggle1Out,
		toggle2Out,
		OUTPUTS_LEN
	};
	enum LightId {
		link1,
		lock1,
		link2,
		lock2,
		toggle1L,
		toggle2L,
		mixL,
		LIGHTS_LEN
	};

	MiniFX() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
	}

	void process(const ProcessArgs& args) override {

		//check links
		isLinkedOut(toggle1Out, link1);
		isLinkedOut(toggle2Out, link2);
		isLinkedIn(toggle1In, lock1, toggle1);
		isLinkedIn(toggle2In, lock2, toggle2);

		//set mix value
		float mixval = params[togglemix].getValue();
		lights[mixL].setBrightness(mixval);
		if(mixval == 1.f){
			mix = true;
		} else {
			mix = false;
		}

		bool onOne = buttonOn(toggle1, toggle1L, toggle1Out);
		bool onTwo = buttonOn(toggle2, toggle2L, toggle2Out);

		sendReturn(onOne, in1, s1, r1, out1, mix1);
		sendReturn(onTwo, in2, s2, r2, out2, mix2);
	}

	void isLinkedOut(int out, int light){
		if(outputs[out].isConnected()){
			lights[light].setBrightness(1.f);
		} else {
			lights[light].setBrightness(0.f);
		}
	}

	void isLinkedIn(int in, int light, int param){
		if(inputs[in].isConnected()){
			lights[light].setBrightness(1.f);
			if(inputs[in].getVoltage() > 5.f){
				params[param].setValue(1.f);
			} else {
				params[param].setValue(0.f);
			}
		} else {
			lights[light].setBrightness(0.f);
		}
	}

	bool mix;

	bool buttonOn(int latch, int light, int out){
		float value = params[latch].getValue();
		lights[light].setBrightness(value);
		if(value == 1.f){
			outputs[out].setVoltage(10.f);
			return true;
		} else {
			outputs[out].setVoltage(0.f);
			return false;
		}
	}

	void sendReturn(bool isOn, int extIn, int s, int r, int extOut, int mixer){
		if(isOn){
			outputs[s].setVoltage(inputs[extIn].getVoltage());
			if(mix){
				float mixout = (params[mixer].getValue() * inputs[r].getVoltage()) + ((1 - params[mixer].getValue()) * inputs[extIn].getVoltage());
				outputs[extOut].setVoltage(mixout);
			} else {
				outputs[extOut].setVoltage(inputs[r].getVoltage());
			}
		} else {
			outputs[extOut].setVoltage(inputs[extIn].getVoltage());
		}
	}



};


struct MiniFXWidget : ModuleWidget {
	MiniFXWidget(MiniFX* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/miniFX.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x1 = 5.66; 
		float x2 = 14.66;
		float y1 = 24 - 5.75;
		float y2 = 35.5 - 5.75;
		float y3 = 47 - 5.75;
		float y4 = 58.5 - 5.75;
		float y5 = 70 - 5.75;

		//channel 1
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1, y1)), module, MiniFX::in1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1, y4)), module, MiniFX::r1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1, y2)), module, MiniFX::s1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1, y5)), module, MiniFX::out1));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x1, y3)), module, MiniFX::toggle1, MiniFX::toggle1L));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(x1, y3 - 5)), module, MiniFX::link1));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(x1, (y3 + 5))), module, MiniFX::lock1));

		//channel 2
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2, y1)), module, MiniFX::in2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2, y4)), module, MiniFX::r2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2, y2)), module, MiniFX::s2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2, y5)), module, MiniFX::out2));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(x2, y3)), module, MiniFX::toggle2, MiniFX::toggle2L));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(x2, y3 - 5)), module, MiniFX::link2));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(x2, (y3 + 5))), module, MiniFX::lock2));

		//mix controls
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(10.16, 75)), module, MiniFX::togglemix, MiniFX::mixL));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 84.5)), module, MiniFX::mix1));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(10.16, 95)), module, MiniFX::mix2));

		//link ports
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1, 107.5)), module, MiniFX::toggle1Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2, 107.5)), module, MiniFX::toggle2Out));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1, 116.5)), module, MiniFX::toggle1In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2, 116.5)), module, MiniFX::toggle2In));


		

	}
};


Model* modelMiniFX = createModel<MiniFX, MiniFXWidget>("miniFX");