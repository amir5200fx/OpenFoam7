#include <lduAddressing.hxx>

#include <demandDrivenData.hxx>
#include <scalarField.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::lduAddressing::calcLosort() const
{
	if (losortPtr_)
	{
		FatalErrorInFunction
			<< "losort already calculated"
			<< abort(FatalError);
	}

	// Scan the neighbour list to find out how many times the cell
	// appears as a neighbour of the face. Done this way to avoid guessing
	// and resizing list
	labelList nNbrOfFace(size(), 0);

	const labelUList& nbr = upperAddr();

	forAll(nbr, nbrI)
	{
		nNbrOfFace[nbr[nbrI]]++;
	}

	// Create temporary neighbour addressing
	labelListList cellNbrFaces(size());

	forAll(cellNbrFaces, celli)
	{
		cellNbrFaces[celli].setSize(nNbrOfFace[celli]);
	}

	// Reset the list of number of neighbours to zero
	nNbrOfFace = 0;

	// Scatter the neighbour faces
	forAll(nbr, nbrI)
	{
		cellNbrFaces[nbr[nbrI]][nNbrOfFace[nbr[nbrI]]] = nbrI;

		nNbrOfFace[nbr[nbrI]]++;
	}

	// Gather the neighbours into the losort array
	losortPtr_ = new labelList(nbr.size(), -1);

	labelList& lst = *losortPtr_;

	// Set counter for losort
	label lstI = 0;

	forAll(cellNbrFaces, celli)
	{
		const labelList& curNbr = cellNbrFaces[celli];

		forAll(curNbr, curNbrI)
		{
			lst[lstI] = curNbr[curNbrI];
			lstI++;
		}
	}
}


void tnbLib::lduAddressing::calcOwnerStart() const
{
	if (ownerStartPtr_)
	{
		FatalErrorInFunction
			<< "owner start already calculated"
			<< abort(FatalError);
	}

	const labelList& own = lowerAddr();

	ownerStartPtr_ = new labelList(size() + 1, own.size());

	labelList& ownStart = *ownerStartPtr_;

	// Set up first lookup by hand
	ownStart[0] = 0;
	label nOwnStart = 0;
	label i = 1;

	forAll(own, facei)
	{
		label curOwn = own[facei];

		if (curOwn > nOwnStart)
		{
			while (i <= curOwn)
			{
				ownStart[i++] = facei;
			}

			nOwnStart = curOwn;
		}
	}
}


void tnbLib::lduAddressing::calcLosortStart() const
{
	if (losortStartPtr_)
	{
		FatalErrorInFunction
			<< "losort start already calculated"
			<< abort(FatalError);
	}

	losortStartPtr_ = new labelList(size() + 1, 0);

	labelList& lsrtStart = *losortStartPtr_;

	const labelList& nbr = upperAddr();

	const labelList& lsrt = losortAddr();

	// Set up first lookup by hand
	lsrtStart[0] = 0;
	label nLsrtStart = 0;
	label i = 0;

	forAll(lsrt, facei)
	{
		// Get neighbour
		const label curNbr = nbr[lsrt[facei]];

		if (curNbr > nLsrtStart)
		{
			while (i <= curNbr)
			{
				lsrtStart[i++] = facei;
			}

			nLsrtStart = curNbr;
		}
	}

	// Set up last lookup by hand
	lsrtStart[size()] = nbr.size();
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::lduAddressing::~lduAddressing()
{
	deleteDemandDrivenData(losortPtr_);
	deleteDemandDrivenData(ownerStartPtr_);
	deleteDemandDrivenData(losortStartPtr_);
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::labelUList& tnbLib::lduAddressing::losortAddr() const
{
	if (!losortPtr_)
	{
		calcLosort();
	}

	return *losortPtr_;
}


const tnbLib::labelUList& tnbLib::lduAddressing::ownerStartAddr() const
{
	if (!ownerStartPtr_)
	{
		calcOwnerStart();
	}

	return *ownerStartPtr_;
}


const tnbLib::labelUList& tnbLib::lduAddressing::losortStartAddr() const
{
	if (!losortStartPtr_)
	{
		calcLosortStart();
	}

	return *losortStartPtr_;
}


tnbLib::label tnbLib::lduAddressing::triIndex(const label a, const label b) const
{
	label own = min(a, b);

	label nbr = max(a, b);

	label startLabel = ownerStartAddr()[own];

	label endLabel = ownerStartAddr()[own + 1];

	const labelUList& neighbour = upperAddr();

	for (label i = startLabel; i < endLabel; i++)
	{
		if (neighbour[i] == nbr)
		{
			return i;
		}
	}

	// If neighbour has not been found, something has gone seriously
	// wrong with the addressing mechanism
	FatalErrorInFunction
		<< "neighbour " << nbr << " not found for owner " << own << ". "
		<< "Problem with addressing"
		<< abort(FatalError);

	return -1;
}


tnbLib::Tuple2<tnbLib::label, tnbLib::scalar> tnbLib::lduAddressing::band() const
{
	const labelUList& owner = lowerAddr();
	const labelUList& neighbour = upperAddr();

	labelList cellBandwidth(size(), 0);

	forAll(neighbour, facei)
	{
		label own = owner[facei];
		label nei = neighbour[facei];

		// Note: mag not necessary for correct (upper-triangular) ordering.
		label diff = nei - own;
		cellBandwidth[nei] = max(cellBandwidth[nei], diff);
	}

	label bandwidth = max(cellBandwidth);

	// Do not use field algebra because of conversion label to scalar
	scalar profile = 0.0;
	forAll(cellBandwidth, celli)
	{
		profile += 1.0*cellBandwidth[celli];
	}

	return Tuple2<label, scalar>(bandwidth, profile);
}


// ************************************************************************* //