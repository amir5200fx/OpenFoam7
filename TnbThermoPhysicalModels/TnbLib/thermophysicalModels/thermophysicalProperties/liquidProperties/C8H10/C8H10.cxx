#include <C8H10.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C8H10, 0);
	addToRunTimeSelectionTable(liquidProperties, C8H10, );
	addToRunTimeSelectionTable(liquidProperties, C8H10, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C8H10::C8H10()
	:
	liquidProperties
	(
		106.167,
		617.17,
		3.6094e+6,
		0.37381,
		0.263,
		178.15,
		4.038e-3,
		409.35,
		1.9680e-30,
		0.3036,
		1.8043e+4
	),
	rho_(76.3765398, 0.26438, 617.17, 0.2921),
	pv_(88.246, -7691.1, -9.797, 5.931e-06, 2.0),
	hl_(617.17, 516167.924119547, 0.3882, 0.0, 0.0, 0.0),
	Cp_
	(
		818.521762883005,
		6.66873887366131,
		-0.0248005500767658,
		4.23860521631015e-05,
		0.0,
		0.0
	),
	h_
	(
		-524002.612929508,
		818.521762883005,
		3.33436943683065,
		-0.00826685002558862,
		1.05965130407754e-05,
		0.0
	),
	Cpg_(738.835984816374, 3201.5598067196, 1559, 2285.07916772632, -702.0),
	B_
	(
		0.00165776559571242,
		-2.77958310962917,
		-388067.855359952,
		-5.86905535618412e+18,
		1.58052878954854e+21
	),
	mu_(-10.452, 1048.4, -0.0715, 0.0, 0.0),
	mug_(1.2e-06, 0.4518, 439.0, 0.0),
	kappa_(0.20149, -0.00023988, 0.0, 0.0, 0.0, 0.0),
	kappag_(1.708e-05, 1.319, 565.6, 0.0),
	sigma_(617.17, 0.066, 1.268, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 106.167, 28.0) // note: Same as nHeptane
{}


tnbLib::C8H10::C8H10
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


tnbLib::C8H10::C8H10(const dictionary& dict)
	:
	C8H10()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C8H10::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C8H10& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //