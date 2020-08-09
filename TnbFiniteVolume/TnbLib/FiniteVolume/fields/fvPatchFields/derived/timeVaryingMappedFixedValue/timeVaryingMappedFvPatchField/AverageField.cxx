#include <AverageField.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::AverageField<Type>::AverageField(const label size)
	:
	Field<Type>(size),
	average_(Zero)
{}


template<class Type>
tnbLib::AverageField<Type>::AverageField
(
	const Field<Type>& f,
	const Type& average
)
	:
	Field<Type>(f),
	average_(average)
{}


template<class Type>
tnbLib::AverageField<Type>::AverageField(Istream& is)
	:
	Field<Type>(is),
	average_(pTraits<Type>(is))
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const Type& tnbLib::AverageField<Type>::average() const
{
	return average_;
}


template<class Type>
Type&tnbLib::AverageField<Type>::average()
{
	return average_;
}


template<class Type>
bool tnbLib::AverageField<Type>::writeData(Ostream& os) const
{
	os << static_cast<const Field<Type>&>(*this)
		<< token::NL
		<< average_;

	return os.good();
}


// ************************************************************************* //