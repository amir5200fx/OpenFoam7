#pragma once
// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::coupleGroupIdentifier::name() const
{
	return name_;
}


bool tnbLib::coupleGroupIdentifier::valid() const
{
	return !name_.empty();
}


// ************************************************************************* //