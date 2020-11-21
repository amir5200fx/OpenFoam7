#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#include <LeastSquaresGradTemplate.hxx>

#include <centredCPCCellToCellStencilObject.hxx>
#include <centredCECCellToCellStencilObject.hxx>
#include <LeastSquaresVectorsTemplate.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// makeLeastSquaresGradScheme
// (
//     faceCellsLeastSquares,
//     centredCFCCellToCellStencilObject
// )

makeLeastSquaresGradScheme
(
	pointCellsLeastSquares,
	centredCPCCellToCellStencilObject
)

makeLeastSquaresGradScheme
(
	edgeCellsLeastSquares,
	centredCECCellToCellStencilObject
)

// ************************************************************************* //