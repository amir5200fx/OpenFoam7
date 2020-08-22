#include <distributedWeightedFvPatchFieldMapper.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelListList&
tnbLib::distributedWeightedFvPatchFieldMapper::addressing() const
{
	return addressing_;
}


const tnbLib::scalarListList&
tnbLib::distributedWeightedFvPatchFieldMapper::weights() const
{
	return weights_;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

tnbLib::tmp<tnbLib::Field<tnbLib::scalar>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const Field<scalar>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::vector>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const Field<vector>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::sphericalTensor>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const Field<sphericalTensor>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::symmTensor>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const Field<symmTensor>& mapF
	) const
{
	return map(mapF);
}


tnbLib::tmp<tnbLib::Field<tnbLib::tensor>>
tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	const Field<tensor>& mapF
	) const
{
	return map(mapF);
}


void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<scalar>& f,
	const Field<scalar>& mapF
	) const
{
	return map(f, mapF);
}


void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<vector>& f,
	const Field<vector>& mapF
	) const
{
	return map(f, mapF);
}


void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<sphericalTensor>& f,
	const Field<sphericalTensor>& mapF
	) const
{
	return map(f, mapF);
}


void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<symmTensor>& f,
	const Field<symmTensor>& mapF
	) const
{
	return map(f, mapF);
}


void tnbLib::distributedWeightedFvPatchFieldMapper::operator()
(
	Field<tensor>& f,
	const Field<tensor>& mapF
	) const
{
	return map(f, mapF);
}


// ************************************************************************* //