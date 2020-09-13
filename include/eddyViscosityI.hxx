#pragma once
#include <fvc.hxx>
#include <fvm.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::eddyViscosity<BasicTurbulenceModel>::eddyViscosity
(
	const word& type,
	const alphaField& alpha,
	const rhoField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	linearViscousStress<BasicTurbulenceModel>
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
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
bool tnbLib::eddyViscosity<BasicTurbulenceModel>::read()
{
	return BasicTurbulenceModel::read();
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::eddyViscosity<BasicTurbulenceModel>::R() const
{
	tmp<volScalarField> tk(k());

	// Get list of patchField type names from k
	wordList patchFieldTypes(tk().boundaryField().types());

	// For k patchField types which do not have an equivalent for symmTensor
	// set to calculated
	forAll(patchFieldTypes, i)
	{
		if
			(
				!fvPatchField<symmTensor>::patchConstructorTablePtr_
				->found(patchFieldTypes[i])
				)
		{
			patchFieldTypes[i] = calculatedFvPatchField<symmTensor>::typeName;
		}
	}

	return volSymmTensorField::New
	(
		IOobject::groupName("R", this->alphaRhoPhi_.group()),
		((2.0 / 3.0)*I)*tk() - (nut_)*dev(twoSymm(fvc::grad(this->U_))),
		patchFieldTypes
	);
}


template<class BasicTurbulenceModel>
void tnbLib::eddyViscosity<BasicTurbulenceModel>::validate()
{
	correctNut();
}


template<class BasicTurbulenceModel>
void tnbLib::eddyViscosity<BasicTurbulenceModel>::correct()
{
	BasicTurbulenceModel::correct();
}


// ************************************************************************* //