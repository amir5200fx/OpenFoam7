#pragma once
#include <surfaceMesh.hxx>  // added by amir
#include <fvBoundaryMesh.hxx>  // added by amir
#include <fvsPatchFields.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::
PhaseIncompressibleTurbulenceModel
(
	const word& type,
	const volScalarField& alpha,
	const geometricOneField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const TransportModel& transportModel,
	const word& propertiesName
)
	:
	TurbulenceModel
	<
	volScalarField,
	geometricOneField,
	incompressibleTurbulenceModel,
	TransportModel
	>
	(
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transportModel,
		propertiesName
		)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::autoPtr<tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::New
(
	const volScalarField& alpha,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const TransportModel& transportModel,
	const word& propertiesName
)
{
	return autoPtr<PhaseIncompressibleTurbulenceModel>
		(
			static_cast<PhaseIncompressibleTurbulenceModel*>(
				TurbulenceModel
				<
				volScalarField,
				geometricOneField,
				incompressibleTurbulenceModel,
				TransportModel
				>::New
				(
					alpha,
					geometricOneField(),
					U,
					alphaRhoPhi,
					phi,
					transportModel,
					propertiesName
				).ptr())
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::pPrime() const
{
	return volScalarField::New
	(
		IOobject::groupName("pPrime", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(dimPressure, 0)
	);
}


template<class TransportModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::pPrimef() const
{
	return surfaceScalarField::New
	(
		IOobject::groupName("pPrimef", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(dimPressure, 0)
	);
}


template<class TransportModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::devReff() const
{
	return devRhoReff();
}


template<class TransportModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::divDevReff
(
	volVectorField& U
) const
{
	return divDevRhoReff(U);
}


template<class TransportModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::
devRhoReff() const
{
	NotImplemented;

	return devReff();
}


template<class TransportModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::PhaseIncompressibleTurbulenceModel<TransportModel>::
divDevRhoReff
(
	volVectorField& U
) const
{
	NotImplemented;

	return divDevReff(U);
}


// ************************************************************************* //