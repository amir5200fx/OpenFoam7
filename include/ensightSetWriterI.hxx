#pragma once
#include <coordSet.hxx>
#include <OFstream.hxx>
#include <addToRunTimeSelectionTable.hxx>
#include <IOmanip.hxx>
#include <tnbVersion.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class Type>
tnbLib::ensightSetWriter<Type>::ensightSetWriter()
	:
	writer<Type>()
{}

// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class Type>
tnbLib::ensightSetWriter<Type>::~ensightSetWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::fileName tnbLib::ensightSetWriter<Type>::getFileName
(
	const coordSet& points,
	const wordList& valueSetNames
) const
{
	return
		this->getBaseName(points, valueSetNames)
		//+ '_'
		//+ pTraits<Type>::typeName
		+ ".case";
}


template<class Type>
void tnbLib::ensightSetWriter<Type>::write
(
	const coordSet& points,
	const wordList& valueSetNames,
	const List<const Field<Type>*>& valueSets,
	Ostream& os
) const
{
	const fileName base(os.name().lessExt());
	const fileName meshFile(base + ".mesh");

	// Write .case file
	os << "FORMAT" << nl
		<< "type: ensight gold" << nl
		<< nl
		<< "GEOMETRY" << nl
		<< "model:        1     " << meshFile.name().c_str() << nl
		<< nl
		<< "VARIABLE"
		<< nl;
	forAll(valueSetNames, setI)
	{
		fileName dataFile(base + ".***." + valueSetNames[setI]);

		os.setf(ios_base::left);
		os << pTraits<Type>::typeName
			<< " per node:            1       "
			<< setw(15) << valueSetNames[setI]
			<< " " << dataFile.name().c_str()
			<< nl;
	}
	os << nl
		<< "TIME" << nl
		<< "time set:                      1" << nl
		<< "number of steps:               1" << nl
		<< "filename start number:         0" << nl
		<< "filename increment:            1" << nl
		<< "time values:" << nl
		<< "0.00000e+00" << nl;

	// Write .mesh file
	{
		string desc = string("written by OpenFOAM-") + tnbLib::FOAMversion;
		OFstream os(meshFile);
		os.setf(ios_base::scientific, ios_base::floatfield);
		os.precision(5);

		os << "EnSight Geometry File" << nl
			<< desc.c_str() << nl
			<< "node id assign" << nl
			<< "element id assign" << nl
			<< "part" << nl
			<< setw(10) << 1 << nl
			<< "internalMesh" << nl
			<< "coordinates" << nl
			<< setw(10) << points.size() << nl;

		for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
		{
			forAll(points, pointi)
			{
				const scalar comp = points[pointi][cmpt];
				if (mag(comp) >= scalar(floatScalarVSmall))
				{
					os << setw(12) << comp << nl;
				}
				else
				{
					os << setw(12) << scalar(0) << nl;
				}
			}
		}
		os << "point" << nl
			<< setw(10) << points.size() << nl;
		forAll(points, pointi)
		{
			os << setw(10) << pointi + 1 << nl;
		}
	}

	// Write data files
	forAll(valueSetNames, setI)
	{
		fileName dataFile(base + ".000." + valueSetNames[setI]);
		OFstream os(dataFile);
		os.setf(ios_base::scientific, ios_base::floatfield);
		os.precision(5);
		{
			os << pTraits<Type>::typeName << nl
				<< "part" << nl
				<< setw(10) << 1 << nl
				<< "coordinates" << nl;
			for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
			{
				const scalarField fld(valueSets[setI]->component(cmpt));
				forAll(fld, i)
				{
					if (mag(fld[i]) >= scalar(floatScalarVSmall))
					{
						os << setw(12) << fld[i] << nl;
					}
					else
					{
						os << setw(12) << scalar(0) << nl;
					}
				}
			}
		}
	}
}


template<class Type>
void tnbLib::ensightSetWriter<Type>::write
(
	const bool writeTracks,
	const PtrList<coordSet>& tracks,
	const wordList& valueSetNames,
	const List<List<Field<Type>>>& valueSets,
	Ostream& os
) const
{
	const fileName base(os.name().lessExt());
	const fileName meshFile(base + ".mesh");

	// Write .case file
	os << "FORMAT" << nl
		<< "type: ensight gold" << nl
		<< nl
		<< "GEOMETRY" << nl
		<< "model:        1     " << meshFile.name().c_str() << nl
		<< nl
		<< "VARIABLE"
		<< nl;
	forAll(valueSetNames, setI)
	{
		fileName dataFile(base + ".***." + valueSetNames[setI]);

		os.setf(ios_base::left);
		os << pTraits<Type>::typeName
			<< " per node:            1       "
			<< setw(15) << valueSetNames[setI]
			<< " " << dataFile.name().c_str()
			<< nl;
	}
	os << nl
		<< "TIME" << nl
		<< "time set:                      1" << nl
		<< "number of steps:               1" << nl
		<< "filename start number:         0" << nl
		<< "filename increment:            1" << nl
		<< "time values:" << nl
		<< "0.00000e+00" << nl;

	// Write .mesh file
	{
		string desc = string("written by OpenFOAM-") + tnbLib::FOAMversion;
		OFstream os(meshFile);
		os.setf(ios_base::scientific, ios_base::floatfield);
		os.precision(5);
		os << "EnSight Geometry File" << nl
			<< desc.c_str() << nl
			<< "node id assign" << nl
			<< "element id assign" << nl;

		forAll(tracks, trackI)
		{
			const coordSet& points = tracks[trackI];

			os << "part" << nl
				<< setw(10) << trackI + 1 << nl
				<< "internalMesh" << nl
				<< "coordinates" << nl
				<< setw(10) << points.size() << nl;

			for (direction cmpt = 0; cmpt < vector::nComponents; cmpt++)
			{
				forAll(points, pointi)
				{
					const scalar comp = points[pointi][cmpt];
					if (mag(comp) >= scalar(floatScalarVSmall))
					{
						os << setw(12) << comp << nl;
					}
					else
					{
						os << setw(12) << scalar(0) << nl;
					}
				}
			}

			if (writeTracks)
			{
				os << "bar2" << nl
					<< setw(10) << points.size() - 1 << nl;
				for (label i = 0; i < points.size() - 1; i++)
				{
					os << setw(10) << i + 1
						<< setw(10) << i + 2
						<< nl;
				}
			}
		}
	}


	// Write data files
	forAll(valueSetNames, setI)
	{
		fileName dataFile(base + ".000." + valueSetNames[setI]);
		OFstream os(dataFile);
		os.setf(ios_base::scientific, ios_base::floatfield);
		os.precision(5);
		{
			os << pTraits<Type>::typeName << nl;

			const List<Field<Type>>& fieldVals = valueSets[setI];
			forAll(fieldVals, trackI)
			{
				os << "part" << nl
					<< setw(10) << trackI + 1 << nl
					<< "coordinates" << nl;

				for
					(
						direction cmpt = 0;
						cmpt < pTraits<Type>::nComponents;
						cmpt++
						)
				{
					const scalarField fld(fieldVals[trackI].component(cmpt));
					forAll(fld, i)
					{
						if (mag(fld[i]) >= scalar(floatScalarVSmall))
						{
							os << setw(12) << fld[i] << nl;
						}
						else
						{
							os << setw(12) << scalar(0) << nl;
						}
					}
				}
			}
		}
	}
}


// ************************************************************************* //