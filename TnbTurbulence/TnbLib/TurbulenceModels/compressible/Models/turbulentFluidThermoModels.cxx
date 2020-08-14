#include <turbulentFluidThermoModels.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

makeBaseTurbulenceModel
(
	geometricOneField,
	volScalarField,
	compressibleTurbulenceModel,
	CompressibleTurbulenceModel,
	ThermalDiffusivity,
	fluidThermo
);


// -------------------------------------------------------------------------- //
// Laminar models
// -------------------------------------------------------------------------- //

#include <Stokes.hxx>
makeLaminarModel(Stokes);

#include <generalizedNewtonian.hxx>
makeLaminarModel(generalizedNewtonian);

#include <Maxwell.hxx>
makeLaminarModel(Maxwell);

#include <Giesekus.hxx>
makeLaminarModel(Giesekus);


// -------------------------------------------------------------------------- //
// RAS models
// -------------------------------------------------------------------------- //

#include <SpalartAllmaras.hxx>
makeRASModel(SpalartAllmaras);

#include <kEpsilon.hxx>
makeRASModel(kEpsilon);

#include <RNGkEpsilon.hxx>
makeRASModel(RNGkEpsilon);

#include <realizableKE.hxx>
makeRASModel(realizableKE);

#include <buoyantKEpsilon.hxx>
makeRASModel(buoyantKEpsilon);

#include <LaunderSharmaKE.hxx>
makeRASModel(LaunderSharmaKE);

#include <kOmega.hxx>
makeRASModel(kOmega);

#include <kOmegaSST.hxx>
makeRASModel(kOmegaSST);

#include <kOmegaSSTSAS.hxx>
makeRASModel(kOmegaSSTSAS);

#include <kOmegaSSTLM.hxx>
makeRASModel(kOmegaSSTLM);

#include <v2f.hxx>
makeRASModel(v2f);

#include <LRR.hxx>
makeRASModel(LRR);

#include <SSG.hxx>
makeRASModel(SSG);


// -------------------------------------------------------------------------- //
// LES models
// -------------------------------------------------------------------------- //

#include <Smagorinsky.hxx>
makeLESModel(Smagorinsky);

#include <WALE.hxx>
makeLESModel(WALE);

#include <kEqn.hxx>
makeLESModel(kEqn);

#include <dynamicKEqn.hxx>
makeLESModel(dynamicKEqn);

#include <dynamicLagrangian.hxx>
makeLESModel(dynamicLagrangian);

#include <kOmegaSSTDES.hxx>
makeLESModel(kOmegaSSTDES);

#include <SpalartAllmarasDES.hxx>
makeLESModel(SpalartAllmarasDES);

#include <SpalartAllmarasDDES.hxx>
makeLESModel(SpalartAllmarasDDES);

#include <SpalartAllmarasIDDES.hxx>
makeLESModel(SpalartAllmarasIDDES);

#include <DeardorffDiffStress.hxx>
makeLESModel(DeardorffDiffStress);


// ************************************************************************* //