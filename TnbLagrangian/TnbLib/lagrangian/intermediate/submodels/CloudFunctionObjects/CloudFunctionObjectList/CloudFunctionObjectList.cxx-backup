#include <CloudFunctionObjectList.hxx>

#include <entry.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudFunctionObjectList<CloudType>::CloudFunctionObjectList
(
	CloudType& owner
)
	:
	PtrList<CloudFunctionObject<CloudType>>(),
	owner_(owner),
	dict_(dictionary::null)
{}


template<class CloudType>
tnbLib::CloudFunctionObjectList<CloudType>::CloudFunctionObjectList
(
	CloudType& owner,
	const dictionary& dict,
	const bool readFields
)
	:
	PtrList<CloudFunctionObject<CloudType>>(),
	owner_(owner),
	dict_(dict)
{
	if (readFields)
	{
		wordList modelNames(dict.toc());

		Info << "Constructing cloud functions" << endl;

		if (modelNames.size() > 0)
		{
			this->setSize(modelNames.size());

			forAll(modelNames, i)
			{
				const word& modelName = modelNames[i];

				const dictionary& modelDict(dict.subDict(modelName));

				// read the type of the function object
				const word objectType(modelDict.lookup("type"));

				this->set
				(
					i,
					CloudFunctionObject<CloudType>::New
					(
						modelDict,
						owner,
						objectType,
						modelName
					)
				);
			}
		}
		else
		{
			Info << "    none" << endl;
		}
	}
}


template<class CloudType>
tnbLib::CloudFunctionObjectList<CloudType>::CloudFunctionObjectList
(
	const CloudFunctionObjectList& cfol
)
	:
	PtrList<CloudFunctionObject<CloudType>>(cfol),
	owner_(cfol.owner_),
	dict_(cfol.dict_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::CloudFunctionObjectList<CloudType>::~CloudFunctionObjectList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::CloudFunctionObjectList<CloudType>::preEvolve()
{
	forAll(*this, i)
	{
		this->operator[](i).preEvolve();
	}
}


template<class CloudType>
void tnbLib::CloudFunctionObjectList<CloudType>::postEvolve()
{
	forAll(*this, i)
	{
		this->operator[](i).postEvolve();
	}
}


template<class CloudType>
void tnbLib::CloudFunctionObjectList<CloudType>::postMove
(
	typename CloudType::parcelType& p,
	const scalar dt,
	const point& position0,
	bool& keepParticle
)
{
	forAll(*this, i)
	{
		if (!keepParticle)
		{
			return;
		}

		this->operator[](i).postMove(p, dt, position0, keepParticle);
	}
}


template<class CloudType>
void tnbLib::CloudFunctionObjectList<CloudType>::postPatch
(
	const typename CloudType::parcelType& p,
	const polyPatch& pp,
	bool& keepParticle
)
{
	forAll(*this, i)
	{
		if (!keepParticle)
		{
			return;
		}

		this->operator[](i).postPatch(p, pp, keepParticle);
	}
}


template<class CloudType>
void tnbLib::CloudFunctionObjectList<CloudType>::postFace
(
	const typename CloudType::parcelType& p,
	bool& keepParticle
)
{
	forAll(*this, i)
	{
		if (!keepParticle)
		{
			return;
		}

		this->operator[](i).postFace(p, keepParticle);
	}
}


// ************************************************************************* //