#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::Square<Type>::read(const dictionary& coeffs)
{
	t0_ = coeffs.lookupOrDefault<scalar>("t0", 0);
	markSpace_ = coeffs.lookupOrDefault<scalar>("markSpace", 1);
	amplitude_ = Function1<scalar>::New("amplitude", coeffs);
	frequency_ = Function1<scalar>::New("frequency", coeffs);
	scale_ = Function1<Type>::New("scale", coeffs);
	level_ = Function1<Type>::New("level", coeffs);
}


template<class Type>
tnbLib::Function1Types::Square<Type>::Square
(
	const word& entryName,
	const dictionary& dict
)
	:
	Function1<Type>(entryName)
{
	read(dict);
}


template<class Type>
tnbLib::Function1Types::Square<Type>::Square(const Square<Type>& se)
	:
	Function1<Type>(se),
	t0_(se.t0_),
	markSpace_(se.markSpace_),
	amplitude_(se.amplitude_, false),
	frequency_(se.frequency_, false),
	scale_(se.scale_, false),
	level_(se.level_, false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Square<Type>::~Square()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::Square<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);
	os << token::END_STATEMENT << nl;
	os << indent << word(this->name() + "Coeffs") << nl;
	os << indent << token::BEGIN_BLOCK << incrIndent << nl;
	writeEntry(os, "t0", t0_);
	writeEntry(os, "markSpace", markSpace_);
	amplitude_->writeData(os);
	frequency_->writeData(os);
	scale_->writeData(os);
	level_->writeData(os);
	os << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //