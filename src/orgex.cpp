#include "plugin.hpp"
#include <map>
#include <cmath>


struct ORG_EX : Module {
	enum ParamId {
		cWhite,
		cRed,
		cBlue,
		dWhite,
		dRed,
		dBlue,
		eWhite,
		eRed,
		eBlue,
		fWhite,
		fRed,
		fBlue,
		gWhite,
		gRed,
		gBlue,
		aWhite,
		aRed,
		aBlue,
		bWhite,
		bRed,
		bBlue,
		csWhite,
		csRed,
		csBlue,
		efWhite,
		efRed,
		efBlue,
		fsWhite,
		fsRed,
		fsBlue,
		afWhite,
		afRed,
		afBlue,
		bfWhite,
		bfRed,
		bfBlue,
		PARAMS_LEN
	};
	enum InputId {
		input,
		INPUTS_LEN
	};
	enum OutputId {
		output,
		OUTPUTS_LEN
	};
	enum LightId {
		cWhiteL,
		cRedL,
		cBlueL,
		dWhiteL,
		dRedL,
		dBlueL,
		eWhiteL,
		eRedL,
		eBlueL,
		fWhiteL,
		fRedL,
		fBlueL,
		gWhiteL,
		gRedL,
		gBlueL,
		aWhiteL,
		aRedL,
		aBlueL,
		bWhiteL,
		bRedL,
		bBlueL,
		csWhiteL,
		csRedL,
		csBlueL,
		efWhiteL,
		efRedL,
		efBlueL,
		fsWhiteL,
		fsRedL,
		fsBlueL,
		afWhiteL,
		afRedL,
		afBlueL,
		bfWhiteL,
		bfRedL,
		bfBlueL,
		LIGHTS_LEN
	};

	ORG_EX() {
		config(PARAMS_LEN, INPUTS_LEN, OUTPUTS_LEN, LIGHTS_LEN);
		configParam(cWhite, 0.f, 1.f, 0.f, "");
		configParam(cRed, 0.f, 1.f, 0.f, "");
		configParam(cBlue, 0.f, 1.f, 0.f, "");
		configParam(dWhite, 0.f, 1.f, 0.f, "");
		configParam(dRed, 0.f, 1.f, 0.f, "");
		configParam(dBlue, 0.f, 1.f, 0.f, "");
		configParam(eWhite, 0.f, 1.f, 0.f, "");
		configParam(eRed, 0.f, 1.f, 0.f, "");
		configParam(eBlue, 0.f, 1.f, 0.f, "");
		configParam(fWhite, 0.f, 1.f, 0.f, "");
		configParam(fRed, 0.f, 1.f, 0.f, "");
		configParam(fBlue, 0.f, 1.f, 0.f, "");
		configParam(gWhite, 0.f, 1.f, 0.f, "");
		configParam(gRed, 0.f, 1.f, 0.f, "");
		configParam(gBlue, 0.f, 1.f, 0.f, "");
		configParam(aWhite, 0.f, 1.f, 0.f, "");
		configParam(aRed, 0.f, 1.f, 0.f, "");
		configParam(aBlue, 0.f, 1.f, 0.f, "");
		configParam(bWhite, 0.f, 1.f, 0.f, "");
		configParam(bRed, 0.f, 1.f, 0.f, "");
		configParam(bBlue, 0.f, 1.f, 0.f, "");
		configParam(csWhite, 0.f, 1.f, 0.f, "");
		configParam(csRed, 0.f, 1.f, 0.f, "");
		configParam(csBlue, 0.f, 1.f, 0.f, "");
		configParam(efWhite, 0.f, 1.f, 0.f, "");
		configParam(efRed, 0.f, 1.f, 0.f, "");
		configParam(efBlue, 0.f, 1.f, 0.f, "");
		configParam(fsWhite, 0.f, 1.f, 0.f, "");
		configParam(fsRed, 0.f, 1.f, 0.f, "");
		configParam(fsBlue, 0.f, 1.f, 0.f, "");
		configParam(afWhite, 0.f, 1.f, 0.f, "");
		configParam(afRed, 0.f, 1.f, 0.f, "");
		configParam(afBlue, 0.f, 1.f, 0.f, "");
		configParam(bfWhite, 0.f, 1.f, 0.f, "");
		configParam(bfRed, 0.f, 1.f, 0.f, "");
		configParam(bfBlue, 0.f, 1.f, 0.f, "");
		configInput(input, "CV");
		configOutput(output, "CV");
	}

	
	// SEE IF MOVING THESE AROUND FIXES INITIALIZE FUNCTION (nvm i think i got it) <- no i fuckin didnt lmao
	float cpitch = 0;
	float dpitch = 0;
	float epitch = 0;
	float fpitch = 0;
	float gpitch = 0;
	float apitch = 0;
	float bpitch = 0;
	float cspitch = 0;
	float efpitch = 0;
	float fspitch = 0;
	float afpitch = 0;
	float bfpitch = 0;

