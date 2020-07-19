#include <regionCoupledFvPatch.hxx>

#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(regionCoupledFvPatch, 0);
	addToRunTimeSelectionTable(fvPatch, regionCoupledFvPatch, polyPatch);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupledFvPatch::interfaceInternalField
(
	const labelUList& internalData
) const
{
	return patchInternalField(internalData);
}


tnbLib::tmp<tnbLib::labelField> tnbLib::regionCoupledFvPatch::internalFieldTransfer
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