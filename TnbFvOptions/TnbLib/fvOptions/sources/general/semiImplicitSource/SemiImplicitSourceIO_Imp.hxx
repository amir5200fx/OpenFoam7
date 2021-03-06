#pragma once
// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::fv::SemiImplicitSource<Type>::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		volumeMode_ = wordToVolumeModeType(coeffs_.lookup("volumeMode"));
		setFieldData(coeffs_.subDict("injectionRateSuSp"));

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //