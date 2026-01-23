#include "plugin.hpp"


struct FXB : Module {
	enum ParamId {
		toggle1,
		toggle2,
		toggle3,
		toggle4,
		toggle5,
		toggle6,
		toggle7,
		toggle8,

		mix1,
		mix2,
		mix3,
		mix4,
		mix5,
		mix6,
		mix7,
		mix8,
		mixtoggle,
		chaintoggle,
		PARAMS_LEN
	};
	enum InputId {
		in1,
		in2,
		in3,
		in4,
		in5,
		in6,
		in7,
		in8,
		r1,
		r2,
		r3,
		r4,
		r5,
		r6,
		r7,
		r8,
		toggle1In,
		toggle2In,
		toggle3In,
		toggle4In,
		toggle5In,
		toggle6In,
		toggle7In,
		toggle8In,
		INPUTS_LEN
	};
	enum OutputId {
		out1,
		out2,
		out3,
		out4,
		out5,
		out6,
		out7,
		out8,
		s1,
		s2,
		s3,
		s4,
		s5,
		s6,
		s7,
		s8,
		toggle1Out,
		toggle2Out,
		toggle3Out,
		toggle4Out,
		toggle5Out,
		toggle6Out,
		toggle7Out,
		toggle8Out,
		OUTPUTS_LEN
	};
	enum LightId {
		toggle1L,
		toggle2L,
		toggle3L,
		toggle4L,
		toggle5L,
		toggle6L,
		toggle7L,
		toggle8L,
		lock1,
		lock2,
		lock3,
		lock4,
		lock5,
		lock6,
		lock7,
		lock8,
		link1,
		link2,
		link3,
		link4,
		link5,
		link6,
		link7,
		link8,
		mixL,
		chainL,
		LIGHTS_LEN
	};

	FXB() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(toggle1, 0.f, 1.f, 0.f, "Bypass #1");
		configParam(toggle2, 0.f, 1.f, 0.f, "Bypass #2");
		configParam(toggle3, 0.f, 1.f, 0.f, "Bypass #3");
		configParam(toggle4, 0.f, 1.f, 0.f, "Bypass #4");
		configParam(toggle5, 0.f, 1.f, 0.f, "Bypass #5");
		configParam(toggle6, 0.f, 1.f, 0.f, "Bypass #6");
		configParam(toggle7, 0.f, 1.f, 0.f, "Bypass #7");
		configParam(toggle8, 0.f, 1.f, 0.f, "Bypass #8");

		configParam(mixtoggle, 0.f, 1.f, 0.f, "Toggle Mix");
		configParam(mix1, 0.f, 1.f, 0.f, "Dry/Wet Mix #1");
		configParam(mix2, 0.f, 1.f, 0.f, "Dry/Wet Mix #2");
		configParam(mix3, 0.f, 1.f, 0.f, "Dry/Wet Mix #3");
		configParam(mix4, 0.f, 1.f, 0.f, "Dry/Wet Mix #4");
		configParam(mix5, 0.f, 1.f, 0.f, "Dry/Wet Mix #5");
		configParam(mix6, 0.f, 1.f, 0.f, "Dry/Wet Mix #6");
		configParam(mix7, 0.f, 1.f, 0.f, "Dry/Wet Mix #7");
		configParam(mix8, 0.f, 1.f, 0.f, "Dry/Wet Mix #8");

		configInput(in1, "Audio #1");
		configInput(in2, "Audio #2");
		configInput(in3, "Audio #3");
		configInput(in4, "Audio #4");
		configInput(in5, "Audio #5");
		configInput(in6, "Audio #6");
		configInput(in7, "Audio #7");
		configInput(in8, "Audio #8");
		configInput(r1, "Return #1");
		configInput(r2, "Return #2");
		configInput(r3, "Return #3");
		configInput(r4, "Return #4");
		configInput(r5, "Return #5");
		configInput(r6, "Return #6");
		configInput(r7, "Return #7");
		configInput(r8, "Return #8");
		configInput(toggle1In, "Link #1");
		configInput(toggle2In, "Link #2");
		configInput(toggle3In, "Link #3");
		configInput(toggle4In, "Link #4");
		configInput(toggle5In, "Link #5");
		configInput(toggle6In, "Link #6");
		configInput(toggle7In, "Link #7");
		configInput(toggle8In, "Link #8");

		configOutput(out1, "Audio #1");
		configOutput(out2, "Audio #2");
		configOutput(out3, "Audio #3");
		configOutput(out4, "Audio #4");
		configOutput(out5, "Audio #5");
		configOutput(out6, "Audio #6");
		configOutput(out7, "Audio #7");
		configOutput(out8, "Audio #8");
		configOutput(s1, "Send #1");
		configOutput(s2, "Send #2");
		configOutput(s3, "Send #3");
		configOutput(s4, "Send #4");
		configOutput(s5, "Send #5");
		configOutput(s6, "Send #6");
		configOutput(s7, "Send #7");
		configOutput(s8, "Send #8");
		configOutput(toggle1Out, "Link #1");
		configOutput(toggle2Out, "Link #2");
		configOutput(toggle3Out, "Link #3");
		configOutput(toggle4Out, "Link #4");
		configOutput(toggle5Out, "Link #5");
		configOutput(toggle6Out, "Link #6");
		configOutput(toggle7Out, "Link #7");
		configOutput(toggle8Out, "Link #8");
	}

	bool mix = false;

	bool chain = false;

	void isLinkedIn(int in, int light, int param) {
		if (inputs[in].isConnected()){
			lights[light].setBrightness(1.f);
			if (inputs[in].getVoltage() > 5.f){
				params[param].setValue(1.f);
			} else {
				params[param].setValue(0.f);
			}
		}else{
			lights[light].setBrightness(0.f);
		}
	}

	void isLinkedOut(int out, int light){
		if(outputs[out].isConnected()){
			lights[light].setBrightness(1.f);
		} else{
			lights[light].setBrightness(0.f);
		}
	}

	bool buttonOn (int param, int light, int out){
		if(params[param].getValue() == 1.f){
			lights[light].setBrightness(1.f);
			outputs[out].setVoltage(10.f);
			return true;
		} else {
			lights[light].setBrightness(0.f);
			outputs[out].setVoltage(0.f);
			return false;
		}
	}

	void process(const ProcessArgs& args) override {

		// call isLinked* functions
		isLinkedIn(toggle1In, lock1, toggle1);
		isLinkedIn(toggle2In, lock2, toggle2);
		isLinkedIn(toggle3In, lock3, toggle3);
		isLinkedIn(toggle4In, lock4, toggle4);
		isLinkedIn(toggle5In, lock5, toggle5);
		isLinkedIn(toggle6In, lock6, toggle6);
		isLinkedIn(toggle7In, lock7, toggle7);
		isLinkedIn(toggle8In, lock8, toggle8);

		isLinkedOut(toggle1Out, link1);
		isLinkedOut(toggle2Out, link2);
		isLinkedOut(toggle3Out, link3);
		isLinkedOut(toggle4Out, link4);
		isLinkedOut(toggle5Out, link5);
		isLinkedOut(toggle6Out, link6);
		isLinkedOut(toggle7Out, link7);
		isLinkedOut(toggle8Out, link8);

		// set mix value and button
		if (params[mixtoggle].getValue() == 1){
			mix = true;
			lights[mixL].setBrightness(1.f);
		} else {
			mix = false;
			lights[mixL].setBrightness(0.f);
		}

		// controls send/return
		if(buttonOn(toggle1, toggle1L, toggle1Out)){
			outputs[s1].setVoltage(inputs[in1].getVoltage());
			if(mix){
				outputs[out1].setVoltage((params[mix1].getValue() * inputs[r1].getVoltage()) + ((1 - params[mix1].getValue()) * inputs[in1].getVoltage()));
			} else {
				outputs[out1].setVoltage(inputs[r1].getVoltage());
			}
		} else {
			outputs[out1].setVoltage(inputs[in1].getVoltage());
		}

		if(buttonOn(toggle2, toggle2L, toggle2Out)){
			outputs[s2].setVoltage(inputs[in2].getVoltage());
			if (mix){
				outputs[out2].setVoltage((params[mix2].getValue() * inputs[r2].getVoltage()) + ((1 - params[mix2].getValue()) * inputs[in2].getVoltage()));
			} else {
				outputs[out2].setVoltage(inputs[r2].getVoltage());
			}
		} else {
			outputs[out2].setVoltage(inputs[in2].getVoltage());
		}

		if(buttonOn(toggle3, toggle3L, toggle3Out)){
			outputs[s3].setVoltage(inputs[in3].getVoltage());
			if (mix){
				outputs[out3].setVoltage((params[mix3].getValue() * inputs[r3].getVoltage()) + ((1 - params[mix3].getValue()) * inputs[in3].getVoltage()));
			} else {
				outputs[out3].setVoltage(inputs[r3].getVoltage());
			}
		} else {
			outputs[out3].setVoltage(inputs[in3].getVoltage());
		}

		if(buttonOn(toggle4, toggle4L, toggle4Out)){
			outputs[s4].setVoltage(inputs[in4].getVoltage());
			if (mix){
				outputs[out4].setVoltage((params[mix4].getValue() * inputs[r4].getVoltage()) + ((1 - params[mix4].getValue()) * inputs[in4].getVoltage()));
			} else {
				outputs[out4].setVoltage(inputs[r4].getVoltage());
			}
		} else {
			outputs[out4].setVoltage(inputs[in4].getVoltage());
		}

		if(buttonOn(toggle5, toggle5L, toggle5Out)){
			outputs[s5].setVoltage(inputs[in5].getVoltage());
			if (mix){
				outputs[out5].setVoltage((params[mix5].getValue() * inputs[r5].getVoltage()) + ((1 - params[mix5].getValue()) * inputs[in5].getVoltage()));
			} else {
				outputs[out5].setVoltage(inputs[r5].getVoltage());
			}
		} else {
			outputs[out5].setVoltage(inputs[in5].getVoltage());
		}

		if(buttonOn(toggle6, toggle6L, toggle6Out)){
			outputs[s6].setVoltage(inputs[in6].getVoltage());
			if (mix){
				outputs[out6].setVoltage((params[mix6].getValue() * inputs[r6].getVoltage()) + ((1 - params[mix6].getValue()) * inputs[in6].getVoltage()));
			} else {
				outputs[out6].setVoltage(inputs[r6].getVoltage());
			}
		} else {
			outputs[out6].setVoltage(inputs[in6].getVoltage());
		}

		if(buttonOn(toggle7, toggle7L, toggle7Out)){
			outputs[s7].setVoltage(inputs[in7].getVoltage());
			if (mix){
				outputs[out7].setVoltage((params[mix7].getValue() * inputs[r7].getVoltage()) + ((1 - params[mix7].getValue()) * inputs[in7].getVoltage()));
			} else {
				outputs[out7].setVoltage(inputs[r7].getVoltage());
			}
		} else {
			outputs[out7].setVoltage(inputs[in7].getVoltage());
		}

		if(buttonOn(toggle8, toggle8L, toggle8Out)){
			outputs[s8].setVoltage(inputs[in8].getVoltage());
			if (mix) {
				outputs[out8].setVoltage((params[mix8].getValue() * inputs[r8].getVoltage()) + ((1 - params[mix8].getValue()) * inputs[in8].getVoltage()));
			} else {
				outputs[out8].setVoltage(inputs[r8].getVoltage());
			}
		} else {
			outputs[out8].setVoltage(inputs[in8].getVoltage());
		}

	}

	
};


