#include <C6H6.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C6H6, 0);
	addToRunTimeSelectionTable(liquidProperties, C6H6, );
	addToRunTimeSelectionTable(liquidProperties, C6H6, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C6H6::C6H6()
	:
	liquidProperties
	(
		78.114,
		562.16,
		4.898e+6,
		0.25894,
		0.271,
		278.68,
		4.7961e+3,
		353.24,
		0.0,
		0.2108,
		1.8706e+4
	),
	rho_(80.5511568, 0.2667, 562.16, 0.2818),
	pv_(78.05, -6275.5, -8.4443, 6.26e-06, 2),
	hl_(562.16, 649435.440510024, 0.7616, -0.5052, 0.1564, 0),
	Cp_
	(
		1386.69124612745,
		-0.416058581048212,
		0.00542796425736744,
		0.0,
		0.0,
		0.0
	),
	h_
	(
		186141.395065592,
		1386.69124612745,
		-0.208029290524106,
		0.00180932141912248,
		0.0,
		0.0
	),
	Cpg_(568.656066774202, 2970.65826868423, 1494.6, 2203.57426325627, -678.15),
	B_
	(
		0.00184089919860716,
		-2.30176408838364,
		-309176.332027549,
		-5.12072099751645e+15,
		-2.90216862534245e+19
	),
	mu_(6.764, 336.4, -2.687, 0.0, 0.0),
	mug_(3.134e-08, 0.9676, 7.9, 0.0),
	kappa_(0.2407, -0.0003202, 0.0, 0.0, 0.0, 0.0),
	kappag_(1.652e-05, 1.3117, 491, 0.0),
	sigma_(562.16, 0.07195, 1.2389, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 78.114, 28) // note: Same as nHeptane
{}


tnbLib::C6H6::C6H6
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


tnbLib::C6H6::C6H6(const dictionary& dict)
	:
	C6H6()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C6H6::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

FoamThermophysicalModels_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C6H6& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //