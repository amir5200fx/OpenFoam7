#pragma once
#include <constants.hxx>

using namespace tnbLib::constant;
using namespace tnbLib::constant::mathematical;

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParcelType>
inline const tnbLib::word& tnbLib::DSMCCloud<ParcelType>::cloudName() const
{
	return cloudName_;
}


template<class ParcelType>
inline const tnbLib::fvMesh& tnbLib::DSMCCloud<ParcelType>::mesh() const
{
	return mesh_;
}


template<class ParcelType>
inline const tnbLib::IOdictionary&
tnbLib::DSMCCloud<ParcelType>::particleProperties() const
{
	return particleProperties_;
}


template<class ParcelType>
inline const tnbLib::List<tnbLib::word>&
tnbLib::DSMCCloud<ParcelType>::typeIdList() const
{
	return typeIdList_;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCCloud<ParcelType>::nParticle() const
{
	return nParticle_;
}


template<class ParcelType>
inline const tnbLib::List<tnbLib::DynamicList<ParcelType*>>&
tnbLib::DSMCCloud<ParcelType>::cellOccupancy() const
{
	return cellOccupancy_;
}


template<class ParcelType>
inline tnbLib::volScalarField& tnbLib::DSMCCloud<ParcelType>::sigmaTcRMax()
{
	return sigmaTcRMax_;
}


template<class ParcelType>
inline tnbLib::scalarField&
tnbLib::DSMCCloud<ParcelType>::collisionSelectionRemainder()
{
	return collisionSelectionRemainder_;
}


template<class ParcelType>
inline const tnbLib::List<typename ParcelType::constantProperties>&
tnbLib::DSMCCloud<ParcelType>::constProps() const
{
	return constProps_;
}


template<class ParcelType>
inline const typename ParcelType::constantProperties&
tnbLib::DSMCCloud<ParcelType>::constProps
(
	label typeId
) const
{
	if (typeId < 0 || typeId >= constProps_.size())
	{
		FatalErrorInFunction
			<< "constantProperties for requested typeId index "
			<< typeId << " do not exist" << nl
			<< abort(FatalError);
	}

	return constProps_[typeId];
}


template<class ParcelType>
inline tnbLib::Random& tnbLib::DSMCCloud<ParcelType>::rndGen()
{
	return rndGen_;
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::qBF()
{
	return q_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volVectorField::Boundary&
tnbLib::DSMCCloud<ParcelType>::fDBF()
{
	return fD_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::rhoNBF()
{
	return rhoN_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::rhoMBF()
{
	return rhoM_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::linearKEBF()
{
	return linearKE_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::internalEBF()
{
	return internalE_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volScalarField::Boundary&
tnbLib::DSMCCloud<ParcelType>::iDofBF()
{
	return iDof_.boundaryFieldRef();
}


template<class ParcelType>
inline tnbLib::volVectorField::Boundary&
tnbLib::DSMCCloud<ParcelType>::momentumBF()
{
	return momentum_.boundaryFieldRef();
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::boundaryT() const
{
	return boundaryT_;
}


template<class ParcelType>
inline const tnbLib::volVectorField&
tnbLib::DSMCCloud<ParcelType>::boundaryU() const
{
	return boundaryU_;
}


template<class ParcelType>
inline const tnbLib::BinaryCollisionModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::binaryCollision() const
{
	return binaryCollisionModel_;
}


template<class ParcelType>
inline tnbLib::BinaryCollisionModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::binaryCollision()
{
	return binaryCollisionModel_();
}


template<class ParcelType>
inline const tnbLib::WallInteractionModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::wallInteraction() const
{
	return wallInteractionModel_;
}


template<class ParcelType>
inline tnbLib::WallInteractionModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::wallInteraction()
{
	return wallInteractionModel_();
}


template<class ParcelType>
inline const tnbLib::InflowBoundaryModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::inflowBoundary() const
{
	return inflowBoundaryModel_;
}


template<class ParcelType>
inline tnbLib::InflowBoundaryModel<tnbLib::DSMCCloud<ParcelType>>&
tnbLib::DSMCCloud<ParcelType>::inflowBoundary()
{
	return inflowBoundaryModel_();
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCCloud<ParcelType>::massInSystem() const
{
	scalar sysMass = 0.0;

	forAllConstIter(typename DSMCCloud<ParcelType>, *this, iter)
	{
		const ParcelType& p = iter();

		const typename ParcelType::constantProperties& cP = constProps
		(
			p.typeId()
		);

		sysMass += cP.mass();
	}

	return nParticle_ * sysMass;
}


template<class ParcelType>
inline tnbLib::vector tnbLib::DSMCCloud<ParcelType>::linearMomentumOfSystem() const
{
	vector linearMomentum(Zero);

	forAllConstIter(typename DSMCCloud<ParcelType>, *this, iter)
	{
		const ParcelType& p = iter();

		const typename ParcelType::constantProperties& cP = constProps
		(
			p.typeId()
		);

		linearMomentum += cP.mass()*p.U();
	}

	return nParticle_ * linearMomentum;
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCCloud<ParcelType>::linearKineticEnergyOfSystem() const
{
	scalar linearKineticEnergy = 0.0;

	forAllConstIter(typename DSMCCloud<ParcelType>, *this, iter)
	{
		const ParcelType& p = iter();

		const typename ParcelType::constantProperties& cP = constProps
		(
			p.typeId()
		);

		linearKineticEnergy += 0.5*cP.mass()*(p.U() & p.U());
	}

	return nParticle_ * linearKineticEnergy;
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCCloud<ParcelType>::internalEnergyOfSystem() const
{
	scalar internalEnergy = 0.0;

	forAllConstIter(typename DSMCCloud<ParcelType>, *this, iter)
	{
		const ParcelType& p = iter();

		internalEnergy += p.Ei();
	}

	return nParticle_ * internalEnergy;
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCCloud<ParcelType>::maxwellianAverageSpeed
(
	scalar temperature,
	scalar mass
) const
{
	return
		2.0*sqrt(2.0*physicoChemical::k.value()*temperature / (pi*mass));
}


template<class ParcelType>
inline tnbLib::scalarField tnbLib::DSMCCloud<ParcelType>::maxwellianAverageSpeed
(
	scalarField temperature,
	scalar mass
) const
{
	tmp<scalarField> tfld =
		2.0*sqrt(2.0*physicoChemical::k.value()*temperature / (pi*mass));
	return tfld();
}


template<class ParcelType>
inline tnbLib::scalar tnbLib::DSMCCloud<ParcelType>::maxwellianRMSSpeed
(
	scalar temperature,
	scalar mass
) const
{
	return sqrt(3.0*physicoChemical::k.value()*temperature / mass);
}


template<class ParcelType>
inline tnbLib::scalarField tnbLib::DSMCCloud<ParcelType>::maxwellianRMSSpeed
(
	scalarField temperature,
	scalar mass
) const
{
	tmp<scalarField> tfld =
		sqrt(3.0*physicoChemical::k.value()*temperature / mass);
	return tfld();
}


template<class ParcelType>
inline tnbLib::scalar
tnbLib::DSMCCloud<ParcelType>::maxwellianMostProbableSpeed
(
	scalar temperature,
	scalar mass
) const
{
	return sqrt(2.0*physicoChemical::k.value()*temperature / mass);
}


template<class ParcelType>
inline tnbLib::scalarField
tnbLib::DSMCCloud<ParcelType>::maxwellianMostProbableSpeed
(
	scalarField temperature,
	scalar mass
) const
{
	tmp<scalarField> tfld =
		sqrt(2.0*physicoChemical::k.value()*temperature / mass);
	return tfld();
}


template<class ParcelType>
inline const tnbLib::volScalarField& tnbLib::DSMCCloud<ParcelType>::q() const
{
	return q_;
}


template<class ParcelType>
inline const tnbLib::volVectorField& tnbLib::DSMCCloud<ParcelType>::fD() const
{
	return fD_;
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::rhoN() const
{
	return rhoN_;
}


template<class ParcelType>
inline const tnbLib::volScalarField& tnbLib::DSMCCloud<ParcelType>::rhoM() const
{
	return rhoM_;
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::dsmcRhoN() const
{
	return dsmcRhoN_;
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::linearKE() const
{
	return linearKE_;
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::internalE() const
{
	return internalE_;
}


template<class ParcelType>
inline const tnbLib::volScalarField&
tnbLib::DSMCCloud<ParcelType>::iDof() const
{
	return iDof_;
}


template<class ParcelType>
inline const tnbLib::volVectorField& tnbLib::DSMCCloud<ParcelType>::momentum() const
{
	return momentum_;
}


template<class ParcelType>
inline void tnbLib::DSMCCloud<ParcelType>::clear()
{
	return IDLList<ParcelType>::clear();
}


// ************************************************************************* //