#include <reactionRateFlameArea.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(reactionRateFlameArea, 0);
	defineRunTimeSelectionTable(reactionRateFlameArea, dictionary);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::reactionRateFlameArea::reactionRateFlameArea
(
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh,
	const combustionModel& combModel
)
	:
	coeffDict_(dict.optionalSubDict(modelType + "Coeffs")),
	mesh_(mesh),
	combModel_(combModel),
	fuel_(dict.lookup("fuel")),
	omega_
	(
		IOobject
		(
			"FSDomega",
			mesh_.time().timeName(),
			mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		mesh_
	)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::reactionRateFlameArea::~reactionRateFlameArea()
{}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

bool tnbLib::reactionRateFlameArea::read(const dictionary& dict)
{
	dict.lookup("fuel") >> fuel_;

	return true;
}


// ************************************************************************* //