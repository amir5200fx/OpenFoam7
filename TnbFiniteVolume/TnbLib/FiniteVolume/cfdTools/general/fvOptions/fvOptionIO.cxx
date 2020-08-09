#include <fvOption.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::option::writeHeader(Ostream& os) const
{
	os << indent << name_ << nl
		<< indent << token::BEGIN_BLOCK << incrIndent << nl;
}


void tnbLib::fv::option::writeFooter(Ostream& os) const
{
	os << decrIndent << indent << token::END_BLOCK << endl;
}


void tnbLib::fv::option::writeData(Ostream& os) const
{
	writeEntry(os, "type", type());
	writeEntry(os, "active", active_);
	os << nl;
	os << indent << word(type() + "Coeffs");
	coeffs_.write(os);
}


bool tnbLib::fv::option::read(const dictionary& dict)
{
	dict.readIfPresent("active", active_);

	coeffs_ = dict.optionalSubDict(modelType_ + "Coeffs");

	return true;
}


// ************************************************************************* //