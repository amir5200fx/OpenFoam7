#include <C3H6O.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C3H6O, 0);
	addToRunTimeSelectionTable(liquidProperties, C3H6O, );
	addToRunTimeSelectionTable(liquidProperties, C3H6O, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C3H6O::C3H6O()
	:
	liquidProperties
	(
		58.08,
		508.20,
		4.7015e+6,
		0.209,
		0.233,
		178.45,
		2.5938,
		329.44,
		9.6066e-30,
		0.3064,
		1.9774e+4
	),
	rho_(71.426784, 0.2576, 508.2, 0.29903),
	pv_(70.72, -5685, -7.351, 6.3e-06, 2.0),
	hl_(508.20, 846590.909090909, 1.036, -1.294, 0.672, 0.0),
	Cp_
	(
		2334.71074380165,
		-3.04752066115702,
		0.00488464187327824,
		1.18629476584022e-05,
		0.0,
		0.0
	),
	h_
	(
		-4.905296049462618e06,
		2334.71074380165,
		-1.52376033057851,
		0.00162821395775941,
		2.96573691460055e-06,
		0.0
	),
	Cpg_(828.512396694215, 2830.57851239669, 1250.0, 1234.50413223141, -524.4),
	B_
	(
		0.00190599173553719,
		-1.70798898071625,
		-525826.446280992,
		1.70282369146006e+17,
		-2.83298898071625e+20
	),
	mu_(-14.918, 1023.4, 0.5961, 0.0, 0.0),
	mug_(3.1005e-08, 0.9762, 23.139, 0.0),
	kappa_(0.2502, -0.000298, 0.0, 0.0, 0.0, 0.0),
	kappag_(-26.8, 0.9098, -126500000, 0.0),
	sigma_(508.20, 0.0622, 1.124, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 58.08, 28) // note: Same as nHeptane
{}


tnbLib::C3H6O::C3H6O
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


tnbLib::C3H6O::C3H6O(const dictionary& dict)
	:
	C3H6O()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C3H6O::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C3H6O& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //