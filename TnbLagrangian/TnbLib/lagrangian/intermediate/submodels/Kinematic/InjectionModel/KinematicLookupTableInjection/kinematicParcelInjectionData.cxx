#include <kinematicParcelInjectionData.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(kinematicParcelInjectionData, 0);
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::kinematicParcelInjectionData::kinematicParcelInjectionData()
	:
	x_(point::zero),
	U_(Zero),
	d_(0.0),
	rho_(0.0),
	mDot_(0.0)
{}


tnbLib::kinematicParcelInjectionData::kinematicParcelInjectionData
(
	const dictionary& dict
)
	:
	x_(dict.lookup("x")),
	U_(dict.lookup("U")),
	d_(readScalar(dict.lookup("d"))),
	rho_(readScalar(dict.lookup("rho"))),
	mDot_(readScalar(dict.lookup("mDot")))
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::kinematicParcelInjectionData::~kinematicParcelInjectionData()
{}


// ************************************************************************* //