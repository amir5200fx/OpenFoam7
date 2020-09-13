#pragma once
#include <surfaceFields.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class BasicTurbulenceModel>
void tnbLib::EddyDiffusivity<BasicTurbulenceModel>::correctNut()
{
	// Read Prt if provided
	Prt_ = dimensioned<scalar>::lookupOrDefault
	(
		"Prt",
		this->coeffDict(),
		1.0
	);

	alphat_ = this->rho_*this->nut() / Prt_;
	alphat_.correctBoundaryConditions();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::EddyDiffusivity<BasicTurbulenceModel>::EddyDiffusivity
(
	const word& type,
	const alphaField& alpha,
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	BasicTurbulenceModel
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

	// Cannot read Prt yet
	Prt_("Prt", dimless, 1.0),

	alphat_
	(
		IOobject
		(
			IOobject::groupName("alphat", alphaRhoPhi.group()),
			this->runTime_.timeName(),
			this->mesh_,
			IOobject::MUST_READ,
			IOobject::AUTO_WRITE
		),
		this->mesh_
	)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::EddyDiffusivity<BasicTurbulenceModel>::read()
{
	if (BasicTurbulenceModel::read())
	{
		Prt_.readIfPresent(this->coeffDict());

		return true;
	}
	else
	{
		return false;
	}
}


template<class BasicTurbulenceModel>
void tnbLib::EddyDiffusivity<BasicTurbulenceModel>::correctEnergyTransport()
{
	EddyDiffusivity<BasicTurbulenceModel>::correctNut();
}


// ************************************************************************* //