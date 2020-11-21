#include <vectorTensorTransform.hxx>

#include <IOstreams.hxx>
#include <OStringStream.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

const char* const tnbLib::vectorTensorTransform::typeName =
"vectorTensorTransform";

const tnbLib::vectorTensorTransform tnbLib::vectorTensorTransform::zero
(
	Zero,
	Zero,
	false
);


const tnbLib::vectorTensorTransform tnbLib::vectorTensorTransform::I
(
	Zero,
	sphericalTensor::I,
	false
);


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::vectorTensorTransform::vectorTensorTransform(Istream& is)
{
	is >> *this;
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::word tnbLib::name(const vectorTensorTransform& s)
{
	OStringStream buf;

	buf << '(' << s.t() << ',' << s.R() << ')';

	return buf.str();
}


template<>
tnbLib::tmp<tnbLib::Field<bool>> tnbLib::vectorTensorTransform::transform
(
	const Field<bool>& fld
) const
{
	return fld;
}
template<>
tnbLib::tmp<tnbLib::Field<tnbLib::label>> tnbLib::vectorTensorTransform::transform
(
	const Field<label>& fld
) const
{
	return fld;
}
template<>
tnbLib::tmp<tnbLib::Field<tnbLib::scalar>> tnbLib::vectorTensorTransform::transform
(
	const Field<scalar>& fld
) const
{
	return fld;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, vectorTensorTransform& tr)
{
	// Read beginning of vectorTensorTransform
	is.readBegin("vectorTensorTransform");

	is >> tr.t_ >> tr.R_ >> tr.hasR_;

	// Read end of vectorTensorTransform
	is.readEnd("vectorTensorTransform");

	// Check state of Istream
	is.check("operator>>(Istream&, vectorTensorTransform&)");

	return is;
}


FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const vectorTensorTransform& tr)
{
	os << token::BEGIN_LIST
		<< tr.t() << token::SPACE << tr.R() << token::SPACE << tr.hasR()
		<< token::END_LIST;

	return os;
}


// ************************************************************************* //