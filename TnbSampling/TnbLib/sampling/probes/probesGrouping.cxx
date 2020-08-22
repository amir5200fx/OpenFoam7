#include <probes.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <IOobjectList.hxx>
#include <stringListOps.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::probes::clearFieldGroups()
{
	scalarFields_.clear();
	vectorFields_.clear();
	sphericalTensorFields_.clear();
	symmTensorFields_.clear();
	tensorFields_.clear();

	surfaceScalarFields_.clear();
	surfaceVectorFields_.clear();
	surfaceSphericalTensorFields_.clear();
	surfaceSymmTensorFields_.clear();
	surfaceTensorFields_.clear();
}


tnbLib::label tnbLib::probes::appendFieldGroup
(
	const word& fieldName,
	const word& fieldType
)
{
	if (fieldType == volScalarField::typeName)
	{
		scalarFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == volVectorField::typeName)
	{
		vectorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == volSphericalTensorField::typeName)
	{
		sphericalTensorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == volSymmTensorField::typeName)
	{
		symmTensorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == volTensorField::typeName)
	{
		tensorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == surfaceScalarField::typeName)
	{
		surfaceScalarFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == surfaceVectorField::typeName)
	{
		surfaceVectorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == surfaceSphericalTensorField::typeName)
	{
		surfaceSphericalTensorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == surfaceSymmTensorField::typeName)
	{
		surfaceSymmTensorFields_.append(fieldName);
		return 1;
	}
	else if (fieldType == surfaceTensorField::typeName)
	{
		surfaceTensorFields_.append(fieldName);
		return 1;
	}

	return 0;
}


tnbLib::label tnbLib::probes::classifyFields()
{
	label nFields = 0;
	clearFieldGroups();

	if (loadFromFiles_)
	{
		// check files for a particular time
		IOobjectList objects(mesh_, mesh_.time().timeName());
		wordList allFields = objects.sortedNames();

		labelList indices = findStrings(fieldSelection_, allFields);

		forAll(indices, fieldi)
		{
			const word& fieldName = allFields[indices[fieldi]];

			nFields += appendFieldGroup
			(
				fieldName,
				objects.find(fieldName)()->headerClassName()
			);
		}
	}
	else
	{
		// check currently available fields
		wordList allFields = mesh_.sortedNames();
		labelList indices = findStrings(fieldSelection_, allFields);

		forAll(indices, fieldi)
		{
			const word& fieldName = allFields[indices[fieldi]];

			nFields += appendFieldGroup
			(
				fieldName,
				mesh_.find(fieldName)()->type()
			);
		}
	}

	return nFields;
}

// ************************************************************************* //