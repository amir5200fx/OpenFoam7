#pragma once
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class ThermophysicalProperties>
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::
thermophysicalPropertiesSelector
(
	const word& name
)
	:
	propertiesPtr_(ThermophysicalProperties::New(name))
{}


template<class ThermophysicalProperties>
tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::
thermophysicalPropertiesSelector
(
	const dictionary& dict
)
{
	const word name(dict.first()->keyword());

	if (dict.isDict(name))
	{
		propertiesPtr_ = ThermophysicalProperties::New(dict.subDict(name));
	}
	else
	{
		propertiesPtr_ = ThermophysicalProperties::New(name);
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class ThermophysicalProperties>
void tnbLib::thermophysicalPropertiesSelector<ThermophysicalProperties>::write
(
	Ostream& os
) const
{
	propertiesPtr_->write(os);
}


// ************************************************************************* //