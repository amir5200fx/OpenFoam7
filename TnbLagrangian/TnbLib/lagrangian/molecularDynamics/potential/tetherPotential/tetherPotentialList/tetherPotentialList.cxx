#include <tetherPotentialList.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::tetherPotentialList::readTetherPotentialDict
(
	const List<word>& siteIdList,
	const dictionary& tetherPotentialDict,
	const List<word>& tetherSiteIdList
)
{

	Info << nl << "Building tether potentials." << endl;

	idMap_ = List<label>(siteIdList.size(), -1);

	label tetherMapIndex = 0;

	forAll(tetherSiteIdList, t)
	{
		word tetherPotentialName = tetherSiteIdList[t];

		label tetherId = findIndex(siteIdList, tetherPotentialName);

		if (tetherId == -1)
		{
			FatalErrorInFunction
				<< nl
				<< "No matching entry found in siteIdList for tether name "
				<< tetherPotentialName
				<< abort(FatalError);
		}
		else if (!tetherPotentialDict.found(tetherPotentialName))
		{
			FatalErrorInFunction
				<< nl << "tether potential specification subDict "
				<< tetherPotentialName << " not found"
				<< abort(FatalError);
		}
		else
		{
			this->set
			(
				tetherMapIndex,
				tetherPotential::New
				(
					tetherPotentialName,
					tetherPotentialDict.subDict(tetherPotentialName)
				)
			);
		}

		idMap_[tetherId] = tetherMapIndex;

		tetherMapIndex++;
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::tetherPotentialList::tetherPotentialList()
	:
	PtrList<tetherPotential>(),
	idMap_()
{}


tnbLib::tetherPotentialList::tetherPotentialList
(
	const List<word>& siteIdList,
	const dictionary& tetherPotentialDict,
	const List<word>& tetherSiteIdList
)
	:
	PtrList<tetherPotential>(),
	idMap_()
{
	buildPotentials(siteIdList, tetherPotentialDict, tetherSiteIdList);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::tetherPotentialList::~tetherPotentialList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::tetherPotentialList::buildPotentials
(
	const List<word>& siteIdList,
	const dictionary& tetherPotentialDict,
	const List<word>& tetherSiteIdList
)
{
	setSize(tetherSiteIdList.size());

	readTetherPotentialDict(siteIdList, tetherPotentialDict, tetherSiteIdList);
}


const tnbLib::tetherPotential& tnbLib::tetherPotentialList::tetherPotentialFunction
(
	const label a
) const
{
	return (*this)[tetherPotentialIndex(a)];
}


tnbLib::vector tnbLib::tetherPotentialList::force
(
	const label a,
	const vector rIT
) const
{
	return (*this)[tetherPotentialIndex(a)].force(rIT);
}


tnbLib::scalar tnbLib::tetherPotentialList::energy
(
	const label a,
	const vector rIT
) const
{
	return (*this)[tetherPotentialIndex(a)].energy(rIT);
}


// ************************************************************************* //