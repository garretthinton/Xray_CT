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

#ifndef CT_Source_hpp
#define CT_Source_hpp

using namespace std;

/*
Summary:	This class provides a way for the source's behavior to be defined.  It provides a position in space and the
relative amount of radiation emitted.

Methods:
-CT_Source():								Default Constructor
-CT_Source(double, double, double, char):	Overloaded Constructor
-~CT_Source():								Destructor
-Getters for all members

Members:
char intensity:				intensity of source
double centerPosx:			the x, y, and z position of the source
double centerPosy:			same
double centerPosz:			same
*/
class CT_Source
{
public:

	/*
	CT_Source():	Default constructor for the CT_Source class.
	Parameters:			None
	Output:				None
	*/
	CT_Source();

	/*
	CT_Source(double, double, double, char):
	Overloaded constructor for the CT_Source class.
	Parameters:
	double centerPosx:			Position of source
	double centerPosy:			Position of source
	double centerPosz:			Position of source
	Output:				None
	*/
	CT_Source(
		double centerPosx,
		double centerPosy,
		double centerPosz,
		char intensity);

	/*
	~CT_Source():	Default constructor for the CT_Source class.
	Parameters:			None
	Output:				None
	*/
	~CT_Source();

	// Getters for all members
	double getCenterPosx();
	double getCenterPosy();
	double getCenterPosz();
	char getIntensity();

	//Setters??


private:

	// The x, y, and z position of the source
	double centerPosx;
	double centerPosy;
	double centerPosz;

	// Relative intensity of a source.  256 is the highest, 0 is the lowest.
	char intensity;
};

#endif// CT_Source_hpp 