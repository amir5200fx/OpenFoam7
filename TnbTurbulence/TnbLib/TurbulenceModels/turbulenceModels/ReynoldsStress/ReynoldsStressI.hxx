#pragma once
#include <fvc.hxx>
#include <fvm.hxx>
#include <wallFvPatch.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class BasicTurbulenceModel>
void tnbLib::ReynoldsStress<BasicTurbulenceModel>::boundNormalStress
(
	volSymmTensorField& R
) const
{
	scalar kMin = this->kMin_.value();

	R.max
	(
		dimensionedSymmTensor
		(
			"zero",
			R.dimensions(),
			symmTensor
			(
				kMin, -great, -great,
				kMin, -great,
				kMin
			)
		)
	);
}


template<class BasicTurbulenceModel>
void tnbLib::ReynoldsStress<BasicTurbulenceModel>::correctWallShearStress
(
	volSymmTensorField& R
) const
{
	const fvPatchList& patches = this->mesh_.boundary();

	volSymmTensorField::Boundary& RBf = R.boundaryFieldRef();

	forAll(patches, patchi)
	{
		const fvPatch& curPatch = patches[patchi];

		if (isA<wallFvPatch>(curPatch))
		{
			symmTensorField& Rw = RBf[patchi];

			const scalarField& nutw = this->nut_.boundaryField()[patchi];

			const vectorField snGradU
			(
				this->U_.boundaryField()[patchi].snGrad()
			);

			const vectorField& faceAreas
				= this->mesh_.Sf().boundaryField()[patchi];

			const scalarField& magFaceAreas
				= this->mesh_.magSf().boundaryField()[patchi];

			forAll(curPatch, facei)
			{
				// Calculate near-wall velocity gradient
				const tensor gradUw
					= (faceAreas[facei] / magFaceAreas[facei])*snGradU[facei];

				// Set the wall Reynolds-stress to the near-wall shear-stress
				// Note: the spherical part of the normal stress is included in
				// the pressure
				Rw[facei] = -nutw[facei] * 2 * dev(symm(gradUw));
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::ReynoldsStress
(
	const word& modelName,
	const alphaField& alpha,
	const rhoField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	BasicTurbulenceModel
	(
		modelName,
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transport,
		propertiesName
	),

	couplingFactor_
	(
		dimensioned<scalar>::lookupOrAddToDict
		(
			"couplingFactor",
			this->coeffDict_,
			0.0
		)
	),

	R_
	(
		IOobject
		(
			IOobject::groupName("R", alphaRhoPhi.group()),
			this->runTime_.timeName(),
			this->mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		this->mesh_
	),

	nut_
	(
		IOobject
		(
			IOobject::groupName("nut", alphaRhoPhi.group()),
			this->runTime_.timeName(),
			this->mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		this->mesh_
	)
{
	if (couplingFactor_.value() < 0.0 || couplingFactor_.value() > 1.0)
	{
		FatalErrorInFunction
			<< "couplingFactor = " << couplingFactor_
			<< " is not in range 0 - 1" << nl
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::ReynoldsStress<BasicTurbulenceModel>::read()
{
	return BasicTurbulenceModel::read();
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::R() const
{
	return R_;
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::k() const
{
	tmp<tnbLib::volScalarField> tk(0.5*tr(R_));
	tk.ref().rename("k");
	return tk;
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::devRhoReff() const
{
	return volSymmTensorField::New
	(
		IOobject::groupName("devRhoReff", this->alphaRhoPhi_.group()),
		this->alpha_*this->rho_*R_
		- (this->alpha_*this->rho_*this->nu())
		*dev(twoSymm(fvc::grad(this->U_)))
	);
}


template<class BasicTurbulenceModel>
template<class RhoFieldType>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::DivDevRhoReff
(
	const RhoFieldType& rho,
	volVectorField& U
) const
{
	if (couplingFactor_.value() > 0.0)
	{
		return
			(
				fvc::laplacian
				(
				(1.0 - couplingFactor_)*this->alpha_*rho*this->nut(),
					U,
					"laplacian(nuEff,U)"
				)
				+ fvc::div
				(
					this->alpha_*rho*R_
					+ couplingFactor_
					* this->alpha_*rho*this->nut()*fvc::grad(U),
					"div(devRhoReff)"
				)
				- fvc::div(this->alpha_*rho*this->nu()*dev2(T(fvc::grad(U))))
				- fvm::laplacian(this->alpha_*rho*this->nuEff(), U)
				);
	}
	else
	{
		return
			(
				fvc::laplacian
				(
					this->alpha_*rho*this->nut(),
					U,
					"laplacian(nuEff,U)"
				)
				+ fvc::div(this->alpha_*rho*R_)
				- fvc::div(this->alpha_*rho*this->nu()*dev2(T(fvc::grad(U))))
				- fvm::laplacian(this->alpha_*rho*this->nuEff(), U)
				);
	}
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::divDevRhoReff
(
	volVectorField& U
) const
{
	return DivDevRhoReff(this->rho_, U);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::ReynoldsStress<BasicTurbulenceModel>::divDevRhoReff
(
	const volScalarField& rho,
	volVectorField& U
) const
{
	return DivDevRhoReff(rho, U);
}


template<class BasicTurbulenceModel>
void tnbLib::ReynoldsStress<BasicTurbulenceModel>::validate()
{
	correctNut();
}


template<class BasicTurbulenceModel>
void tnbLib::ReynoldsStress<BasicTurbulenceModel>::correct()
{
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //