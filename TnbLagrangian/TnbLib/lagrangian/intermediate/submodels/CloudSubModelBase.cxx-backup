#include <CloudSubModelBase.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudSubModelBase<CloudType>::CloudSubModelBase(CloudType& owner)
	:
	subModelBase(owner.outputProperties()),
	owner_(owner)
{}


template<class CloudType>
tnbLib::CloudSubModelBase<CloudType>::CloudSubModelBase
(
	CloudType& owner,
	const dictionary& dict,
	const word& baseName,
	const word& modelType,
	const word& dictExt
)
	:
	subModelBase
	(
		owner.outputProperties(),
		dict,
		baseName,
		modelType,
		dictExt
	),
	owner_(owner)
{}


template<class CloudType>
tnbLib::CloudSubModelBase<CloudType>::CloudSubModelBase
(
	const word& modelName,
	CloudType& owner,
	const dictionary& dict,
	const word& baseName,
	const word& modelType
)
	:
	subModelBase
	(
		modelName,
		owner.outputProperties(),
		dict,
		baseName,
		modelType
	),
	owner_(owner)
{}


template<class CloudType>
tnbLib::CloudSubModelBase<CloudType>::CloudSubModelBase
(
	const CloudSubModelBase<CloudType>& smb
)
	:
	subModelBase(smb),
	owner_(smb.owner_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudSubModelBase<CloudType>::~CloudSubModelBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
const CloudType& tnbLib::CloudSubModelBase<CloudType>::owner() const
{
	return owner_;
}


template<class CloudType>
CloudType& tnbLib::CloudSubModelBase<CloudType>::owner()
{
	return owner_;
}


template<class CloudType>
bool tnbLib::CloudSubModelBase<CloudType>::writeTime() const
{
	return
		active()
		&& owner_.solution().transient()
		&& owner_.db().time().writeTime();
}


template<class CloudType>
void tnbLib::CloudSubModelBase<CloudType>::write(Ostream& os) const
{
	writeEntry(os, "owner", owner_.name());
	subModelBase::write(os);
}


// ************************************************************************* //