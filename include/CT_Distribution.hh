// CT_Distribution.hh
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

#ifndef CT_Distribution_hpp
#define CT_Distribution_hpp

#include "CT_Source.hh"
#include <vector>
#include <sstream>
#include "G4UImanager.hh"

using namespace std;

/*
Summary:  This class acts as a collection of sources to be analyzed.  The sources are stored in a vector.  Methods in the
class can run a macro that will run the simulations and plot them.  Other methods advance the time and adjust the sources
depending on the sources' properties.

Methods:
CT_Distribution():					Default constructor.
CT_Distribution(G4String, int, int, int):		Overloaded constructor
~CT_Distribution():					The Destructor for the class.
void SetVoxels():					Mainly for simple development purposes for easy GPS sources.
void ExecuteMacro():				Executes the simulation and plots the data.
void AddSource(CT_Source):			Adds a source to the vector, sources.
void AdvanceTime():					Advances time by the amount timeStep.  Also, it adjusts the sources depending on their properties.
void Organize_Sources(int, int, int):	Creates and places sources.
void Read_SPECT_File(string, int, int, int):	Reads in an image file and places the values into a character array.
double getTimeStep():				Getter for timeStep
void setTimeStep(double):			Setter for timeStep
void setDoseRadiation(double):		Setter for doseRadiation
double getDoseRadiation():			Getter for doseRadiation


Members:
vector<CT_Source> sources:			This vector holds the sources to be analyzed
double timeStep:					This is how much the AdvanceTime method steps forward in time.
double doseRadiation:				The radiation dose being given to the patient (mCi).
double xLength:						Length of rectangular prism in x-direction.
double yLength:						Length of rectangular prism in y-direction.
double zLength:						Length of rectangular prism in z-direction.
double xCenter:						Center of rectangular prism in x-direction.
double yCenter:						Center of rectangular prism in x-direction.
double zCenter:						Center of rectangular prism in x-direction.
double xIncr:						xLength divided by the amount of x-voxels.
double yIncr:						yLength divided by the amount of y-voxels.
double zIncr:						zLength divided by the amount of z-voxels.
char *im_data:						Character array to store intensity values for voxels.
*/
class CT_Distribution
{
public:
	/*
	CT_Distribution():	Default constructor for the CT_Distribution class.  Sets timeStep to .001.
	Parameters:			None
	Output:				None
	*/
	CT_Distribution();

	/*
	CT_Distribution(G4String filename, int x_dim, int y_dim, int z_dim):
	Overloaded constructor:  This takes in a SPECT image file and will adjust the class accordingly.
	This constructor makes it possible to duplicate the results of a real SPECT image onto the simulator.
	Parameters:
	G4String filename:  Filename and location of the file to be read
	int x_dim:			How many voxels are in the x-direction.
	int y_dim:			How many voxels are in the y-direction.
	int z_dim:			How many voxels are in the z-direction.
	Output:				None
	*/
	CT_Distribution(G4String filename, int x_dim, int y_dim, int z_dim);

	/*
	~CT_Distribution():	Destructor for the CT_Distribution class.
	Parameters:			None
	Output:				None
	*/
	~CT_Distribution();

	/*
	ExecuteMacro():		This method takes the data in each source, writes it to a macro file, and runs a simulation on it.
	Parameters:			None
	Output:				None
	*/
	void ExecuteMacro();

	/*
	AddSource(CT_Source):	This method takes a CT_Source and adds it to the vector, 'sources'.  As the CT_Distribution class does not
	start out with any sources, this method is imperative in order to run a simulation.
	Parameters:
	CT_Source source:	This is the source to be added.  It will have the data needed to run the simulation.
	Output:				None
	*/
	void AddSource(CT_Source source);

	/*
	SetVoxels():		This method takes a volume and turns it into a set of voxels.  This is mainly for development purposes to be done					with the default constructor.
	Parameters:			None
	Output:				None
	*/
	void SetVoxels();

	/*
	AdvanceTime():		This method is under construction. This method advances time forward by the amount timeStep.  This method also						adjusts the CT_Source sources in the 'sources' vector.
	the 'sources' vector.
	Parameters:			None
	Output:				None
	*/
	void AdvanceTime();

	/*
	Organize_Sources(int x_vox, int y_vox, int z_vox):		This method takes the amount of voxels in each direction, and makes sources from each voxel.  For example, a 256 x 256 x 128 image will have x_vox = 256, y_vox = 256, z_vox = 128. It will then use the			class data for how big each dimension is to find the length, width, and height, of each individual source.  It will assign each			source to a position and an intensity.
	Parameters:
	int x_vox: number of voxels in the x-direction
	int y_vox: number of voxels in the y-direction
	int z_vox: number of voxels in the z-direction
	Output:				None
	*/
	void Organize_Sources(int x_vox, int y_vox, int z_vox);

	/*
	setTimeStep():		timeStep setter.
	Parameters:
	double stepTime:  This is the amount that AdvanceTime() moves time forward.
	Output:				None
	*/
	void setTimeStep(double stepTime);

	/*
	setDoseRadiation(double dose):		Sets the radiation dose to a milliCurie amount.
	Parameters:
	double dose:  The total dose injected, in milliCuries.
	Output:				None
	*/
	void setDoseRadiation(double dose);

	/*
	getDoseRadiation():		Gets the radiation dose in a milliCurie amount.
	Parameters:	None
	Output:
	double dose:  The total dose injected, in milliCuries.
	*/
	double getDoseRadiation();

	/*
	getTimeStep():		timeStep getter.
	Parameters:			None
	Output:
	double timeStep:  This is the amount that AdvanceTime() moves time forward.
	*/
	double getTimeStep();

private:

	/*
	Read_SPECT_File(string, int, int, int):		This is a private method that reads in a SPECT file, and puts the data into im_data, the character array.
	Parameters:
	string filename:	The name of the .dat file that has the image data
	int x_vox:			The number of voxels in the x-direction
	int y_vox:			The number of voxels in the x-direction
	int z_vox:			The number of voxels in the x-direction
	Output:				None
	*/
	void Read_SPECT_File(string filename, int x_vox, int y_vox, int z_vox);

	// See top of page for detailed description of class members
	vector<CT_Source> sources;
	double timeStep;
	double doseRadiation;
	double xLength;
	double yLength;
	double zLength;
	double xCenter;
	double yCenter;
	double zCenter;
	double xIncr;
	double yIncr;
	double zIncr;
	char *im_data;
};

#endif// CT_Source_hpp 