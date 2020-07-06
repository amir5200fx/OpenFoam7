#include <nonuniformTransformCyclicPointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(nonuniformTransformCyclicPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		nonuniformTransformCyclicPointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const vectorField& nonuniformTransformCyclicPointPatch::pointNormals() const
	{
		// Use underlying patch normals
		return refCast<const facePointPatch>
			(
				*this
				).facePointPatch::pointNormals();
	}


	void nonuniformTransformCyclicPointPatch::applyConstraint
	(
		const label pointi,
		pointConstraint& pc
	) const
	{
		pc.applyConstraint(pointNormals()[pointi]);
	}


	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

} // End namespace tnbLib

// ************************************************************************* //