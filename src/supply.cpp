#include "plugin.hpp"


struct SUPPLY : Module {
	enum ParamId {
		C1P2_PARAM,
		C1P4_PARAM,
		C1P3_PARAM,
		C1P1_PARAM,
		C1B_PARAM,
		C2P4_PARAM,
		C2P3_PARAM,
		C2P1_PARAM,
		C2P2_PARAM,
		C2B_PARAM,
		C3P3_PARAM,
		C3P1_PARAM,
		C3P2_PARAM,
		C3P4_PARAM,
		C3B_PARAM,
		C4P2_PARAM,
		C4P1_PARAM,
		C4B_PARAM,
		C4P3_PARAM,
		C4P4_PARAM,
		C5P2_PARAM,
		C5P3_PARAM,
		C5P4_PARAM,
		C5P1_PARAM,
		C5B_PARAM,
		C6P2_PARAM,
		C6P1_PARAM,
		C6P4_PARAM,
		C6B_PARAM,
		C6P3_PARAM,
		C7P1_PARAM,
		C7P3_PARAM,
		C7B_PARAM,
		C7P4_PARAM,
		C7P2_PARAM,
		C8P3_PARAM,
		C8P1_PARAM,
		C8P2_PARAM,
		C8P4_PARAM,
		C8B_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		GATE1_INPUT,
		GATE2_INPUT,
		GATE3_INPUT,
		GATE4_INPUT,
		GATE5_INPUT,
		GATE6_INPUT,
		GATE7_INPUT,
		GATE8_INPUT,
		SYNC_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT1_OUTPUT,
		OUT4_OUTPUT,
		OUT3_OUTPUT,
		OUT2_OUTPUT,
		SYNC_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHT1_LIGHT,
		LIGHT2_LIGHT,
		LIGHT3_LIGHT,
		LIGHT4_LIGHT,
		LIGHT5_LIGHT,
		LIGHT6_LIGHT,
		LIGHT7_LIGHT,
		LIGHT8_LIGHT,
		SYNC_LIGHT,
		SYNCOut_LIGHT,
		LIGHTS_LEN
	};

	SUPPLY() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(C1P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C1P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C1P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C1P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C1B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C2P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C2P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C2P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C2P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C2B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C3P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C3P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C3P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C3P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C3B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C4P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C4P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C4B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C4P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C4P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C5P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C5P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C5P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C5P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C5B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C6P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C6P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C6P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C6B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C6P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C7P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C7P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C7B_PARAM, 0.f, 1.f, 0.f, "");
		configParam(C7P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C7P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C8P3_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C8P1_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C8P2_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C8P4_PARAM, -10.f, 10.f, 0.f, "");
		configParam(C8B_PARAM, 0.f, 1.f, 0.f, "");
		configInput(GATE1_INPUT, "");
		configInput(GATE2_INPUT, "");
		configInput(GATE3_INPUT, "");
		configInput(GATE4_INPUT, "");
		configInput(GATE5_INPUT, "");
		configInput(GATE6_INPUT, "");
		configInput(GATE7_INPUT, "");
		configInput(GATE8_INPUT, "");
		configInput(SYNC_INPUT, "");
		configOutput(OUT1_OUTPUT, "");
		configOutput(OUT4_OUTPUT, "");
		configOutput(OUT3_OUTPUT, "");
		configOutput(OUT2_OUTPUT, "");
		configOutput(SYNC_OUTPUT, "");
	}

	// output selector and sync variables, broken sync tolerance
	float channelout = 1;
	// float tol = 0.01;


	void process(const ProcessArgs& args) override {

		// select channel

		if(inputs[SYNC_INPUT].isConnected() == true){
			lights[SYNC_LIGHT].setBrightness(1.f);

			// check sync input for voltage

			// if(inputs[SYNC_INPUT].getVoltage() == 1.f){
			// 	channelout = 1;
			// 	outputs[SYNC_OUTPUT].setVoltage(1.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 2.f){
			// 	channelout = 2;
			// 	outputs[SYNC_OUTPUT].setVoltage(2.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 3.f){
			// 	channelout = 3;
			// 	outputs[SYNC_OUTPUT].setVoltage(3.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 4.f){
			// 	channelout = 4;
			// 	outputs[SYNC_OUTPUT].setVoltage(4.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 5.f){
			// 	channelout = 5;
			// 	outputs[SYNC_OUTPUT].setVoltage(5.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 6.f){
			// 	channelout = 6;
			// 	outputs[SYNC_OUTPUT].setVoltage(6.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 7.f){
			// 	channelout = 7;
			// 	outputs[SYNC_OUTPUT].setVoltage(7.f);
			// } else if(inputs[SYNC_INPUT].getVoltage() == 8.f){
			// 	channelout = 8;
			// 	outputs[SYNC_OUTPUT].setVoltage(8.f);
			// }

			outputs[SYNC_OUTPUT].setVoltage(inputs[SYNC_INPUT].getVoltage());
			channelout = (int)inputs[SYNC_INPUT].getVoltage();

		} else {
			lights[SYNC_LIGHT].setBrightness(0.f);

			// select via gate and button if not synced (FIX THIS WITH CAST TO CHANNELOUT)

			if(params[C1B_PARAM].getValue() == 1 || inputs[GATE1_INPUT].getVoltage() > 5.f){
			channelout = 1;
			outputs[SYNC_OUTPUT].setVoltage(1.f);
			}
			else if(params[C2B_PARAM].getValue() == 1 || inputs[GATE2_INPUT].getVoltage() > 5.f){
			channelout = 2;
			outputs[SYNC_OUTPUT].setVoltage(2.f);
			}
			else if(params[C3B_PARAM].getValue() == 1 || inputs[GATE3_INPUT].getVoltage() > 5.f){
			channelout = 3;
			outputs[SYNC_OUTPUT].setVoltage(3.f);
			}
			else if(params[C4B_PARAM].getValue() == 1 || inputs[GATE4_INPUT].getVoltage() > 5.f){
			channelout = 4;
			outputs[SYNC_OUTPUT].setVoltage(4.f);
			}
			else if(params[C5B_PARAM].getValue() == 1 || inputs[GATE5_INPUT].getVoltage() > 5.f){
			channelout = 5;
			outputs[SYNC_OUTPUT].setVoltage(5.f);
			}
			else if(params[C6B_PARAM].getValue() == 1 || inputs[GATE6_INPUT].getVoltage() > 5.f){
			channelout = 6;
			outputs[SYNC_OUTPUT].setVoltage(6.f);
			}
			else if(params[C7B_PARAM].getValue() == 1 || inputs[GATE7_INPUT].getVoltage() > 5.f){
			channelout = 7;
			outputs[SYNC_OUTPUT].setVoltage(7.f);
			}
			else if(params[C8B_PARAM].getValue() == 1 || inputs[GATE8_INPUT].getVoltage() > 5.f){
			channelout = 8;
			outputs[SYNC_OUTPUT].setVoltage(8.f);
			}
		}

	
		
		// set channel
		if(channelout == 1){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(1.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C1P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C1P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C1P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C1P4_PARAM].getValue());


		} else if(channelout == 2){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(1.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);
			
			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C2P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C2P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C2P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C2P4_PARAM].getValue());
			
		} else if(channelout == 3){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(1.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);
			
			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C3P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C3P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C3P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C3P4_PARAM].getValue());
			
		} else if(channelout == 4){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(1.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C4P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C4P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C4P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C4P4_PARAM].getValue());
			
		} else if(channelout == 5){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(1.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C5P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C5P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C5P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C5P4_PARAM].getValue());
			
		} else if(channelout == 6){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(1.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C6P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C6P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C6P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C6P4_PARAM].getValue());
			
		} else if(channelout == 7){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(1.f);
			lights[LIGHT8_LIGHT].setBrightness(0.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C7P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C7P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C7P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C7P4_PARAM].getValue());
			
		} else if(channelout == 8){
			// lights
			
			lights[LIGHT1_LIGHT].setBrightness(0.f);
			lights[LIGHT2_LIGHT].setBrightness(0.f);
			lights[LIGHT3_LIGHT].setBrightness(0.f);
			lights[LIGHT4_LIGHT].setBrightness(0.f);
			lights[LIGHT5_LIGHT].setBrightness(0.f);
			lights[LIGHT6_LIGHT].setBrightness(0.f);
			lights[LIGHT7_LIGHT].setBrightness(0.f);
			lights[LIGHT8_LIGHT].setBrightness(1.f);

			// voltages
			outputs[OUT1_OUTPUT].setVoltage(params[C8P1_PARAM].getValue());
			outputs[OUT2_OUTPUT].setVoltage(params[C8P2_PARAM].getValue());
			outputs[OUT3_OUTPUT].setVoltage(params[C8P3_PARAM].getValue());
			outputs[OUT4_OUTPUT].setVoltage(params[C8P4_PARAM].getValue());
			
		}

		if(outputs[SYNC_OUTPUT].isConnected()){
				lights[SYNCOut_LIGHT].setBrightness(1.f);
			} else {
				lights[SYNCOut_LIGHT].setBrightness(0.f);
			}

	}
};


