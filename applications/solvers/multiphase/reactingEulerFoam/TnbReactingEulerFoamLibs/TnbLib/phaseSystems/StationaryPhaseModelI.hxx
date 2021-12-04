#pragma once
using namespace tnbLib;

template<class BasePhaseModel>
template<class Type, template<class> class PatchField, class GeoMesh>
tnbLib::tmp<tnbLib::GeometricField<Type, PatchField, GeoMesh>>
tnbLib::StationaryPhaseModel<BasePhaseModel>::zeroField
(
	const word& name,
	const dimensionSet& dims,
	const bool cache
) const
{
	return tmp<GeometricField<Type, PatchField, GeoMesh>>
		(
			new GeometricField<Type, PatchField, GeoMesh>
			(
				IOobject
				(
					IOobject::groupName(name, this->name()),
					this->mesh().time().timeName(),
					this->mesh()
				),
				this->mesh(),
				dimensioned<Type>("zero", dims, pTraits<Type>::zero)
				)
			);
}


template<class BasePhaseModel>
template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::StationaryPhaseModel<BasePhaseModel>::zeroVolField
(
	const word& name,
	const dimensionSet& dims,
	const bool cache
) const
{
	return zeroField<Type, fvPatchField, volMesh>(name, dims, cache);
}


template<class BasePhaseModel>
template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::StationaryPhaseModel<BasePhaseModel>::zeroSurfaceField
(
	const word& name,
	const dimensionSet& dims,
	const bool cache
) const
{
	return zeroField<Type, fvsPatchField, surfaceMesh>(name, dims, cache);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::StationaryPhaseModel<BasePhaseModel>::StationaryPhaseModel
(
	const phaseSystem& fluid,
	const word& phaseName,
	const label index
)
	:
	BasePhaseModel(fluid, phaseName, index)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class BasePhaseModel>
tnbLib::StationaryPhaseModel<BasePhaseModel>::~StationaryPhaseModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class BasePhaseModel>
bool tnbLib::StationaryPhaseModel<BasePhaseModel>::stationary() const
{
	return true;
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::StationaryPhaseModel<BasePhaseModel>::UEqn()
{
	FatalErrorInFunction
		<< "Cannot construct a momentum equation for a stationary phase"
		<< exit(FatalError);

	return tmp<fvVectorMatrix>();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::fvVectorMatrix>
tnbLib::StationaryPhaseModel<BasePhaseModel>::UfEqn()
{
	FatalErrorInFunction
		<< "Cannot construct a momentum equation for a stationary phase"
		<< exit(FatalError);

	return tmp<fvVectorMatrix>();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volVectorField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::U() const
{
	return zeroVolField<vector>("U", dimVelocity, true);
}


template<class BasePhaseModel>
tnbLib::volVectorField&
tnbLib::StationaryPhaseModel<BasePhaseModel>::URef()
{
	FatalErrorInFunction
		<< "Cannot access the velocity of a stationary phase"
		<< exit(FatalError);

	return const_cast<volVectorField&>(volVectorField::null());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::phi() const
{
	return zeroSurfaceField<scalar>("phi", dimVolume / dimTime);
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::StationaryPhaseModel<BasePhaseModel>::phiRef()
{
	FatalErrorInFunction
		<< "Cannot access the flux of a stationary phase"
		<< exit(FatalError);

	return const_cast<surfaceScalarField&>(surfaceScalarField::null());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaPhi() const
{
	return zeroSurfaceField<scalar>("alphaPhi", dimVolume / dimTime);
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaPhiRef()
{
	FatalErrorInFunction
		<< "Cannot access the volumetric flux of a stationary phase"
		<< exit(FatalError);

	return const_cast<surfaceScalarField&>(surfaceScalarField::null());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaRhoPhi() const
{
	return zeroSurfaceField<scalar>("alphaRhoPhi", dimMass / dimTime);
}


template<class BasePhaseModel>
tnbLib::surfaceScalarField&
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaRhoPhiRef()
{
	FatalErrorInFunction
		<< "Cannot access the mass flux of a stationary phase"
		<< exit(FatalError);

	return const_cast<surfaceScalarField&>(surfaceScalarField::null());
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volVectorField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::DUDt() const
{
	return zeroVolField<vector>("DUDt", dimVelocity / dimTime);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::surfaceScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::DUDtf() const
{
	return zeroSurfaceField<scalar>("DUDtf", dimVelocity * dimArea / dimTime);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::continuityError() const
{
	return zeroVolField<scalar>("continuityError", dimDensity / dimTime);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::continuityErrorFlow() const
{
	return zeroVolField<scalar>("continuityErrorFlow", dimDensity / dimTime);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::continuityErrorSources() const
{
	return zeroVolField<scalar>("continuityErrorSources", dimDensity / dimTime);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::K() const
{
	return zeroVolField<scalar>("K", sqr(dimVelocity));
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::divU() const
{
	return tmp<volScalarField>();
}


template<class BasePhaseModel>
void tnbLib::StationaryPhaseModel<BasePhaseModel>::divU
(
	tmp<volScalarField> divU
)
{
	FatalErrorInFunction
		<< "Cannot set the dilatation rate of a stationary phase"
		<< exit(FatalError);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::mut() const
{
	return zeroVolField<scalar>("continuityError", dimDynamicViscosity);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::muEff() const
{
	return this->thermo().mu();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::nut() const
{
	return zeroVolField<scalar>("continuityError", dimViscosity);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::nuEff() const
{
	return this->thermo().nu();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::kappaEff() const
{
	return this->thermo().kappa();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::kappaEff(const label patchi) const
{
	return this->thermo().kappa(patchi);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaEff() const
{
	return this->thermo().alpha();
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::scalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::alphaEff(const label patchi) const
{
	return this->thermo().alpha(patchi);
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::k() const
{
	return zeroVolField<scalar>("k", sqr(dimVelocity));
}


template<class BasePhaseModel>
tnbLib::tmp<tnbLib::volScalarField>
tnbLib::StationaryPhaseModel<BasePhaseModel>::pPrime() const
{
	return zeroVolField<scalar>("pPrime", dimPressure);
}