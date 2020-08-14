#include <IncompressibleTurbulenceModelTemplate.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::
IncompressibleTurbulenceModel
(
	const word& type,
	const geometricOneField& alpha,
	const geometricOneField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const TransportModel& transport,
	const word& propertiesName
)
	:
	TurbulenceModel
	<
	geometricOneField,
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
		transport,
		propertiesName
		)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::autoPtr<tnbLib::IncompressibleTurbulenceModel<TransportModel>>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::New
(
	const volVectorField& U,
	const surfaceScalarField& phi,
	const TransportModel& transport,
	const word& propertiesName
)
{
	return autoPtr<IncompressibleTurbulenceModel>
		(
			static_cast<IncompressibleTurbulenceModel*>(
				TurbulenceModel
				<
				geometricOneField,
				geometricOneField,
				incompressibleTurbulenceModel,
				TransportModel
				>::New
				(
					geometricOneField(),
					geometricOneField(),
					U,
					phi,
					phi,
					transport,
					propertiesName
				).ptr())
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TransportModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::devReff() const
{
	return devRhoReff();
}


template<class TransportModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::divDevReff
(
	volVectorField& U
) const
{
	return divDevRhoReff(U);
}


template<class TransportModel>
tnbLib::tmp<tnbLib::volSymmTensorField>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::
devRhoReff() const
{
	NotImplemented;

	return devReff();
}


template<class TransportModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::
divDevRhoReff
(
	volVectorField& U
) const
{
	NotImplemented;

	return divDevReff(U);
}


template<class TransportModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::IncompressibleTurbulenceModel<TransportModel>::
divDevRhoReff
(
	const volScalarField& rho,
	volVectorField& U
) const
{
	NotImplemented;

	return divDevReff(U);
}


// ************************************************************************* //