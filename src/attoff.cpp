#include "plugin.hpp"


struct ATTOFF : Module {
	enum ParamId {
		OFF1_PARAM,
		AFF1_PARAM,
		OFF2_PARAM,
		AFF2_PARAM,
		OFF3_PARAM,
		AFF3_PARAM,
		OFF4_PARAM,
		AFF4_PARAM,
		OFF5_PARAM,
		AFF5_PARAM,
		OFF6_PARAM,
		AFF6_PARAM,
		OFF7_PARAM,
		AFF7_PARAM,
		OFF8_PARAM,
		AFF8_PARAM,
		PARAMS_LEN
	};
	enum InputId {
		IN1_INPUT,
		IN2_INPUT,
		IN3_INPUT,
		IN4_INPUT,
		IN5_INPUT,
		IN6_INPUT,
		IN7_INPUT,
		IN8_INPUT,
		INPUTS_LEN
	};
	enum OutputId {
		OUT1_OUTPUT,
		OUT2_OUTPUT,
		OUT3_OUTPUT,
		OUT4_OUTPUT,
		OUT5_OUTPUT,
		OUT6_OUTPUT,
		OUT7_OUTPUT,
		OUT8_OUTPUT,
		OUTPUTS_LEN
	};
	enum LightId {
		LIGHTS_LEN
	};

