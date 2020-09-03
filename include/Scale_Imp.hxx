#pragma once
#include <Constant.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::Scale<Type>::read(const dictionary& coeffs)
{
	xScale_ = coeffs.found("xScale")
		? Function1<scalar>::New("xScale", coeffs)
		: autoPtr<Function1<scalar>>(new Constant<scalar>("xScale", 1));

	scale_ = Function1<scalar>::New("scale", coeffs);
	value_ = Function1<Type>::New("value", coeffs);
}


template<class Type>
tnbLib::Function1Types::Scale<Type>::Scale
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
tnbLib::Function1Types::Scale<Type>::Scale(const Scale<Type>& se)
	:
	Function1<Type>(se),
	xScale_(se.xScale_, false),
	scale_(se.scale_, false),
	value_(se.value_, false)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::Scale<Type>::~Scale()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::Function1Types::Scale<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);
	os << token::END_STATEMENT << nl;
	os << indent << word(this->name() + "Coeffs") << nl;
	os << indent << token::BEGIN_BLOCK << incrIndent << nl;
	xScale_->writeData(os);
	scale_->writeData(os);
	value_->writeData(os);
	os << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //