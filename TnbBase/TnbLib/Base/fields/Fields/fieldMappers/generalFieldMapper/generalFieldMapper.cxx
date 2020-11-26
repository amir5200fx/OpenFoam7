#include <generalFieldMapper.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelUList& tnbLib::generalFieldMapper::directAddressing() const
{
	FatalErrorInFunction
		<< "attempt to access null direct addressing"
		<< abort(FatalError);

	return labelUList::null();
}


const tnbLib::labelListList& tnbLib::generalFieldMapper::addressing() const
{
	FatalErrorInFunction
		<< "attempt to access null interpolation addressing"
		<< abort(FatalError);

	return labelListList::null();
}


const tnbLib::scalarListList& tnbLib::generalFieldMapper::weights() const
{
	FatalErrorInFunction
		<< "attempt to access null interpolation weights"
		<< abort(FatalError);

	return scalarListList::null();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

void tnbLib::generalFieldMapper::operator()
(
	Field<scalar>& f,
	const Field<scalar>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::generalFieldMapper::operator()
(
	Field<vector>& f,
	const Field<vector>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::generalFieldMapper::operator()
(
	Field<sphericalTensor>& f,
	const Field<sphericalTensor>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::generalFieldMapper::operator()
(
	Field<symmTensor>& f,
	const Field<symmTensor>& mapF
	) const
{
	map(f, mapF);
}


void tnbLib::generalFieldMapper::operator()
(
	Field<tensor>& f,
	const Field<tensor>& mapF
	) const
{
	map(f, mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::scalar>> tnbLib::generalFieldMapper::operator()
(
	const Field<scalar>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>> tnbLib::generalFieldMapper::operator()
(
	const Field<vector>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>>
tnbLib::generalFieldMapper::operator()
(
	const Field<sphericalTensor>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>> tnbLib::generalFieldMapper::operator()
(
	const Field<symmTensor>& mapF
	) const
{
	return map(mapF);
}

tnbLib::tmp<tnbLib::Field<tnbLib::tensor>> tnbLib::generalFieldMapper::operator()
(
	const Field<tensor>& mapF
	) const
{
	return map(mapF);
}


// ************************************************************************* //