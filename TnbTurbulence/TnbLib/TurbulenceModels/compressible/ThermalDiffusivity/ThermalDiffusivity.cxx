#include <ThermalDiffusivity.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::ThermalDiffusivity<BasicTurbulenceModel>::ThermalDiffusivity
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
	)
{}


// * * * * * * * * * * * * * * * * * Selectors * * * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::autoPtr<tnbLib::ThermalDiffusivity<BasicTurbulenceModel>>
tnbLib::ThermalDiffusivity<BasicTurbulenceModel>::New
(
	const alphaField& alpha,
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& alphaRhoPhi,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
{
	return autoPtr<ThermalDiffusivity>
		(
			static_cast<ThermalDiffusivity*>(
				BasicTurbulenceModel::New
				(
					alpha,
					rho,
					U,
					alphaRhoPhi,
					phi,
					transport,
					propertiesName
				).ptr())
			);
}


template<class BasicTurbulenceModel>
tnbLib::autoPtr<tnbLib::ThermalDiffusivity<BasicTurbulenceModel>>
tnbLib::ThermalDiffusivity<BasicTurbulenceModel>::New
(
	const volScalarField& rho,
	const volVectorField& U,
	const surfaceScalarField& phi,
	const transportModel& transport,
	const word& propertiesName
)
{
	return autoPtr<ThermalDiffusivity>
		(
			static_cast<ThermalDiffusivity*>(
				BasicTurbulenceModel::New
				(
					rho,
					U,
					phi,
					transport,
					propertiesName
				).ptr())
			);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::ThermalDiffusivity<BasicTurbulenceModel>::alphat() const
{
	return volScalarField::New
	(
		IOobject::groupName("alphat", this->alphaRhoPhi_.group()),
		this->mesh_,
		dimensionedScalar(dimDensity*dimViscosity, 0)
	);
}


template<class BasicTurbulenceModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::ThermalDiffusivity<BasicTurbulenceModel>::alphat
(
	const label patchi
) const
{
	return tmp<scalarField>
		(
			new scalarField(this->mesh_.boundary()[patchi].size(), 0.0)
			);
}


// ************************************************************************* //