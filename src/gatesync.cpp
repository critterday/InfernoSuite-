#include "plugin.hpp"

// FIX THE CORNERS ON THE 'back' SVG ELEMENT THEYRE ROUNDED RN


struct GATESYNC : Module {
	enum ParamId {
		PARAMS_LEN
	};
	enum InputId {
		syncIn,
		g1In,
		g2In,
		g3In,
		g4In,
		g5In,
		g6In,
		g7In,
		g8In,
		INPUTS_LEN
	};
	enum OutputId {
		syncOut,
		g1Out,
		g2Out,
		g3Out,
		g4Out,
		g5Out,
		g6Out,
		g7Out,
		g8Out,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	GATESYNC() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		
		configInput(syncIn, "SYNC IN");
		configInput(g1In, "gate 1");
		configInput(g2In, "gate 2");
		configInput(g3In, "gate 3");
		configInput(g4In, "gate 4");
		configInput(g5In, "gate 5");
		configInput(g6In, "gate 6");
		configInput(g7In, "gate 7");
		configInput(g8In, "gate 8");

		configOutput(syncOut, "SYNC Out");
		configOutput(g1Out, "gate 1");
		configOutput(g2Out, "gate 2");
		configOutput(g3Out, "gate 3");
		configOutput(g4Out, "gate 4");
		configOutput(g5Out, "gate 5");
		configOutput(g6Out, "gate 6");
		configOutput(g7Out, "gate 7");
		configOutput(g8Out, "gate 8");
	}

	void process(const ProcessArgs& args) override {
		
		// sync input to gate outputs

		if (inputs[syncIn].isConnected() == true){

			if (inputs[syncIn].getVoltage() == 1){
				outputs[g1Out].setVoltage(10.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 2){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(10.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 3){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(10.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 4){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(10.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 5){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(10.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 6){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(10.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 7){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(10.f);
				outputs[g8Out].setVoltage(0.f);
			} else if (inputs[syncIn].getVoltage() == 8){
				outputs[g1Out].setVoltage(0.f);
				outputs[g2Out].setVoltage(0.f);
				outputs[g3Out].setVoltage(0.f);
				outputs[g4Out].setVoltage(0.f);
				outputs[g5Out].setVoltage(0.f);
				outputs[g6Out].setVoltage(0.f);
				outputs[g7Out].setVoltage(0.f);
				outputs[g8Out].setVoltage(10.f);
			}
		} else {
			outputs[g1Out].setVoltage(0.f);
			outputs[g2Out].setVoltage(0.f);
			outputs[g3Out].setVoltage(0.f);
			outputs[g4Out].setVoltage(0.f);
			outputs[g5Out].setVoltage(0.f);
			outputs[g6Out].setVoltage(0.f);
			outputs[g7Out].setVoltage(0.f);
			outputs[g8Out].setVoltage(0.f);
		}

		// gate inputs to sync output

		if(inputs[g1In].getVoltage() > 5){
			outputs[syncOut].setVoltage(1.f);
		} else if(inputs[g2In].getVoltage() > 5){
			outputs[syncOut].setVoltage(2.f);
		} else if(inputs[g3In].getVoltage() > 5){
			outputs[syncOut].setVoltage(3.f);
		} else if(inputs[g4In].getVoltage() > 5){
			outputs[syncOut].setVoltage(4.f);
		} else if(inputs[g5In].getVoltage() > 5){
			outputs[syncOut].setVoltage(5.f);
		} else if(inputs[g6In].getVoltage() > 5){
			outputs[syncOut].setVoltage(6.f);
		} else if(inputs[g7In].getVoltage() > 5){
			outputs[syncOut].setVoltage(7.f);
		} else if(inputs[g8In].getVoltage() > 5){
			outputs[syncOut].setVoltage(8.f);
		}

	}
};


struct GATESYNCWidget : ModuleWidget {
	GATESYNCWidget(GATESYNC* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/GATESYNC.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		//gates in
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 40)), module, GATESYNC::g1In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 51.5)), module, GATESYNC::g2In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 63)), module, GATESYNC::g3In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 74.5)), module, GATESYNC::g4In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 86)), module, GATESYNC::g5In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 97.5)), module, GATESYNC::g6In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 109)), module, GATESYNC::g7In));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 120)), module, GATESYNC::g8In));
		
		//sync out
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 23)), module, GATESYNC::syncOut));
		
		// sync in
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.773, 23)), module, GATESYNC::syncIn));
		
		//gates out
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 40)), module, GATESYNC::g1Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 51.5)), module, GATESYNC::g2Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 63)), module, GATESYNC::g3Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 74.5)), module, GATESYNC::g4Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 86)), module, GATESYNC::g5Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 97.5)), module, GATESYNC::g6Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 109)), module, GATESYNC::g7Out));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(14.547, 120)), module, GATESYNC::g8Out));

	}
};


Model* modelGATESYNC = createModel<GATESYNC, GATESYNCWidget>("GATESYNC");