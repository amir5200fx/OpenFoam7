#pragma once
#include <dictionary.hxx>
#include <fileNameList.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class TablePtr>
bool tnbLib::dlLibraryTable::open
(
	const dictionary& dict,
	const word& libsEntry,
	const TablePtr& tablePtr
)
{
	if (dict.found(libsEntry))
	{
		fileNameList libNames(dict.lookup(libsEntry));

		bool allOpened = (libNames.size() > 0);

		forAll(libNames, i)
		{
			const fileName& libName = libNames[i];

			label nEntries = 0;

			if (tablePtr)
			{
				nEntries = tablePtr->size();
			}

			bool opened = dlLibraryTable::open(libName);
			allOpened = opened && allOpened;

			if (!opened)
			{
				WarningInFunction
					<< "Could not open library " << libName
					<< endl << endl;
			}
			else if (debug && (!tablePtr || tablePtr->size() <= nEntries))
			{
				WarningInFunction
					<< "library " << libName
					<< " did not introduce any new entries"
					<< endl << endl;
			}
		}

		return allOpened;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //