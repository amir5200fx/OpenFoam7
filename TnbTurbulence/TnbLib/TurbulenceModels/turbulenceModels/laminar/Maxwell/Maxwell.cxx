#include <Maxwell.hxx>

#include <fvOptions.hxx>
#include <uniformDimensionedFields.hxx>

#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace laminarModels
	{

		// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		tmp<fvSymmTensorMatrix> Maxwell<BasicTurbulenceModel>::sigmaSource() const
		{
			return tmp<fvSymmTensorMatrix>
				(
					new fvSymmTensorMatrix
					(
						sigma_,
						dimVolume*this->rho_.dimensions()*sigma_.dimensions() / dimTime
					)
					);
		}


		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		Maxwell<BasicTurbulenceModel>::Maxwell
		(
			const alphaField& alpha,
			const rhoField& rho,
			const volVectorField& U,
			const surfaceScalarField& alphaRhoPhi,
			const surfaceScalarField& phi,
			const transportModel& transport,
			const word& propertiesName,
			const word& type
		)
			:
			laminarModel<BasicTurbulenceModel>
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

			nuM_
			(
				dimensioned<scalar>
				(
					"nuM",
					dimViscosity,
					this->coeffDict_.lookup("nuM")
					)
			),

			lambda_
			(
				dimensioned<scalar>
				(
					"lambda",
					dimTime,
					this->coeffDict_.lookup("lambda")
					)
			),

			sigma_
			(
				IOobject
				(
					IOobject::groupName("sigma", alphaRhoPhi.group()),
					this->runTime_.timeName(),
					this->mesh_,
					IOobject::MUST_READ,
					IOobject::AUTO_WRITE
				),
				this->mesh_
			)
		{
			if (type == typeName)
			{
				this->printCoeffs(type);
			}
		}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

		template<class BasicTurbulenceModel>
		bool Maxwell<BasicTurbulenceModel>::read()
		{
			if (laminarModel<BasicTurbulenceModel>::read())
			{
				nuM_.readIfPresent(this->coeffDict());
				lambda_.readIfPresent(this->coeffDict());

				return true;
			}
			else
			{
				return false;
			}
		}

		template<class BasicTurbulenceModel>
		tmp<tnbLib::volSymmTensorField>
			Maxwell<BasicTurbulenceModel>::R() const
		{
			return sigma_;
		}

		template<class BasicTurbulenceModel>
		tmp<tnbLib::volSymmTensorField>
			Maxwell<BasicTurbulenceModel>::devRhoReff() const
		{
			return volSymmTensorField::New
			(
				IOobject::groupName("devRhoReff", this->alphaRhoPhi_.group()),
				this->alpha_*this->rho_*sigma_
				- (this->alpha_*this->rho_*this->nu())
				*dev(twoSymm(fvc::grad(this->U_)))
			);
		}


		template<class BasicTurbulenceModel>
		tmp<tnbLib::fvVectorMatrix>
			Maxwell<BasicTurbulenceModel>::divDevRhoReff
			(
				volVectorField& U
			) const
		{
			return
				(
					fvc::div
					(
						this->alpha_*this->rho_*this->nuM_*fvc::grad(U)
					)
					+ fvc::div(this->alpha_*this->rho_*sigma_)
					- fvc::div(this->alpha_*this->rho_*this->nu()*dev2(T(fvc::grad(U))))
					- fvm::laplacian(this->alpha_*this->rho_*nu0(), U)
					);
		}


		template<class BasicTurbulenceModel>
		tmp<tnbLib::fvVectorMatrix>
			Maxwell<BasicTurbulenceModel>::divDevRhoReff
			(
				const volScalarField& rho,
				volVectorField& U
			) const
		{
			return
				(
					fvc::div
					(
						this->alpha_*rho*this->nuM_*fvc::grad(U)
					)
					+ fvc::div(this->alpha_*rho*sigma_)
					- fvc::div(this->alpha_*rho*this->nu()*dev2(T(fvc::grad(U))))
					- fvm::laplacian(this->alpha_*rho*nu0(), U)
					);
		}


		template<class BasicTurbulenceModel>
		void Maxwell<BasicTurbulenceModel>::correct()
		{
			// Local references
			const alphaField& alpha = this->alpha_;
			const rhoField& rho = this->rho_;
			const surfaceScalarField& alphaRhoPhi = this->alphaRhoPhi_;
			const volVectorField& U = this->U_;
			volSymmTensorField& sigma = this->sigma_;
			fv::options& fvOptions(fv::options::New(this->mesh_));

			laminarModel<BasicTurbulenceModel>::correct();

			tmp<volTensorField> tgradU(fvc::grad(U));
			const volTensorField& gradU = tgradU();

			uniformDimensionedScalarField rLambda
			(
				IOobject
				(
					IOobject::groupName("rLambda", this->alphaRhoPhi_.group()),
					this->runTime_.constant(),
					this->mesh_
				),
				1.0 / (lambda_)
			);

			// Note sigma is positive on lhs of momentum eqn
			volSymmTensorField P
			(
				twoSymm(sigma & gradU)
				- nuM_ * rLambda*twoSymm(gradU)
			);

			// Viscoelastic stress equation
			tmp<fvSymmTensorMatrix> sigmaEqn
			(
				fvm::ddt(alpha, rho, sigma)
				+ fvm::div(alphaRhoPhi, sigma)
				+ fvm::Sp(alpha*rho*rLambda, sigma)
				==
				alpha * rho*P
				+ sigmaSource()
				+ fvOptions(alpha, rho, sigma)
			);

			sigmaEqn.ref().relax();
			fvOptions.constrain(sigmaEqn.ref());
			solve(sigmaEqn);
			fvOptions.correct(sigma_);
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace laminarModels
} // End namespace tnbLib

// ************************************************************************* //