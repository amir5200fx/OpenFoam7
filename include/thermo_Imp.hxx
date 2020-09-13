#pragma once
/* * * * * * * * * * * * * * * private static data * * * * * * * * * * * * * */

template<class Thermo, template<class> class Type>
const tnbLib::scalar tnbLib::species::thermo<Thermo, Type>::tol_ = 1.0e-4;

template<class Thermo, template<class> class Type>
const int tnbLib::species::thermo<Thermo, Type>::maxIter_ = 100;


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Thermo, template<class> class Type>
tnbLib::species::thermo<Thermo, Type>::thermo(const dictionary& dict)
	:
	Thermo(dict)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Thermo, template<class> class Type>
void tnbLib::species::thermo<Thermo, Type>::write(Ostream& os) const
{
	Thermo::write(os);
}


// * * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * //

template<class Thermo, template<class> class Type>
tnbLib::Ostream& tnbLib::species::operator<<
(
	Ostream& os, const thermo<Thermo, Type>& st
	)
{
	st.write(os);
	return os;
}


// ************************************************************************* //