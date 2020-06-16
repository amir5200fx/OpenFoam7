#include <setSizeFieldMapper.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::setSizeFieldMapper::setSizeFieldMapper(const label size)
	:
	size_(size)
{}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::setSizeFieldMapper::operator()
(
	Field<scalar>& f,
	const Field<scalar>&
	) const
{
	setSize(f);
}


void tnbLib::setSizeFieldMapper::operator()
(
	Field<vector>& f,
	const Field<vector>&
	) const
{
	setSize(f);
}


void tnbLib::setSizeFieldMapper::operator()
(
	Field<sphericalTensor>& f,
	const Field<sphericalTensor>&
	) const
{
	setSize(f);
}


void tnbLib::setSizeFieldMapper::operator()
(
	Field<symmTensor>& f,
	const Field<symmTensor>&
	) const
{
	setSize(f);
}


void tnbLib::setSizeFieldMapper::operator()
(
	Field<tensor>& f,
	const Field<tensor>&
	) const
{
	setSize(f);
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>> tnbLib::setSizeFieldMapper::operator()
(
	const Field<scalar>&
	) const
{
	return setSize<scalar>();
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>> tnbLib::setSizeFieldMapper::operator()
(
	const Field<vector>&
	) const
{
	return setSize<vector>();
}


tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>>
tnbLib::setSizeFieldMapper::operator()
(
	const Field<sphericalTensor>&
	) const
{
	return setSize<sphericalTensor>();
}


tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>> tnbLib::setSizeFieldMapper::operator()
(
	const Field<symmTensor>&
	) const
{
	return setSize<symmTensor>();
}


tnbLib::tmp<tnbLib::Field<tnbLib::tensor>> tnbLib::setSizeFieldMapper::operator()
(
	const Field<tensor>&
	) const
{
	return setSize<tensor>();
}


// ************************************************************************* //