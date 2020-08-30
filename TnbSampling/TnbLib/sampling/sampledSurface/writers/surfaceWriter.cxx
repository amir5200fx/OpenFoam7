#include <surfaceWriter.hxx>

#include <MeshedSurfaceProxy.hxx>
#include <proxySurfaceWriter.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(surfaceWriter, 0);
	defineRunTimeSelectionTable(surfaceWriter, word);
	defineRunTimeSelectionTable(surfaceWriter, wordDict);
}


// * * * * * * * * * * * * * Static Member Functions * * * * * * * * * * * * //

tnbLib::autoPtr<tnbLib::surfaceWriter>
tnbLib::surfaceWriter::New(const word& writeType)
{
	wordConstructorTable::iterator cstrIter =
		wordConstructorTablePtr_->find(writeType);

	if (cstrIter == wordConstructorTablePtr_->end())
	{
		if (MeshedSurfaceProxy<face>::canWriteType(writeType))
		{
			// generally unknown, but can be written via MeshedSurfaceProxy
			// use 'proxy' handler instead
			return autoPtr<surfaceWriter>(new proxySurfaceWriter(writeType));
		}

		if (cstrIter == wordConstructorTablePtr_->end())
		{
			FatalErrorInFunction
				<< "Unknown write type \"" << writeType << "\"\n\n"
				<< "Valid write types : "
				<< wordConstructorTablePtr_->sortedToc() << nl
				<< "Valid proxy types : "
				<< MeshedSurfaceProxy<face>::writeTypes() << endl
				<< exit(FatalError);
		}
	}

	return autoPtr<surfaceWriter>(cstrIter()());
}


tnbLib::autoPtr<tnbLib::surfaceWriter>
tnbLib::surfaceWriter::New(const word& writeType, const dictionary& optDict)
{
	// find constructors with dictionary options
	wordDictConstructorTable::iterator cstrIter =
		wordDictConstructorTablePtr_->find(writeType);

	if (cstrIter == wordDictConstructorTablePtr_->end())
	{
		// revert to versions without options
		return tnbLib::surfaceWriter::New(writeType);
	}

	return autoPtr<surfaceWriter>(cstrIter()(optDict));
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::surfaceWriter::surfaceWriter()
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::surfaceWriter::~surfaceWriter()
{}


// ************************************************************************* //