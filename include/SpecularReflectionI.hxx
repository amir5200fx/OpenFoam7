#pragma once
#include <error.hxx>

#include <vector.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SpecularReflection<CloudType>::SpecularReflection
(
	const dictionary& dict,
	CloudType& cloud
)
	:
	WallInteractionModel<CloudType>(cloud)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::SpecularReflection<CloudType>::~SpecularReflection()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::SpecularReflection<CloudType>::correct
(
	typename CloudType::parcelType& p
)
{
	vector& U = p.U();

	const vector nw = p.normal();

	scalar U_dot_nw = U & nw;

	if (U_dot_nw > 0.0)
	{
		U -= 2.0*U_dot_nw*nw;
	}
}


// ************************************************************************* //