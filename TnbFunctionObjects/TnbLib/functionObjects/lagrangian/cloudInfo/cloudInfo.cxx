#include <cloudInfo.hxx>

#include <kinematicCloud.hxx>
#include <dictionary.hxx>
#include <PstreamReduceOps.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(cloudInfo, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			cloudInfo,
			dictionary
		);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

void tnbLib::functionObjects::cloudInfo::writeFileHeader(const label i)
{
	writeHeader(file(), "Cloud information");
	writeCommented(file(), "Time");
	writeTabbed(file(), "nParcels");
	writeTabbed(file(), "mass");
	file() << endl;
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::cloudInfo::cloudInfo
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	regionFunctionObject(name, runTime, dict),
	logFiles(obr_, name)
{
	read(dict);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::cloudInfo::~cloudInfo()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::cloudInfo::read(const dictionary& dict)
{
	regionFunctionObject::read(dict);

	logFiles::resetNames(dict.lookup("clouds"));

	Info << type() << " " << name() << ": ";
	if (names().size())
	{
		Info << "applying to clouds:" << nl;
		forAll(names(), i)
		{
			Info << "    " << names()[i] << nl;
		}
		Info << endl;
	}
	else
	{
		Info << "no clouds to be processed" << nl << endl;
	}

	return true;
}


bool tnbLib::functionObjects::cloudInfo::execute()
{
	return true;
}


bool tnbLib::functionObjects::cloudInfo::write()
{
	logFiles::write();

	forAll(names(), i)
	{
		const word& cloudName = names()[i];

		const kinematicCloud& cloud =
			obr_.lookupObject<kinematicCloud>(cloudName);

		label nParcels = returnReduce(cloud.nParcels(), sumOp<label>());
		scalar massInSystem =
			returnReduce(cloud.massInSystem(), sumOp<scalar>());

		if (Pstream::master())
		{
			writeTime(file(i));
			file(i)
				<< tab
				<< nParcels << tab
				<< massInSystem << endl;
		}
	}

	return true;
}


// ************************************************************************* //