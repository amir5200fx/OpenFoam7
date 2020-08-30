#include <basicKinematicCollidingParcel.hxx>

#include <makeParcelCloudFunctionObjects.hxx>

// Kinematic
#include <makeParcelForces.hxx>
#include <makeParcelDispersionModels.hxx>
#include <makeParcelInjectionModels.hxx>
#include <makeParcelCollisionModels.hxx>
#include <makeParcelPatchInteractionModels.hxx>
#include <makeParcelStochasticCollisionModels.hxx>
#include <makeParcelSurfaceFilmModels.hxx>

#include <basicKinematicCollidingCloud.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeParcelCloudFunctionObjects(basicKinematicCollidingCloud);

// Kinematic sub-models
makeParcelForces(basicKinematicCollidingCloud);
makeParcelDispersionModels(basicKinematicCollidingCloud);
makeParcelInjectionModels(basicKinematicCollidingCloud);
makeParcelCollisionModels(basicKinematicCollidingCloud);
makeParcelPatchInteractionModels(basicKinematicCollidingCloud);
makeParcelStochasticCollisionModels(basicKinematicCollidingCloud);
makeParcelSurfaceFilmModels(basicKinematicCollidingCloud);


// ************************************************************************* //