	ATTOFF() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(OFF1_PARAM, -5.f, 5.f, 0.f, "Channel 1 Offset");
		configParam(AFF1_PARAM, -1.f, 1.f, 0.f, "Channel 1 Attenuvert");
		configParam(OFF2_PARAM, -5.f, 5.f, 0.f, "Channel 2 Offset");
		configParam(AFF2_PARAM, -1.f, 1.f, 0.f, "Channel 2 Attenuvert");
		configParam(OFF3_PARAM, -5.f, 5.f, 0.f, "Channel 3 Offset");
		configParam(AFF3_PARAM, -1.f, 1.f, 0.f, "Channel 3 Attenuvert");
		configParam(OFF4_PARAM, -5.f, 5.f, 0.f, "Channel 4 Offset");
		configParam(AFF4_PARAM, -1.f, 1.f, 0.f, "Channel 4 Attenuvert");
		configParam(OFF5_PARAM, -5.f, 5.f, 0.f, "Channel 5 Offset");
		configParam(AFF5_PARAM, -1.f, 1.f, 0.f, "Channel 5 Attenuvert");
		configParam(OFF6_PARAM, -5.f, 5.f, 0.f, "Channel 6 Offset");
		configParam(AFF6_PARAM, -1.f, 1.f, 0.f, "Channel 6 Attenuvert");
		configParam(OFF7_PARAM, -5.f, 5.f, 0.f, "Channel 7 Offset");
		configParam(AFF7_PARAM, -1.f, 1.f, 0.f, "Channel 7 Attenuvert");
		configParam(OFF8_PARAM, -5.f, 5.f, 0.f, "Channel 8 Offset");
		configParam(AFF8_PARAM, -1.f, 1.f, 0.f, "Channel 8 Attenuvert");
		configInput(IN1_INPUT, "Channel 1");
		configInput(IN2_INPUT, "Channel 2");
		configInput(IN3_INPUT, "Channel 3");
		configInput(IN4_INPUT, "Channel 4");
		configInput(IN5_INPUT, "Channel 5");
		configInput(IN6_INPUT, "Channel 6");
		configInput(IN7_INPUT, "Channel 7");
		configInput(IN8_INPUT, "Channel 8");
		configOutput(OUT1_OUTPUT, "Channel 1");
		configOutput(OUT2_OUTPUT, "Channel 2");
		configOutput(OUT3_OUTPUT, "Channel 3");
		configOutput(OUT4_OUTPUT, "Channel 4");
		configOutput(OUT5_OUTPUT, "Channel 5");
		configOutput(OUT6_OUTPUT, "Channel 6");
		configOutput(OUT7_OUTPUT, "Channel 7");
		configOutput(OUT8_OUTPUT, "Channel 8");
	}

	void process(const ProcessArgs& args) override {

		// get input voltages 

		float involt1 = inputs[IN1_INPUT].getVoltage();
		float involt2 = inputs[IN2_INPUT].getVoltage();
		float involt3 = inputs[IN3_INPUT].getVoltage();
		float involt4 = inputs[IN4_INPUT].getVoltage();
		float involt5 = inputs[IN5_INPUT].getVoltage();
		float involt6 = inputs[IN6_INPUT].getVoltage();
		float involt7 = inputs[IN7_INPUT].getVoltage();
		float involt8 = inputs[IN8_INPUT].getVoltage();

		// compute attenuversion voltages

		float att1 = involt1 * params[AFF1_PARAM].getValue();
		float att2 = involt2 * params[AFF2_PARAM].getValue();
		float att3 = involt3 * params[AFF3_PARAM].getValue();
		float att4 = involt4 * params[AFF4_PARAM].getValue();
		float att5 = involt5 * params[AFF5_PARAM].getValue();
		float att6 = involt6 * params[AFF6_PARAM].getValue();
		float att7 = involt7 * params[AFF7_PARAM].getValue();
		float att8 = involt8 * params[AFF8_PARAM].getValue();

		// compute offsets

		float off1 = att1 + params[OFF1_PARAM].getValue();
		float off2 = att2 + params[OFF2_PARAM].getValue();
		float off3 = att3 + params[OFF3_PARAM].getValue();
		float off4 = att4 + params[OFF4_PARAM].getValue();
		float off5 = att5 + params[OFF5_PARAM].getValue();
		float off6 = att6 + params[OFF6_PARAM].getValue();
		float off7 = att7 + params[OFF7_PARAM].getValue();
		float off8 = att8 + params[OFF8_PARAM].getValue();

		// output
		
		
		outputs[OUT1_OUTPUT].setVoltage(off1);
		outputs[OUT2_OUTPUT].setVoltage(off2);
		outputs[OUT3_OUTPUT].setVoltage(off3);
		outputs[OUT4_OUTPUT].setVoltage(off4);
		outputs[OUT5_OUTPUT].setVoltage(off5);
		outputs[OUT6_OUTPUT].setVoltage(off6);
		outputs[OUT7_OUTPUT].setVoltage(off7);
		outputs[OUT8_OUTPUT].setVoltage(off8);

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

		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 28.5)), module, ATTOFF::OFF1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 28.5)), module, ATTOFF::AFF1_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 40)), module, ATTOFF::OFF2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 40)), module, ATTOFF::AFF2_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 51.5)), module, ATTOFF::OFF3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 51.5)), module, ATTOFF::AFF3_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 63)), module, ATTOFF::OFF4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 63)), module, ATTOFF::AFF4_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 74.5)), module, ATTOFF::OFF5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 74.5)), module, ATTOFF::AFF5_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 86)), module, ATTOFF::OFF6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 86)), module, ATTOFF::AFF6_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 97.5)), module, ATTOFF::OFF7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 97.5)), module, ATTOFF::AFF7_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(40, 109)), module, ATTOFF::OFF8_PARAM));
		addParam(createParamCentered<RoundBlackKnob>(mm2px(Vec(19, 109)), module, ATTOFF::AFF8_PARAM));

		// inputs

		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 28.5)), module, ATTOFF::IN1_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 40)), module, ATTOFF::IN2_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 51.5)), module, ATTOFF::IN3_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 63)), module, ATTOFF::IN4_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 74.5)), module, ATTOFF::IN5_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 86)), module, ATTOFF::IN6_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 97.5)), module, ATTOFF::IN7_INPUT));
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(5.75, 109)), module, ATTOFF::IN8_INPUT));

		// outputs

		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 28.5)), module, ATTOFF::OUT1_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 40)), module, ATTOFF::OUT2_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 51.5)), module, ATTOFF::OUT3_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 63)), module, ATTOFF::OUT4_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 74.5)), module, ATTOFF::OUT5_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 86)), module, ATTOFF::OUT6_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 97.5)), module, ATTOFF::OUT7_OUTPUT));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(55.25, 109)), module, ATTOFF::OUT8_OUTPUT));
	}
};


Model* modelATTOFF = createModel<ATTOFF, ATTOFFWidget>("ATTOFF");