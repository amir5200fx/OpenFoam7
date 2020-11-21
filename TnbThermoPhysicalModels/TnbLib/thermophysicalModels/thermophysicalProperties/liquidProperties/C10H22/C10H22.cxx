#include <C10H22.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C10H22, 0);
	addToRunTimeSelectionTable(liquidProperties, C10H22, );
	addToRunTimeSelectionTable(liquidProperties, C10H22, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C10H22::C10H22()
	:
	liquidProperties
	(
		142.285,
		617.70,
		2.11e+6,
		0.6,
		0.247,
		243.51,
		1.393,
		447.30,
		0.0,
		0.4923,
		1.57e+4
	),
	rho_(60.94208835, 0.25745, 617.7, 0.28912),
	pv_(112.73, -9749.6, -13.245, 7.1266e-06, 2.0),
	hl_(617.70, 464743.296904101, 0.39797, 0.0, 0.0, 0.0),
	Cp_
	(
		1958.18252099659,
		-1.39094071757388,
		0.00754612221948905,
		0.0,
		0.0,
		0.0
	),
	h_
	(
		-2699436.15229142,
		1958.18252099659,
		-0.695470358786942,
		0.00251537407316302,
		0.0,
		0.0
	),
	Cpg_(1175.10630073444, 3762.16748076045, 1614.1, 2658.04547211582, 742),
	B_
	(
		0.00337351091119935,
		-4.13606494008504,
		-534560.916470464,
		-1.13364022911762e+19,
		2.80704220402713e+21
	),
	mu_(-16.468, 1533.5, 0.7511, 0.0, 0.0),
	mug_(2.64e-08, 0.9487, 71.0, 0.0),
	kappa_(0.2063, -0.000254, 0.0, 0.0, 0.0, 0.0),
	kappag_(-668.4, 0.9323, -4071000000.0, 0.0),
	sigma_(617.70, 0.055435, 1.3095, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 142.285, 28.0) // note: Same as nHeptane
{}


tnbLib::C10H22::C10H22
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


tnbLib::C10H22::C10H22(const dictionary& dict)
	:
	C10H22()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C10H22::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C10H22& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //