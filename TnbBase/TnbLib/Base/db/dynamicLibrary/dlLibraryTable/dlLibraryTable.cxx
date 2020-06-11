#include <dlLibraryTable.hxx>

#include <OSspecific.hxx>
#include <int.hxx>
#include <dictionary.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(dlLibraryTable, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::dlLibraryTable::dlLibraryTable()
{}


tnbLib::dlLibraryTable::dlLibraryTable
(
	const dictionary& dict,
	const word& libsEntry
)
{
	open(dict, libsEntry);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::dlLibraryTable::~dlLibraryTable()
{
	forAllReverse(libPtrs_, i)
	{
		if (libPtrs_[i])
		{
			if (debug)
			{
				InfoInFunction
					<< "Closing " << libNames_[i]
					<< " with handle " << uintptr_t(libPtrs_[i]) << endl;
			}
			if (!dlClose(libPtrs_[i]))
			{
				WarningInFunction << "Failed closing " << libNames_[i]
					<< " with handle " << uintptr_t(libPtrs_[i]) << endl;
			}
		}
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::dlLibraryTable::open
(
	const fileName& functionLibName,
	const bool verbose
)
{
	if (functionLibName.size())
	{
		void* functionLibPtr = dlOpen
		(
			fileName(functionLibName).expand(),
			verbose
		);

		if (debug)
		{
			InfoInFunction
				<< "Opened " << functionLibName
				<< " resulting in handle " << uintptr_t(functionLibPtr) << endl;
		}

		if (!functionLibPtr)
		{
			if (verbose)
			{
				WarningInFunction
					<< "could not load " << functionLibName
					<< endl;
			}

			return false;
		}
		else
		{
			libPtrs_.append(functionLibPtr);
			libNames_.append(functionLibName);
			return true;
		}
	}
	else
	{
		return false;
	}
}


bool tnbLib::dlLibraryTable::close
(
	const fileName& functionLibName,
	const bool verbose
)
{
	label index = -1;
	forAllReverse(libNames_, i)
	{
		if (libNames_[i] == functionLibName)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		if (debug)
		{
			InfoInFunction
				<< "Closing " << functionLibName
				<< " with handle " << uintptr_t(libPtrs_[index]) << endl;
		}

		bool ok = dlClose(libPtrs_[index]);

		libPtrs_[index] = nullptr;
		libNames_[index] = fileName::null;

		if (!ok)
		{
			if (verbose)
			{
				WarningInFunction
					<< "could not close " << functionLibName
					<< endl;
			}

			return false;
		}

		return true;
	}
	return false;
}


void* tnbLib::dlLibraryTable::findLibrary(const fileName& functionLibName)
{
	label index = -1;
	forAllReverse(libNames_, i)
	{
		if (libNames_[i] == functionLibName)
		{
			index = i;
			break;
		}
	}

	if (index != -1)
	{
		return libPtrs_[index];
	}
	return nullptr;
}


bool tnbLib::dlLibraryTable::open
(
	const dictionary& dict,
	const word& libsEntry
)
{
	if (dict.found(libsEntry))
	{
		fileNameList libNames(dict.lookup(libsEntry));

		bool allOpened = !libNames.empty();

		forAll(libNames, i)
		{
			allOpened = dlLibraryTable::open(libNames[i]) && allOpened;
		}

		return allOpened;
	}
	else
	{
		return false;
	}
}


// ************************************************************************* //