#include <flipOp.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<>
tnbLib::scalar tnbLib::flipOp::operator()(const scalar& v) const
{
	return -v;
}


template<> tnbLib::vector tnbLib::flipOp::operator()(const vector& v) const
{
	return -v;
}


template<>tnbLib::sphericalTensor tnbLib::flipOp::operator()
(
	const sphericalTensor& v
	) const
{
	return -v;
}


template<> tnbLib::symmTensor tnbLib::flipOp::operator()
(
	const symmTensor& v
	) const
{
	return -v;
}


template<> tnbLib::tensor tnbLib::flipOp::operator()(const tensor& v) const
{
	return -v;
}


template<> tnbLib::triad tnbLib::flipOp::operator()
(
	const triad& v
	) const
{
	return -v;
}


// ************************************************************************* //