#include "plugin.hpp"


struct RETOURS : Module {
	enum ParamId {
		ENUMS(t, 8),
		PARAMS_LEN
	};
	enum InputId {
		ENUMS(INPUT1, 8),
		ENUMS(INPUT2, 8),
		ENUMS(INPUT3, 8),
		syncInput,
		INPUTS_LEN
	};
	enum OutputId {
		out1,
		out2,
		out3,
		syncOutput,
		OUTPUTS_LEN
	};
	enum LightId {
		ENUMS(tL, 8),
		synclink,
		synclock,
		LIGHTS_LEN
	};

	RETOURS() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
	}

	int channelin = 0;
	
	float lightvals[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

	bool cvval[8] = {false, false, false, false, false, false, false, false};
	bool gateval[8] = {false, false, false, false, false, false, false, false};
	bool modval[8] = {false, false, false, false, false, false, false, false};

	int cvcount = 1;
	int gatecount = 1;
	int modcount = 1;

	bool isSyncedIn;
	bool isSyncedOut;

	void process(const ProcessArgs& args) override {

		isSyncedOut = outputs[syncOutput].isConnected();
		isSyncedIn = inputs[syncInput].isConnected();
		
		//select channel
		if(isSyncedIn){
			float inVoltage = inputs[syncInput].getVoltage();
			if(inVoltage < 1.f){
				channelin = 0;
			} else {
				channelin = ((int)inVoltage) -1;
			}
		} else {
			for(int i = 0; i<8; i++){
				if(params[t + i].getValue() == 1.f){
					channelin = i;
				}
			}
		}

		float syncvoltsout = (float)(channelin + 1);
		outputs[syncOutput].setVoltage(syncvoltsout);
		

		lightButtons();

		//sync lights
		if(outputs[syncOutput].isConnected()){
			lights[synclink].setBrightness(1.f);
		} else {
			lights[synclink].setBrightness(0.f);
		} 
		if(inputs[syncInput].isConnected()){
			lights[synclock].setBrightness(1.f);
		} else {
			lights[synclock].setBrightness(0.f);
		}

		//set output channels
		for (int i = 0; i<8; i++){
			cvval[i] = false;
			gateval[i] = false;
			modval[i] = false;
		}
		cvval[channelin] = true;
		gateval[channelin] = true;
		modval[channelin] = true;

		//route function

		for (int i = 0; i<8; i++){
			if(cvval[i]){
				cvcount = std::max(1, inputs[INPUT1 + i].getChannels());
				outputs[out1].setChannels(cvcount);
				for(int c = 0; c<cvcount; c++){
					outputs[out1].setVoltage(inputs[INPUT1 + i].getVoltage(c), c);
				}
			} 
			if(gateval[i]){
				gatecount = std::max(1, inputs[INPUT2 + i].getChannels());
				outputs[out2].setChannels(gatecount);
				for(int c = 0; c<gatecount; c++){
					outputs[out2].setVoltage(inputs[INPUT2 + i].getVoltage(c), c);
				}
			} 
			if(modval[i]){
				modcount = std::max(1, inputs[INPUT3 + i].getChannels());
				outputs[out3].setChannels(modcount);
				for(int c = 0; c<modcount; c++){
					outputs[out3].setVoltage(inputs[INPUT3 + i].getVoltage(c), c);
				}
			} 
		}

	}

	void lightButtons(){
		for(int i = 0; i < 8; i++){
			lightvals[i] = 0;
		}
		lightvals[channelin] = 1.f;

		for(int i = 0; i< 8; i++){
			lights[tL + i].setBrightness(lightvals[i]);
		}
	}
};


struct RETOURSWidget : ModuleWidget {
	RETOURSWidget(RETOURS* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/RETOURS.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float spacing = 5;
		float yDelta = spacing/2;
		float xDelta = sqrt((spacing * spacing) - (yDelta * yDelta));

		float outx = 50.96;
		float outy = 60;

		float selectx = 35.96;
		
		float x1in = 10;
		float x2in = 23.46;

		float yCoords[8] = {9.5, 24.5, 39.5, 54.5, 69.5, 84.5, 99.5, 114.5};

		// channel 1
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in - xDelta, yCoords[0] - yDelta)), module, RETOURS::INPUT1 + 0));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in + xDelta, yCoords[0] - yDelta)), module, RETOURS::INPUT2 + 0));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in, yCoords[0] + spacing)), module, RETOURS::INPUT3 + 0));

		// channel 2
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in - xDelta, yCoords[1] - yDelta)), module, RETOURS::INPUT1 + 1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in + xDelta, yCoords[1] - yDelta)), module, RETOURS::INPUT2 + 1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in, yCoords[1] + spacing)), module, RETOURS::INPUT3 + 1));

		// channel 3
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in - xDelta, yCoords[2] - yDelta)), module, RETOURS::INPUT1 + 2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in + xDelta, yCoords[2] - yDelta)), module, RETOURS::INPUT2 + 2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in, yCoords[2] + spacing)), module, RETOURS::INPUT3 + 2));

		// channel 4
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in - xDelta, yCoords[3] - yDelta)), module, RETOURS::INPUT1 + 3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in + xDelta, yCoords[3] - yDelta)), module, RETOURS::INPUT2 + 3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in, yCoords[3] + spacing)), module, RETOURS::INPUT3 + 3));

		// channel 5
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in - xDelta, yCoords[4] - yDelta)), module, RETOURS::INPUT1 + 4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in + xDelta, yCoords[4] - yDelta)), module, RETOURS::INPUT2 + 4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in, yCoords[4] + spacing)), module, RETOURS::INPUT3 + 4));

		// channel 6
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in - xDelta, yCoords[5] - yDelta)), module, RETOURS::INPUT1 + 5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in + xDelta, yCoords[5] - yDelta)), module, RETOURS::INPUT2 + 5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in, yCoords[5] + spacing)), module, RETOURS::INPUT3 + 5));

		// channel 7
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in - xDelta, yCoords[6] - yDelta)), module, RETOURS::INPUT1 + 6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in + xDelta, yCoords[6] - yDelta)), module, RETOURS::INPUT2 + 6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x2in, yCoords[6] + spacing)), module, RETOURS::INPUT3 + 6));

		// channel 8
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in - xDelta, yCoords[7] - yDelta)), module, RETOURS::INPUT1 + 7));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in + xDelta, yCoords[7] - yDelta)), module, RETOURS::INPUT2 + 7));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1in, yCoords[7] + spacing)), module, RETOURS::INPUT3 + 7));

		//outputs
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outx - xDelta, outy - yDelta)), module, RETOURS::out1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outx + xDelta, outy - yDelta)), module, RETOURS::out2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(outx, outy + spacing)), module, RETOURS::out3));

		//select buttons
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[0])), module, RETOURS::t + 0, RETOURS::tL + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[1])), module, RETOURS::t + 1, RETOURS::tL + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[2])), module, RETOURS::t + 2, RETOURS::tL + 2));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[3])), module, RETOURS::t + 3, RETOURS::tL + 3));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[4])), module, RETOURS::t + 4, RETOURS::tL + 4));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[5])), module, RETOURS::t + 5, RETOURS::tL + 5));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[6])), module, RETOURS::t + 6, RETOURS::tL + 6));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[7])), module, RETOURS::t + 7, RETOURS::tL + 7));

		// sync stuff
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(50, 100)), module, RETOURS::syncOutput));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(50, 115)), module, RETOURS::syncInput));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(50, 92.5)), module, RETOURS::synclink));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(50, 107.5)), module, RETOURS::synclock));

		
	}
};


Model* modelRETOURS = createModel<RETOURS, RETOURSWidget>("RETOURS");