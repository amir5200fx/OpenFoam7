#include <N2.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(N2, 0);
	addToRunTimeSelectionTable(liquidProperties, N2, );
	addToRunTimeSelectionTable(liquidProperties, N2, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::N2::N2()
	:
	liquidProperties
	(
		28.014,
		126.10,
		3.3944e+6,
		0.0901,
		0.292,
		63.15,
		1.2517e+4,
		77.35,
		0.0,
		0.0403,
		9.0819e+3
	),
	rho_(88.8716136, 0.28479, 126.1, 0.2925),
	pv_(59.826, -1097.6, -8.6689, 0.046346, 1.0),
	hl_(126.10, 336617.405582923, 1.201, -1.4811, 0.7085, 0.0),
	Cp_
	(
		-1192.26101235097,
		125.187406296852,
		-1.66702363104162,
		0.00759263225530092,
		0.0,
		0.0
	),
	h_
	(
		-5480656.55276541,
		-1192.26101235097,
		62.5937031484258,
		-0.555674543680541,
		0.00189815806382523,
		0.0
	),
	Cpg_(1038.94481330763, 307.52123938031, 1701.6, 3.69351038766331, 909.79),
	B_
	(
		0.00166702363104162,
		-0.533661740558292,
		-2182.12322410223,
		2873563218390.8,
		-165274505604341.0
	),
	mu_(-32.165, 496.9, 3.9069, -1.08e-21, 10.0),
	mug_(7.632e-07, 0.58823, 67.75, 0.0),
	kappa_(0.7259, -0.016728, 0.00016215, -5.7605e-07, 0.0, 0.0),
	kappag_(0.000351, 0.7652, 25.767, 0.0),
	sigma_(126.10, 0.02898, 1.2457, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 28.014, 28.0) // note: Same as nHeptane
{}


tnbLib::N2::N2
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


tnbLib::N2::N2(const dictionary& dict)
	:
	N2()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::N2::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const N2& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //