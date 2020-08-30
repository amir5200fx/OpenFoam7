#include <nastranSurfaceWriter.hxx>

#include <makeSurfaceWriterMethods.hxx>

#include <dictionary.hxx>  // added by amir
#include <IOmanip.hxx>  // added by amir
#include <OSspecific.hxx>  // added by amir
#include <List.hxx>  // added by amir
#include <Tuple2.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	makeSurfaceWriterType(nastranSurfaceWriter);
	addToRunTimeSelectionTable(surfaceWriter, nastranSurfaceWriter, wordDict);

	// create write methods
	defineSurfaceWriterWriteFields(nastranSurfaceWriter);

	template<>
	const char* NamedEnum<nastranSurfaceWriter::writeFormat, 3>::names[] =
	{
		"short",
		"long",
		"free"
	};

	const NamedEnum<nastranSurfaceWriter::writeFormat, 3>
		nastranSurfaceWriter::writeFormatNames_;
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::nastranSurfaceWriter::formatOS(OFstream& os) const
{
	os.setf(ios_base::scientific);

	// capitalize the E marker
	os.setf(ios_base::uppercase);

	label prec = 0;
	label offset = 7;
	switch (writeFormat_)
	{
	case (wfShort):
	case (wfFree):
	{
		prec = 8 - offset;
		break;
	}
	case (wfLong):
	{
		prec = 16 - offset;
		break;
	}
	default:
	{
	}
	}

	os.precision(prec);
}


void tnbLib::nastranSurfaceWriter::writeCoord
(
	const point& p,
	const label pointi,
	OFstream& os
) const
{
	// Fixed short/long formats:
	// 1 GRID
	// 2 ID   : point ID - requires starting index of 1
	// 3 CP   : co-ordinate system ID                (blank)
	// 4 X1   : point x cp-ordinate
	// 5 X2   : point x cp-ordinate
	// 6 X3   : point x cp-ordinate
	// 7 CD   : co-ordinate system for displacements (blank)
	// 8 PS   : single point constraints             (blank)
	// 9 SEID : super-element ID

	switch (writeFormat_)
	{
	case wfShort:
	{
		os.setf(ios_base::left);
		os << setw(8) << "GRID";
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(8) << pointi + 1
			<< "        "
			<< setw(8) << p.x()
			<< setw(8) << p.y()
			<< setw(8) << p.z()
			<< nl;
		os.unsetf(ios_base::right);

		break;
	}
	case wfLong:
	{
		os.setf(ios_base::left);
		os << setw(8) << "GRID*";
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(16) << pointi + 1
			<< "                "
			<< setw(16) << p.x()
			<< setw(16) << p.y()
			<< nl;
		os.unsetf(ios_base::right);
		os.setf(ios_base::left);
		os << setw(8) << "*";
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(16) << p.z()
			<< nl;
		os.unsetf(ios_base::right);

		break;
	}
	case wfFree:
	{
		os << "GRID"
			<< ',' << pointi + 1
			<< ','
			<< ',' << p.x()
			<< ',' << p.y()
			<< ',' << p.z()
			<< nl;

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown writeFormat enumeration" << abort(FatalError);
	}
	}
}

void tnbLib::nastranSurfaceWriter::writeFace
(
	const word& faceType,
	const labelList& facePts,
	label& nFace,
	OFstream& os
) const
{
	// Only valid surface elements are CTRIA3 and CQUAD4

	// Fixed short/long formats:
	// 1 CQUAD4
	// 2 EID  : element ID
	// 3 PID  : property element ID; default = EID   (blank)
	// 4 G1   : grid point index - requires starting index of 1
	// 5 G2   : grid point index
	// 6 G3   : grid point index
	// 7 G4   : grid point index
	// 8 onwards - not used

	// For CTRIA3 elements, cols 7 onwards are not used

	switch (writeFormat_)
	{
	case wfShort:
	{
		os.setf(ios_base::left);
		os << setw(8) << faceType;
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(8) << nFace++
			<< "        ";

		forAll(facePts, i)
		{
			os << setw(8) << facePts[i] + 1;
		}

		os << nl;
		os.unsetf(ios_base::right);

		break;
	}
	case wfLong:
	{
		os.setf(ios_base::left);
		os << setw(8) << word(faceType + "*");
		os.unsetf(ios_base::left);
		os.setf(ios_base::right);
		os << setw(16) << nFace++
			<< "                ";

		forAll(facePts, i)
		{
			os << setw(16) << facePts[i] + 1;
			if (i == 1)
			{
				os << nl;
				os.unsetf(ios_base::right);
				os.setf(ios_base::left);
				os << setw(8) << "*";
				os.unsetf(ios_base::left);
				os.setf(ios_base::right);
			}
		}

		os << nl;
		os.unsetf(ios_base::right);

		break;
	}
	case wfFree:
	{
		os << faceType << ','
			<< ++nFace << ',';

		forAll(facePts, i)
		{
			os << ',' << facePts[i] + 1;
		}

		os << nl;

		break;
	}
	default:
	{
		FatalErrorInFunction
			<< "Unknown writeFormat enumeration" << abort(FatalError);
	}
	}

}


void tnbLib::nastranSurfaceWriter::writeGeometry
(
	const pointField& points,
	const faceList& faces,
	List<DynamicList<face>>& decomposedFaces,
	OFstream& os
) const
{
	// write points

	os << "$" << nl
		<< "$ Points" << nl
		<< "$" << nl;

	forAll(points, pointi)
	{
		writeCoord(points[pointi], pointi, os);
	}


	// write faces

	os << "$" << nl
		<< "$ Faces" << nl
		<< "$" << nl;

	label nFace = 1;

	forAll(faces, facei)
	{
		const face& f = faces[facei];

		if (f.size() == 3)
		{
			writeFace("CTRIA3", faces[facei], nFace, os);
			decomposedFaces[facei].append(faces[facei]);
		}
		else if (f.size() == 4)
		{
			writeFace("CQUAD4", faces[facei], nFace, os);
			decomposedFaces[facei].append(faces[facei]);
		}
		else
		{
			// decompose poly face into tris
			label nTri = 0;
			faceList triFaces;
			f.triangles(points, nTri, triFaces);

			forAll(triFaces, triI)
			{
				writeFace("CTRIA3", triFaces[triI], nFace, os);
				decomposedFaces[facei].append(triFaces[triI]);
			}
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::nastranSurfaceWriter::nastranSurfaceWriter()
	:
	surfaceWriter(),
	writeFormat_(wfShort),
	fieldMap_(),
	scale_(1.0)
{}


tnbLib::nastranSurfaceWriter::nastranSurfaceWriter(const dictionary& options)
	:
	surfaceWriter(),
	writeFormat_(wfLong),
	fieldMap_(),
	scale_(options.lookupOrDefault("scale", 1.0))
{
	if (options.found("format"))
	{
		writeFormat_ = writeFormatNames_.read(options.lookup("format"));
	}

	List<Tuple2<word, word>> fieldSet(options.lookup("fields"));

	forAll(fieldSet, i)
	{
		fieldMap_.insert(fieldSet[i].first(), fieldSet[i].second());
	}
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::nastranSurfaceWriter::~nastranSurfaceWriter()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::nastranSurfaceWriter::write
(
	const fileName& outputDir,
	const fileName& surfaceName,
	const pointField& points,
	const faceList& faces,
	const bool verbose
) const
{
	if (!isDir(outputDir))
	{
		mkDir(outputDir);
	}

	OFstream os(outputDir / surfaceName + ".dat");
	formatOS(os);

	if (verbose)
	{
		Info << "Writing nastran file to " << os.name() << endl;
	}

	os << "TITLE=OpenFOAM " << surfaceName.c_str() << " mesh" << nl
		<< "$" << nl
		<< "BEGIN BULK" << nl;

	List<DynamicList<face>> decomposedFaces(faces.size());

	writeGeometry(points, faces, decomposedFaces, os);

	if (!isDir(outputDir))
	{
		mkDir(outputDir);
	}

	os << "ENDDATA" << endl;
}


// ************************************************************************* //