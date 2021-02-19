#include <interRegionHeatTransferModel.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::fv::interRegionHeatTransferModel::read(const dictionary& dict)
{
	if (interRegionOption::read(dict))
	{
		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //