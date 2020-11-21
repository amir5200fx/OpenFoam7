#pragma once

#include <IOMap.hxx>
#include <OSspecific.hxx>

#include <IOmanip.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class Type>
void tnbLib::nastranSurfaceWriter::writeFaceValue
(
	const word& nasFieldName,
	const Type& value,
	const label EID,
	OFstream& os
) const
{
	// Fixed short/long formats:
	// 1 Nastran distributed load type, e.g. PLOAD4
	// 2 SID  : load set ID
	// 3 EID  : element ID
	// 4 onwards: load values

	label SID = 1;

	Type scaledValue = scale_ * value;

	switch (writeFormat_)
	{
	case wfShort:
	{
		os.setf(ios_base::left);
		os << setw(8) << nasFieldName;
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(8) << SID
			<< setw(8) << EID;

		for (direction dirI = 0; dirI < pTraits<Type>::nComponents; dirI++)
		{
			os << setw(8) << component(scaledValue, dirI);
		}

		os.unsetf(ios_base::right);

		break;
	}
	case wfLong:
	{
		os.setf(ios_base::left);
		os << setw(8) << word(nasFieldName + "*");
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(16) << SID
			<< setw(16) << EID;

		for (direction dirI = 0; dirI < pTraits<Type>::nComponents; dirI++)
		{
			os << setw(16) << component(scaledValue, dirI);
		}

		os.unsetf(ios_base::right);

		os << nl;

		os.setf(ios_base::left);
		os << '*';
		os.unsetf(ios_base::left);

		break;
	}
	case wfFree:
	{
		os << nasFieldName << ','
			<< SID << ','
			<< EID;

		for (direction dirI = 0; dirI < pTraits<Type>::nComponents; dirI++)
		{
			os << ',' << component(scaledValue, dirI);
		}

		break;
	}
	default:
	{
	}
	}

	os << nl;
}


template<class Type>
void tnbLib::nastranSurfaceWriter::writeTemplate
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const word& fieldName,
	const Field<Type>& values,
	const bool isNodeValues,
	const bool verbose
) const
{
	if (!fieldMap_.found(fieldName))
	{
		WarningInFunction
			<< "No mapping found between field " << fieldName
			<< " and corresponding Nastran field.  Available types are:"
			<< fieldMap_
			<< exit(FatalError);

		return;
	}

	const word& nasFieldName(fieldMap_[fieldName]);

	if (!isDir(outputDir / fieldName))
	{
		mkDir(outputDir / fieldName);
	}

	// const scalar timeValue = tnbLib::name(this->mesh().time().timeValue());
	const scalar timeValue = 0.0;

	OFstream os(outputDir / fieldName / surfaceName + ".dat");
	formatOS(os);

	if (verbose)
	{
		Info << "Writing nastran file to " << os.name() << endl;
	}

	os << "TITLE=OpenFOAM " << surfaceName.c_str() << " " << fieldName
		<< " data" << nl
		<< "$" << nl
		<< "TIME " << timeValue << nl
		<< "$" << nl
		<< "BEGIN BULK" << nl;

	List<DynamicList<face>> decomposedFaces(faces.size());

	writeGeometry(points, faces, decomposedFaces, os);


	os << "$" << nl
		<< "$ Field data" << nl
		<< "$" << nl;

	if (isNodeValues)
	{
		label n = 0;

		forAll(decomposedFaces, i)
		{
			const DynamicList<face>& dFaces = decomposedFaces[i];
			forAll(dFaces, facei)
			{
				Type v = Zero;
				const face& f = dFaces[facei];

				forAll(f, fptI)
				{
					v += values[f[fptI]];
				}
				v /= f.size();

				writeFaceValue(nasFieldName, v, ++n, os);
			}
		}
	}
	else
	{
		label n = 0;

		forAll(decomposedFaces, i)
		{
			const DynamicList<face>& dFaces = decomposedFaces[i];

			forAll(dFaces, facei)
			{
				writeFaceValue(nasFieldName, values[facei], ++n, os);
			}
		}
	}

	os << "ENDDATA" << endl;
}


// ************************************************************************* //