#include <directFieldMapper.hxx>

// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::directFieldMapper::operator()
(
	Field<scalar>& f,
	const Field<scalar>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::directFieldMapper::operator()
(
	Field<vector>& f,
	const Field<vector>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::directFieldMapper::operator()
(
	Field<sphericalTensor>& f,
	const Field<sphericalTensor>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::directFieldMapper::operator()
(
	Field<symmTensor>& f,
	const Field<symmTensor>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::directFieldMapper::operator()
(
	Field<tensor>& f,
	const Field<tensor>& mapF
	) const
{
	map(f, mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>> tnbLib::directFieldMapper::operator()
(
	const Field<scalar>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>> tnbLib::directFieldMapper::operator()
(
	const Field<vector>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>>
tnbLib::directFieldMapper::operator()
(
	const Field<sphericalTensor>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>> tnbLib::directFieldMapper::operator()
(
	const Field<symmTensor>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::tensor>> tnbLib::directFieldMapper::operator()
(
	const Field<tensor>& mapF
	) const
{
	return map(mapF);
}


// ************************************************************************* //