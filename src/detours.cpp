#include "plugin.hpp"


struct DETOURS : Module {
	enum ParamId {
		ENUMS(t, 8),
		PARAMS_LEN
	};
	enum InputId {
		in1,
		in2,
		in3,
		syncin,
		INPUTS_LEN
	};
	enum OutputId {
		ENUMS(OUTPUT1, 8), // OUTPUT1 + 0, OUTPUT1 + 1, OUTPUT1 + 2...
		ENUMS(OUTPUT2, 8),
		ENUMS(OUTPUT3, 8),
		syncout,
		OUTPUTS_LEN
	};
	enum LightId {
		ENUMS(tL, 8),
		synclock,
		synclink,
		LIGHTS_LEN
	};

	DETOURS() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configOutput(syncout, "sync output");
	}

	int channelout = 0;
	
	float lightvals[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};

	bool cvval[8] = {false, false, false, false, false, false, false, false};
	bool gateval[8] = {false, false, false, false, false, false, false, false};
	bool modval[8] = {false, false, false, false, false, false, false, false};

	bool isSyncedIn;
	bool isSyncedOut;

	void process(const ProcessArgs& args) override {

		//set outputs to right channel count
		int cvcount = std::max(1, inputs[in1].getChannels());
		int gatecount = std::max(1, inputs[in2].getChannels());
		int modcount = std::max(1, inputs[in3].getChannels());

		for (int i = 0; i < 8; i++){
			outputs[OUTPUT1 + i].setChannels(cvcount);
			outputs[OUTPUT2 + i].setChannels(gatecount);
			outputs[OUTPUT3 + i].setChannels(modcount);
		}
		
		//get channelout var

		// sync bools
		isSyncedIn = inputs[syncin].isConnected();
		isSyncedOut = outputs[syncout].isConnected();

		if(isSyncedIn){
			float inVoltage = inputs[syncin].getVoltage();
			if(inVoltage < 1.f){
				channelout = 0;
			} else {
				channelout = ((int)inVoltage) -1;
			};
		} else { 
			for(int i = 0; i<8; i++){
				if(params[t + i].getValue() == 1.f){
					channelout = i;
				}
			}
		}
		
		float syncvoltsout = (float)(channelout + 1);
		outputs[syncout].setVoltage(syncvoltsout);
		

		lightButtons();
		//sync lights
		if(isSyncedOut){
			lights[synclink].setBrightness(1.f);
		} else {
			lights[synclink].setBrightness(0.f);
		} 
		if(isSyncedIn){
			lights[synclock].setBrightness(1.f);
		} else {
			lights[synclock].setBrightness(0.f);
		}

		

		//route function
		for (int i = 0; i<8; i++){
			cvval[i] = false;
			gateval[i] = false;
			modval[i] = false;
		}
		cvval[channelout] = true;
		gateval[channelout] = true;
		modval[channelout] = true;
		
		for(int i = 0; i < 8; i++){
			if(cvval[i]){
				for(int c = 0; c < cvcount; c++){
					outputs[OUTPUT1 + i].setVoltage(inputs[in1].getVoltage(c), c);
				}
			} else{
				for(int c = 0; c < cvcount; c++){
					outputs[OUTPUT1 + i].setVoltage(0.f, c);
				}
			}
			if(gateval[i]){
				for(int c = 0; c < gatecount; c++){
					outputs[OUTPUT2 + i].setVoltage(inputs[in2].getVoltage(c), c);
				}
			} else{
				for(int c = 0; c < gatecount; c++){
					outputs[OUTPUT2 + i].setVoltage(0.f, c);
				}
			}
			if(modval[i]){
				for(int c = 0; c < modcount; c++){
					outputs[OUTPUT3 + i].setVoltage(inputs[in3].getVoltage(c), c);
				};
			} else{
				for(int c = 0; c < modcount; c++){
					outputs[OUTPUT3 + i].setVoltage(0.f, c);
				}
			}
		}

		//route(in1, cvval, cvcount, OUTPUT1);
		// route(in2, gateval, gatecount, OUTPUT2);
		// route(in3, modval, modcount, OUTPUT3);
	}

	void lightButtons(){
		for(int i = 0; i < 8; i++){
			lightvals[i] = 0;
		}
		lightvals[channelout] = 1.f;

		for(int i = 0; i< 8; i++){
			lights[tL + i].setBrightness(lightvals[i]);
		}
	}

	// void route(int input, bool array[], int channels, int ports){
	// 	for (int i = 0; i<8; i++){
	// 		array[i] = false;
	// 	}

	// 	array[channelout] = true;

	// 	for(int i = 0; i < 8; i++){
	// 		if(array[i]){
	// 			for(int c = 0; c < channels; c++){
	// 				outputs[ports + i].setVoltage(inputs[input].getVoltage(c), c);
	// 			}
	// 		} else{
	// 			for(int c = 0; c < channels; c++){
	// 				outputs[ports + i].setVoltage(0.f, c);
	// 			}
	// 		}
	// 	}
	// }
};


struct DETOURSWidget : ModuleWidget {
	DETOURSWidget(DETOURS* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/DETOURS.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float spacing = 5;
		float yDelta = spacing/2;
		float xDelta = sqrt((spacing * spacing) - (yDelta * yDelta));

		float inx = 10;
		float iny = 60;

		float selectx = 25;
		
		float x1out = 37.5;
		float x2out = 50.96;

		float yCoords[8] = {9.5, 24.5, 39.5, 54.5, 69.5, 84.5, 99.5, 114.5};

		//inputs
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inx - xDelta, iny - yDelta)), module, DETOURS::in1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inx + xDelta, iny - yDelta)), module, DETOURS::in2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(inx, iny + spacing)), module, DETOURS::in3));

		//outputs
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out - xDelta, yCoords[0] - yDelta)), module, DETOURS::OUTPUT1 + 0));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out + xDelta, yCoords[0] - yDelta)), module, DETOURS::OUTPUT2 + 0));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out, yCoords[0] + spacing)), module, DETOURS::OUTPUT3 + 0));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out - xDelta, yCoords[1] - yDelta)), module, DETOURS::OUTPUT1 + 1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out + xDelta, yCoords[1] - yDelta)), module, DETOURS::OUTPUT2 + 1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out, yCoords[1] + spacing)), module, DETOURS::OUTPUT3 + 1));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out - xDelta, yCoords[2] - yDelta)), module, DETOURS::OUTPUT1 + 2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out + xDelta, yCoords[2] - yDelta)), module, DETOURS::OUTPUT2 + 2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out, yCoords[2] + spacing)), module, DETOURS::OUTPUT3 + 2));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out - xDelta, yCoords[3] - yDelta)), module, DETOURS::OUTPUT1 + 3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out + xDelta, yCoords[3] - yDelta)), module, DETOURS::OUTPUT2 + 3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out, yCoords[3] + spacing)), module, DETOURS::OUTPUT3 + 3));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out - xDelta, yCoords[4] - yDelta)), module, DETOURS::OUTPUT1 + 4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out + xDelta, yCoords[4] - yDelta)), module, DETOURS::OUTPUT2 + 4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out, yCoords[4] + spacing)), module, DETOURS::OUTPUT3 + 4));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out - xDelta, yCoords[5] - yDelta)), module, DETOURS::OUTPUT1 + 5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out + xDelta, yCoords[5] - yDelta)), module, DETOURS::OUTPUT2 + 5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out, yCoords[5] + spacing)), module, DETOURS::OUTPUT3 + 5));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out - xDelta, yCoords[6] - yDelta)), module, DETOURS::OUTPUT1 + 6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out + xDelta, yCoords[6] - yDelta)), module, DETOURS::OUTPUT2 + 6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1out, yCoords[6] + spacing)), module, DETOURS::OUTPUT3 + 6));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out - xDelta, yCoords[7] - yDelta)), module, DETOURS::OUTPUT1 + 7));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out + xDelta, yCoords[7] - yDelta)), module, DETOURS::OUTPUT2 + 7));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x2out, yCoords[7] + spacing)), module, DETOURS::OUTPUT3 + 7));

		//select buttons
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[0])), module, DETOURS::t + 0, DETOURS::tL + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[1])), module, DETOURS::t + 1, DETOURS::tL + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[2])), module, DETOURS::t + 2, DETOURS::tL + 2));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[3])), module, DETOURS::t + 3, DETOURS::tL + 3));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[4])), module, DETOURS::t + 4, DETOURS::tL + 4));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[5])), module, DETOURS::t + 5, DETOURS::tL + 5));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[6])), module, DETOURS::t + 6, DETOURS::tL + 6));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(selectx, yCoords[7])), module, DETOURS::t + 7, DETOURS::tL + 7));

		// sync stuff (fucked)
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(10, 100)), module, DETOURS::syncout));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(10, 115)), module, DETOURS::syncin));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(10, 92.5)), module, DETOURS::synclink));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(10, 107.5)), module, DETOURS::synclock));


		
		
	}
};


Model* modelDETOURS = createModel<DETOURS, DETOURSWidget>("DETOURS");