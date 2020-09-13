#pragma once
#include <interpolation.hxx>  // added by amir

// * * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::RelativeVelocity<CloudType>::write()
{
	IOField<vector> URel
	(
		this->owner().fieldIOobject("URel", IOobject::NO_READ),
		this->owner().size()
	);

	autoPtr<interpolation<vector>> UcInterp
	(
		interpolation<vector>::New
		(
			this->owner().solution().interpolationSchemes(),
			this->owner().U()
		)
	);

	label i = 0;
	forAllConstIter(typename CloudType, this->owner(), iter)
	{
		URel[i] =
			iter().U()
			- UcInterp->interpolate
			(
				iter().coordinates(),
				iter().currentTetIndices()
			);
		++i;
	}

	URel.write(this->owner().size() > 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::RelativeVelocity<CloudType>::RelativeVelocity
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName)
{}


template<class CloudType>
tnbLib::RelativeVelocity<CloudType>::RelativeVelocity
(
	const RelativeVelocity<CloudType>& ppm
)
	:
	CloudFunctionObject<CloudType>(ppm)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::RelativeVelocity<CloudType>::~RelativeVelocity()
{}


// ************************************************************************* //