#include <profileModelList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::profileModelList::profileModelList
(
	const dictionary& dict,
	const bool readFields
)
	:
	PtrList<profileModel>(),
	dict_(dict)
{
	if (readFields)
	{
		wordList modelNames(dict.toc());

		Info << "    Constructing blade profiles:" << endl;

		if (modelNames.size() > 0)
		{
			this->setSize(modelNames.size());

			forAll(modelNames, i)
			{
				const word& modelName = modelNames[i];

				this->set
				(
					i,
					profileModel::New(dict.subDict(modelName))
				);
			}
		}
		else
		{
			Info << "        none" << endl;
		}
	}
}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::profileModelList::~profileModelList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::profileModelList::connectBlades
(
	const List<word>& names,
	List<label>& addr
) const
{
	// construct the addressing between blade sections and profiles
	forAll(names, bI)
	{
		label index = -1;
		const word& profileName = names[bI];

		forAll(*this, pI)
		{
			const profileModel& pm = this->operator[](pI);

			if (pm.name() == profileName)
			{
				index = pI;
				break;
			}
		}

		if (index == -1)
		{
			List<word> profileNames(size());
			forAll(*this, i)
			{
				const profileModel& pm = this->operator[](i);
				profileNames[i] = pm.name();
			}

			FatalErrorInFunction
				<< "Profile " << profileName << " could not be found "
				<< "in profile list.  Available profiles are"
				<< profileNames << exit(FatalError);
		}
		else
		{
			addr[bI] = index;
		}
	}
}


// ************************************************************************* //