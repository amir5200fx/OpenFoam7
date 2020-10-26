#pragma once
#include <fileOperation.hxx>
#include <DynamicList.hxx>

#include <IStringStream.hxx>  // added by amir

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::csvTableReader<Type>::csvTableReader(const dictionary& dict)
	:
	tableReader<Type>(dict),
	headerLine_(readBool(dict.lookup("hasHeaderLine"))),
	timeColumn_(readLabel(dict.lookup("timeColumn"))),
	componentColumns_(dict.lookup("valueColumns")),
	separator_(dict.lookupOrDefault<string>("separator", string(","))[0])
{
	if (componentColumns_.size() != pTraits<Type>::nComponents)
	{
		FatalErrorInFunction
			<< componentColumns_ << " does not have the expected length "
			<< pTraits<Type>::nComponents << endl
			<< exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::csvTableReader<Type>::~csvTableReader()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

namespace tnbLib
{
	// doesn't recognize specialization otherwise
	template<>
	scalar csvTableReader<scalar>::readValue(const List<string>& split)
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


	template<class Type>
	Type csvTableReader<Type>::readValue(const List<string>& split)
	{
		Type result;

		for (label i = 0; i < pTraits<Type>::nComponents; i++)
		{
			if (componentColumns_[i] >= split.size())
			{
				FatalErrorInFunction
					<< "No column " << componentColumns_[i] << " in "
					<< split << endl
					<< exit(FatalError);
			}

			result[i] = readScalar
			(
				IStringStream(split[componentColumns_[i]])()
			);
		}

		return result;
	}
}


template<class Type>
void tnbLib::csvTableReader<Type>::operator()
(
	const fileName& fName,
	List<Tuple2<scalar, Type>>& data
	)
{
	// IFstream in(fName);
	autoPtr<ISstream> inPtr(fileHandler().NewIFstream(fName));
	ISstream& in = inPtr();

	DynamicList<Tuple2<scalar, Type>> values;

	// Skip header
	if (headerLine_)
	{
		string line;
		in.getLine(line);
	}

	while (in.good())
	{
		string line;
		in.getLine(line);

		DynamicList<string> split;

		std::size_t pos = 0;
		while (pos != std::string::npos)
		{
			std::size_t nPos = line.find(separator_, pos);

			if (nPos == std::string::npos)
			{
				split.append(line.substr(pos));
				pos = nPos;
			}
			else
			{
				split.append(line.substr(pos, nPos - pos));
				pos = nPos + 1;
			}
		}

		if (split.size() <= 1)
		{
			break;
		}

		scalar time = readScalar(IStringStream(split[timeColumn_])());
		Type value = readValue(split);

		values.append(Tuple2<scalar, Type>(time, value));
	}

	data.transfer(values);
}


template<class Type>
void tnbLib::csvTableReader<Type>::operator()
(
	const fileName& fName,
	List<Tuple2<scalar, List<Tuple2<scalar, Type>>>>& data
	)
{
	NotImplemented;
}


template<class Type>
void tnbLib::csvTableReader<Type>::write(Ostream& os) const
{
	tableReader<Type>::write(os);

	writeEntry(os, "hasHeaderLine", headerLine_);
	writeEntry(os, "timeColumn", timeColumn_);

	// Force writing labelList in ascii
	os.writeKeyword("valueColumns");
	if (os.format() == IOstream::BINARY)
	{
		os.format(IOstream::ASCII);
		os << componentColumns_;
		os.format(IOstream::BINARY);
	}
	os << token::END_STATEMENT << nl;

	writeEntry(os, "separator", string(separator_));
}


// ************************************************************************* //