#include <regionModelFunctionObjectList.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModelFunctionObjectList::regionModelFunctionObjectList
(
	regionModel& region
)
	:
	PtrList<regionModelFunctionObject>(),
	regionModel_(region),
	dict_(dictionary::null)
{}


tnbLib::regionModels::regionModelFunctionObjectList::regionModelFunctionObjectList
(
	regionModel& region,
	const dictionary& dict,
	const bool readFields
)
	:
	PtrList<regionModelFunctionObject>(),
	regionModel_(region),
	dict_(dict)
{
	if (readFields)
	{
		wordList modelNames(dict.toc());

		Info << "    Selecting region model functions" << endl;

		if (modelNames.size() > 0)
		{
			this->setSize(modelNames.size());

			forAll(modelNames, i)
			{
				const word& modelName = modelNames[i];

				this->set
				(
					i,
					regionModelFunctionObject::New
					(
						dict,
						region,
						modelName
					)
				);
			}
		}
		else
		{
			Info << "    none" << endl;
		}
	}
}


tnbLib::regionModels::regionModelFunctionObjectList::regionModelFunctionObjectList
(
	const regionModelFunctionObjectList& cfol
)
	:
	PtrList<regionModelFunctionObject>(cfol),
	regionModel_(cfol.regionModel_),
	dict_(cfol.dict_)
{}


// * * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModelFunctionObjectList::
~regionModelFunctionObjectList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionModels::regionModelFunctionObjectList::preEvolveRegion()
{
	forAll(*this, i)
	{
		this->operator[](i).preEvolveRegion();
	}
}


void tnbLib::regionModels::regionModelFunctionObjectList::postEvolveRegion()
{
	forAll(*this, i)
	{
		this->operator[](i).postEvolveRegion();
	}
}


// ************************************************************************* //