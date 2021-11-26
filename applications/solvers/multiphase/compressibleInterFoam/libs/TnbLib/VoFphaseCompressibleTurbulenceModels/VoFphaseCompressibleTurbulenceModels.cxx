#define FoamRASModel_EXPORT_DEFINE
#define FoamlaminarModel_EXPORT_DEFINE
#define FoamLESModel_EXPORT_DEFINE

#define FoamRegisterDebugSwitch_EXPORT_DEFINE
#define FoamTurbulenceModel_EXPORT_DEFINE

#define FoamStokes_EXPORT_DEFINE
#define FoamMaxwell_EXPORT_DEFINE
#define FoamGiesekus_EXPORT_DEFINE
#define FoamkEpsilon_EXPORT_DEFINE
#define FoamkOmegaSST_EXPORT_DEFINE
#define FoamSmagorinsky_EXPORT_DEFINE
#define FoamkEqn_EXPORT_DEFINE

#include <compressibleInterFoamLibs_Module.hxx>
#include <PhaseCompressibleTurbulenceModel.hxx>

#include <fluidThermo.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <compressibleMakeTurbulenceModel.hxx>

#include <ThermalDiffusivity.hxx>
#include <EddyDiffusivity.hxx>

#include <laminarModelTemplate.hxx>
#include <RASModel.hxx>
#include <LESModel.hxx>


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeTurbulenceModelTypes
(
	volScalarField,
	volScalarField,
	compressibleTurbulenceModel,
	PhaseCompressibleTurbulenceModel,
	ThermalDiffusivity,
	fluidThermo
);

makeBaseTurbulenceModel
(
	volScalarField,
	volScalarField,
	compressibleTurbulenceModel,
	PhaseCompressibleTurbulenceModel,
	ThermalDiffusivity,
	fluidThermo
);

#define makeLaminarModel(Type)                                                 \
    makeTemplatedLaminarModel                                                  \
    (fluidThermoPhaseCompressibleTurbulenceModel, laminar, Type)

#define makeRASModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoPhaseCompressibleTurbulenceModel, RAS, Type)

#define makeLESModel(Type)                                                     \
    makeTemplatedTurbulenceModel                                               \
    (fluidThermoPhaseCompressibleTurbulenceModel, LES, Type)


#include <Stokes.hxx>
makeLaminarModel(Stokes);

#include <Maxwell.hxx>
makeLaminarModel(Maxwell);

#include <Giesekus.hxx>
makeLaminarModel(Giesekus);

#include <kEpsilon.hxx>
makeRASModel(kEpsilon);

#include <kOmegaSST.hxx>
makeRASModel(kOmegaSST);

#include <Smagorinsky.hxx>
makeLESModel(Smagorinsky);

#include <kEqn.hxx>
makeLESModel(kEqn);

// ************************************************************************* //