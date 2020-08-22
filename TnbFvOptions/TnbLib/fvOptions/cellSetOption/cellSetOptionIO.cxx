#include <cellSetOption.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::cellSetOption::read(const dictionary& dict)
{
	if (option::read(dict))
	{
		if (coeffs_.readIfPresent("timeStart", timeStart_))
		{
			coeffs_.lookup("duration") >> duration_;
		}
	}

	return true;
}


// ************************************************************************* //