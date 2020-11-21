#pragma once

// .cxx

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class GeoFieldType>
tnbLib::tmp<GeoFieldType>
tnbLib::functionObjects::add::calcFieldType() const
{
	tmp<GeoFieldType> tresult
	(
		lookupObject<GeoFieldType>(fieldNames_[0])
		+ lookupObject<GeoFieldType>(fieldNames_[1])
	);

	for (label i = 2; i < fieldNames_.size(); i++)
	{
		tresult.ref() += lookupObject<GeoFieldType>(fieldNames_[i]);
	}

	return tresult;
}


// ************************************************************************* //