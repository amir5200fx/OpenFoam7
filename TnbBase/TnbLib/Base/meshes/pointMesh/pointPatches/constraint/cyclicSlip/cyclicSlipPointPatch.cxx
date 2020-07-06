#include <cyclicSlipPointPatch.hxx>

#include <pointConstraint.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{

	// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	defineTypeNameAndDebug(cyclicSlipPointPatch, 0);

	addToRunTimeSelectionTable
	(
		facePointPatch,
		cyclicSlipPointPatch,
		polyPatch
	);


	// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

	const vectorField& cyclicSlipPointPatch::pointNormals() const
	{
		// Use underlying patch normals
		return refCast<const facePointPatch>
			(
				*this
				).facePointPatch::pointNormals();
	}


	void cyclicSlipPointPatch::applyConstraint
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