	void process(const ProcessArgs& args) override {

		//change pitch val variables

		//c
		if(params[cWhite].getValue() == 1){
			cpitch = 0;
		} else if (params[cRed].getValue() == 1){
			cpitch = -1;
		} else if (params[cBlue].getValue() == 1){
			cpitch = 1;
		}

		//d
		if(params[dWhite].getValue() == 1){
			dpitch = 0;
		} else if (params[dRed].getValue() == 1){
			dpitch = -1;
		} else if (params[dBlue].getValue() == 1){
			dpitch = 1;
		}

		//e
		if(params[eWhite].getValue() == 1){
			epitch = 0;
		} else if (params[eRed].getValue() == 1){
			epitch = -1;
		} else if (params[eBlue].getValue() == 1){
			epitch = 1;
		}

		//f
		if(params[fWhite].getValue() == 1){
			fpitch = 0;
		} else if (params[fRed].getValue() == 1){
			fpitch = -1;
		} else if (params[fBlue].getValue() == 1){
			fpitch = 1;
		}

		//g
		if(params[gWhite].getValue() == 1){
			gpitch = 0;
		} else if (params[gRed].getValue() == 1){
			gpitch = -1;
		} else if (params[gBlue].getValue() == 1){
			gpitch = 1;
		}

		//a
		if(params[aWhite].getValue() == 1){
			apitch = 0;
		} else if (params[aRed].getValue() == 1){
			apitch = -1;
		} else if (params[aBlue].getValue() == 1){
			apitch = 1;
		}

		//b
		if(params[bWhite].getValue() == 1){
			bpitch = 0;
		} else if (params[bRed].getValue() == 1){
			bpitch = -1;
		} else if (params[bBlue].getValue() == 1){
			bpitch = 1;
		}

		//cs
		if(params[csWhite].getValue() == 1){
			cspitch = 0;
		} else if (params[csRed].getValue() == 1){
			cspitch = -1;
		} else if (params[csBlue].getValue() == 1){
			cspitch = 1;
		}
		//ef
		if(params[efWhite].getValue() == 1){
			efpitch = 0;
		} else if (params[efRed].getValue() == 1){
			efpitch = -1;
		} else if (params[efBlue].getValue() == 1){
			efpitch = 1;
		}

		//fs
		if(params[fsWhite].getValue() == 1){
			fspitch = 0;
		} else if (params[fsRed].getValue() == 1){
			fspitch = -1;
		} else if (params[fsBlue].getValue() == 1){
			fspitch = 1;
		}

		//af
		if(params[afWhite].getValue() == 1){
			afpitch = 0;
		} else if (params[afRed].getValue() == 1){
			afpitch = -1;
		} else if (params[afBlue].getValue() == 1){
			afpitch = 1;
		}

		//bf
		if(params[bfWhite].getValue() == 1){
			bfpitch = 0;
		} else if (params[bfRed].getValue() == 1){
			bfpitch = -1;
		} else if (params[bfBlue].getValue() == 1){
			bfpitch = 1;
		}
		
		//set lights
		
		//c
		if(cpitch == 1){
			lights[cWhite].setBrightness(0.f);
			lights[cRed].setBrightness(0.f);
			lights[cBlue].setBrightness(1.f);
		} else if (cpitch == -1){
			lights[cWhite].setBrightness(0.f);
			lights[cRed].setBrightness(1.f);
			lights[cBlue].setBrightness(0.f);
		} else {
			lights[cWhite].setBrightness(1.f);
			lights[cRed].setBrightness(0.f);
			lights[cBlue].setBrightness(0.f);
		}

		//d
		if(dpitch == 1){
			lights[dWhite].setBrightness(0.f);
			lights[dRed].setBrightness(0.f);
			lights[dBlue].setBrightness(1.f);
		} else if (dpitch == -1){
			lights[dWhite].setBrightness(0.f);
			lights[dRed].setBrightness(1.f);
			lights[dBlue].setBrightness(0.f);
		} else {
			lights[dWhite].setBrightness(1.f);
			lights[dRed].setBrightness(0.f);
			lights[dBlue].setBrightness(0.f);
		}

		//e
		if(epitch == 1){
			lights[eWhite].setBrightness(0.f);
			lights[eRed].setBrightness(0.f);
			lights[eBlue].setBrightness(1.f);
		} else if (epitch == -1){
			lights[eWhite].setBrightness(0.f);
			lights[eRed].setBrightness(1.f);
			lights[eBlue].setBrightness(0.f);
		} else {
			lights[eWhite].setBrightness(1.f);
			lights[eRed].setBrightness(0.f);
			lights[eBlue].setBrightness(0.f);
		}

		//f
		if(fpitch == 1){
			lights[fWhite].setBrightness(0.f);
			lights[fRed].setBrightness(0.f);
			lights[fBlue].setBrightness(1.f);
		} else if (fpitch == -1){
			lights[fWhite].setBrightness(0.f);
			lights[fRed].setBrightness(1.f);
			lights[fBlue].setBrightness(0.f);
		} else {
			lights[fWhite].setBrightness(1.f);
			lights[fRed].setBrightness(0.f);
			lights[fBlue].setBrightness(0.f);
		}
		//g
		if(gpitch == 1){
			lights[gWhite].setBrightness(0.f);
			lights[gRed].setBrightness(0.f);
			lights[gBlue].setBrightness(1.f);
		} else if (gpitch == -1){
			lights[gWhite].setBrightness(0.f);
			lights[gRed].setBrightness(1.f);
			lights[gBlue].setBrightness(0.f);
		} else {
			lights[gWhite].setBrightness(1.f);
			lights[gRed].setBrightness(0.f);
			lights[gBlue].setBrightness(0.f);
		}
		//a
		if(apitch == 1){
			lights[aWhite].setBrightness(0.f);
			lights[aRed].setBrightness(0.f);
			lights[aBlue].setBrightness(1.f);
		} else if (apitch == -1){
			lights[aWhite].setBrightness(0.f);
			lights[aRed].setBrightness(1.f);
			lights[aBlue].setBrightness(0.f);
		} else {
			lights[aWhite].setBrightness(1.f);
			lights[aRed].setBrightness(0.f);
			lights[aBlue].setBrightness(0.f);
		}
		//b
		if(bpitch == 1){
			lights[bWhite].setBrightness(0.f);
			lights[bRed].setBrightness(0.f);
			lights[bBlue].setBrightness(1.f);
		} else if (bpitch == -1){
			lights[bWhite].setBrightness(0.f);
			lights[bRed].setBrightness(1.f);
			lights[bBlue].setBrightness(0.f);
		} else {
			lights[bWhite].setBrightness(1.f);
			lights[bRed].setBrightness(0.f);
			lights[bBlue].setBrightness(0.f);
		}
		//cs
		if(cspitch == 1){
			lights[csWhite].setBrightness(0.f);
			lights[csRed].setBrightness(0.f);
			lights[csBlue].setBrightness(1.f);
		} else if (cspitch == -1){
			lights[csWhite].setBrightness(0.f);
			lights[csRed].setBrightness(1.f);
			lights[csBlue].setBrightness(0.f);
		} else {
			lights[csWhite].setBrightness(1.f);
			lights[csRed].setBrightness(0.f);
			lights[csBlue].setBrightness(0.f);
		}
		//ef
		if(efpitch == 1){
			lights[efWhite].setBrightness(0.f);
			lights[efRed].setBrightness(0.f);
			lights[efBlue].setBrightness(1.f);
		} else if (efpitch == -1){
			lights[efWhite].setBrightness(0.f);
			lights[efRed].setBrightness(1.f);
			lights[efBlue].setBrightness(0.f);
		} else {
			lights[efWhite].setBrightness(1.f);
			lights[efRed].setBrightness(0.f);
			lights[efBlue].setBrightness(0.f);
		}
		//fs
		if(fspitch == 1){
			lights[fsWhite].setBrightness(0.f);
			lights[fsRed].setBrightness(0.f);
			lights[fsBlue].setBrightness(1.f);
		} else if (fspitch == -1){
			lights[fsWhite].setBrightness(0.f);
			lights[fsRed].setBrightness(1.f);
			lights[fsBlue].setBrightness(0.f);
		} else {
			lights[fsWhite].setBrightness(1.f);
			lights[fsRed].setBrightness(0.f);
			lights[fsBlue].setBrightness(0.f);
		}

		//af
		if(afpitch == 1){
			lights[afWhite].setBrightness(0.f);
			lights[afRed].setBrightness(0.f);
			lights[afBlue].setBrightness(1.f);
		} else if (afpitch == -1){
			lights[afWhite].setBrightness(0.f);
			lights[afRed].setBrightness(1.f);
			lights[afBlue].setBrightness(0.f);
		} else {
			lights[afWhite].setBrightness(1.f);
			lights[afRed].setBrightness(0.f);
			lights[afBlue].setBrightness(0.f);
		}
		//bf
		if(bfpitch == 1){
			lights[bfWhite].setBrightness(0.f);
			lights[bfRed].setBrightness(0.f);
			lights[bfBlue].setBrightness(1.f);
		} else if (bfpitch == -1){
			lights[bfWhite].setBrightness(0.f);
			lights[bfRed].setBrightness(1.f);
			lights[bfBlue].setBrightness(0.f);
		} else {
			lights[bfWhite].setBrightness(1.f);
			lights[bfRed].setBrightness(0.f);
			lights[bfBlue].setBrightness(0.f);
		}

		// determine voltage
		int channelcount = std::max(1, inputs[input].getChannels());
		outputs[output].setChannels(channelcount);

		for (int c = 0; c < channelcount; c++){
			
			//get input voltage on channel and find determinant
			float voltsin = inputs[input].getPolyVoltage(c);
			float vdeterm = voltsin - floor(voltsin);
			//correct for rounding errors
			vdeterm *= 1000;
			vdeterm = std::round(vdeterm); // <- for possible precision issues idk

			//determinant storage map 
			std::map<float, float> pcs;
			pcs[0.f] = 0.f;
			pcs[83.f] = 1.f;
			pcs[167.f] = 2.f;
			pcs[250.f] = 3.f;
			pcs[333.f] = 4.f;
			pcs[417.f] = 5.f;
			pcs[500.f] = 6.f;
			pcs[583.f] = 7.f;
			pcs[667.f] = 8.f;
			pcs[750.f] = 9.f;
			pcs[833.f] = 10.f;
			pcs[917.f] = 11.f;

			float pitchclass = pcs[vdeterm]; // <- USE QUANTIZER BEFORE INPUT: i need to find a way to do this without [] operator, as it is now any values that aren't 12-TET will default to C

			//look up and bend pitches

			float tempVout = 0;
			if(pitchclass == 0.f){
				tempVout = voltsin + cpitch/24;
			} else if(pitchclass == 1.f){
				tempVout = voltsin + cspitch/24;
			} else if(pitchclass == 2.f){
				tempVout = voltsin + dpitch/24;
			} else if(pitchclass == 3.f){
				tempVout = voltsin + efpitch/24;
			} else if(pitchclass == 4.f){
				tempVout = voltsin + epitch/24;
			} else if(pitchclass == 5.f){
				tempVout = voltsin + fpitch/24;
			} else if(pitchclass == 6.f){
				tempVout = voltsin + fspitch/24;
			} else if(pitchclass == 7.f){
				tempVout = voltsin + gpitch/24;
			} else if(pitchclass == 8.f){
				tempVout = voltsin + afpitch/24;
			} else if(pitchclass == 9.f){
				tempVout = voltsin + apitch/24;
			} else if(pitchclass == 10.f){
				tempVout = voltsin + bfpitch/24;
			} else if(pitchclass == 11.f){
				tempVout = voltsin + bpitch/24;
			} else {
				tempVout = voltsin;
			}

			outputs[output].setVoltage(tempVout, c);

		}
		
	}
};


struct ORG_EXWidget : ModuleWidget {
	ORG_EXWidget(ORG_EX* module) {
		setModule(module);
		setPanel(createPanel(asset::plugin(pluginInstance, "res/orgex.svg")));

		
		float leftoffset = 9.807;
		float rightoffset = 4.904;
		float redx = 43.75;
		float bluex = 34.5;
		float whitex = 39.125;

		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, 0)));
		addChild(createWidget<ScrewSilver>(Vec(RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));
		addChild(createWidget<ScrewSilver>(Vec(box.size.x - 2 * RACK_GRID_WIDTH, RACK_GRID_HEIGHT - RACK_GRID_WIDTH)));

		// C
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 99.588 + rightoffset)), module, ORG_EX::cRed, ORG_EX::cRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 99.588 + leftoffset)), module, ORG_EX::cWhite, ORG_EX::cWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(bluex, 99.588 + rightoffset)), module, ORG_EX::cBlue, ORG_EX::cBlueL));

		// D
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 85.706 + rightoffset)), module, ORG_EX::dRed, ORG_EX::dRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 85.706 + leftoffset)), module, ORG_EX::dWhite, ORG_EX::dWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(bluex, 85.706 + rightoffset)), module, ORG_EX::dBlue, ORG_EX::dBlueL));

		// E
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 71.825 + rightoffset)), module, ORG_EX::eRed, ORG_EX::eRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 71.825 + leftoffset)), module, ORG_EX::eWhite, ORG_EX::eWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px (Vec(bluex, 71.825 + rightoffset)), module, ORG_EX::eBlue, ORG_EX::eBlueL));

		// F
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 57.943 + rightoffset)), module, ORG_EX::fRed, ORG_EX::fRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 57.943 + leftoffset)), module, ORG_EX::fWhite, ORG_EX::fWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec (bluex, 57.943 + rightoffset)), module, ORG_EX::fBlue, ORG_EX::fBlueL));

		// G
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 44.062 + rightoffset)), module, ORG_EX::gRed, ORG_EX::gRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 44.062 + leftoffset)), module, ORG_EX::gWhite, ORG_EX::gWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(bluex, 44.062 + rightoffset)), module, ORG_EX::gBlue, ORG_EX::gBlueL));

		// A
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 30.180 + rightoffset)), module, ORG_EX::aRed, ORG_EX::aRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 30.180 + leftoffset)), module, ORG_EX::aWhite, ORG_EX::aWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(bluex, 30.180 + rightoffset)), module, ORG_EX::aBlue, ORG_EX::aBlueL));

		// B
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(redx, 16.299 + rightoffset)), module, ORG_EX::bRed, ORG_EX::bRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(whitex, 16.299 + leftoffset)), module, ORG_EX::bWhite, ORG_EX::bWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(bluex, 16.299 + rightoffset)), module, ORG_EX::bBlue, ORG_EX::bBlueL));
		
		// C#
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(24.167, 99.4)), module, ORG_EX::csRed, ORG_EX::csRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(16.217, 99.4)), module, ORG_EX::csWhite, ORG_EX::csWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(8.26, 99.4)), module, ORG_EX::csBlue, ORG_EX::csBlueL));

		// Ef
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(24.167, 86.121)), module, ORG_EX::efRed, ORG_EX::efRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(16.217, 86.121)), module, ORG_EX::efWhite, ORG_EX::efWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(8.26, 86.121)), module, ORG_EX::efBlue, ORG_EX::efBlueL));

		// F#
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(24.167, 58.538)), module, ORG_EX::fsRed, ORG_EX::fsRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(16.217, 58.538)), module, ORG_EX::fsWhite, ORG_EX::fsWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(8.26, 58.538)), module, ORG_EX::fsBlue, ORG_EX::fsBlueL));

		// Af
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(24.167, 44.476)), module, ORG_EX::afRed, ORG_EX::afRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(16.217, 44.476)), module, ORG_EX::afWhite, ORG_EX::afWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(8.26, 44.476)), module, ORG_EX::afBlue, ORG_EX::afBlueL));

		// Bf
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<RedLight>>>(mm2px(Vec(24.167, 30.595)), module, ORG_EX::bfRed, ORG_EX::bfRedL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<WhiteLight>>>(mm2px(Vec(16.217, 30.595)), module, ORG_EX::bfWhite, ORG_EX::bfWhiteL));
		addParam(createLightParamCentered<VCVLightButton<MediumSimpleLight<BlueLight>>>(mm2px(Vec(8.26, 30.595)), module, ORG_EX::bfBlue, ORG_EX::bfBlueL));

		//ports
		addInput(createInputCentered<PJ301MPort>(mm2px(Vec(16.933, 120)), module, ORG_EX::input));
		addOutput(createOutputCentered<PJ301MPort>(mm2px(Vec(33.866, 120)), module, ORG_EX::output));

		
	}
};


Model* modelORG_EX = createModel<ORG_EX, ORG_EXWidget>("ORG-EX");