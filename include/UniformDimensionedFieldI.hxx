#pragma once
// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const IOobject& io,
	const dimensioned<Type>& dt
)
	:
	regIOobject(io),
	dimensioned<Type>(dt)
{
	// Read value
	if
		(
		(
			io.readOpt() == IOobject::MUST_READ
			|| io.readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
			|| (io.readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		dictionary dict(readStream(typeName));
		scalar multiplier;
		this->dimensions().read(dict.lookup("dimensions"), multiplier);
		dict.lookup("value") >> this->value();
		this->value() *= multiplier;
	}
}


template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const UniformDimensionedField<Type>& rdt
)
	:
	regIOobject(rdt),
	dimensioned<Type>(rdt)
{}


template<class Type>
tnbLib::UniformDimensionedField<Type>::UniformDimensionedField
(
	const IOobject& io
)
	:
	regIOobject(io),
	dimensioned<Type>(regIOobject::name(), dimless, Zero)
{
	dictionary dict(readStream(typeName));
	scalar multiplier;
	this->dimensions().read(dict.lookup("dimensions"), multiplier);
	dict.lookup("value") >> this->value();
	this->value() *= multiplier;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::UniformDimensionedField<Type>::~UniformDimensionedField()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::UniformDimensionedField<Type>::writeData(Ostream& os) const
{
	scalar multiplier;
	os.writeKeyword("dimensions");
	this->dimensions().write(os, multiplier) << token::END_STATEMENT << nl;
	writeEntry(os, "value", this->value() / multiplier);
	os << nl;

	return (os.good());
}


// * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * * //

template<class Type>
void tnbLib::UniformDimensionedField<Type>::operator=
(
	const UniformDimensionedField<Type>& rhs
	)
{
	dimensioned<Type>::operator=(rhs);
}


template<class Type>
void tnbLib::UniformDimensionedField<Type>::operator=
(
	const dimensioned<Type>& rhs
	)
{
	dimensioned<Type>::operator=(rhs);
}


// ************************************************************************* //