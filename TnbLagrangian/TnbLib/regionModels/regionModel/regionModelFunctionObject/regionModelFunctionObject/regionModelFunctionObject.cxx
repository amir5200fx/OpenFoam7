#include <regionModelFunctionObject.hxx>

#include <regionModel.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		defineTypeNameAndDebug(regionModelFunctionObject, 0);
		defineRunTimeSelectionTable(regionModelFunctionObject, dictionary);
	}
}

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModelFunctionObject::regionModelFunctionObject
(
	regionModel& region
)
	:
	dict_(dictionary::null),
	regionModel_(region),
	modelType_("modelType")
{}


tnbLib::regionModels::regionModelFunctionObject::regionModelFunctionObject
(
	const dictionary& dict,
	regionModel& region,
	const word& type
)
	:
	dict_(dict),
	regionModel_(region),
	modelType_(type)
{}


tnbLib::regionModels::regionModelFunctionObject::regionModelFunctionObject
(
	const regionModelFunctionObject& rmfo
)
	:
	dict_(rmfo.dict_),
	regionModel_(rmfo.regionModel_),
	modelType_(rmfo.modelType_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionModels::regionModelFunctionObject::~regionModelFunctionObject()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::regionModels::regionModelFunctionObject::preEvolveRegion()
{}


void tnbLib::regionModels::regionModelFunctionObject::postEvolveRegion()
{
	if (regionModel_.regionMesh().time().writeTime())
	{
		write();
	}
}


void tnbLib::regionModels::regionModelFunctionObject::write() const
{}


// ************************************************************************* //