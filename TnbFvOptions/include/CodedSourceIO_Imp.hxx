#pragma once
#include <stringOps.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::fv::CodedSource<Type>::read(const dictionary& dict)
{
	if (cellSetOption::read(dict))
	{
		coeffs_.lookup("fields") >> fieldNames_;
		applied_.setSize(fieldNames_.size(), false);

		// The name keyword is "name". "redirectType" is also maintained here
		// for backwards compatibility, but "name" is taken in preference and
		// is printed in the error message if neither keyword is present.
		name_ = word::null;
		name_ = dict.lookupOrDefault("redirectType", name_);
		name_ = dict.lookupOrDefault("name", name_);
		if (name_ == word::null)
		{
			dict.lookup("name"); // <-- generate error message with "name" in it
		}

		updateLibrary(name_);

		return true;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //