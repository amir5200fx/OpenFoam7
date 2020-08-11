#include <H2O.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(H2O, 0);
	addToRunTimeSelectionTable(liquidProperties, H2O, );
	addToRunTimeSelectionTable(liquidProperties, H2O, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::H2O::H2O()
	:
	liquidProperties
	(
		18.015,
		647.13,
		2.2055e+7,
		0.05595,
		0.229,
		273.16,
		6.113e+2,
		373.15,
		6.1709e-30,
		0.3449,
		4.7813e+4
	),
	rho_(98.343885, 0.30542, 647.13, 0.081),
	pv_(73.649, -7258.2, -7.3037, 4.1653e-06, 2),
	hl_(647.13, 2889425.47876769, 0.3199, -0.212, 0.25795, 0),
	Cp_
	(
		15341.1046350264,
		-116.019983347211,
		0.451013044684985,
		-0.000783569247849015,
		5.20127671384957e-07,
		0
	),
	h_
	(
		-17957283.7993676,
		15341.1046350264,
		-58.0099916736053,
		0.150337681561662,
		-0.000195892311962254,
		1.04025534276991e-07
	),
	Cpg_
	(
		1851.73466555648,
		1487.53816264224,
		2609.3,
		493.366638912018,
		1167.6
	),
	B_
	(
		-0.0012789342214821,
		1.4909797391063,
		-1563696.91923397,
		1.85445462114904e+19,
		-7.68082153760755e+21
	),
	mu_(-51.964, 3670.6, 5.7331, -5.3495e-29, 10),
	mug_(2.6986e-06, 0.498, 1257.7, -19570),
	kappa_(-0.4267, 0.0056903, -8.0065e-06, 1.815e-09, 0, 0),
	kappag_(6.977e-05, 1.1243, 844.9, -148850),
	sigma_(647.13, 0.18548, 2.717, -3.554, 2.047, 0),
	D_(15.0, 15.0, 18.015, 28)
{}


tnbLib::H2O::H2O
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


tnbLib::H2O::H2O(const dictionary& dict)
	:
	H2O()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::H2O::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const H2O& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //