#include <interRegionOption.hxx>


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::interRegionOption::read(const dictionary& dict)
{
	if (option::read(dict))
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //