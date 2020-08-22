#include <pairPotentialList.hxx>

#include <OFstream.hxx>
#include <Time.hxx>

#include <fileOperation.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::pairPotentialList::readPairPotentialDict
(
	const List<word>& idList,
	const dictionary& pairPotentialDict,
	const polyMesh& mesh
)
{
	Info << nl << "Building pair potentials." << endl;

	rCutMax_ = 0.0;

	for (label a = 0; a < nIds_; ++a)
	{
		word idA = idList[a];

		for (label b = a; b < nIds_; ++b)
		{
			word idB = idList[b];

			word pairPotentialName;

			if (a == b)
			{
				if (pairPotentialDict.found(idA + "-" + idB))
				{
					pairPotentialName = idA + "-" + idB;
				}
				else
				{
					FatalErrorInFunction
						<< "Pair pairPotential specification subDict "
						<< idA << "-" << idB << " not found"
						<< nl << abort(FatalError);
				}
			}
			else
			{
				if (pairPotentialDict.found(idA + "-" + idB))
				{
					pairPotentialName = idA + "-" + idB;
				}

				else if (pairPotentialDict.found(idB + "-" + idA))
				{
					pairPotentialName = idB + "-" + idA;
				}

				else
				{
					FatalErrorInFunction
						<< "Pair pairPotential specification subDict "
						<< idA << "-" << idB << " or "
						<< idB << "-" << idA << " not found"
						<< nl << abort(FatalError);
				}

				if
					(
						pairPotentialDict.found(idA + "-" + idB)
						&& pairPotentialDict.found(idB + "-" + idA)
						)
				{
					FatalErrorInFunction
						<< "Pair pairPotential specification subDict "
						<< idA << "-" << idB << " and "
						<< idB << "-" << idA << " found multiple definition"
						<< nl << abort(FatalError);
				}
			}

			(*this).set
			(
				pairPotentialIndex(a, b),
				pairPotential::New
				(
					pairPotentialName,
					pairPotentialDict.subDict(pairPotentialName)
				)
			);

			if ((*this)[pairPotentialIndex(a, b)].rCut() > rCutMax_)
			{
				rCutMax_ = (*this)[pairPotentialIndex(a, b)].rCut();
			}

			if ((*this)[pairPotentialIndex(a, b)].writeTables())
			{
				fileHandler().mkDir(mesh.time().path());
				autoPtr<Ostream> ppTabFile
				(
					fileHandler().NewOFstream
					(
						mesh.time().path() / pairPotentialName
					)
				);

				if
					(
						!(*this)[pairPotentialIndex(a, b)].writeEnergyAndForceTables
						(
							ppTabFile()
						)
						)
				{
					FatalErrorInFunction
						<< "Failed writing to "
						<< ppTabFile().name() << nl
						<< abort(FatalError);
				}
			}
		}
	}

	if (!pairPotentialDict.found("electrostatic"))
	{
		FatalErrorInFunction
			<< "Pair pairPotential specification subDict electrostatic"
			<< nl << abort(FatalError);
	}

	electrostaticPotential_ = pairPotential::New
	(
		"electrostatic",
		pairPotentialDict.subDict("electrostatic")
	);

	if (electrostaticPotential_->rCut() > rCutMax_)
	{
		rCutMax_ = electrostaticPotential_->rCut();
	}

	if (electrostaticPotential_->writeTables())
	{
		fileHandler().mkDir(mesh.time().path());
		autoPtr<Ostream> ppTabFile
		(
			fileHandler().NewOFstream
			(
				mesh.time().path() / "electrostatic"
			)
		);

		if (!electrostaticPotential_->writeEnergyAndForceTables(ppTabFile()))
		{
			FatalErrorInFunction
				<< "Failed writing to "
				<< ppTabFile().name() << nl
				<< abort(FatalError);
		}
	}

	rCutMaxSqr_ = rCutMax_ * rCutMax_;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::pairPotentialList::pairPotentialList()
	:
	PtrList<pairPotential>()
{}


tnbLib::pairPotentialList::pairPotentialList
(
	const List<word>& idList,
	const dictionary& pairPotentialDict,
	const polyMesh& mesh
)
	:
	PtrList<pairPotential>()
{
	buildPotentials(idList, pairPotentialDict, mesh);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::pairPotentialList::~pairPotentialList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::pairPotentialList::buildPotentials
(
	const List<word>& idList,
	const dictionary& pairPotentialDict,
	const polyMesh& mesh
)
{
	setSize(((idList.size()*(idList.size() + 1)) / 2));

	nIds_ = idList.size();

	readPairPotentialDict(idList, pairPotentialDict, mesh);
}


const tnbLib::pairPotential& tnbLib::pairPotentialList::pairPotentialFunction
(
	const label a,
	const label b
) const
{
	return (*this)[pairPotentialIndex(a, b)];
}


bool tnbLib::pairPotentialList::rCutMaxSqr(const scalar rIJMagSqr) const
{
	if (rIJMagSqr < rCutMaxSqr_)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool tnbLib::pairPotentialList::rCutSqr
(
	const label a,
	const label b,
	const scalar rIJMagSqr
) const
{
	if (rIJMagSqr < rCutSqr(a, b))
	{
		return true;
	}
	else
	{
		return false;
	}
}


tnbLib::scalar tnbLib::pairPotentialList::rMin
(
	const label a,
	const label b
) const
{
	return (*this)[pairPotentialIndex(a, b)].rMin();
}


tnbLib::scalar tnbLib::pairPotentialList::dr
(
	const label a,
	const label b
) const
{
	return (*this)[pairPotentialIndex(a, b)].dr();
}


tnbLib::scalar tnbLib::pairPotentialList::rCutSqr
(
	const label a,
	const label b
) const
{
	return (*this)[pairPotentialIndex(a, b)].rCutSqr();
}


tnbLib::scalar tnbLib::pairPotentialList::rCut
(
	const label a,
	const label b
) const
{
	return (*this)[pairPotentialIndex(a, b)].rCut();
}


tnbLib::scalar tnbLib::pairPotentialList::force
(
	const label a,
	const label b,
	const scalar rIJMag
) const
{
	scalar f = (*this)[pairPotentialIndex(a, b)].force(rIJMag);

	return f;
}


tnbLib::scalar tnbLib::pairPotentialList::energy
(
	const label a,
	const label b,
	const scalar rIJMag
) const
{
	scalar e = (*this)[pairPotentialIndex(a, b)].energy(rIJMag);

	return e;
}


// ************************************************************************* //