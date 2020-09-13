#pragma once
#include <Pstream.hxx>
#include <stringListOps.hxx>
#include <ListOps.hxx>
#include <ListListOps.hxx>

#include <scalarField.hxx>  // added by amir
#include <dimensionSet.hxx>  // added by amir

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchCollisionDensity<CloudType>::write()
{
	const scalarField z(this->owner().mesh().nCells(), 0);

	volScalarField
	(
		IOobject
		(
			this->owner().name() + ":collisionDensity",
			this->owner().mesh().time().timeName(),
			this->owner().mesh()
		),
		this->owner().mesh(),
		dimless / dimArea,
		z,
		collisionDensity_
	)
		.write();

	volScalarField
	(
		IOobject
		(
			this->owner().name() + ":collisionDensityRate",
			this->owner().mesh().time().timeName(),
			this->owner().mesh()
		),
		this->owner().mesh(),
		dimless / dimArea / dimTime,
		z,
		(collisionDensity_ - collisionDensity0_)
		/ (this->owner().mesh().time().value() - time0_)
	)
		.write();

	collisionDensity0_ == collisionDensity_;
	time0_ = this->owner().mesh().time().value();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchCollisionDensity<CloudType>::PatchCollisionDensity
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName),
	minSpeed_(dict.lookupOrDefault<scalar>("minSpeed", -1)),
	collisionDensity_
	(
		this->owner().mesh().boundary(),
		volScalarField::Internal::null(),
		calculatedFvPatchField<scalar>::typeName
	),
	collisionDensity0_
	(
		this->owner().mesh().boundary(),
		volScalarField::Internal::null(),
		calculatedFvPatchField<scalar>::typeName
	),
	time0_(this->owner().mesh().time().value())
{
	collisionDensity_ == 0;
	collisionDensity0_ == 0;

	IOobject io
	(
		this->owner().name() + ":collisionDensity",
		this->owner().mesh().time().timeName(),
		this->owner().mesh(),
		IOobject::MUST_READ,
		IOobject::NO_WRITE
	);

	if (io.typeHeaderOk<volScalarField>())
	{
		const volScalarField collisionDensity(io, this->owner().mesh());
		collisionDensity_ == collisionDensity.boundaryField();
		collisionDensity0_ == collisionDensity.boundaryField();
	}
}


template<class CloudType>
tnbLib::PatchCollisionDensity<CloudType>::PatchCollisionDensity
(
	const PatchCollisionDensity<CloudType>& ppm
)
	:
	CloudFunctionObject<CloudType>(ppm),
	minSpeed_(ppm.minSpeed_),
	collisionDensity_(ppm.collisionDensity_),
	collisionDensity0_(ppm.collisionDensity0_),
	time0_(ppm.time0_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchCollisionDensity<CloudType>::~PatchCollisionDensity()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchCollisionDensity<CloudType>::postPatch
(
	const parcelType& p,
	const polyPatch& pp,
	bool&
)
{
	const label patchi = pp.index();
	const label patchFacei = p.face() - pp.start();

	vector nw, Up;
	this->owner().patchData(p, pp, nw, Up);

	const scalar speed = (p.U() - Up) & nw;
	if (speed > minSpeed_)
	{
		collisionDensity_[patchi][patchFacei] +=
			1 / this->owner().mesh().magSf().boundaryField()[patchi][patchFacei];
	}
}


// ************************************************************************* //