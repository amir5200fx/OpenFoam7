#pragma once
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <ListListOps.hxx>
#include <stringListOps.hxx>

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::sampledSurfaces::writeSurface
(
	const Field<Type>& values,
	const label surfI,
	const word& fieldName,
	const fileName& outputDir
)
{
	const sampledSurface& s = operator[](surfI);

	if (Pstream::parRun())
	{
		// Collect values from all processors
		List<Field<Type>> gatheredValues(Pstream::nProcs());
		gatheredValues[Pstream::myProcNo()] = values;
		Pstream::gatherList(gatheredValues);

		if (Pstream::master())
		{
			// Combine values into single field
			Field<Type> allValues
			(
				ListListOps::combine<Field<Type>>
				(
					gatheredValues,
					accessOp<Field<Type>>()
					)
			);

			// Renumber (point data) to correspond to merged points
			if (mergeList_[surfI].pointsMap.size() == allValues.size())
			{
				inplaceReorder(mergeList_[surfI].pointsMap, allValues);
				allValues.setSize(mergeList_[surfI].points.size());
			}

			// Write to time directory under outputPath_
			// skip surface without faces (eg, a failed cut-plane)
			if (mergeList_[surfI].faces.size())
			{
				formatter_->write
				(
					outputDir,
					s.name(),
					mergeList_[surfI].points,
					mergeList_[surfI].faces,
					fieldName,
					allValues,
					s.interpolate()
				);
			}
		}
	}
	else
	{
		// Write to time directory under outputPath_
		// skip surface without faces (eg, a failed cut-plane)
		if (s.faces().size())
		{
			formatter_->write
			(
				outputDir,
				s.name(),
				s.points(),
				s.faces(),
				fieldName,
				values,
				s.interpolate()
			);
		}
	}
}

template<class Type>
void tnbLib::sampledSurfaces::sampleAndWrite
(
	const GeometricField<Type, fvPatchField, volMesh>& vField
)
{
	// interpolator for this field
	autoPtr<interpolation<Type>> interpolatorPtr;

	const word& fieldName = vField.name();
	const fileName outputDir = outputPath_ / vField.time().timeName();

	forAll(*this, surfI)
	{
		const sampledSurface& s = operator[](surfI);

		Field<Type> values;

		if (s.interpolate())
		{
			if (interpolatorPtr.empty())
			{
				interpolatorPtr = interpolation<Type>::New
				(
					interpolationScheme_,
					vField
				);
			}

			values = s.interpolate(interpolatorPtr());
		}
		else
		{
			values = s.sample(vField);
		}

		writeSurface<Type>(values, surfI, fieldName, outputDir);
	}
}

template<class Type>
void tnbLib::sampledSurfaces::sampleAndWrite
(
	const GeometricField<Type, fvsPatchField, surfaceMesh>& sField
)
{
	const word& fieldName = sField.name();
	const fileName outputDir = outputPath_ / sField.time().timeName();

	forAll(*this, surfI)
	{
		const sampledSurface& s = operator[](surfI);
		Field<Type> values(s.sample(sField));
		writeSurface<Type>(values, surfI, fieldName, outputDir);
	}
}


template<class GeoField>
void tnbLib::sampledSurfaces::sampleAndWriteGeoField(const IOobjectList& objects)
{
	wordList names;
	if (loadFromFiles_)
	{
		IOobjectList fieldObjects(objects.lookupClass(GeoField::typeName));
		names = fieldObjects.names();
	}
	else
	{
		names = mesh_.thisDb().names<GeoField>();
	}

	labelList nameIDs(findStrings(fieldSelection_, names));

	wordHashSet fieldNames(wordList(names, nameIDs));

	forAllConstIter(wordHashSet, fieldNames, iter)
	{
		const word& fieldName = iter.key();

		if ((Pstream::master()) && verbose_)
		{
			Pout << "sampleAndWrite: " << fieldName << endl;
		}

		if (loadFromFiles_)
		{
			const GeoField fld
			(
				IOobject
				(
					fieldName,
					mesh_.time().timeName(),
					mesh_,
					IOobject::MUST_READ
				),
				mesh_
			);

			sampleAndWrite(fld);
		}
		else
		{
			sampleAndWrite
			(
				mesh_.thisDb().lookupObject<GeoField>(fieldName)
			);
		}
	}
}


// ************************************************************************* //