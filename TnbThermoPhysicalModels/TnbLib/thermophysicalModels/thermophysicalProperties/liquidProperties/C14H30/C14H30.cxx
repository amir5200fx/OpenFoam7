#include <C14H30.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C14H30, 0);
	addToRunTimeSelectionTable(liquidProperties, C14H30, );
	addToRunTimeSelectionTable(liquidProperties, C14H30, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C14H30::C14H30()
	:
	liquidProperties
	(
		198.392,
		692.40,
		1.6212e+6,
		0.8428,
		0.237,
		279.01,
		1.8849e-1,
		526.73,
		0.0,
		0.6617,
		1.6173e+4
	),
	rho_(60.92023144, 0.2582, 692.4, 0.26628),
	pv_(249.21, -16915, -35.195, 0.028451, 1.0),
	hl_(692.40, 455764.345336506, 0.428, 0.0, 0.0, 0.0),
	Cp_
	(
		2565.72845679261,
		-4.78114036856325,
		0.0120362716238558,
		0.0,
		0.0,
		0.0
	),
	h_
	(
		-2690601.01887934,
		2565.72845679261,
		-2.39057018428162,
		0.00401209054128527,
		0.0,
		0.0
	),
	Cpg_(1134.11831122223, 3629.17859591113, -1440.3, 2275.29335860317, -682),
	B_
	(
		0.00247837614419936,
		-2.62692044034034,
		-1427174.48284205,
		-1.68288035807895e+19,
		3.48854792531957e+21
	),
	mu_(-18.964, 2010.9, 1.0648, 0.0, 0.0),
	mug_(4.4565e-08, 0.8684, 228.16, -4347.2),
	kappa_(0.1957, -0.0001993, 0.0, 0.0, 0.0, 0.0),
	kappag_(-0.000628, 0.944, -5490, 0.0),
	sigma_(692.40, 0.056436, 1.3658, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 198.392, 28.0) // note: Same as nHeptane
{}


tnbLib::C14H30::C14H30
(
	const liquidProperties& l,
	const NSRDSfunc5& density,
	const NSRDSfunc1& vapourPressure,
	const NSRDSfunc6& heatOfVapourisation,
	const NSRDSfunc0& heatCapacity,
	const NSRDSfunc0& enthalpy,
	const NSRDSfunc7& idealGasHeatCapacity,
	const NSRDSfunc4& secondVirialCoeff,
	const NSRDSfunc1& dynamicViscosity,
	const NSRDSfunc2& vapourDynamicViscosity,
	const NSRDSfunc0& thermalConductivity,
	const NSRDSfunc2& vapourThermalConductivity,
	const NSRDSfunc6& surfaceTension,
	const APIdiffCoefFunc& vapourDiffussivity
)
	:
	liquidProperties(l),
	rho_(density),
	pv_(vapourPressure),
	hl_(heatOfVapourisation),
	Cp_(heatCapacity),
	h_(enthalpy),
	Cpg_(idealGasHeatCapacity),
	B_(secondVirialCoeff),
	mu_(dynamicViscosity),
	mug_(vapourDynamicViscosity),
	kappa_(thermalConductivity),
	kappag_(vapourThermalConductivity),
	sigma_(surfaceTension),
	D_(vapourDiffussivity)
{}


tnbLib::C14H30::C14H30(const dictionary& dict)
	:
	C14H30()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C14H30::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C14H30& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //