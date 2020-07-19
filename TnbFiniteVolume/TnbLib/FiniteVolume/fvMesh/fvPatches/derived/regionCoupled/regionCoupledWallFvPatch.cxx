#include <regionCoupledWallFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledWallFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, regionCoupledWallFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupledWallFvPatch::
interfaceInternalField
(
	const labelUList& internalData
) const
{
	return patchInternalField(internalData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupledWallFvPatch::
internalFieldTransfer
(
	const Pstream::commsTypes commsType,
	const labelUList& iF
) const
{
	if (neighbFvPatch().sameRegion())
	{
		return neighbFvPatch().patchInternalField(iF);
	}
	else
	{
		return tmp<labelField>(new labelField(iF.size(), 0));

	}
	return tmp<labelField>(nullptr);
}

// ************************************************************************* //