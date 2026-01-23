#include "plugin.hpp"


Plugin* pluginInstance;


void init(Plugin* p) {
	pluginInstance = p;

	// Add modules here
	// p->addModel(modelMyModule);
	p->addModel(modelATTOFF);
	p->addModel(modelSUPPLY);
	p->addModel(modelFORK);
	p->addModel(modelORG_EX);
	p->addModel(modelDEPOT);
	p->addModel(modelGATESYNC);
	p->addModel(modelMiniSUPPLY);
	p->addModel(modelFXB);
	p->addModel(modelSATURN);
	p->addModel(modelCVMEM);
	p->addModel(modelPOLYSEQ);

	// Any other plugin initialization may go here.
	// As an alternative, consider lazy-loading assets and lookup tables when your module is created to reduce startup times of Rack.
}
