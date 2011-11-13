#pragma once

class Weights
{
public:
	double thetaAllyPF;
	double thetaSquadCenterPF;
	double thetaMaximumDistancePF;
	double thetaWeaponCoolDownPF;
	double thetaEdgesPF;
	Weights(void);
	void Weights::UpdateThetasList();
};
