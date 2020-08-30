#include <standardPhaseChange.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <thermoSingleLayer.hxx>
#include <zeroField.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(standardPhaseChange, 0);

			addToRunTimeSelectionTable
			(
				phaseChangeModel,
				standardPhaseChange,
				dictionary
			);

			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			scalar standardPhaseChange::Sh
			(
				const scalar Re,
				const scalar Sc
			) const
			{
				if (Re < 5.0E+05)
				{
					return 0.664*sqrt(Re)*cbrt(Sc);
				}
				else
				{
					return 0.037*pow(Re, 0.8)*cbrt(Sc);
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			standardPhaseChange::standardPhaseChange
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				phaseChangeModel(typeName, film, dict),
				deltaMin_(readScalar(coeffDict_.lookup("deltaMin"))),
				L_(readScalar(coeffDict_.lookup("L"))),
				TbFactor_(coeffDict_.lookupOrDefault<scalar>("TbFactor", 1.1)),
				YInfZero_(coeffDict_.lookupOrDefault<Switch>("YInfZero", false))
			{}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			standardPhaseChange::~standardPhaseChange()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			template<class YInfType>
			void standardPhaseChange::correctModel
			(
				const scalar dt,
				scalarField& availableMass,
				scalarField& dMass,
				scalarField& dEnergy,
				YInfType YInf
			)
			{
				const thermoSingleLayer& film = filmType<thermoSingleLayer>();

				// Set local thermo properties
				const SLGThermo& thermo = film.thermo();
				const filmThermoModel& filmThermo = film.filmThermo();
				const label vapId = thermo.carrierId(filmThermo.name());

				// Retrieve fields from film model
				const scalarField& delta = film.delta();
				const scalarField& pInf = film.pPrimary();
				const scalarField& T = film.T();
				const scalarField& hs = film.hs();
				const scalarField& rho = film.rho();
				const scalarField& rhoInf = film.rhoPrimary();
				const scalarField& muInf = film.muPrimary();
				const scalarField& magSf = film.magSf();
				const vectorField dU(film.UPrimary() - film.Us());
				const scalarField limMass
				(
					max(scalar(0), availableMass - deltaMin_ * rho*magSf)
				);

				// Molecular weight of vapour [kg/kmol]
				const scalar Wvap = thermo.carrier().Wi(vapId);

				// Molecular weight of liquid [kg/kmol]
				const scalar Wliq = filmThermo.W();

				forAll(dMass, celli)
				{
					scalar dm = 0;

					if (delta[celli] > deltaMin_)
					{
						// Cell pressure [Pa]
						const scalar pc = pInf[celli];

						// Calculate the boiling temperature
						const scalar Tb = filmThermo.Tb(pc);

						// Local temperature - impose lower limit of 200 K for stability
						const scalar Tloc = min(TbFactor_*Tb, max(200.0, T[celli]));

						// Saturation pressure [Pa]
						const scalar pSat = filmThermo.pv(pc, Tloc);

						// Latent heat [J/kg]
						const scalar hVap = filmThermo.hl(pc, Tloc);

						// Calculate mass transfer
						if (pSat >= 0.95*pc)
						{
							// Boiling
							const scalar Cp = filmThermo.Cp(pc, Tloc);
							const scalar Tcorr = max(0.0, T[celli] - Tb);
							const scalar qCorr = limMass[celli] * Cp*(Tcorr);
							dm = qCorr / hVap;
						}
						else
						{
							// Primary region density [kg/m^3]
							const scalar rhoInfc = rhoInf[celli];

							// Primary region viscosity [Pa.s]
							const scalar muInfc = muInf[celli];

							// Reynolds number
							const scalar Re = rhoInfc * mag(dU[celli])*L_ / muInfc;

							// Vapour mass fraction at interface
							const scalar Ys = Wliq * pSat / (Wliq*pSat + Wvap * (pc - pSat));

							// Vapour diffusivity [m2/s]
							const scalar Dab = filmThermo.D(pc, Tloc);

							// Schmidt number
							const scalar Sc = muInfc / (rhoInfc*(Dab + rootVSmall));

							// Sherwood number
							const scalar Sh = this->Sh(Re, Sc);

							// Mass transfer coefficient [m/s]
							const scalar hm = Sh * Dab / (L_ + rootVSmall);

							// Add mass contribution to source
							dm = dt * magSf[celli] * rhoInfc*hm*(Ys - YInf[celli]) / (1.0 - Ys);
						}

						dMass[celli] += min(limMass[celli], max(dm, 0));

						// Heat is assumed to be removed by heat-transfer to the wall
						// so the energy remains unchanged by the phase-change.
						dEnergy[celli] += dm * hs[celli];
						// dEnergy[celli] += dm*(hs[celli] + hVap);
					}
				}
			}


			void standardPhaseChange::correctModel
			(
				const scalar dt,
				scalarField& availableMass,
				scalarField& dMass,
				scalarField& dEnergy
			)
			{
				if (YInfZero_)
				{
					correctModel(dt, availableMass, dMass, dEnergy, zeroField());
				}
				else
				{
					const thermoSingleLayer& film = filmType<thermoSingleLayer>();
					const label vapId = film.thermo().carrierId(film.filmThermo().name());
					const scalarField& YInf = film.YPrimary()[vapId];

					correctModel(dt, availableMass, dMass, dEnergy, YInf);
				}
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //