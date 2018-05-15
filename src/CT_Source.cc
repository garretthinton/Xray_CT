#include "CT_Source.hh"
#include <sstream>
#include "G4UImanager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

// See CT_Source.hh for details
CT_Source::CT_Source()
{
	centerPosx = 0;
	centerPosy = 0;
	centerPosz = 75.0;
	intensity = 1;
}

// See CT_Source.hh for details
CT_Source::CT_Source(
	double injectionPosx,
	double injectionPosy,
	double injectionPosz,
	char src_intensity)
{
	this->centerPosx = injectionPosx;
	this->centerPosy = injectionPosy;
	this->centerPosz = injectionPosz;
	this->intensity = src_intensity;
}

// See CT_Source.hh for details
CT_Source::~CT_Source()
{

}

//Getters
double CT_Source::getCenterPosx() { return centerPosx; }
double CT_Source::getCenterPosy() { return centerPosy; }
double CT_Source::getCenterPosz() { return centerPosz; }
char CT_Source::getIntensity() { return intensity; }