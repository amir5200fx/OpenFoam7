#include <Ar.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(Ar, 0);
	addToRunTimeSelectionTable(liquidProperties, Ar, );
	addToRunTimeSelectionTable(liquidProperties, Ar, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::Ar::Ar()
	:
	liquidProperties
	(
		39.948,
		150.86,
		4.8981e+6,
		0.07459,
		0.291,
		83.78,
		6.88e+4,
		87.28,
		0.0,
		0.0,
		1.4138e+4
	),
	rho_(151.922244, 0.286, 150.86, 0.2984),
	pv_(39.233, -1051.7, -3.5895, 5.0444e-05, 2),
	hl_(150.86, 218509.061780314, 0.352, 0.0, 0.0, 0.0),
	Cp_(4562.43116050866, -70.7770101131471, 0.367477721037349, 0.0, 0.0, 0.0),
	h_
	(
		-1460974.49982473,
		4562.43116050866,
		-35.3885050565735,
		0.122492573679116,
		0.0,
		0.0
	),
	Cpg_(520.326424351657, 0.0, 0.0, 0.0, 0.0, 0.0),
	B_
	(
		0.000952488234705117,
		-0.379993992189847,
		-2022.62941824372,
		4633523580654.85,
		-302893761890458.0
	),
	mu_(-8.868, 204.3, -0.3831, -1.3e-22, 10.0),
	mug_(8.386e-07, 0.6175, 75.377, -432.5),
	kappa_(0.1819, -0.0003176, -4.11e-06, 0.0, 0.0, 0.0),
	kappag_(0.0001236, 0.8262, -132.8, 16000),
	sigma_(150.86, 0.03823, 1.2927, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 39.948, 28) // note: Same as nHeptane
{}


tnbLib::Ar::Ar
(
	const liquidProperties& l,
	const NSRDSfunc5& density,
	const NSRDSfunc1& vapourPressure,
	const NSRDSfunc6& heatOfVapourisation,
	const NSRDSfunc0& heatCapacity,
	const NSRDSfunc0& enthalpy,
	const NSRDSfunc0& idealGasHeatCapacity,
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


tnbLib::Ar::Ar(const dictionary& dict)
	:
	Ar()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::Ar::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const Ar& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //