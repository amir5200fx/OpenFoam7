#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::CompressibleTurbulenceModel<TransportModel>::
CompressibleTurbulenceModel
(
	const word& type,
	const geometricOneField& alpha,
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
	:
	TurbulenceModel
	<
	geometricOneField,
	volScalarField,
	compressibleTurbulenceModel,
	transportModel
	>
	(
		alpha,
		rho,
		U,
		alphaRhoPhi,
		phi,
		transport,
		propertiesName
		)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::autoPtr<tnbLib::CompressibleTurbulenceModel<TransportModel>>
tnbLib::CompressibleTurbulenceModel<TransportModel>::New
(
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
{
	return autoPtr<CompressibleTurbulenceModel>
		(
			static_cast<CompressibleTurbulenceModel*>(
				TurbulenceModel
				<
				geometricOneField,
				volScalarField,
				compressibleTurbulenceModel,
				transportModel
				>::New
				(
					geometricOneField(),
					rho,
					U,
					phi,
					phi,
					transport,
					propertiesName
				).ptr())
			);
}


// ************************************************************************* //