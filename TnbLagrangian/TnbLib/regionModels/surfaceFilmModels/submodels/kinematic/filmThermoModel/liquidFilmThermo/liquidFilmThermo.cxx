#include <liquidFilmThermo.hxx>

#include <demandDrivenData.hxx>
#include <thermoSingleLayer.hxx>
#include <SLGThermo.hxx>
#include <extrapolatedCalculatedFvPatchFields.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(liquidFilmThermo, 0);

			addToRunTimeSelectionTable
			(
				filmThermoModel,
				liquidFilmThermo,
				dictionary
			);


			// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

			const thermoSingleLayer& liquidFilmThermo::thermoFilm() const
			{
				if (!isA<thermoSingleLayer>(filmModel_))
				{
					FatalErrorInFunction
						<< "Thermo model requires a " << thermoSingleLayer::typeName
						<< " film to supply the pressure and temperature, but "
						<< filmModel_.type() << " film model selected.  "
						<< "Use the 'useReferenceValues' flag to employ reference "
						<< "pressure and temperature" << exit(FatalError);
				}

				return refCast<const thermoSingleLayer>(filmModel_);
			}


			void liquidFilmThermo::initLiquid(const dictionary& dict)
			{
				if (liquidPtr_ != nullptr)
				{
					return;
				}

				dict.lookup("liquid") >> name_;

				if (filmModel_.primaryMesh().foundObject<SLGThermo>("SLGThermo"))
				{
					// retrieve from film thermo
					ownLiquid_ = false;

					const SLGThermo& thermo =
						filmModel_.primaryMesh().lookupObject<SLGThermo>("SLGThermo");
					label id = thermo.liquidId(name_);
					liquidPtr_ = &thermo.liquids().properties()[id];
				}
				else
				{
					// new liquid create
					ownLiquid_ = true;

					liquidPtr_ =
						liquidProperties::New(dict.optionalSubDict(name_ + "Coeffs")).ptr();
				}
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			liquidFilmThermo::liquidFilmThermo
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				filmThermoModel(typeName, film, dict),
				name_("unknown_liquid"),
				liquidPtr_(nullptr),
				ownLiquid_(false),
				useReferenceValues_(readBool(coeffDict_.lookup("useReferenceValues"))),
				pRef_(0.0),
				TRef_(0.0)
			{
				initLiquid(coeffDict_);

				if (useReferenceValues_)
				{
					coeffDict_.lookup("pRef") >> pRef_;
					coeffDict_.lookup("TRef") >> TRef_;
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			liquidFilmThermo::~liquidFilmThermo()
			{
				if (ownLiquid_)
				{
					deleteDemandDrivenData(liquidPtr_);
				}
			}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			const word& liquidFilmThermo::name() const
			{
				return name_;
			}


			scalar liquidFilmThermo::rho
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->rho(p, T);
			}


			scalar liquidFilmThermo::mu
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->mu(p, T);
			}


			scalar liquidFilmThermo::sigma
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->sigma(p, T);
			}


			scalar liquidFilmThermo::Cp
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->Cp(p, T);
			}


			scalar liquidFilmThermo::kappa
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->kappa(p, T);
			}


			scalar liquidFilmThermo::D
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->D(p, T);
			}


			scalar liquidFilmThermo::hl
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->hl(p, T);
			}


			scalar liquidFilmThermo::pv
			(
				const scalar p,
				const scalar T
			) const
			{
				return liquidPtr_->pv(p, T);
			}


			scalar liquidFilmThermo::W() const
			{
				return liquidPtr_->W();
			}


			scalar liquidFilmThermo::Tb(const scalar p) const
			{
				return liquidPtr_->pvInvert(p);
			}


			tmp<volScalarField> liquidFilmThermo::rho() const
			{
				tmp<volScalarField> trho
				(
					volScalarField::New
					(
						type() + ":rho",
						film().regionMesh(),
						dimensionedScalar(dimDensity, 0),
						extrapolatedCalculatedFvPatchScalarField::typeName
					)
				);

				scalarField& rho = trho.ref().primitiveFieldRef();

				if (useReferenceValues_)
				{
					forAll(rho, celli)
					{
						rho[celli] = this->rho(pRef_, TRef_);
					}
				}
				else
				{
					const thermoSingleLayer& film = thermoFilm();

					const volScalarField& T = film.T();
					const volScalarField& p = film.pPrimary();

					forAll(rho, celli)
					{
						rho[celli] = this->rho(p[celli], T[celli]);
					}
				}

				trho.ref().correctBoundaryConditions();

				return trho;
			}


			tmp<volScalarField> liquidFilmThermo::mu() const
			{
				tmp<volScalarField> tmu
				(
					volScalarField::New
					(
						type() + ":mu",
						film().regionMesh(),
						dimensionedScalar(dimPressure*dimTime, 0),
						extrapolatedCalculatedFvPatchScalarField::typeName
					)
				);

				scalarField& mu = tmu.ref().primitiveFieldRef();

				if (useReferenceValues_)
				{
					forAll(mu, celli)
					{
						mu[celli] = this->mu(pRef_, TRef_);
					}
				}
				else
				{
					const thermoSingleLayer& film = thermoFilm();

					const volScalarField& T = film.T();
					const volScalarField& p = film.pPrimary();

					forAll(mu, celli)
					{
						mu[celli] = this->mu(p[celli], T[celli]);
					}
				}

				tmu.ref().correctBoundaryConditions();

				return tmu;
			}


			tmp<volScalarField> liquidFilmThermo::sigma() const
			{
				tmp<volScalarField> tsigma
				(
					volScalarField::New
					(
						type() + ":sigma",
						film().regionMesh(),
						dimensionedScalar(dimMass / sqr(dimTime), 0),
						extrapolatedCalculatedFvPatchScalarField::typeName
					)
				);

				scalarField& sigma = tsigma.ref().primitiveFieldRef();

				if (useReferenceValues_)
				{
					forAll(sigma, celli)
					{
						sigma[celli] = this->sigma(pRef_, TRef_);
					}
				}
				else
				{
					const thermoSingleLayer& film = thermoFilm();

					const volScalarField& T = film.T();
					const volScalarField& p = film.pPrimary();

					forAll(sigma, celli)
					{
						sigma[celli] = this->sigma(p[celli], T[celli]);
					}
				}

				tsigma.ref().correctBoundaryConditions();

				return tsigma;
			}


			tmp<volScalarField> liquidFilmThermo::Cp() const
			{
				tmp<volScalarField> tCp
				(
					volScalarField::New
					(
						type() + ":Cp",
						film().regionMesh(),
						dimensionedScalar(dimEnergy / dimMass / dimTemperature, 0),
						extrapolatedCalculatedFvPatchScalarField::typeName
					)
				);

				scalarField& Cp = tCp.ref().primitiveFieldRef();

				if (useReferenceValues_)
				{
					forAll(Cp, celli)
					{
						Cp[celli] = this->Cp(pRef_, TRef_);
					}
				}
				else
				{
					const thermoSingleLayer& film = thermoFilm();

					const volScalarField& T = film.T();
					const volScalarField& p = film.pPrimary();

					forAll(Cp, celli)
					{
						Cp[celli] = this->Cp(p[celli], T[celli]);
					}
				}

				tCp.ref().correctBoundaryConditions();

				return tCp;
			}


			tmp<volScalarField> liquidFilmThermo::kappa() const
			{
				tmp<volScalarField> tkappa
				(
					volScalarField::New
					(
						type() + ":kappa",
						film().regionMesh(),
						dimensionedScalar(dimPower / dimLength / dimTemperature, 0),
						extrapolatedCalculatedFvPatchScalarField::typeName
					)
				);

				scalarField& kappa = tkappa.ref().primitiveFieldRef();

				if (useReferenceValues_)
				{
					forAll(kappa, celli)
					{
						kappa[celli] = this->kappa(pRef_, TRef_);
					}
				}
				else
				{
					const thermoSingleLayer& film = thermoFilm();

					const volScalarField& T = film.T();
					const volScalarField& p = film.pPrimary();

					forAll(kappa, celli)
					{
						kappa[celli] = this->kappa(p[celli], T[celli]);
					}
				}

				tkappa.ref().correctBoundaryConditions();

				return tkappa;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //