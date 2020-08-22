#include <motionDiffusivity.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(motionDiffusivity, 0);
	defineRunTimeSelectionTable(motionDiffusivity, Istream);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::motionDiffusivity::motionDiffusivity(const fvMesh& mesh)
	:
	mesh_(mesh)
{}


// * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::motionDiffusivity> tnbLib::motionDiffusivity::New
(
	const fvMesh& mesh,
	Istream& mdData
)
{
	const word motionType(mdData);

	Info << "Selecting motion diffusion: " << motionType << endl;

	IstreamConstructorTable::iterator cstrIter =
		IstreamConstructorTablePtr_->find(motionType);

	if (cstrIter == IstreamConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown diffusion type "
			<< motionType << nl << nl
			<< "Valid diffusion types are :" << endl
			<< IstreamConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<motionDiffusivity>(cstrIter()(mesh, mdData));
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::motionDiffusivity::~motionDiffusivity()
{}


// ************************************************************************* //