struct SUPPLYWidget : ModuleWidget {
	SUPPLYWidget(SUPPLY* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/SUPPLY.svg")));

		// screws

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// selection buttons
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 28.5)), module, SUPPLY::C1B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 40)), module, SUPPLY::C2B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 51.5)), module, SUPPLY::C3B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 63)), module, SUPPLY::C4B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 74.5)), module, SUPPLY::C5B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 86)), module, SUPPLY::C6B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 97.5)), module, SUPPLY::C7B_PARAM));
		addParam(createParamCentered<VCVButton>(mm2px(Vec(15.75, 109)), module, SUPPLY::C8B_PARAM));

		// voltage dials

		// channel 1

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 28.5)), module, SUPPLY::C1P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 28.5)), module, SUPPLY::C1P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 28.5)), module, SUPPLY::C1P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 28.5)), module, SUPPLY::C1P1_PARAM));

		// channel 2
		
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 40)), module, SUPPLY::C2P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 40)), module, SUPPLY::C2P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 40)), module, SUPPLY::C2P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 40)), module, SUPPLY::C2P2_PARAM));

		// channel 3
		
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 51.5)), module, SUPPLY::C3P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 51.5)), module, SUPPLY::C3P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 51.5)), module, SUPPLY::C3P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 51.5)), module, SUPPLY::C3P4_PARAM));

		// channel 4
		
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 63)), module, SUPPLY::C4P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 63)), module, SUPPLY::C4P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 63)), module, SUPPLY::C4P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 63)), module, SUPPLY::C4P4_PARAM));

		// channel 5

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 74.5)), module, SUPPLY::C5P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 74.5)), module, SUPPLY::C5P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 74.5)), module, SUPPLY::C5P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 74.5)), module, SUPPLY::C5P1_PARAM));

		// channel 6
		
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 86)), module, SUPPLY::C6P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 86)), module, SUPPLY::C6P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 86)), module, SUPPLY::C6P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 86)), module, SUPPLY::C6P3_PARAM));

		// channel 7

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 97.5)), module, SUPPLY::C7P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 97.5)), module, SUPPLY::C7P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 97.5)), module, SUPPLY::C7P4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 97.5)), module, SUPPLY::C7P2_PARAM));

		// channel 8

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(53.5, 109)), module, SUPPLY::C8P3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(32.305, 109)), module, SUPPLY::C8P1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(43, 109)), module, SUPPLY::C8P2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(64, 109)), module, SUPPLY::C8P4_PARAM));
		
		// select gate inputs

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 28.5)), module, SUPPLY::GATE1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 40)), module, SUPPLY::GATE2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 51.5)), module, SUPPLY::GATE3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 63)), module, SUPPLY::GATE4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 74.5)), module, SUPPLY::GATE5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 86)), module, SUPPLY::GATE6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 97.5)), module, SUPPLY::GATE7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 109)), module, SUPPLY::GATE8_INPUT));

		// voltage outputs

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(17.56, 120)), module, SUPPLY::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(53.56, 120)), module, SUPPLY::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(41.56, 120)), module, SUPPLY::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(29.56, 120)), module, SUPPLY::OUT2_OUTPUT));

		// indicator lights

		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 28.5)), module, SUPPLY::LIGHT1_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 40)), module, SUPPLY::LIGHT2_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 51.5)), module, SUPPLY::LIGHT3_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 63)), module, SUPPLY::LIGHT4_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 74.5)), module, SUPPLY::LIGHT5_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 86)), module, SUPPLY::LIGHT6_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 97.5)), module, SUPPLY::LIGHT7_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(23.285, 109)), module, SUPPLY::LIGHT8_LIGHT));

		// sync

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(6.75, 12.5)), module, SUPPLY::SYNC_INPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(64.37, 12.5)), module, SUPPLY::SYNC_OUTPUT));
		addChild(createLightCentered<MediumLight<RedLight>>(mm2px(Vec(13.75, 12.5)), module, SUPPLY::SYNC_LIGHT));
		addChild(createLightCentered<MediumLight<YellowLight>>(mm2px(Vec(57.37, 12.5)), module, SUPPLY::SYNCOut_LIGHT));
	}
};


Model* modelSUPPLY = createModel<SUPPLY, SUPPLYWidget>("SUPPLY");