#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ParticleType>
const tnbLib::polyMesh& tnbLib::InteractionLists<ParticleType>::mesh() const
{
	return mesh_;
}


template<class ParticleType>
const tnbLib::mapDistribute&
tnbLib::InteractionLists<ParticleType>::cellMap() const
{
	return cellMapPtr_();
}


template<class ParticleType>
const tnbLib::mapDistribute&
tnbLib::InteractionLists<ParticleType>::wallFaceMap() const
{
	return wallFaceMapPtr_();
}


template<class ParticleType>
const tnbLib::labelListList& tnbLib::InteractionLists<ParticleType>::dil() const
{
	return dil_;
}


template<class ParticleType>
const tnbLib::labelListList&
tnbLib::InteractionLists<ParticleType>::dwfil() const
{
	return dwfil_;
}


template<class ParticleType>
const tnbLib::labelListList& tnbLib::InteractionLists<ParticleType>::ril() const
{
	return ril_;
}


template<class ParticleType>
const tnbLib::labelListList&
tnbLib::InteractionLists<ParticleType>::rilInverse() const
{
	return rilInverse_;
}


template<class ParticleType>
const tnbLib::labelListList& tnbLib::InteractionLists<ParticleType>::rwfil() const
{
	return rwfil_;
}


template<class ParticleType>
const tnbLib::labelListList&
tnbLib::InteractionLists<ParticleType>::rwfilInverse() const
{
	return rwfilInverse_;
}


template<class ParticleType>
const tnbLib::List<tnbLib::labelPair>&
tnbLib::InteractionLists<ParticleType>::cellIndexAndTransformToDistribute() const
{
	return cellIndexAndTransformToDistribute_;
}


template<class ParticleType>
const tnbLib::List<tnbLib::labelPair>&
tnbLib::InteractionLists<ParticleType>::
wallFaceIndexAndTransformToDistribute() const
{
	return wallFaceIndexAndTransformToDistribute_;
}


template<class ParticleType>
const tnbLib::List<tnbLib::referredWallFace>&
tnbLib::InteractionLists<ParticleType>::referredWallFaces() const
{
	return referredWallFaces_;
}


template<class ParticleType>
const tnbLib::word& tnbLib::InteractionLists<ParticleType>::UName() const
{
	return UName_;
}


template<class ParticleType>
const tnbLib::List<tnbLib::vector>&
tnbLib::InteractionLists<ParticleType>::referredWallData() const
{
	return referredWallData_;
}


template<class ParticleType>
const tnbLib::List<tnbLib::IDLList<ParticleType>>&
tnbLib::InteractionLists<ParticleType>::referredParticles() const
{
	return referredParticles_;
}


template<class ParticleType>
tnbLib::List<tnbLib::IDLList<ParticleType>>&
tnbLib::InteractionLists<ParticleType>::referredParticles()
{
	return referredParticles_;
}


// ************************************************************************* //