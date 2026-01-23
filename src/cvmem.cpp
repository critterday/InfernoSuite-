#include "plugin.hpp"


struct CVMEM : Module {
	enum ParamId {
		b1,
		PARAMS_LEN
	};
	enum InputId {
		cvIn,
		gateIn,
		INPUTS_LEN
	};
	enum OutputId {
		cvOut,
		gateOut,
		OUTPUTS_LEN
	};
	enum LightId {
		matchLight,
		LIGHTS_LEN
	};

	CVMEM() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(b1, 0.f, 1.f, 0.f, "Set Voltage");
		configInput(cvIn, "Control Voltage");
		configInput(gateIn, "Memory Gate");
		configOutput(cvOut, "Control Voltage"),
		configOutput(gateOut, "Value Match Boolean");
		configLight(matchLight, "Matching Light");
	}

	float cv = 0.f;

	void process(const ProcessArgs& args) override {

		if((params[b1].getValue() == 1.f) || (inputs[gateIn].getVoltage() > 5.f)){
			cv = inputs[cvIn].getVoltage();
		}

		if(inputs[cvIn].getVoltage() == cv){
			outputs[cvOut].setVoltage(inputs[cvIn].getVoltage());
			outputs[gateOut].setVoltage(10.f);
		} else {
			outputs[gateOut].setVoltage(0.f);
		}

	}
};


struct CVMEMWidget : ModuleWidget {
	CVMEMWidget(CVMEM* module) {

		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/CVMEM.svg")));

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		//addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		addParam(createParamCentered<VCVButton>   (mm2px(Vec(7.62, 30)), module, CVMEM::b1));
		addInput(createInputCentered<PJ301MPort>  (mm2px(Vec(7.62, 56)), module, CVMEM::cvIn));
		addInput(createInputCentered<PJ301MPort>  (mm2px(Vec(7.62, 41)), module, CVMEM::gateIn));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 90)), module, CVMEM::cvOut));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(7.62, 101)), module, CVMEM::gateOut));
	}
};


Model* modelCVMEM = createModel<CVMEM, CVMEMWidget>("CVMEM");