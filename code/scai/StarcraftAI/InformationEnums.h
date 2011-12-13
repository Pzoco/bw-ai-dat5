#pragma once
#include <BWAPI.h>
namespace InformationEnums
{
	enum ThreatLevel {ThreatLow,ThreatMedium,ThreatHigh};
	enum Matchup{NotSet,MatchupTvZ,MatchupTvP,MatchupTvT};
	enum Positions {NE,SE,SW,NW};
	enum Time {AlmostNone=100, Fast=340, Middle=360,Long=500};
};