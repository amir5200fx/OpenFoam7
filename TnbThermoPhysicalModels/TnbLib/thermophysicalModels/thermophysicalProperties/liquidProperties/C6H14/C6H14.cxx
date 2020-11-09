#include <C6H14.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C6H14, 0);
	addToRunTimeSelectionTable(liquidProperties, C6H14, );
	addToRunTimeSelectionTable(liquidProperties, C6H14, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C6H14::C6H14()
	:
	liquidProperties
	(
		86.177,
		507.60,
		3.025e+6,
		0.371,
		0.266,
		177.83,
		9.017e-1,
		341.88,
		0.0,
		0.3013,
		1.49e+4
	),
	rho_(61.03399848, 0.26411, 507.6, 0.27537),
	pv_(104.65, -6995.5, -12.702, 1.2381e-05, 2.0),
	hl_(507.60, 527286.863084118, 0.39002, 0.0, 0.0, 0.0),
	Cp_
	(
		1997.28465831951,
		-2.13258758137322,
		0.0102964828202421,
		0.0,
		0.0,
		0.0
	),
	h_
	(
		-2902186.5403246,
		1997.28465831951,
		-1.06629379068661,
		0.00343216094008069,
		0.0,
		0.0
	),
	Cpg_(1211.4601343746, 4088.0977523005, 1694.6, 2748.99335089409, 761.6),
	B_
	(
		0.0022859927822969,
		-2.32080485512376,
		-430509.300625457,
		1.93787205402834e+17,
		-7.17128700233241e+19
	),
	mu_(-20.715, 1207.5, 1.4993, 0.0, 0.0),
	mug_(1.7514e-07, 0.70737, 157.14, 0.0),
	kappa_(0.22492, -0.0003533, 0.0, 0.0, 0.0, 0.0),
	kappag_(-650.5, 0.8053, -1412100000, 0.0),
	sigma_(507.60, 0.055003, 1.2674, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 86.177, 28) // note: Same as nHeptane
{}


tnbLib::C6H14::C6H14
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


tnbLib::C6H14::C6H14(const dictionary& dict)
	:
	C6H14()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C6H14::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C6H14& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //