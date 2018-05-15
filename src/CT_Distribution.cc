// CT_Distribution.cc
//
//
// Copyright info
//
//
//
//
//
//
//
//
//
//
//					Date			Author		
// Creation:		Mar 21 2018		Garrett Hinton
// Revision Dates:  
#include "CT_Distribution.hh"
#include <stdlib.h>

// CT_Distribution():  See CT_Distribution.hh for details
CT_Distribution::CT_Distribution()
{
	timeStep = .001;
	doseRadiation = .00001;

	//5, 5, 30, 0, 0, 75, .1, .1, .1
	xLength = 5.0;
	yLength = 5.0;
	zLength = 30.0;
	xCenter = 0.0;
	yCenter = 0.0;
	zCenter = 75.0;
	xIncr = 1;
	yIncr = 1;
	zIncr = 1;
	SetVoxels();
}

CT_Distribution::CT_Distribution(G4String filename, int x_pix, int y_pix, int z_pix)
{
	// In the future, another constructor will be made where all of these variables can be controlled better.
	xLength = 10;
	yLength = 10;
	zLength = 10;
	xCenter = 0;
	yCenter = 0;
	zCenter = 80;
	xIncr = xLength / x_pix;
	yIncr = yLength / y_pix;
	zIncr = zLength / z_pix;
	doseRadiation = .00001;

	// Create a char array to hold the intensity values of all of the sources. 
	im_data = new char[x_pix * y_pix * z_pix];

	// Read in the file to be simulated, along with its size.  
	Read_SPECT_File(filename, x_pix, y_pix, z_pix);

	// Make sources from each element in the char array, im_data, and position it correctly.
	Organize_Sources(x_pix, y_pix, z_pix);
}

// ~CT_Distribution():  See CT_Distribution.hh for details
CT_Distribution::~CT_Distribution()
{

}

// ExecuteMacro:	This class will need to be updated as experiments change.  Right now, it is designed for one source type, spherical
//					in shape, that gives off a specific amount of beams.
void CT_Distribution::ExecuteMacro()
{
	// Get the pointer to the User Interface manager
	G4UImanager* UImanager = G4UImanager::GetUIpointer();

	//Use this command to do a simple spherical GPS source on the head.
	//UImanager->ApplyCommand("/control/execute dist_test.mac");

	//These apply to all sources.  For more information on how these work, search the Application Development manual for Geant4
	UImanager->ApplyCommand("/control/verbose 0");
	UImanager->ApplyCommand("/tracking/verbose 0");
	UImanager->ApplyCommand("/event/verbose 0");
	UImanager->ApplyCommand("/gps/verbose 2");

	//This may not be needed and may cause issues in storing data
	UImanager->ApplyCommand("/gps/source/clear");

	// This makes multiple sources emit at the same intensity for every event run.  Set to false for our purposes.  Setting to false allows
	//   the intensities to be applied to each source so that when beamOn is run, it will randomly select a source to have a beam emit from
	//   depending on the intensities of the sources.
	UImanager->ApplyCommand("/gps/source/multiplevertex false");

	// This is a temporary variable that needs to be removed when using the simulation.  It cuts the amount of sources simulated by the
	//   amount, make_shorter.  Normal simulations with ~100000 sources takes ~an hour, or 20 minutes if it is a good computer.  This just
	//   shortens the wait time for when the program is still being developed.  
	int make_shorter = 1000;
	//
	for (int i = 0; i<sources.size() / make_shorter; i++)
	{
		// This gets the type 'int' into type 'string' format.
		std::ostringstream add1("");
		add1 << (i + 1);
		G4String a0 = add1.str();

		// Add a source.  It is a gamma ray source, a volume source, and a paralellepipe source.
		UImanager->ApplyCommand("/gps/source/add " + a0);
		UImanager->ApplyCommand("/gps/particle gamma");
		UImanager->ApplyCommand("/gps/pos/type Volume");
		UImanager->ApplyCommand("/gps/pos/shape Para");

		//The following lines of code are to get the type 'double' into type 'string' format, so that it can be used in the commands.
		std::ostringstream ss("");
		ss << sources[i].getCenterPosx();
		ss << " ";
		ss << sources[i].getCenterPosy();
		ss << " ";
		ss << sources[i].getCenterPosz();
		G4String a1 = ss.str();

		std::ostringstream xL("");
		xL << xLength;
		G4String a_xL = xL.str();

		std::ostringstream yL("");
		yL << yLength;
		G4String a_yL = yL.str();

		std::ostringstream zL("");
		zL << zLength;
		G4String a_zL = zL.str();


		// Length of the rectangular prism dimensions.
		UImanager->ApplyCommand("/gps/pos/halfx " + a_xL);
		UImanager->ApplyCommand("/gps/pos/halfy " + a_yL);
		UImanager->ApplyCommand("/gps/pos/halfz " + a_zL);

		// Center of the prism
		UImanager->ApplyCommand("/gps/pos/centre " + a1);

		// Intensity of the source being displayed (0 - 255)
		UImanager->ApplyCommand("/gps/source/intensity " + im_data[i]);

		// Same for all sources:  isotropic, one energy that is 140.5 keV.
		UImanager->ApplyCommand("/gps/ang/type iso");
		UImanager->ApplyCommand("/gps/ene/type Mono");
		UImanager->ApplyCommand("/gps/ene/mono 140.5 keV");
	}

	// Lets the viewer see the last 500 rays being emitted.
	UImanager->ApplyCommand("/vis/scene/endOfEventAction accumulate 500");

	//This runs x beams per source. This will depend on the mCi of the total injection
	std::ostringstream beam("");
	beam << (getDoseRadiation()* 3.7 * 10000000);
	G4String sBeam = beam.str();
	UImanager->ApplyCommand("/run/beamOn " + sBeam);

}

// AddSource:  See CT_Distribution.hh for details.
void CT_Distribution::AddSource(CT_Source source)
{
	sources.push_back(source);
}

// SetVoxels:  See CT_Distribution.hh for details.
void CT_Distribution::SetVoxels()
{
	//how many voxels are needed
	int total_Voxels = (xLength / xIncr) * (yLength / yIncr) * (zLength / zIncr);
	int xVox = (xLength / xIncr);
	int yVox = (yLength / yIncr);
	int zVox = (zLength / zIncr);
	double xStart = xCenter - xLength / 2;
	double yStart = yCenter - yLength / 2;
	double zStart = zCenter - zLength / 2;
	for (int i = 0; i < xVox; i++)
	{
		for (int j = 0; j < yVox; j++)
		{
			for (int k = 0; k < zVox; k++)
			{

				sources.push_back(CT_Source(xStart + i*xIncr, yStart + j*yIncr, zStart + k*zIncr, 1));
			}
		}
	}
}

// AdvanceTime:  See CT_Distribution.hh for details.
//	This method is reserved for the dynamic sources
void CT_Distribution::AdvanceTime()
{

}


// Read_SPECT_File:  See CT_Distribution.hh for details.
void CT_Distribution::Read_SPECT_File(string filename, int x, int y, int z)
{
	// Open an input filestream
	std::ifstream fin(filename, ios::binary);

	// If it's open, read in all of the data
	if (fin.is_open())
	{
		fin.read(im_data, (std::streamsize) x*y*z);
	}

	// Close the filestream
	fin.close();
}

// Organize_Sources:  See CT_Distribution.hh for details.
void CT_Distribution::Organize_Sources(int x, int y, int z)
{
	// Start at the edge:  center - (length of side)/2
	double xStart = xCenter - xLength / 2;
	double yStart = yCenter - yLength / 2;
	double zStart = zCenter - zLength / 2;

	// Get to the correct position, create a source at that position, with a specified intensity.
	for (int i = 0; i < z; i++)
	{
		for (int j = 0; j < y; j++)
		{
			for (int k = 0; k < x; k++)
			{
				// If the pixel intensity is greater than 50, then put it into sources.  This helps weed out unneeded sources.
				if (im_data[i*j*k] > 50)
				{
					sources.push_back(CT_Source(xStart + k*xIncr, yStart + j*yIncr, zStart + i*zIncr, im_data[i*j*k]));
				}
			}
		}
	}

}

//getters and setters
double CT_Distribution::getTimeStep()
{
	return timeStep;
}

void CT_Distribution::setTimeStep(double stepTime)
{
	timeStep = stepTime;
}

void CT_Distribution::setDoseRadiation(double dose)
{
	doseRadiation = dose;
}

double CT_Distribution::getDoseRadiation() { return doseRadiation; }