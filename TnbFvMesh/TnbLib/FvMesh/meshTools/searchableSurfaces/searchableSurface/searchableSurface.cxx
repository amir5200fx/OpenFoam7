#include <searchableSurface.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(searchableSurface, 0);
	defineRunTimeSelectionTable(searchableSurface, dict);
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::searchableSurface> tnbLib::searchableSurface::New
(
	const word& searchableSurfaceType,
	const IOobject& io,
	const dictionary& dict
)
{
	dictConstructorTable::iterator cstrIter =
		dictConstructorTablePtr_->find(searchableSurfaceType);

	if (cstrIter == dictConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown searchableSurface type " << searchableSurfaceType
			<< endl << endl
			<< "Valid searchableSurface types : " << endl
			<< dictConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<searchableSurface>(cstrIter()(io, dict));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::searchableSurface::searchableSurface(const IOobject& io)
	:
	regIOobject(io)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::searchableSurface::~searchableSurface()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::searchableSurface::findNearest
(
	const pointField& sample,
	const scalarField& nearestDistSqr,
	List<pointIndexHit>& info,
	vectorField& normal,
	labelList& region
) const
{
	findNearest(sample, nearestDistSqr, info);
	getNormal(info, normal);
	getRegion(info, region);
}


// ************************************************************************* //