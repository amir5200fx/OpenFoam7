#pragma once
// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::writeFile::writeHeaderValue
(
	Ostream& os,
	const string& property,
	const Type& value
) const
{
	os << setw(1) << '#' << setw(1) << ' '
		<< setf(ios_base::left) << setw(charWidth() - 2) << property.c_str()
		<< setw(1) << ':' << setw(1) << ' ' << value << nl;
}


// ************************************************************************* //