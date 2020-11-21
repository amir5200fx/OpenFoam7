#pragma once
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


template<class Type>
Type tnbLib::Function1Types::CSV<Type>::readValue(const List<string>& split)
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

		result[i] =
			readScalar(IStringStream(split[componentColumns_[i]])());
	}

	return result;
}


template<class Type>
void tnbLib::Function1Types::CSV<Type>::read()
{
	fileName expandedFile(fName_);
	autoPtr<ISstream> isPtr(fileHandler().NewIFstream(expandedFile.expand()));
	ISstream& is = isPtr();

	if (!is.good())
	{
		FatalIOErrorInFunction(is)
			<< "Cannot open CSV file for reading."
			<< exit(FatalIOError);
	}

	DynamicList<Tuple2<scalar, Type>> values;

	// Skip header
	for (label i = 0; i < nHeaderLine_; i++)
	{
		string line;
		is.getLine(line);
	}

	const label nEntries = max(refColumn_, max(componentColumns_));

	// Read data
	while (is.good())
	{
		string line;
		is.getLine(line);


		label n = 0;
		std::size_t pos = 0;
		DynamicList<string> split;

		if (mergeSeparators_)
		{
			std::size_t nPos = 0;

			while ((pos != std::string::npos) && (n <= nEntries))
			{
				bool found = false;
				while (!found)
				{
					nPos = line.find(separator_, pos);

					if ((nPos != std::string::npos) && (nPos - pos == 0))
					{
						pos = nPos + 1;
					}
					else
					{
						found = true;
					}
				}

				nPos = line.find(separator_, pos);

				if (nPos == std::string::npos)
				{
					split.append(line.substr(pos));
					pos = nPos;
					n++;
				}
				else
				{
					split.append(line.substr(pos, nPos - pos));
					pos = nPos + 1;
					n++;
				}
			}
		}
		else
		{
			while ((pos != std::string::npos) && (n <= nEntries))
			{
				std::size_t nPos = line.find(separator_, pos);

				if (nPos == std::string::npos)
				{
					split.append(line.substr(pos));
					pos = nPos;
					n++;
				}
				else
				{
					split.append(line.substr(pos, nPos - pos));
					pos = nPos + 1;
					n++;
				}
			}
		}


		if (split.size() <= 1)
		{
			break;
		}

		scalar x = readScalar(IStringStream(split[refColumn_])());
		Type value = readValue(split);

		values.append(Tuple2<scalar, Type>(x, value));
	}

	this->table_.transfer(values);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::CSV<Type>::CSV
(
	const word& entryName,
	const dictionary& dict
)
	:
	TableBase<Type>(entryName, dict),
	nHeaderLine_(readLabel(dict.lookup("nHeaderLine"))),
	refColumn_(readLabel(dict.lookup("refColumn"))),
	componentColumns_(dict.lookup("componentColumns")),
	separator_(dict.lookupOrDefault<string>("separator", string(","))[0]),
	mergeSeparators_(readBool(dict.lookup("mergeSeparators"))),
	fName_(dict.lookup("file"))
{
	if (componentColumns_.size() != pTraits<Type>::nComponents)
	{
		FatalErrorInFunction
			<< componentColumns_ << " does not have the expected length of "
			<< pTraits<Type>::nComponents << endl
			<< exit(FatalError);
	}

	read();

	TableBase<Type>::check();
}


template<class Type>
tnbLib::Function1Types::CSV<Type>::CSV(const CSV<Type>& tbl)
	:
	TableBase<Type>(tbl),
	nHeaderLine_(tbl.nHeaderLine_),
	refColumn_(tbl.refColumn_),
	componentColumns_(tbl.componentColumns_),
	separator_(tbl.separator_),
	mergeSeparators_(tbl.mergeSeparators_),
	fName_(tbl.fName_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::CSV<Type>::~CSV()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
const tnbLib::fileName& tnbLib::Function1Types::CSV<Type>::fName() const
{
	return fName_;
}


template<class Type>
void tnbLib::Function1Types::CSV<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);
	os << token::END_STATEMENT << nl;
	os << indent << word(this->name() + "Coeffs") << nl;
	os << indent << token::BEGIN_BLOCK << incrIndent << nl;

	// Note: for TableBase write the dictionary entries it needs but not
	// the values themselves
	TableBase<Type>::writeEntries(os);

	writeEntry(os, "nHeaderLine", nHeaderLine_);
	writeEntry(os, "refColumn", refColumn_);
	writeEntry(os, "componentColumns", componentColumns_);
	writeEntry(os, "separator", string(separator_));
	writeEntry(os, "mergeSeparators", mergeSeparators_);
	writeEntry(os, "file", fName_);

	os << decrIndent << indent << token::END_BLOCK << endl;
}


// ************************************************************************* //