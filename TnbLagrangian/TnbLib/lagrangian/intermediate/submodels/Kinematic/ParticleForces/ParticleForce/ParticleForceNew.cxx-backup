#include <ParticleForce.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::autoPtr<tnbLib::ParticleForce<CloudType>>
tnbLib::ParticleForce<CloudType>::New
(
	CloudType& owner,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& name
)
{
	word forceType = name;
	typename dictionaryConstructorTable::iterator cstrIter =
		dictionaryConstructorTablePtr_->find(forceType);

	if (cstrIter == dictionaryConstructorTablePtr_->end() && dict.found("type"))
	{
		forceType = dict.lookupType<word>("type");
		cstrIter = dictionaryConstructorTablePtr_->find(forceType);
	}

	Info << "    Selecting particle force " << forceType << endl;

	if (cstrIter == dictionaryConstructorTablePtr_->end())
	{
		FatalErrorInFunction
			<< "Unknown particle force type "
			<< forceType
			<< ", constructor not in hash table" << nl << nl
			<< "    Valid particle force types are:" << nl
			<< dictionaryConstructorTablePtr_->sortedToc()
			<< exit(FatalError);
	}

	return autoPtr<ParticleForce<CloudType>>
		(
			cstrIter()
			(
				owner,
				mesh,
				dict
				)
			);
}


// ************************************************************************* //