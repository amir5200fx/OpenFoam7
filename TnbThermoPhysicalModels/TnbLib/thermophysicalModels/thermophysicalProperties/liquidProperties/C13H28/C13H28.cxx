#include <C13H28.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(C13H28, 0);
	addToRunTimeSelectionTable(liquidProperties, C13H28, );
	addToRunTimeSelectionTable(liquidProperties, C13H28, dictionary);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::C13H28::C13H28()
	:
	liquidProperties
	(
		184.365,
		675.80,
		1.7225e+6,
		0.77,
		0.236,
		267.76,
		3.801e-1,
		508.62,
		0.0,
		0.6186,
		1.5901e+4
	),
	rho_(59.513022, 0.2504, 675.8, 0.312),
	pv_(118.27, -11432, -13.769, 5.9641e-06, 2.0),
	hl_(675.80, 444227.48352453, 0.4162, 0.0, 0.0, 0.0),
	Cp_
	(
		4275.05220622135,
		-16.6539202126217,
		0.0325755973205326,
		0.0,
		0.0,
		0.0
	),
	h_
	(
		-2860442.0545124,
		4275.05220622135,
		-8.32696010631085,
		0.0108585324401775,
		0.0,
		0.0
	),
	Cpg_(1136.87522035093, 3641.14663846175, -1443, 2277.00485450058, -683.0),
	B_
	(
		0.00246321156401703,
		-2.66601578390692,
		-1249532.17801643,
		-1.0460770753668e+19,
		1.90117430097904e+21
	),
	mu_(-23.341, 2121.9, 1.7208, 0.0, 0.0),
	mug_(3.5585e-08, 0.8987, 165.3, 0.0),
	kappa_(0.1981, -0.0002046, 0.0, 0.0, 0.0, 0.0),
	kappag_(5.3701e-06, 1.4751, 599.09, 0.0),
	sigma_(675.80, 0.05561, 1.3361, 0.0, 0.0, 0.0),
	D_(147.18, 20.1, 184.365, 28.0) // note: Same as nHeptane
{}


tnbLib::C13H28::C13H28
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


tnbLib::C13H28::C13H28(const dictionary& dict)
	:
	C13H28()
{
	readIfPresent(*this, dict);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::C13H28::writeData(Ostream& os) const
{
	liquidProperties::writeData(*this, os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const C13H28& l)
{
	l.writeData(os);
	return os;
}


// ************************************************************************* //