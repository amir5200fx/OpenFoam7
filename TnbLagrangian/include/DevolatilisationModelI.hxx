#pragma once
#include <PstreamReduceOps.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DevolatilisationModel<CloudType>::DevolatilisationModel
(
	CloudType& owner
)
	:
	CloudSubModelBase<CloudType>(owner),
	dMass_(0.0)
{}


template<class CloudType>
tnbLib::DevolatilisationModel<CloudType>::DevolatilisationModel
(
	const dictionary& dict,
	CloudType& owner,
	const word& type
)
	:
	CloudSubModelBase<CloudType>(owner, dict, typeName, type),
	dMass_(0.0)
{}


template<class CloudType>
tnbLib::DevolatilisationModel<CloudType>::DevolatilisationModel
(
	const DevolatilisationModel<CloudType>& dm
)
	:
	CloudSubModelBase<CloudType>(dm),
	dMass_(dm.dMass_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::DevolatilisationModel<CloudType>::~DevolatilisationModel()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::DevolatilisationModel<CloudType>::addToDevolatilisationMass
(
	const scalar dMass
)
{
	dMass_ += dMass;
}


template<class CloudType>
void tnbLib::DevolatilisationModel<CloudType>::info(Ostream& os)
{
	const scalar mass0 = this->template getBaseProperty<scalar>("mass");
	const scalar massTotal = mass0 + returnReduce(dMass_, sumOp<scalar>());

	Info << "    Mass transfer devolatilisation  = " << massTotal << nl;

	if (this->writeTime())
	{
		this->setBaseProperty("mass", massTotal);
		dMass_ = 0.0;
	}
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //