#pragma once
#include <BWAPI.h>
#include <BWTA.h>
#include <windows.h>
#include "../ReinforcementLearning.h"
#include "../Squad.h"
#include "../BaseTactic.h"
#include "../UnitHelper.h"

class StarcraftAI : public BWAPI::AIModule
{
public:
	static ReinforcementLearning reinforcementLearning;
	virtual struct Thetas; 
	virtual void onStart();
	virtual void onEnd(bool isWinner);
	virtual void onFrame();
	virtual void onSendText(std::string text);
	virtual void onReceiveText(BWAPI::Player* player, std::string text);
	virtual void onPlayerLeft(BWAPI::Player* player);
	virtual void onNukeDetect(BWAPI::Position target);
	virtual void onUnitEvade(BWAPI::Unit* unit);
	virtual void onUnitShow(BWAPI::Unit* unit);
	virtual void onUnitHide(BWAPI::Unit* unit);
	virtual void onUnitCreate(BWAPI::Unit* unit);
	virtual void onUnitDestroy(BWAPI::Unit* unit);
};
