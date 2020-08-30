#include <basicKinematicCloud.hxx>

#include <makeParcelCloudFunctionObjects.hxx>

// Kinematic
#include <makeParcelForces.hxx>
#include <makeParcelDispersionModels.hxx>
#include <makeParcelInjectionModels.hxx>
#include <makeParcelPatchInteractionModels.hxx>
#include <makeParcelStochasticCollisionModels.hxx>
#include <makeParcelSurfaceFilmModels.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeParcelCloudFunctionObjects(basicKinematicCloud);

// Kinematic sub-models
makeParcelForces(basicKinematicCloud);
makeParcelDispersionModels(basicKinematicCloud);
makeParcelInjectionModels(basicKinematicCloud);
makeParcelPatchInteractionModels(basicKinematicCloud);
makeParcelStochasticCollisionModels(basicKinematicCloud);
makeParcelSurfaceFilmModels(basicKinematicCloud);


// ************************************************************************* //