#include "plugin.hpp"


struct MiniTOURS : Module {
	enum ParamId {
		ENUMS(inselect, 8),
		ENUMS(outselect, 8),
		PARAMS_LEN
	};
	enum InputId {
		in1, 
		ENUMS(ins, 8),
		inSyncIn,
		outSyncIn,
		INPUTS_LEN
	};
	enum OutputId {
		ENUMS(outs, 8),
		out1,
		inSyncOut,
		outSyncOut,
		OUTPUTS_LEN
	};
	enum LightId {
		ENUMS(inselectL, 8),
		ENUMS(outselectL, 8),
		inlink,
		inlock,
		outlink,
		outlock,
		LIGHTS_LEN
	};

	MiniTOURS() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configOutput(outSyncOut, "out sync");
		configOutput(inSyncOut, "in sync");
		configInput(outSyncIn, "out sync");
		configInput(inSyncIn, "in sync");
	}

	// int channelout = 0;
	// int channelin = 0;
	
	// bool outSyncedIn = inputs[outSyncIn].isConnected();
	// bool outSyncedOut = outputs[outSyncOut].isConnected();
	// bool inSyncedIn = inputs[inSyncIn].isConnected();
	// bool inSyncedOut = outputs[inSyncOut].isConnected();

	// bool outvals[8] = {false, false, false, false, false, false, false, false};
	// bool invals[8] = {false, false, false, false, false, false, false, false};
	
	// float outLvals[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	// float inLvals[8] = {0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f, 0.f};
	
	void process(const ProcessArgs& args) override {

		// sync math
		

		// if(outSyncedIn){
		// 	float ininVoltage = inputs[outSyncIn].getVoltage();
		// 	if (ininVoltage < 1.f){
		// 		channelout = 0;
		// 	} else if (ininVoltage > 8.f){
		// 		channelout = 7;
		// 	} else {
		// 		channelout = ((int)ininVoltage) - 1;
		// 	}
		// } else {
		// 	for(int i = 0; i<8; i++){
		// 		if(params[outselect + i].getValue() == 1.f){
		// 			channelout = i;
		// 		}
		// 	}
		// }

		// float syncvoltsout = (float)(channelout + 1);
		// outputs[outSyncOut].setVoltage(syncvoltsout);

		// if(inSyncedIn){
		// 	float outinvoltage = inputs[inSyncIn].getVoltage();
		// 	if(outinvoltage < 1.f){
		// 		channelin = 0;
		// 	} else if(outinvoltage > 8.f){
		// 		channelin = 7;
		// 	} else {
		// 		channelin = ((int)outinvoltage - 1);
		// 	}
		// } else {
		// 	for(int i = 0; i<8; i++){
		// 		if(params[inselect + i].getValue() == 1.f){
		// 			channelin = i;
		// 		}
		// 	}
		// }

		// syncvoltsout = (float)(channelin + 1);
		// outputs[inSyncOut].setVoltage(syncvoltsout);

		// if(outSyncedOut){
		// 	lights[outlink].setBrightness(1.f);
		// } else {
		// 	lights[outlink].setBrightness(0.f);
		// }

		// if(outSyncedIn){
		// 	lights[outlock].setBrightness(1.f);
		// } else {
		// 	lights[outlock].setBrightness(0.f);
		// }

		// if(inSyncedOut){
		// 	lights[inlink].setBrightness(1.f);
		// } else {
		// 	lights[inlink].setBrightness(0.f);
		// }

		// if(inSyncedIn){
		// 	lights[inlock].setBrightness(1.f);
		// } else {
		// 	lights[inlock].setBrightness(0.f);
		// }


		//lightButtons();

		// channel counts
		//int incount = std::max(1, inputs[in1].getChannels());;
		//int outcount std::max(1, inputs[in1].getChannels());

	}
	
	// void lightButtons(){
	// 	for(int i = 0; i < 8; i++){
	// 		inLvals[i] = 0;
	// 		outLvals[i] = 0;
	// 	}
	// 	inLvals[channelin] = 1.f;
	// 	outLvals[channelout] = 1.f;

	// 	for(int i = 0; i< 8; i++){
	// 		lights[inselectL + i].setBrightness(inLvals[i]);
	// 		lights[outselectL + i].setBrightness(outLvals[i]);
	// 	}
	// }
};