struct FXBWidget : ModuleWidget {
	FXBWidget(FXB* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/FXB.svg")));

		float inity = 12.5;
		float offY = 11.5;

		float xpos1 = 7.56;
		float xpos2 = 16.56;
		float xpos3 = 25.56;
		float xpos4 = 34.56;
		float xpos5 = 43.56;
		float xpos6 = 53.56;

		//screws
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// channel 1
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, inity)), module, FXB::in1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, inity)), module, FXB::s1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, inity)), module, FXB::r1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, inity)), module, FXB::out1));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, inity)), module, FXB::toggle1, FXB::toggle1L));

		// channel 2 
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 1 * offY))), module, FXB::in2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 1 * offY))), module, FXB::s2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 1 * offY))), module, FXB::r2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 1 * offY))), module, FXB::out2));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 1 * offY))), module, FXB::toggle2, FXB::toggle2L));
		
		// channel 3 
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 2 * offY))), module, FXB::in3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 2 * offY))), module, FXB::s3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 2 * offY))), module, FXB::r3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 2 * offY))), module, FXB::out3));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 2 * offY))), module, FXB::toggle3, FXB::toggle3L));
		
		// channel 4 
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 3 * offY))), module, FXB::in4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 3 * offY))), module, FXB::s4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 3 * offY))), module, FXB::r4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 3 * offY))), module, FXB::out4));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 3 * offY))), module, FXB::toggle4, FXB::toggle4L));
		
		// channel 5 
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 4 * offY))), module, FXB::in5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 4 * offY))), module, FXB::s5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 4 * offY))), module, FXB::r5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 4 * offY))), module, FXB::out5));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 4 * offY))), module, FXB::toggle5, FXB::toggle5L));
		
		// channel 6
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 5 * offY))), module, FXB::in6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 5 * offY))), module, FXB::s6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 5 * offY))), module, FXB::r6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 5 * offY))), module, FXB::out6));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 5 * offY))), module, FXB::toggle6, FXB::toggle6L)); 
		
		// channel 7
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 6 * offY))), module, FXB::in7));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 6 * offY))), module, FXB::s7));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 6 * offY))), module, FXB::r7));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 6 * offY))), module, FXB::out7));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 6 * offY))), module, FXB::toggle7, FXB::toggle7L)); 
		
		// channel 8
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos1, (inity + 7 * offY))), module, FXB::in8));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos2, (inity + 7 * offY))), module, FXB::s8));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(xpos4, (inity + 7 * offY))), module, FXB::r8));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(xpos5, (inity + 7 * offY))), module, FXB::out8));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(xpos3, (inity + 7 * offY))), module, FXB::toggle8, FXB::toggle8L));

		// toggle bay ports
		float toggleY = 104.5;
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(05.06, toggleY + 12)), module, FXB::toggle1In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(13.78, toggleY + 12)), module, FXB::toggle2In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(22.50, toggleY + 12)), module, FXB::toggle3In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(31.22, toggleY + 12)), module, FXB::toggle4In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(39.94, toggleY + 12)), module, FXB::toggle5In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(48.66, toggleY + 12)), module, FXB::toggle6In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(57.38, toggleY + 12)), module, FXB::toggle7In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(66.06, toggleY + 12)), module, FXB::toggle8In));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(05.06, toggleY)), module, FXB::toggle1Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(13.78, toggleY)), module, FXB::toggle2Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(22.50, toggleY)), module, FXB::toggle3Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(31.22, toggleY)), module, FXB::toggle4Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(39.94, toggleY)), module, FXB::toggle5Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(48.66, toggleY)), module, FXB::toggle6Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(57.38, toggleY)), module, FXB::toggle7Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(66.06, toggleY)), module, FXB::toggle8Out));

		//toggle lock indicator lights
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 0 * offY))), module, FXB::lock1));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 1 * offY))), module, FXB::lock2));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 2 * offY))), module, FXB::lock3));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 3 * offY))), module, FXB::lock4));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 4 * offY))), module, FXB::lock5));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 5 * offY))), module, FXB::lock6));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 6 * offY))), module, FXB::lock7));
		addChild(createLightCentered<SmallLight<RedLight>>(mm2px(Vec(xpos3 + 3.45, (inity - 3 + 7 * offY))), module, FXB::lock8));

		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 0 * offY))), module, FXB::link1));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 1 * offY))), module, FXB::link2));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 2 * offY))), module, FXB::link3));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 3 * offY))), module, FXB::link4));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 4 * offY))), module, FXB::link5));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 5 * offY))), module, FXB::link6));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 6 * offY))), module, FXB::link7));
		addChild(createLightCentered<SmallLight<YellowLight>>(mm2px(Vec(xpos3 - 3.45, (inity - 3 + 7 * offY))), module, FXB::link8));


		//mix wheels
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 0 * offY))), module, FXB::mix1));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 1 * offY))), module, FXB::mix2));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 2 * offY))), module, FXB::mix3));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 3 * offY))), module, FXB::mix4));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 4 * offY))), module, FXB::mix5));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 5 * offY))), module, FXB::mix6));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 6 * offY))), module, FXB::mix7));
		addParam(createParamCentered<RoundSmallBlackKnob>(mm2px(Vec(xpos6, (inity + 7 * offY))), module, FXB::mix8));

		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<RedLight>>>(mm2px(Vec(xpos6 + 10, 9)), module, FXB::mixtoggle, FXB::mixL));
		addParam(createLightParamCentered<VCVLightLatch<MediumSimpleLight<YellowLight>>>(mm2px(Vec(xpos6 + 10, 21)), module, FXB::chaintoggle, FXB::chainL));
	}
};


Model* modelFXB = createModel<FXB, FXBWidget>("FXB");