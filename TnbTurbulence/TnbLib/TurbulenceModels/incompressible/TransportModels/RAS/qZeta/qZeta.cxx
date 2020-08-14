#include <qZeta.hxx>

#include <bound.hxx>
#include <addToRunTimeSelectionTable.hxx>

#include <fvc.hxx>  // added by amir
#include <fvm.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace incompressible
	{
		namespace RASModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(qZeta, 0);
			addToRunTimeSelectionTable(RASModel, qZeta, dictionary);

			// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

			tmp<volScalarField> qZeta::fMu() const
			{
				const volScalarField Rt(q_*k_ / (2.0*nu()*zeta_));

				if (anisotropic_)
				{
					return exp((-scalar(2.5) + Rt / 20.0) / pow3(scalar(1) + Rt / 130.0));
				}
				else
				{
					return
						exp(-6.0 / sqr(scalar(1) + Rt / 50.0))
						*(scalar(1) + 3.0*exp(-Rt / 10.0));
				}
			}


			tmp<volScalarField> qZeta::f2() const
			{
				tmp<volScalarField> Rt = q_ * k_ / (2.0*nu()*zeta_);
				return scalar(1) - 0.3*exp(-sqr(Rt));
			}


			void qZeta::correctNut()
			{
				nut_ = Cmu_ * fMu()*sqr(k_) / epsilon_;
				nut_.correctBoundaryConditions();
			}


			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			qZeta::qZeta
			(
				const geometricOneField& alpha,
				const geometricOneField& rho,
				const volVectorField& U,
				const surfaceScalarField& alphaRhoPhi,
				const surfaceScalarField& phi,
				const transportModel& transport,
				const word& propertiesName,
				const word& type
			)
				:
				eddyViscosity<incompressible::RASModel>
				(
					type,
					alpha,
					rho,
					U,
					alphaRhoPhi,
					phi,
					transport,
					propertiesName
					),

				Cmu_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"Cmu",
						coeffDict_,
						0.09
					)
				),
				C1_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"C1",
						coeffDict_,
						1.44
					)
				),
				C2_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"C2",
						coeffDict_,
						1.92
					)
				),
				sigmaZeta_
				(
					dimensioned<scalar>::lookupOrAddToDict
					(
						"sigmaZeta",
						coeffDict_,
						1.3
					)
				),
				anisotropic_
				(
					Switch::lookupOrAddToDict
					(
						"anisotropic",
						coeffDict_,
						false
					)
				),

				qMin_("qMin", sqrt(kMin_)),
				zetaMin_("zetaMin", epsilonMin_ / (2 * qMin_)),

				k_
				(
					IOobject
					(
						IOobject::groupName("k", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				epsilon_
				(
					IOobject
					(
						IOobject::groupName("epsilon", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::MUST_READ,
						IOobject::AUTO_WRITE
					),
					mesh_
				),

				q_
				(
					IOobject
					(
						IOobject::groupName("q", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					sqrt(bound(k_, kMin_)),
					k_.boundaryField().types()
				),

				zeta_
				(
					IOobject
					(
						IOobject::groupName("zeta", alphaRhoPhi.group()),
						runTime_.timeName(),
						mesh_,
						IOobject::NO_READ,
						IOobject::AUTO_WRITE
					),
					bound(epsilon_, epsilonMin_) / (2.0*q_),
					epsilon_.boundaryField().types()
				)
			{
				bound(zeta_, zetaMin_);

				if (type == typeName)
				{
					printCoeffs(type);
				}
			}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			bool qZeta::read()
			{
				if (eddyViscosity<incompressible::RASModel>::read())
				{
					Cmu_.readIfPresent(coeffDict());
					C1_.readIfPresent(coeffDict());
					C2_.readIfPresent(coeffDict());
					sigmaZeta_.readIfPresent(coeffDict());
					anisotropic_.readIfPresent("anisotropic", coeffDict());

					qMin_.readIfPresent(*this);
					zetaMin_.readIfPresent(*this);

					return true;
				}
				else
				{
					return false;
				}
			}


			void qZeta::correct()
			{
				if (!turbulence_)
				{
					return;
				}

				eddyViscosity<incompressible::RASModel>::correct();

				volScalarField G(GName(), nut_ / (2.0*q_) * 2 * magSqr(symm(fvc::grad(U_))));
				const volScalarField E(nu()*nut_ / q_ * fvc::magSqrGradGrad(U_));

				// Zeta equation
				tmp<fvScalarMatrix> zetaEqn
				(
					fvm::ddt(zeta_)
					+ fvm::div(phi_, zeta_)
					- fvm::laplacian(DzetaEff(), zeta_)
					==
					(2.0*C1_ - 1)*G*zeta_ / q_
					- fvm::SuSp((2.0*C2_*f2() - dimensionedScalar(1.0))*zeta_ / q_, zeta_)
					+ E
				);

				zetaEqn.ref().relax();
				solve(zetaEqn);
				bound(zeta_, zetaMin_);


				// q equation
				tmp<fvScalarMatrix> qEqn
				(
					fvm::ddt(q_)
					+ fvm::div(phi_, q_)
					- fvm::laplacian(DqEff(), q_)
					==
					G - fvm::Sp(zeta_ / q_, q_)
				);

				qEqn.ref().relax();
				solve(qEqn);
				bound(q_, qMin_);


				// Re-calculate k and epsilon
				k_ = sqr(q_);
				k_.correctBoundaryConditions();

				epsilon_ = 2 * q_*zeta_;
				epsilon_.correctBoundaryConditions();

				correctNut();
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace RASModels
	} // End namespace incompressible
} // End namespace tnbLib

// ************************************************************************* //