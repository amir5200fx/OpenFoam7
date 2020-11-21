#include <mapDistribute.hxx>

#include <globalIndexAndTransform.hxx>
#include <transformField.hxx>

#include <EdgeMap.hxx> // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(mapDistribute, 0);
}

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<>
void tnbLib::mapDistribute::transform::operator()
(
	const vectorTensorTransform&,
	const bool,
	List<label>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	UList<label>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	Map<label>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	EdgeMap<label>&
	) const
{}


template<>
void tnbLib::mapDistribute::transform::operator()
(
	const vectorTensorTransform&,
	const bool,
	List<scalar>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	UList<scalar>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	Map<scalar>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	EdgeMap<scalar>&
	) const
{}


template<>
void tnbLib::mapDistribute::transform::operator()
(
	const vectorTensorTransform&,
	const bool,
	List<bool>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	UList<bool>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	Map<bool>&
	) const
{}
template<>
void tnbLib::mapDistribute::transform::operator()
(
	const coupledPolyPatch&,
	EdgeMap<bool>&
	) const
{}


void tnbLib::mapDistribute::printLayout(Ostream& os) const
{
	mapDistributeBase::printLayout(os);

	forAll(transformElements_, trafoI)
	{
		if (transformElements_[trafoI].size() > 0)
		{
			os << "transform " << trafoI << ':' << endl
				<< "    start : " << transformStart_[trafoI] << endl
				<< "    size  : " << transformElements_[trafoI].size() << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::mapDistribute::mapDistribute()
	:
	mapDistributeBase()
{}


tnbLib::mapDistribute::mapDistribute
(
	const label constructSize,
	labelListList&& subMap,
	labelListList&& constructMap,
	const bool subHasFlip,
	const bool constructHasFlip
)
	:
	mapDistributeBase
	(
		constructSize,
		move(subMap),
		move(constructMap),
		subHasFlip,
		constructHasFlip
	)
{}


tnbLib::mapDistribute::mapDistribute
(
	const label constructSize,
	labelListList&& subMap,
	labelListList&& constructMap,
	labelListList&& transformElements,
	labelList&& transformStart,
	const bool subHasFlip,
	const bool constructHasFlip
)
	:
	mapDistributeBase
	(
		constructSize,
		move(subMap),
		move(constructMap),
		subHasFlip,
		constructHasFlip
	),
	transformElements_(move(transformElements)),
	transformStart_(move(transformStart))
{}


tnbLib::mapDistribute::mapDistribute
(
	const labelList& sendProcs,
	const labelList& recvProcs
)
	:
	mapDistributeBase(sendProcs, recvProcs)
{}


tnbLib::mapDistribute::mapDistribute
(
	const globalIndex& globalNumbering,
	labelList& elements,
	List<Map<label>>& compactMap,
	const int tag
)
	:
	mapDistributeBase
	(
		globalNumbering,
		elements,
		compactMap,
		tag
	)
{}


tnbLib::mapDistribute::mapDistribute
(
	const globalIndex& globalNumbering,
	labelListList& cellCells,
	List<Map<label>>& compactMap,
	const int tag
)
	:
	mapDistributeBase
	(
		globalNumbering,
		cellCells,
		compactMap,
		tag
	)
{}


tnbLib::mapDistribute::mapDistribute
(
	const globalIndex& globalNumbering,
	labelList& elements,
	const globalIndexAndTransform& globalTransforms,
	const labelPairList& transformedElements,
	labelList& transformedIndices,
	List<Map<label>>& compactMap,
	const int tag
)
	:
	mapDistributeBase()
{
	// Construct per processor compact addressing of the global elements
	// needed. The ones from the local processor are not included since
	// these are always all needed.
	calcCompactAddressing
	(
		globalNumbering,
		elements,
		compactMap
	);

	// Add all (non-local) transformed elements needed.
	forAll(transformedElements, i)
	{
		labelPair elem = transformedElements[i];
		label proci = globalTransforms.processor(elem);
		if (proci != Pstream::myProcNo())
		{
			label index = globalTransforms.index(elem);
			label nCompact = compactMap[proci].size();
			compactMap[proci].insert(index, nCompact);
		}
	}


	// Exchange what I need with processor that supplies it. Renumber elements
	// into compact numbering
	labelList compactStart;
	exchangeAddressing
	(
		tag,
		globalNumbering,
		elements,
		compactMap,
		compactStart
	);


	// Renumber the transformed elements
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Count per transformIndex
	label nTrafo = globalTransforms.transformPermutations().size();
	labelList nPerTransform(nTrafo, 0);
	forAll(transformedElements, i)
	{
		labelPair elem = transformedElements[i];
		label trafoI = globalTransforms.transformIndex(elem);
		nPerTransform[trafoI]++;
	}
	// Offset per transformIndex
	transformStart_.setSize(nTrafo);
	transformElements_.setSize(nTrafo);
	forAll(transformStart_, trafoI)
	{
		transformStart_[trafoI] = constructSize_;
		constructSize_ += nPerTransform[trafoI];
		transformElements_[trafoI].setSize(nPerTransform[trafoI]);
	}

	// Sort transformed elements into their new slot.
	nPerTransform = 0;

	transformedIndices.setSize(transformedElements.size());
	forAll(transformedElements, i)
	{
		labelPair elem = transformedElements[i];
		label proci = globalTransforms.processor(elem);
		label index = globalTransforms.index(elem);
		label trafoI = globalTransforms.transformIndex(elem);

		// Get compact index for untransformed element
		label rawElemI =
			(
				proci == Pstream::myProcNo()
				? index
				: compactMap[proci][index]
				);

		label& n = nPerTransform[trafoI];
		// index of element to transform
		transformElements_[trafoI][n] = rawElemI;
		// destination of transformed element
		transformedIndices[i] = transformStart_[trafoI] + n;
		n++;
	}

	if (debug)
	{
		printLayout(Pout);
	}
}


tnbLib::mapDistribute::mapDistribute
(
	const globalIndex& globalNumbering,
	labelListList& cellCells,
	const globalIndexAndTransform& globalTransforms,
	const List<labelPairList>& transformedElements,
	labelListList& transformedIndices,
	List<Map<label>>& compactMap,
	const int tag
)
	:
	mapDistributeBase()
{
	// Construct per processor compact addressing of the global elements
	// needed. The ones from the local processor are not included since
	// these are always all needed.
	calcCompactAddressing
	(
		globalNumbering,
		cellCells,
		compactMap
	);

	// Add all (non-local) transformed elements needed.
	forAll(transformedElements, celli)
	{
		const labelPairList& elems = transformedElements[celli];

		forAll(elems, i)
		{
			label proci = globalTransforms.processor(elems[i]);
			if (proci != Pstream::myProcNo())
			{
				label index = globalTransforms.index(elems[i]);
				label nCompact = compactMap[proci].size();
				compactMap[proci].insert(index, nCompact);
			}
		}
	}


	// Exchange what I need with processor that supplies it. Renumber elements
	// into compact numbering
	labelList compactStart;
	exchangeAddressing
	(
		tag,
		globalNumbering,
		cellCells,
		compactMap,
		compactStart
	);


	// Renumber the transformed elements
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// Count per transformIndex
	label nTrafo = globalTransforms.transformPermutations().size();
	labelList nPerTransform(nTrafo, 0);
	forAll(transformedElements, celli)
	{
		const labelPairList& elems = transformedElements[celli];

		forAll(elems, i)
		{
			label trafoI = globalTransforms.transformIndex(elems[i]);
			nPerTransform[trafoI]++;
		}
	}
	// Offset per transformIndex
	transformStart_.setSize(nTrafo);
	transformElements_.setSize(nTrafo);
	forAll(transformStart_, trafoI)
	{
		transformStart_[trafoI] = constructSize_;
		constructSize_ += nPerTransform[trafoI];
		transformElements_[trafoI].setSize(nPerTransform[trafoI]);
	}

	// Sort transformed elements into their new slot.
	nPerTransform = 0;

	transformedIndices.setSize(transformedElements.size());
	forAll(transformedElements, celli)
	{
		const labelPairList& elems = transformedElements[celli];
		transformedIndices[celli].setSize(elems.size());

		forAll(elems, i)
		{
			label proci = globalTransforms.processor(elems[i]);
			label index = globalTransforms.index(elems[i]);
			label trafoI = globalTransforms.transformIndex(elems[i]);

			// Get compact index for untransformed element
			label rawElemI =
				(
					proci == Pstream::myProcNo()
					? index
					: compactMap[proci][index]
					);

			label& n = nPerTransform[trafoI];
			// index of element to transform
			transformElements_[trafoI][n] = rawElemI;
			// destination of transformed element
			transformedIndices[celli][i] = transformStart_[trafoI] + n;
			n++;
		}
	}

	if (debug)
	{
		printLayout(Pout);
	}
}


tnbLib::mapDistribute::mapDistribute(const mapDistribute& map)
	:
	mapDistributeBase(map),
	transformElements_(map.transformElements_),
	transformStart_(map.transformStart_)
{}


tnbLib::mapDistribute::mapDistribute(mapDistribute&& map)
	:
	mapDistributeBase(move(map)),
	transformElements_(move(map.transformElements_)),
	transformStart_(move(map.transformStart_))
{}


tnbLib::mapDistribute::mapDistribute(Istream& is)
{
	is >> *this;
}


tnbLib::autoPtr<tnbLib::mapDistribute> tnbLib::mapDistribute::clone() const
{
	return autoPtr<mapDistribute>(new mapDistribute(*this));
}


// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

tnbLib::label tnbLib::mapDistribute::whichTransform(const label index)
const
{
	return findLower(transformStart_, index + 1);
}


void tnbLib::mapDistribute::transfer(mapDistribute& rhs)
{
	mapDistributeBase::transfer(rhs);
	transformElements_.transfer(rhs.transformElements_);
	transformStart_.transfer(rhs.transformStart_);
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

FoamBase_EXPORT void tnbLib::mapDistribute::operator=(const mapDistribute& rhs)
{
	// Check for assignment to self
	if (this == &rhs)
	{
		FatalErrorInFunction
			<< "Attempted assignment to self"
			<< abort(FatalError);
	}
	mapDistributeBase::operator=(rhs);
	transformElements_ = rhs.transformElements_;
	transformStart_ = rhs.transformStart_;
}


// * * * * * * * * * * * * * * Istream Operator  * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Istream& tnbLib::operator>>(Istream& is, mapDistribute& map)
{
	is.fatalCheck("operator>>(Istream&, mapDistribute&)");

	is >> static_cast<mapDistributeBase&>(map)
		>> map.transformElements_ >> map.transformStart_;

	return is;
}


// * * * * * * * * * * * * * * Ostream Operator  * * * * * * * * * * * * * * //

FoamBase_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const mapDistribute& map)
{
	os << static_cast<const mapDistributeBase&>(map) << token::NL
		<< map.transformElements_ << token::NL
		<< map.transformStart_;

	return os;
}


// ************************************************************************* //