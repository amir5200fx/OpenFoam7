#pragma once
// * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * * //

template<class Type>
tnbLib::label tnbLib::interpolationLookUpTable<Type>::index
(
	const List<scalar>& indices,
	const bool lastDim
) const
{
	label totalIndex = 0;

	forAll(dim_, i)
	{
		label dim = 1;
		for (int j = i + 1; j < dim_.size(); j++)
		{
			dim *= dim_[j] + 1;
		}

		totalIndex +=
			dim
			* min
			(
				max(label((indices[i] - min_[i]) / delta_[i]), 0),
				dim_[i]
			);
	}

	if (lastDim)
	{
		label iLastdim = dim_.size() - 1;
		totalIndex += tnbLib::min
		(
			max
			(
				label((indices[iLastdim] - min_[iLastdim]) / delta_[iLastdim]),
				0
			),
			dim_[iLastdim]
		);
	}

	return totalIndex;
}


template<class Type>
tnbLib::label tnbLib::interpolationLookUpTable<Type>::index
(
	const scalar indice
) const
{
	label i = 0;
	label totalIndex =
		tnbLib::min
		(
			tnbLib::max
			(
				label((indice - min_[i]) / delta_[i]),
				0
			),
			dim_[i]
		);

	return totalIndex;
}


template<class Type>
bool tnbLib::interpolationLookUpTable<Type>::checkRange
(
	const scalar lookUpValue,
	const label interfield
) const
{
	return lookUpValue >= min_[interfield] && lookUpValue <= max_[interfield];
}


template<class Type>
tnbLib::scalar tnbLib::interpolationLookUpTable<Type>::interpolate
(
	const label lo,
	const label hi,
	const scalar lookUpValue,
	const label ofield,
	const label interfield
) const
{
	if
		(
			List<scalarField>::operator[](interfield).operator[](hi)
			!= List<scalarField>::operator[](interfield).operator[](lo)
			)
	{
		scalar output
		(
			List<scalarField>::operator[](ofield).operator[](lo)
			+ (
				List<scalarField>::operator[](ofield).operator[](hi)
				- List<scalarField>::operator[](ofield).operator[](lo)
				)
			*(
				lookUpValue
				- List<scalarField>::operator[](interfield).operator[](lo)
				)
			/ (
				List<scalarField>::operator[](interfield).operator[](hi)
				- List<scalarField>::operator[](interfield).operator[](lo)
				)
		);
		return output;
	}
	else
	{
		return List<scalarField>::operator[](ofield).operator[](lo);
	}
}


template<class Type>
void tnbLib::interpolationLookUpTable<Type>::dimensionTable()
{
	min_.setSize(entries_.size());
	dim_.setSize(entries_.size());
	delta_.setSize(entries_.size());
	max_.setSize(entries_.size());
	entryIndices_.setSize(entries_.size());
	outputIndices_.setSize(output_.size());
	label index = 0;
	label tableDim = 1;

	forAll(entries_, i)
	{
		dim_[i] = readLabel(entries_[i].lookup("N"));
		max_[i] = readScalar(entries_[i].lookup("max"));
		min_[i] = readScalar(entries_[i].lookup("min"));
		delta_[i] = (max_[i] - min_[i]) / dim_[i];
		tableDim *= dim_[i] + 1;
		fieldIndices_.insert(entries_[i].lookup("name"), index);
		entryIndices_[i] = index;
		index++;
	}

	forAll(output_, i)
	{
		fieldIndices_.insert(output_[i].lookup("name"), index);
		outputIndices_[i] = index;
		index++;
	}

	List<scalarField>& internal = *this;

	internal.setSize(entries_.size() + output_.size());

	interpOutput_.setSize(entries_.size() + output_.size());

	forAll(internal, i)
	{
		internal[i].setSize(tableDim);
	}
}


template<class Type>
void tnbLib::interpolationLookUpTable<Type>::readTable
(
	const word& instance,
	const objectRegistry& obr
)
{
	IOdictionary control
	(
		IOobject
		(
			fileName_,
			instance,
			obr,
			IOobject::MUST_READ_IF_MODIFIED,
			IOobject::NO_WRITE
		)
	);

	control.lookup("fields") >> entries_;
	control.lookup("output") >> output_;
	control.lookup("values") >> *this;

	dimensionTable();

	check();

	if (this->size() == 0)
	{
		FatalErrorInFunction
			<< "table is empty" << nl << exit(FatalError);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::interpolationLookUpTable<Type>::interpolationLookUpTable()
	:
	List<scalarField>(),
	fileName_("fileNameIsUndefined")
{}


template<class Type>
tnbLib::interpolationLookUpTable<Type>::interpolationLookUpTable
(
	const fileName& fn,
	const word& instance,
	const objectRegistry& obr
)
	:
	List<scalarField>(),
	fileName_(fn),
	dim_(0),
	min_(0),
	delta_(0.0),
	max_(0.0),
	entries_(0),
	output_(0),
	entryIndices_(0),
	outputIndices_(0),
	interpOutput_(0)
{
	readTable(instance, obr);
}


template<class Type>
tnbLib::interpolationLookUpTable<Type>::interpolationLookUpTable
(
	const interpolationLookUpTable& interpTable
)
	:
	List<scalarField>(interpTable),
	fileName_(interpTable.fileName_),
	entryIndices_(interpTable.entryIndices_),
	outputIndices_(interpTable.outputIndices_),
	dim_(interpTable.dim_),
	min_(interpTable.min_),
	delta_(interpTable.delta_),
	max_(interpTable.max_),
	entries_(0),
	output_(0),
	interpOutput_(interpTable.interpOutput_)
{}


template<class Type>
tnbLib::interpolationLookUpTable<Type>::interpolationLookUpTable
(
	const dictionary& dict
)
	:
	List<scalarField>(),
	fileName_(fileName(dict.lookup("file")).expand()),
	dim_(0),
	min_(0.0),
	delta_(0.0),
	max_(0.0),
	entries_(dict.lookup("fields")),
	output_(dict.lookup("output")),
	entryIndices_(0),
	outputIndices_(0),
	fieldIndices_(0),
	interpOutput_(0)
{
	dimensionTable();
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
void tnbLib::interpolationLookUpTable<Type>::check() const
{
	// check order in the first dimension.
	scalar prevValue = List<scalarField>::operator[](0).operator[](0);
	label dim = 1;
	for (int j = 1; j < dim_.size(); j++)
	{
		dim *= dim_[j] + 1;
	}

	for (label i = 1; i < dim_[0]; i++)
	{
		label index = i * dim;
		const scalar currValue =
			List<scalarField>::operator[](0).operator[](index);

		// avoid duplicate values (divide-by-zero error)
		if (currValue <= prevValue)
		{
			FatalErrorInFunction
				<< "out-of-order value: " << currValue
				<< " at index " << index << nl << exit(FatalError);
		}
		prevValue = currValue;
	}
}


template<class Type>
void tnbLib::interpolationLookUpTable<Type>::write
(
	Ostream& os,
	const fileName& fn,
	const word& instance,
	const objectRegistry& obr
) const
{
	IOdictionary control
	(
		IOobject
		(
			fn,
			instance,
			obr,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		)
	);

	control.writeHeader(os);

	writeEntry(os, "fields", entries_);

	writeEntry(os, "output", output_);

	if (this->size() == 0)
	{
		FatalErrorInFunction
			<< "table is empty" << nl << exit(FatalError);
	}
	writeEntry(os, "values", *this);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

template<class Type>
tnbLib::scalarField&
tnbLib::interpolationLookUpTable<Type>::operator[](const label i)
{
	const label n = this->size();

	if (n <= 1)
	{
		FatalErrorInFunction
			<< "table has (" << n << ") columns" << nl << exit(FatalError);
	}
	else if (i < 0)
	{
		FatalErrorInFunction
			<< "index (" << i << ") underflow" << nl << exit(FatalError);
	}
	else if (i >= n)
	{
		FatalErrorInFunction
			<< "index (" << i << ") overflow" << nl << exit(FatalError);
	}

	return List<scalarField>::operator[](i);
}


template<class Type>
const tnbLib::scalarField&
tnbLib::interpolationLookUpTable<Type>::operator[](const label i) const
{
	const label n = this->size();

	if (n <= 1)
	{
		FatalErrorInFunction
			<< "table has (" << n << ") columns" << nl << exit(FatalError);
	}
	else if (i < 0)
	{
		FatalErrorInFunction
			<< "index (" << i << ") underflow" << nl << exit(FatalError);
	}
	else if (i >= n)
	{
		FatalErrorInFunction
			<< "index (" << i << ") overflow" << nl
			<< exit(FatalError);
	}

	return List<scalarField>::operator[](i);
}


template<class Type>
bool tnbLib::interpolationLookUpTable<Type>::found(const word& fieldName) const
{
	return fieldIndices_.found(fieldName);
}


template<class Type>
const tnbLib::scalarList&
tnbLib::interpolationLookUpTable<Type>::lookUp(const scalar retvals)
{
	const label lo = index(retvals);
	findHi(lo, retvals);
	return interpOutput_;
}


template<class Type>
void tnbLib::interpolationLookUpTable<Type>::findHi
(
	const label lo,
	const scalar retvals
)
{
	forAll(outputIndices_, j)
	{
		scalar tmp = 0;
		label ofield = outputIndices_[j];
		scalar baseValue = List<scalarField>::operator[](ofield).operator[](lo);

		forAll(entryIndices_, i)
		{
			if (checkRange(retvals, entryIndices_[i]))
			{
				label dim = 1;

				label hi = tnbLib::min(lo + dim, (*this)[0].size() - 1);

				tmp += interpolate(lo, hi, retvals, ofield, entryIndices_[i])
					- baseValue;
			}
			interpOutput_[entryIndices_[i]] = retvals;
		}

		tmp += baseValue;
		interpOutput_[outputIndices_[j]] = tmp;
	}
}


// ************************************************************************* //