#include <mappedVariableThicknessWallFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <regionModel1D.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mappedVariableThicknessWallFvPatch, 0);
	addToRunTimeSelectionTable
	(
		fvPatch,
		mappedVariableThicknessWallFvPatch,
		polyPatch
	);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::mappedVariableThicknessWallFvPatch::
makeDeltaCoeffs(scalarField& dc) const
{
	const mappedVariableThicknessWallPolyPatch& pp =
		refCast<const mappedVariableThicknessWallPolyPatch>(patch());

	typedef regionModels::regionModel1D modelType;

	const modelType& region1D =
		patch().boundaryMesh().mesh().time().lookupObject<modelType>
		(
			"thermalBaffleProperties"
			);

	dc = 2.0 / (pp.thickness() / region1D.nLayers());
}


// ************************************************************************* //