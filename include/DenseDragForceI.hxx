#pragma once
#include <SchillerNaumannDragForce.hxx>
#include <volFields.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DenseDragForce<CloudType>::DenseDragForce
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& typeName
)
	:
	ParticleForce<CloudType>(owner, mesh, dict, typeName, true),
	alphacName_(this->coeffs().lookup("alphac")),
	alphacPtr_(nullptr),
	alphacInterpPtr_(nullptr)
{}


template<class CloudType>
tnbLib::DenseDragForce<CloudType>::DenseDragForce
(
	const DenseDragForce<CloudType>& df
)
	:
	ParticleForce<CloudType>(df),
	alphacName_(df.alphacName_),
	alphacPtr_(nullptr),
	alphacInterpPtr_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DenseDragForce<CloudType>::~DenseDragForce()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const tnbLib::interpolation<tnbLib::scalar>&
tnbLib::DenseDragForce<CloudType>::alphacInterp() const
{
	if (!alphacInterpPtr_.valid())
	{
		FatalErrorInFunction
			<< "Carrier phase volume-fraction interpolation object not set"
			<< abort(FatalError);
	}

	return alphacInterpPtr_();
}


template<class CloudType>
void tnbLib::DenseDragForce<CloudType>::cacheFields(const bool store)
{
	if (store)
	{
		if (!this->mesh().template foundObject<volVectorField>(alphacName_))
		{
			alphacPtr_.reset
			(
				new volScalarField(alphacName_, 1 - this->owner().theta())
			);
		}

		const volScalarField& alphac =
			this->mesh().template lookupObject<volScalarField>(alphacName_);

		alphacInterpPtr_.reset
		(
			interpolation<scalar>::New
			(
				this->owner().solution().interpolationSchemes(),
				alphac
			).ptr()
		);
	}
	else
	{
		alphacInterpPtr_.clear();
		alphacPtr_.clear();
	}
}


// ************************************************************************* //