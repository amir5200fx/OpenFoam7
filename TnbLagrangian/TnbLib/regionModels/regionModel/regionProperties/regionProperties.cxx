#include <regionProperties.hxx>

#include <IOdictionary.hxx>
#include <argList.hxx>
#include <polyMesh.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::regionProperties::regionProperties(const Time& runTime)
	:
	HashTable<wordList>
	(
		IOdictionary
		(
			tnbLib::IOobject
			(
				"regionProperties",
				runTime.time().constant(),
				runTime.db(),
				tnbLib::IOobject::MUST_READ_IF_MODIFIED,
				tnbLib::IOobject::NO_WRITE
			)
		).lookup("regions")
		)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::regionProperties::~regionProperties()
{}


// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

const tnbLib::word& tnbLib::regionDir(const word& regionName)
{
	return
		regionName == polyMesh::defaultRegion
		? word::null
		: regionName;
}


tnbLib::wordList tnbLib::selectRegionNames(const argList& args, const Time& runTime)
{
	const bool allRegions = args.optionFound("allRegions");

	wordList regionNames;

	if (allRegions)
	{
		const regionProperties rp(runTime);
		forAllConstIter(HashTable<wordList>, rp, iter)
		{
			const wordList& regions = iter();
			forAll(regions, i)
			{
				if (findIndex(regionNames, regions[i]) == -1)
				{
					regionNames.append(regions[i]);
				}
			}
		}
	}
	else
	{
		word regionName;
		if (args.optionReadIfPresent("region", regionName))
		{
			regionNames = wordList(1, regionName);
		}
		else
		{
			regionNames = wordList(1, polyMesh::defaultRegion);
		}
	}

	return regionNames;
}


// ************************************************************************* //