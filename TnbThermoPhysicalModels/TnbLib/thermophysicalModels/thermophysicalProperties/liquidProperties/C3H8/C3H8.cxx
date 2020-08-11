#include <C3H8.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C3H8, 0);
	addToRunTimeSelectionTable(liquidProperties, C3H8, );
	addToRunTimeSelectionTable(liquidProperties, C3H8, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C3H8::C3H8()
	:
	liquidProperties
	(
		44.096,
		369.83,
		4.248e+6,
		0.2, 0.276,
		85.47,
		1.685e-4,
		231.11,
		0.0,
		0.1523,
		1.31e+4
	),
	rho_(60.6628672, 0.27453, 369.83, 0.29359),
	pv_(59.078, -3492.6, -6.0669, 1.0919e-05, 2.0),
	hl_(369.83, 662395.682148041, 0.78237, -0.77319, 0.39246, 0.0),
	Cp_
	(
		369.83,
		9.48470319647089,
		2576.87772133527,
		95.3560311677331,
		-131.535634282099
	),
	h_(0.0, 0.0, 0.0, 0.0, 0.0, 0.0),
	Cpg_(1177.43105950653, 4364.34143686502, 1626.5, 2648.76632801161, 723.6),
	B_
	(
		0.00255578737300435,
		-2.24963715529753,
		-102276.850507983,
		7.00743831640058e+15,
		-1.59878447024673e+18
	),
	mu_(-6.9281, 420.76, -0.63276, -1.713e-26, 10.0),
	mug_(2.4993e-07, 0.68612, 179.34, -8254.6),
	kappa_(0.26755, -0.00066457, 2.774e-07, 0.0, 0.0, 0.0),
	kappag_(-1.12, 0.10972, -9834.6, -7535800),
	sigma_(369.83, 0.05092, 1.2197, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 44.096, 28) // note: Same as nHeptane
{}


tnbLib::C3H8::C3H8
(
	const liquidProperties& l,
	const NSRDSfunc5& density,
	const NSRDSfunc1& vapourPressure,
	const NSRDSfunc6& heatOfVapourisation,
	const NSRDSfunc14& heatCapacity,
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


tnbLib::C3H8::C3H8(const dictionary& dict)
	:
	C3H8()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C3H8::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C3H8& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //