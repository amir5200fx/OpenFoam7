#pragma once
#include <entry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleForceList<CloudType>::ParticleForceList
(
	CloudType& owner,
	const fvMesh& mesh
)
	:
	PtrList<ParticleForce<CloudType>>(),
	owner_(owner),
	mesh_(mesh),
	dict_(dictionary::null),
	calcCoupled_(true),
	calcNonCoupled_(true)
{}


template<class CloudType>
tnbLib::ParticleForceList<CloudType>::ParticleForceList
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const bool readFields
)
	:
	PtrList<ParticleForce<CloudType>>(),
	owner_(owner),
	mesh_(mesh),
	dict_(dict),
	calcCoupled_(true),
	calcNonCoupled_(true)
{
	if (readFields)
	{
		wordList modelNames(dict.toc());

		Info << "Constructing particle forces" << endl;

		if (modelNames.size() > 0)
		{
			this->setSize(modelNames.size());

			label i = 0;
			forAllConstIter(IDLList<entry>, dict, iter)
			{
				const word& model = iter().keyword();
				if (iter().isDict())
				{
					this->set
					(
						i++,
						ParticleForce<CloudType>::New
						(
							owner,
							mesh,
							iter().dict(),
							model
						)
					);
				}
				else
				{
					this->set
					(
						i++,
						ParticleForce<CloudType>::New
						(
							owner,
							mesh,
							dictionary::null,
							model
						)
					);
				}
			}
		}
		else
		{
			Info << "    none" << endl;
		}
	}
}


template<class CloudType>
tnbLib::ParticleForceList<CloudType>::ParticleForceList
(
	const ParticleForceList& pf
)
	:
	PtrList<ParticleForce<CloudType>>(pf),
	owner_(pf.owner_),
	mesh_(pf.mesh_),
	dict_(pf.dict_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::ParticleForceList<CloudType>::~ParticleForceList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::ParticleForceList<CloudType>::cacheFields(const bool store)
{
	forAll(*this, i)
	{
		this->operator[](i).cacheFields(store);
	}
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ParticleForceList<CloudType>::calcCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value(Zero, 0.0);

	if (calcCoupled_)
	{
		forAll(*this, i)
		{
			value += this->operator[](i).calcCoupled(p, td, dt, mass, Re, muc);
		}
	}

	return value;
}


template<class CloudType>
tnbLib::forceSuSp tnbLib::ParticleForceList<CloudType>::calcNonCoupled
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar dt,
	const scalar mass,
	const scalar Re,
	const scalar muc
) const
{
	forceSuSp value(Zero, 0.0);

	if (calcNonCoupled_)
	{
		forAll(*this, i)
		{
			value +=
				this->operator[](i).calcNonCoupled(p, td, dt, mass, Re, muc);
		}
	}

	return value;
}


template<class CloudType>
tnbLib::scalar tnbLib::ParticleForceList<CloudType>::massEff
(
	const typename CloudType::parcelType& p,
	const typename CloudType::parcelType::trackingData& td,
	const scalar mass
) const
{
	scalar massEff = mass;
	forAll(*this, i)
	{
		massEff += this->operator[](i).massAdd(p, td, mass);
	}

	return massEff;
}


// ************************************************************************* //