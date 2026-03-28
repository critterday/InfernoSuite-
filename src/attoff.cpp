#include "plugin.hpp"


struct ATTOFF : Module {
	enum ParamId {
		ENUMS(attp, 8),
		ENUMS(offp, 8),
		PARAMS_LEN
	};
	enum InputId {
		ENUMS(in, 8),
		INPUTS_LEN
	};
	enum OutputId {
		ENUMS(out, 8),
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	ATTOFF() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(offp + 0, -5.f, 5.f, 0.f, "Channel 1 Offset");
		configParam(offp + 1, -5.f, 5.f, 0.f, "Channel 2 Offset");
		configParam(offp + 2, -5.f, 5.f, 0.f, "Channel 3 Offset");
		configParam(offp + 3, -5.f, 5.f, 0.f, "Channel 4 Offset");
		configParam(offp + 4, -5.f, 5.f, 0.f, "Channel 5 Offset");
		configParam(offp + 5, -5.f, 5.f, 0.f, "Channel 6 Offset");
		configParam(offp + 6, -5.f, 5.f, 0.f, "Channel 7 Offset");
		configParam(offp + 7, -5.f, 5.f, 0.f, "Channel 8 Offset");

		configParam(attp + 0, -1.f, 1.f, 0.f, "Channel 1 Attenuvert");
		configParam(attp + 1, -1.f, 1.f, 0.f, "Channel 2 Attenuvert");
		configParam(attp + 2, -1.f, 1.f, 0.f, "Channel 3 Attenuvert");
		configParam(attp + 3, -1.f, 1.f, 0.f, "Channel 4 Attenuvert");
		configParam(attp + 4, -1.f, 1.f, 0.f, "Channel 5 Attenuvert");
		configParam(attp + 5, -1.f, 1.f, 0.f, "Channel 6 Attenuvert");
		configParam(attp + 6, -1.f, 1.f, 0.f, "Channel 7 Attenuvert");
		configParam(attp + 7, -1.f, 1.f, 0.f, "Channel 8 Attenuvert");

		configInput(in + 0, "Channel 1");
		configInput(in + 1, "Channel 2");
		configInput(in + 2, "Channel 3");
		configInput(in + 3, "Channel 4");
		configInput(in + 4, "Channel 5");
		configInput(in + 5, "Channel 6");
		configInput(in + 6, "Channel 7");
		configInput(in + 7, "Channel 8");
		configOutput(out + 0, "Channel 1");
		configOutput(out + 1, "Channel 2");
		configOutput(out + 2, "Channel 3");
		configOutput(out + 3, "Channel 4");
		configOutput(out + 4, "Channel 5");
		configOutput(out + 5, "Channel 6");
		configOutput(out + 6, "Channel 7");
		configOutput(out + 7, "Channel 8");
	}

	void process(const ProcessArgs& args) override {

		for (int i = 0; i < 8; i++){
			int channels = inputs[in + i].getChannels();
			outputs[out + i].setChannels(std::max(1, channels));

			for (int c = 0; c < channels; c++){
				float volts = inputs[in + i].getVoltage(c);
				volts = volts * params[attp + i].getValue();
				volts = volts + params[offp + i].getValue();
				outputs[out + i].setVoltage(volts, c);
			}
		}

	}
};

struct ATTOFFWidget : ModuleWidget {
	ATTOFFWidget(ATTOFF* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/ATTOFF.svg")));

		//screws

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// knobs

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 28.5)), module, ATTOFF::offp + 0));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 28.5)), module, ATTOFF::attp + 0));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 40)), module, ATTOFF::offp + 1));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 40)), module, ATTOFF::attp + 1));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 51.5)), module, ATTOFF::offp + 2));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 51.5)), module, ATTOFF::attp + 2));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 63)), module, ATTOFF::offp + 3));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 63)), module, ATTOFF::attp + 3));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 74.5)), module, ATTOFF::offp + 4));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 74.5)), module, ATTOFF::attp + 4));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 86)), module, ATTOFF::offp + 5));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 86)), module, ATTOFF::attp + 5));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 97.5)), module, ATTOFF::offp + 6));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 97.5)), module, ATTOFF::attp + 6));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 109)), module, ATTOFF::offp + 7));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 109)), module, ATTOFF::attp + 7));

		// inputs

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 28.5)), module, ATTOFF::in + 0));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 40)), module, ATTOFF  ::in + 1));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 51.5)), module, ATTOFF::in + 2));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 63)), module, ATTOFF  ::in + 3));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 74.5)), module, ATTOFF::in + 4));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 86)), module, ATTOFF  ::in + 5));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 97.5)), module, ATTOFF::in + 6));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 109)), module, ATTOFF ::in + 7));

		// outputs

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 28.5)), module, ATTOFF::out + 0));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 40)), module, ATTOFF  ::out + 1));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 51.5)), module, ATTOFF::out + 2));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 63)), module, ATTOFF  ::out + 3));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 74.5)), module, ATTOFF::out + 4));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 86)), module, ATTOFF  ::out + 5));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 97.5)), module, ATTOFF::out + 6));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 109)), module, ATTOFF ::out + 7));
	}
};


Model* modelATTOFF = createModel<ATTOFF, ATTOFFWidget>("ATTOFF");