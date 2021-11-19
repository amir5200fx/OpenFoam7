#include <CSV.hxx>

#include <DynamicList.hxx>

#include <IStringStream.hxx>
#include <fileOperation.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<>
tnbLib::label tnbLib::Function1Types::CSV<tnbLib::label>::readValue
(
	const List<string>& split
)
{
	if (componentColumns_[0] >= split.size())
	{
		FatalErrorInFunction
			<< "No column " << componentColumns_[0] << " in "
			<< split << endl
			<< exit(FatalError);
	}

	return readLabel(IStringStream(split[componentColumns_[0]])());
}


template<>
tnbLib::scalar tnbLib::Function1Types::CSV<tnbLib::scalar>::readValue
(
	const List<string>& split
)
{
	if (componentColumns_[0] >= split.size())
	{
		FatalErrorInFunction
			<< "No column " << componentColumns_[0] << " in "
			<< split << endl
			<< exit(FatalError);
	}

	return readScalar(IStringStream(split[componentColumns_[0]])());
}