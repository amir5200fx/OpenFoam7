#include <interRegionOption.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(interRegionOption, 0);
	}
}


// * * * * * * * * * * * *  Protected member functions * * * * * * * * * * * //

void tnbLib::fv::interRegionOption::setMapper()
{
	if (master_)
	{
		Info << indent << "- selecting inter region mapping" << endl;

		const fvMesh& nbrMesh =
			mesh_.time().lookupObject<fvMesh>(nbrRegionName_);

		if (mesh_.name() == nbrMesh.name())
		{
			FatalErrorInFunction
				<< "Inter-region model selected, but local and "
				<< "neighbour regions are the same: " << nl
				<< "    local region: " << mesh_.name() << nl
				<< "    secondary region: " << nbrMesh.name() << nl
				<< exit(FatalError);
		}

		if (mesh_.bounds().overlaps(nbrMesh.bounds()))
		{
			meshInterpPtr_.reset
			(
				new meshToMesh
				(
					mesh_,
					nbrMesh,
					meshToMesh::interpolationMethodNames_.read
					(
						coeffs_.lookup("interpolationMethod")
					),
					false // not interpolating patches
				)
			);
		}
		else
		{
			FatalErrorInFunction
				<< "regions " << mesh_.name() << " and "
				<< nbrMesh.name() << " do not intersect"
				<< exit(FatalError);
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::interRegionOption::interRegionOption
(
	const word& name,
	const word& modelType,
	const dictionary& dict,
	const fvMesh& mesh
)
	:
	option
	(
		name,
		modelType,
		dict,
		mesh
	),
	master_(coeffs_.lookupOrDefault<bool>("master", true)),
	nbrRegionName_(coeffs_.lookup("nbrRegionName")),
	meshInterpPtr_()
{
	if (active())
	{
		setMapper();
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::fv::interRegionOption::~interRegionOption()
{}


// ************************************************************************* //