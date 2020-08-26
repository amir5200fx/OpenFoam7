#include <CloudFunctionObject.hxx>

// * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::write()
{
	NotImplemented;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudFunctionObject<CloudType>::CloudFunctionObject(CloudType& owner)
	:
	CloudSubModelBase<CloudType>(owner),
	outputDir_()
{}


template<class CloudType>
tnbLib::CloudFunctionObject<CloudType>::CloudFunctionObject
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName,
	const word& objectType
)
	:
	CloudSubModelBase<CloudType>(modelName, owner, dict, typeName, objectType),
	outputDir_(owner.mesh().time().path())
{
	const fileName relPath =
		"postProcessing" / cloud::prefix / owner.name() / this->modelName();


	if (Pstream::parRun())
	{
		// Put in undecomposed case (Note: gives problems for
		// distributed data running)
		outputDir_ = outputDir_ / ".." / relPath;
	}
	else
	{
		outputDir_ = outputDir_ / relPath;
	}
	outputDir_.clean();
}


template<class CloudType>
tnbLib::CloudFunctionObject<CloudType>::CloudFunctionObject
(
	const CloudFunctionObject<CloudType>& ppm
)
	:
	CloudSubModelBase<CloudType>(ppm),
	outputDir_(ppm.outputDir_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudFunctionObject<CloudType>::~CloudFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::preEvolve()
{}


template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::postEvolve()
{
	if (this->owner().time().writeTime())
	{
		this->write();
	}
}


template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::postMove
(
	typename CloudType::parcelType&,
	const scalar,
	const point&,
	bool&
)
{}


template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::postPatch
(
	const typename CloudType::parcelType&,
	const polyPatch&,
	bool&
)
{}


template<class CloudType>
void tnbLib::CloudFunctionObject<CloudType>::postFace
(
	const typename CloudType::parcelType&,
	bool&
)
{}


template<class CloudType>
const tnbLib::fileName& tnbLib::CloudFunctionObject<CloudType>::outputDir() const
{
	return outputDir_;
}


template<class CloudType>
tnbLib::fileName tnbLib::CloudFunctionObject<CloudType>::writeTimeDir() const
{
	return outputDir_ / this->owner().time().timeName();
}


// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

#include <CloudFunctionObjectNew.cxx>

// ************************************************************************* //