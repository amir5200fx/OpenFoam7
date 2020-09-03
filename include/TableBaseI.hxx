#pragma once
#include <Time.hxx>
#include <interpolationWeights.hxx>

// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

template<class Type>
const tnbLib::interpolationWeights&
tnbLib::Function1Types::TableBase<Type>::interpolator() const
{
	if (interpolatorPtr_.empty())
	{
		// Re-work table into linear list
		tableSamplesPtr_.reset(new scalarField(table_.size()));
		scalarField& tableSamples = tableSamplesPtr_();
		forAll(table_, i)
		{
			tableSamples[i] = table_[i].first();
		}
		interpolatorPtr_ = interpolationWeights::New
		(
			interpolationScheme_,
			tableSamples
		);
	}

	return interpolatorPtr_();
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::TableBase<Type>::TableBase
(
	const word& name,
	const dictionary& dict
)
	:
	Function1<Type>(name),
	name_(name),
	boundsHandling_
	(
		wordToBoundsHandling
		(
			dict.lookupOrDefault<word>("outOfBounds", "clamp")
		)
	),
	interpolationScheme_
	(
		dict.lookupOrDefault<word>("interpolationScheme", "linear")
	),
	table_()
{}


template<class Type>
tnbLib::Function1Types::TableBase<Type>::TableBase(const TableBase<Type>& tbl)
	:
	Function1<Type>(tbl),
	name_(tbl.name_),
	boundsHandling_(tbl.boundsHandling_),
	interpolationScheme_(tbl.interpolationScheme_),
	table_(tbl.table_),
	tableSamplesPtr_(tbl.tableSamplesPtr_),
	interpolatorPtr_(tbl.interpolatorPtr_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::Function1Types::TableBase<Type>::~TableBase()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::word tnbLib::Function1Types::TableBase<Type>::boundsHandlingToWord
(
	const boundsHandling& bound
) const
{
	word enumName("warn");

	switch (bound)
	{
	case ERROR:
	{
		enumName = "error";
		break;
	}
	case WARN:
	{
		enumName = "warn";
		break;
	}
	case CLAMP:
	{
		enumName = "clamp";
		break;
	}
	case REPEAT:
	{
		enumName = "repeat";
		break;
	}
	}

	return enumName;
}


template<class Type>
typename tnbLib::Function1Types::TableBase<Type>::boundsHandling
tnbLib::Function1Types::TableBase<Type>::wordToBoundsHandling
(
	const word& bound
) const
{
	if (bound == "error")
	{
		return ERROR;
	}
	else if (bound == "warn")
	{
		return WARN;
	}
	else if (bound == "clamp")
	{
		return CLAMP;
	}
	else if (bound == "repeat")
	{
		return REPEAT;
	}
	else
	{
		WarningInFunction
			<< "bad outOfBounds specifier " << bound << " using 'warn'"
			<< endl;

		return WARN;
	}
}


template<class Type>
typename tnbLib::Function1Types::TableBase<Type>::boundsHandling
tnbLib::Function1Types::TableBase<Type>::outOfBounds
(
	const boundsHandling& bound
)
{
	boundsHandling prev = boundsHandling_;
	boundsHandling_ = bound;

	return prev;
}


template<class Type>
void tnbLib::Function1Types::TableBase<Type>::check() const
{
	if (!table_.size())
	{
		FatalErrorInFunction
			<< "Table for entry " << this->name_ << " is invalid (empty)"
			<< nl << exit(FatalError);
	}

	label n = table_.size();
	scalar prevValue = table_[0].first();

	for (label i = 1; i < n; ++i)
	{
		const scalar currValue = table_[i].first();

		// avoid duplicate values (divide-by-zero error)
		if (currValue <= prevValue)
		{
			FatalErrorInFunction
				<< "out-of-order value: " << currValue << " at index " << i
				<< exit(FatalError);
		}
		prevValue = currValue;
	}
}


template<class Type>
bool tnbLib::Function1Types::TableBase<Type>::checkMinBounds
(
	const scalar x,
	scalar& xDash
) const
{
	if (x < table_[0].first())
	{
		switch (boundsHandling_)
		{
		case ERROR:
		{
			FatalErrorInFunction
				<< "value (" << x << ") underflow"
				<< exit(FatalError);
			break;
		}
		case WARN:
		{
			WarningInFunction
				<< "value (" << x << ") underflow" << nl
				<< endl;

			// fall-through to 'CLAMP'
			[[fallthrough]];
		}
		case CLAMP:
		{
			xDash = table_[0].first();
			return true;
			break;
		}
		case REPEAT:
		{
			// adjust x to >= minX
			scalar span = table_.last().first() - table_[0].first();
			xDash = fmod(x - table_[0].first(), span) + table_[0].first();
			break;
		}
		}
	}
	else
	{
		xDash = x;
	}

	return false;
}


template<class Type>
bool tnbLib::Function1Types::TableBase<Type>::checkMaxBounds
(
	const scalar x,
	scalar& xDash
) const
{
	if (x > table_.last().first())
	{
		switch (boundsHandling_)
		{
		case ERROR:
		{
			FatalErrorInFunction
				<< "value (" << x << ") overflow"
				<< exit(FatalError);
			break;
		}
		case WARN:
		{
			WarningInFunction
				<< "value (" << x << ") overflow" << nl
				<< endl;

			// fall-through to 'CLAMP'
			[[fallthrough]];
		}
		case CLAMP:
		{
			xDash = table_.last().first();
			return true;
			break;
		}
		case REPEAT:
		{
			// adjust x to >= minX
			scalar span = table_.last().first() - table_[0].first();
			xDash = fmod(x - table_[0].first(), span) + table_[0].first();
			break;
		}
		}
	}
	else
	{
		xDash = x;
	}

	return false;
}


template<class Type>
void tnbLib::Function1Types::TableBase<Type>::convertTimeBase(const Time& t)
{
	forAll(table_, i)
	{
		scalar value = table_[i].first();
		table_[i].first() = t.userTimeToTime(value);
	}

	tableSamplesPtr_.clear();
	interpolatorPtr_.clear();
}


template<class Type>
Type tnbLib::Function1Types::TableBase<Type>::value(const scalar x) const
{
	scalar xDash = x;

	if (checkMinBounds(x, xDash))
	{
		return table_[0].second();
	}

	if (checkMaxBounds(xDash, xDash))
	{
		return table_.last().second();
	}

	// Use interpolator
	interpolator().valueWeights(xDash, currentIndices_, currentWeights_);

	Type t = currentWeights_[0] * table_[currentIndices_[0]].second();
	for (label i = 1; i < currentIndices_.size(); i++)
	{
		t += currentWeights_[i] * table_[currentIndices_[i]].second();
	}

	return t;
}


template<class Type>
Type tnbLib::Function1Types::TableBase<Type>::integrate
(
	const scalar x1,
	const scalar x2
) const
{
	// Use interpolator
	interpolator().integrationWeights(x1, x2, currentIndices_, currentWeights_);

	Type sum = currentWeights_[0] * table_[currentIndices_[0]].second();
	for (label i = 1; i < currentIndices_.size(); i++)
	{
		sum += currentWeights_[i] * table_[currentIndices_[i]].second();
	}

	return sum;
}


template<class Type>
tnbLib::tmp<tnbLib::scalarField> tnbLib::Function1Types::TableBase<Type>::x() const
{
	tmp<scalarField> tfld(new scalarField(table_.size(), 0.0));
	scalarField& fld = tfld.ref();

	forAll(table_, i)
	{
		fld[i] = table_[i].first();
	}

	return tfld;
}


template<class Type>
tnbLib::tmp<tnbLib::Field<Type>> tnbLib::Function1Types::TableBase<Type>::y() const
{
	tmp<Field<Type>> tfld(new Field<Type>(table_.size(), Zero));
	Field<Type>& fld = tfld.ref();

	forAll(table_, i)
	{
		fld[i] = table_[i].second();
	}

	return tfld;
}


template<class Type>
void tnbLib::Function1Types::TableBase<Type>::writeEntries(Ostream& os) const
{
	if (boundsHandling_ != CLAMP)
	{
		writeEntry(os, "outOfBounds", boundsHandlingToWord(boundsHandling_));
	}
	if (interpolationScheme_ != "linear")
	{
		writeEntry(os, "interpolationScheme", interpolationScheme_);
	}
}


template<class Type>
void tnbLib::Function1Types::TableBase<Type>::writeData(Ostream& os) const
{
	Function1<Type>::writeData(os);
	os << nl << indent << table_ << token::END_STATEMENT << nl;
	writeEntries(os);
}


// ************************************************************************* //