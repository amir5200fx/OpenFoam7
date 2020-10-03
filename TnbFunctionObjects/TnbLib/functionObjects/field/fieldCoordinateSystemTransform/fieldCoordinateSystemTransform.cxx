#include <fieldCoordinateSystemTransform.hxx>

#include <dictionary.hxx>  // added by amir
#include <fvMesh.hxx>  // added by amir
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(fieldCoordinateSystemTransform, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			fieldCoordinateSystemTransform,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldCoordinateSystemTransform::
fieldCoordinateSystemTransform
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	fieldSet_(),
	coordSys_(mesh_, dict.subDict("coordinateSystem"))
{
	read(dict);

	TnbLog << type() << " " << name << ":" << nl
		<< "   Applying transformation from global Cartesian to local "
		<< coordSys_ << nl << endl;
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::fieldCoordinateSystemTransform::
~fieldCoordinateSystemTransform()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::word
tnbLib::functionObjects::fieldCoordinateSystemTransform::transformFieldName
(
	const word& fieldName
) const
{
	return fieldName + ":Transformed";
}


bool tnbLib::functionObjects::fieldCoordinateSystemTransform::read
(
	const dictionary& dict
)
{
	fvMeshFunctionObject::read(dict);

	dict.lookup("fields") >> fieldSet_;

	return true;
}


bool tnbLib::functionObjects::fieldCoordinateSystemTransform::execute()
{
	forAll(fieldSet_, fieldi)
	{
		transform<scalar>(fieldSet_[fieldi]);
		transform<vector>(fieldSet_[fieldi]);
		transform<sphericalTensor>(fieldSet_[fieldi]);
		transform<symmTensor>(fieldSet_[fieldi]);
		transform<tensor>(fieldSet_[fieldi]);
	}

	return true;
}


bool tnbLib::functionObjects::fieldCoordinateSystemTransform::write()
{
	forAll(fieldSet_, fieldi)
	{
		writeObject(transformFieldName(fieldSet_[fieldi]));
	}

	return true;
}


// ************************************************************************* //