struct MiniTOURSWidget : ModuleWidget {
	MiniTOURSWidget(MiniTOURS* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/miniTOURS.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		float x1 = 6.5;
		float x2 = 14.8;
		float x3 = 25.25;
		float x4 = 35.70;
		float x5 = 46.15;
		float x6 = 54.46;

		float y1 = 62.f;

		float yCoords[8] = {9.5, 24.5, 39.5, 54.5, 69.5, 84.5, 99.5, 114.5};


		//main in
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1, y1)), module, MiniTOURS::in1));

		//out toggles
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[0])), module, MiniTOURS::inselect + 0, MiniTOURS::inselectL + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[1])), module, MiniTOURS::inselect + 1, MiniTOURS::inselectL + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[2])), module, MiniTOURS::inselect + 2, MiniTOURS::inselectL + 2));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[3])), module, MiniTOURS::inselect + 3, MiniTOURS::inselectL + 3));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[4])), module, MiniTOURS::inselect + 4, MiniTOURS::inselectL + 4));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[5])), module, MiniTOURS::inselect + 5, MiniTOURS::inselectL + 5));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[6])), module, MiniTOURS::inselect + 6, MiniTOURS::inselectL + 6));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x2, yCoords[7])), module, MiniTOURS::inselect + 7, MiniTOURS::inselectL + 7));
		
		//out splits
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[0])), module, MiniTOURS::outs + 0));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[1])), module, MiniTOURS::outs + 1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[2])), module, MiniTOURS::outs + 2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[3])), module, MiniTOURS::outs + 3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[4])), module, MiniTOURS::outs + 4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[5])), module, MiniTOURS::outs + 5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[6])), module, MiniTOURS::outs + 6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x3, yCoords[7])), module, MiniTOURS::outs + 7));

		//in splits
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[0])), module, MiniTOURS::ins + 0));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[1])), module, MiniTOURS::ins + 1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[2])), module, MiniTOURS::ins + 2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[3])), module, MiniTOURS::ins + 3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[4])), module, MiniTOURS::ins + 4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[5])), module, MiniTOURS::ins + 5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[6])), module, MiniTOURS::ins + 6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x4, yCoords[7])), module, MiniTOURS::ins + 7));

		//in toggles
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[0])), module, MiniTOURS::outselect + 0, MiniTOURS::outselectL + 0));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[1])), module, MiniTOURS::outselect + 1, MiniTOURS::outselectL + 1));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[2])), module, MiniTOURS::outselect + 2, MiniTOURS::outselectL + 2));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[3])), module, MiniTOURS::outselect + 3, MiniTOURS::outselectL + 3));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[4])), module, MiniTOURS::outselect + 4, MiniTOURS::outselectL + 4));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[5])), module, MiniTOURS::outselect + 5, MiniTOURS::outselectL + 5));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[6])), module, MiniTOURS::outselect + 6, MiniTOURS::outselectL + 6));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<YellowLight>>>(mm2px(Vec(x5, yCoords[7])), module, MiniTOURS::outselect + 7, MiniTOURS::outselectL + 7));

		// main out
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x6, y1)), module, MiniTOURS::out1));

		// sync stuff
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x1, yCoords[2])), module, MiniTOURS::outSyncIn));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(x6, yCoords[2])), module, MiniTOURS::inSyncIn));

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x1, yCoords[5])), module, MiniTOURS::outSyncOut));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(x6, yCoords[5])), module, MiniTOURS::inSyncOut));

		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x1, yCoords[2] - 7.5)), module, MiniTOURS::outlock));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(x1, yCoords[5] - 7.5)), module, MiniTOURS::outlink));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(x6, yCoords[2] - 7.5)), module, MiniTOURS::inlock));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(x6, yCoords[5] - 7.5)), module, MiniTOURS::inlink));
		
	}
};


Model* modelMiniTOURS = createModel<MiniTOURS, MiniTOURSWidget>("miniTOURS");