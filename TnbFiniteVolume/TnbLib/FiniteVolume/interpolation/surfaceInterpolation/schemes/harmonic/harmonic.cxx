#include <harmonic.hxx>

#include <fvMesh.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	defineTypeNameAndDebug(harmonic, 0);

	surfaceInterpolationScheme<scalar>::addMeshFluxConstructorToTable<harmonic>
		addharmonicScalarMeshFluxConstructorToTable_;

	surfaceInterpolationScheme<scalar>::addMeshConstructorToTable<harmonic>
		addharmonicScalarMeshConstructorToTable_;

}

// ************************************************************************* //