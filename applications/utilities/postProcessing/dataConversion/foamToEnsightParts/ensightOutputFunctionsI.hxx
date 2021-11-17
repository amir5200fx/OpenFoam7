#pragma once
template<class Type>
void tnbLib::ensightLagrangianField
(
	const IOobject& fieldObject,
	const fileName& dataDir,
	const fileName& subDir,
	const word& cloudName,
	IOstream::streamFormat format
)
{
	Info << " " << fieldObject.name() << flush;

	fileName cloudDir = subDir / cloud::prefix / cloudName;
	fileName postFileName = cloudDir / fieldObject.name();

	string title =
		postFileName + " with " + pTraits<Type>::typeName + " values";

	ensightFile os(dataDir / postFileName, format);
	os.write(title);
	os.newline();

	IOField<Type> field(fieldObject);

	// 6 values per line
	label count = 0;

	forAll(field, i)
	{
		Type val = field[i];

		if (mag(val) < 1.0e-90)
		{
			val = Zero;
		}

		for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
		{
			os.write(component(val, cmpt));
		}

		count += pTraits<Type>::nComponents;

		if (count % 6 == 0)
		{
			os.newline();
		}
	}

	// add final newline if required
	if (count % 6)
	{
		os.newline();
	}
}


template<class Type>
void tnbLib::ensightVolField
(
	const ensightParts& partsList,
	const IOobject& fieldObject,
	const fvMesh& mesh,
	const fileName& dataDir,
	const fileName& subDir,
	IOstream::streamFormat format
)
{
	Info << " " << fieldObject.name() << flush;

	fileName postFileName = subDir / fieldObject.name();

	ensightFile os(dataDir / postFileName, format);
	os.write(postFileName);
	os.newline();

	// ie, volField<Type>
	partsList.writeField
	(
		os,
		GeometricField<Type, fvPatchField, volMesh>
		(
			fieldObject,
			mesh
			)
	);
}