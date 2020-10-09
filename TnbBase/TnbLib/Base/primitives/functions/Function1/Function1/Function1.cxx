#include <Function1.hxx>

#include <Constant.hxx>

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::label>> 
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<label>>
		(
			new Function1Types::Constant<label>(entryName, is)
			);
}

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::scalar>>
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<scalar>>
		(
			new Function1Types::Constant<scalar>(entryName, is)
			);
}

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::vector>>
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<vector>>
		(
			new Function1Types::Constant<vector>(entryName, is)
			);
}

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::sphericalTensor>>
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<sphericalTensor>>
		(
			new Function1Types::Constant<sphericalTensor>(entryName, is)
			);
}

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::symmTensor>>
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<symmTensor>>
		(
			new Function1Types::Constant<symmTensor>(entryName, is)
			);
}

template<>
tnbLib::autoPtr<tnbLib::Function1<tnbLib::tensor>>
tnbLib::Function1Types::createConstant
(
	const word & entryName,
	Istream & is
)
{
	return autoPtr<Function1<tensor>>
		(
			new Function1Types::Constant<tensor>(entryName, is)
			);
}