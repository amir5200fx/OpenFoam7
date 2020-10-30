#include <surfacePatchIOList.hxx>

#include <entry.hxx> // added by amir
#include <PtrList.hxx>  // added by amir
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfacePatchIOList, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from IOObject
tnbLib::surfacePatchIOList::surfacePatchIOList
(
	const IOobject& io
)
	:
	surfacePatchList(),
	regIOobject(io)
{
	tnbLib::string functionName =
		"surfacePatchIOList::surfacePatchIOList"
		"(const IOobject& io)";


	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			)
	{
		if (readOpt() == IOobject::MUST_READ_IF_MODIFIED)
		{
			WarningInFunction
				<< "Specified IOobject::MUST_READ_IF_MODIFIED but class"
				<< " does not support automatic rereading."
				<< endl;
		}


		surfacePatchList& patches = *this;

		// read polyPatchList
		Istream& is = readStream(typeName);

		PtrList<entry> patchEntries(is);
		patches.setSize(patchEntries.size());

		label facei = 0;

		forAll(patches, patchi)
		{
			const dictionary& dict = patchEntries[patchi].dict();

			label patchSize = readLabel(dict.lookup("nFaces"));
			label startFacei = readLabel(dict.lookup("startFace"));

			patches[patchi] =
				surfacePatch
				(
					word(dict.lookup("geometricType")),
					patchEntries[patchi].keyword(),
					patchSize,
					startFacei,
					patchi
				);


			if (startFacei != facei)
			{
				FatalErrorInFunction
					<< "Patches are not ordered. Start of patch " << patchi
					<< " does not correspond to sum of preceding patches."
					<< endl
					<< "while reading " << io.objectPath()
					<< exit(FatalError);
			}

			facei += patchSize;
		}

		// Check state of IOstream
		is.check(functionName.c_str());

		close();
	}
}

// Construct from IOObject
tnbLib::surfacePatchIOList::surfacePatchIOList
(
	const IOobject& io,
	const surfacePatchList& patches
)
	:
	surfacePatchList(patches),
	regIOobject(io)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfacePatchIOList::~surfacePatchIOList()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


// writeData member function required by regIOobject
bool tnbLib::surfacePatchIOList::writeData(Ostream& os) const
{
	os << *this;
	return os.good();
}


// * * * * * * * * * * * * * * * Friend Operators  * * * * * * * * * * * * * //

FoamFvMesh_EXPORT tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const surfacePatchIOList& patches)
{
	os << patches.size() << nl << token::BEGIN_LIST;

	forAll(patches, patchi)
	{
		patches[patchi].writeDict(os);
	}

	os << token::END_LIST;

	return os;
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //


// * * * * * * * * * * * * * * * Friend Functions  * * * * * * * * * * * * * //

// ************************************************************************* //