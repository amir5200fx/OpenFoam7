#include <fieldAverage.hxx>

#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <OFstream.hxx>

#include <fieldAverageItem.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::functionObjects::fieldAverage::addMeanFieldType(const label fieldi)
{
	const word& fieldName = faItems_[fieldi].fieldName();
	const word& meanFieldName = faItems_[fieldi].meanFieldName();

	TnbLog << "    Reading/initialising field " << meanFieldName << endl;

	if (obr_.foundObject<Type>(meanFieldName))
	{
	}
	else if (obr_.found(meanFieldName))
	{
		TnbLog << "    Cannot allocate average field " << meanFieldName
			<< " since an object with that name already exists."
			<< " Disabling averaging for field." << endl;

		faItems_[fieldi].mean() = false;
	}
	else
	{
		const Type& baseField = obr_.lookupObject<Type>(fieldName);

		// Store on registry
		obr_.store
		(
			new Type
			(
				IOobject
				(
					meanFieldName,
					obr_.time().timeName(obr_.time().startTime().value()),
					obr_,
					restartOnOutput_
					? IOobject::NO_READ
					: IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				1 * baseField
			)
		);
	}
}


template<class Type>
void tnbLib::functionObjects::fieldAverage::addMeanField(const label fieldi)
{
	if (faItems_[fieldi].mean())
	{
		typedef GeometricField<Type, fvPatchField, volMesh>
			VolFieldType;

		typedef GeometricField<Type, fvsPatchField, surfaceMesh>
			SurfaceFieldType;

		const word& fieldName = faItems_[fieldi].fieldName();

		if (obr_.foundObject<VolFieldType>(fieldName))
		{
			addMeanFieldType<VolFieldType>(fieldi);
		}
		else if (obr_.foundObject<SurfaceFieldType>(fieldName))
		{
			addMeanFieldType<SurfaceFieldType>(fieldi);
		}
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::addPrime2MeanFieldType
(
	const label fieldi
)
{
	const word& fieldName = faItems_[fieldi].fieldName();
	const word& meanFieldName = faItems_[fieldi].meanFieldName();
	const word& prime2MeanFieldName = faItems_[fieldi].prime2MeanFieldName();

	TnbLog << "    Reading/initialising field " << prime2MeanFieldName << nl;

	if (obr_.foundObject<Type2>(prime2MeanFieldName))
	{
	}
	else if (obr_.found(prime2MeanFieldName))
	{
		TnbLog << "    Cannot allocate average field " << prime2MeanFieldName
			<< " since an object with that name already exists."
			<< " Disabling averaging for field." << nl;

		faItems_[fieldi].prime2Mean() = false;
	}
	else
	{
		const Type1& baseField = obr_.lookupObject<Type1>(fieldName);
		const Type1& meanField = obr_.lookupObject<Type1>(meanFieldName);

		// Store on registry
		obr_.store
		(
			new Type2
			(
				IOobject
				(
					prime2MeanFieldName,
					obr_.time().timeName(obr_.time().startTime().value()),
					obr_,
					restartOnOutput_
					? IOobject::NO_READ
					: IOobject::READ_IF_PRESENT,
					IOobject::NO_WRITE
				),
				sqr(baseField) - sqr(meanField)
			)
		);
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::addPrime2MeanField(const label fieldi)
{
	typedef GeometricField<Type1, fvPatchField, volMesh> VolFieldType1;
	typedef GeometricField<Type1, fvsPatchField, surfaceMesh> SurfaceFieldType1;

	typedef GeometricField<Type2, fvPatchField, volMesh> VolFieldType2;
	typedef GeometricField<Type2, fvsPatchField, surfaceMesh> SurfaceFieldType2;

	if (faItems_[fieldi].prime2Mean())
	{
		const word& fieldName = faItems_[fieldi].fieldName();

		if (!faItems_[fieldi].mean())
		{
			FatalErrorInFunction
				<< "To calculate the prime-squared average, the "
				<< "mean average must also be selected for field "
				<< fieldName << nl << exit(FatalError);
		}

		if (obr_.foundObject<VolFieldType1>(fieldName))
		{
			addPrime2MeanFieldType<VolFieldType1, VolFieldType2>(fieldi);
		}
		else if (obr_.foundObject<SurfaceFieldType1>(fieldName))
		{
			addPrime2MeanFieldType<SurfaceFieldType1, SurfaceFieldType2>
				(
					fieldi
					);
		}
	}
}


template<class Type>
void tnbLib::functionObjects::fieldAverage::calculateMeanFieldType
(
	const label fieldi
) const
{
	const word& fieldName = faItems_[fieldi].fieldName();

	if (obr_.foundObject<Type>(fieldName))
	{
		const Type& baseField = obr_.lookupObject<Type>(fieldName);

		Type& meanField =
			obr_.lookupObjectRef<Type>(faItems_[fieldi].meanFieldName());

		scalar dt = obr_.time().deltaTValue();
		scalar Dt = totalTime_[fieldi];

		if (faItems_[fieldi].iterBase())
		{
			dt = 1;
			Dt = scalar(totalIter_[fieldi]);
		}

		scalar beta = dt / Dt;

		if (faItems_[fieldi].window() > 0)
		{
			const scalar w = faItems_[fieldi].window();

			if (Dt - dt >= w)
			{
				beta = dt / w;
			}
		}

		meanField = (1 - beta)*meanField + beta * baseField;
	}
}


template<class Type>
void tnbLib::functionObjects::fieldAverage::calculateMeanFields() const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	forAll(faItems_, i)
	{
		if (faItems_[i].mean())
		{
			calculateMeanFieldType<VolFieldType>(i);
			calculateMeanFieldType<SurfaceFieldType>(i);
		}
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::calculatePrime2MeanFieldType
(
	const label fieldi
) const
{
	const word& fieldName = faItems_[fieldi].fieldName();

	if (obr_.foundObject<Type1>(fieldName))
	{
		const Type1& baseField = obr_.lookupObject<Type1>(fieldName);
		const Type1& meanField =
			obr_.lookupObject<Type1>(faItems_[fieldi].meanFieldName());

		Type2& prime2MeanField =
			obr_.lookupObjectRef<Type2>(faItems_[fieldi].prime2MeanFieldName());

		scalar dt = obr_.time().deltaTValue();
		scalar Dt = totalTime_[fieldi];

		if (faItems_[fieldi].iterBase())
		{
			dt = 1;
			Dt = scalar(totalIter_[fieldi]);
		}

		scalar beta = dt / Dt;

		if (faItems_[fieldi].window() > 0)
		{
			const scalar w = faItems_[fieldi].window();

			if (Dt - dt >= w)
			{
				beta = dt / w;
			}
		}

		prime2MeanField =
			(1 - beta)*prime2MeanField
			+ beta * sqr(baseField)
			- sqr(meanField);
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::calculatePrime2MeanFields() const
{
	typedef GeometricField<Type1, fvPatchField, volMesh> VolFieldType1;
	typedef GeometricField<Type1, fvsPatchField, surfaceMesh> SurfaceFieldType1;

	typedef GeometricField<Type2, fvPatchField, volMesh> VolFieldType2;
	typedef GeometricField<Type2, fvsPatchField, surfaceMesh> SurfaceFieldType2;

	forAll(faItems_, i)
	{
		if (faItems_[i].prime2Mean())
		{
			calculatePrime2MeanFieldType<VolFieldType1, VolFieldType2>(i);
			calculatePrime2MeanFieldType<SurfaceFieldType1, SurfaceFieldType2>
				(
					i
					);
		}
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::addMeanSqrToPrime2MeanType
(
	const label fieldi
) const
{
	const word& fieldName = faItems_[fieldi].fieldName();

	if (obr_.foundObject<Type1>(fieldName))
	{
		const Type1& meanField =
			obr_.lookupObject<Type1>(faItems_[fieldi].meanFieldName());

		Type2& prime2MeanField =
			obr_.lookupObjectRef<Type2>(faItems_[fieldi].prime2MeanFieldName());

		prime2MeanField += sqr(meanField);
	}
}


template<class Type1, class Type2>
void tnbLib::functionObjects::fieldAverage::addMeanSqrToPrime2Mean() const
{
	typedef GeometricField<Type1, fvPatchField, volMesh> VolFieldType1;
	typedef GeometricField<Type1, fvsPatchField, surfaceMesh> SurfaceFieldType1;

	typedef GeometricField<Type2, fvPatchField, volMesh> VolFieldType2;
	typedef GeometricField<Type2, fvsPatchField, surfaceMesh> SurfaceFieldType2;

	forAll(faItems_, i)
	{
		if (faItems_[i].prime2Mean())
		{
			addMeanSqrToPrime2MeanType<VolFieldType1, VolFieldType2>(i);
			addMeanSqrToPrime2MeanType<SurfaceFieldType1, SurfaceFieldType2>(i);
		}
	}
}


template<class Type>
void tnbLib::functionObjects::fieldAverage::writeFieldType
(
	const word& fieldName
) const
{
	if (obr_.foundObject<Type>(fieldName))
	{
		const Type& f = obr_.lookupObject<Type>(fieldName);
		f.write();
	}
}


template<class Type>
void tnbLib::functionObjects::fieldAverage::writeFields() const
{
	typedef GeometricField<Type, fvPatchField, volMesh> VolFieldType;
	typedef GeometricField<Type, fvsPatchField, surfaceMesh> SurfaceFieldType;

	forAll(faItems_, i)
	{
		if (faItems_[i].mean())
		{
			const word& fieldName = faItems_[i].meanFieldName();
			writeFieldType<VolFieldType>(fieldName);
			writeFieldType<SurfaceFieldType>(fieldName);
		}
		if (faItems_[i].prime2Mean())
		{
			const word& fieldName = faItems_[i].prime2MeanFieldName();
			writeFieldType<VolFieldType>(fieldName);
			writeFieldType<SurfaceFieldType>(fieldName);
		}
	}
}


// ************************************************************************* //