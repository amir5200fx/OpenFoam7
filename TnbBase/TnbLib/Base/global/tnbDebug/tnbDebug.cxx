#include <tnbDebug.hxx>

#include <dictionary.hxx>
#include <IFstream.hxx>
#include <etcFiles.hxx>
#include <Ostream.hxx>
#include <demandDrivenData.hxx>
#include <simpleObjectRegistry.hxx>
#include <IOobject.hxx>
#include <HashSet.hxx>

#include <IStringStream.hxx>  // added by amir
#include <OSspecific.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace debug
	{

		//! \cond ignoreDocumentation
		//- Skip documentation : local scope only

		dictionary* controlDictPtr_(nullptr);
		dictionary* debugSwitchesPtr_(nullptr);
		dictionary* infoSwitchesPtr_(nullptr);
		dictionary* optimisationSwitchesPtr_(nullptr);

		// Debug switch read and write callback tables.
		simpleObjectRegistry* debugObjectsPtr_(nullptr);
		simpleObjectRegistry* infoObjectsPtr_(nullptr);
		simpleObjectRegistry* optimisationObjectsPtr_(nullptr);
		simpleObjectRegistry* dimensionSetObjectsPtr_(nullptr);
		simpleObjectRegistry* dimensionedConstantObjectsPtr_(nullptr);


		// To ensure controlDictPtr_ is deleted at the end of the run
		class deleteControlDictPtr
		{
		public:

			deleteControlDictPtr()
			{}

			~deleteControlDictPtr()
			{
				deleteDemandDrivenData(debugObjectsPtr_);
				deleteDemandDrivenData(infoObjectsPtr_);
				deleteDemandDrivenData(optimisationObjectsPtr_);
				deleteDemandDrivenData(dimensionSetObjectsPtr_);
				deleteDemandDrivenData(dimensionedConstantObjectsPtr_);

				debugSwitchesPtr_ = nullptr;
				infoSwitchesPtr_ = nullptr;
				optimisationSwitchesPtr_ = nullptr;
				deleteDemandDrivenData(controlDictPtr_);
			}
		};

		deleteControlDictPtr deleteControlDictPtr_;
		//! \endcond


	} // End namespace debug
} // End namespace tnbLib

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

tnbLib::dictionary& tnbLib::debug::controlDict()
{
	if (!controlDictPtr_)
	{
		string controlDictString(getEnv("FOAM_CONTROLDICT"));
		if (!controlDictString.empty())
		{
			// Read from environment
			IStringStream is(controlDictString);
			controlDictPtr_ = new dictionary(is);
		}
		else
		{
			fileNameList controlDictFiles = findEtcFiles("controlDict", true);
			controlDictPtr_ = new dictionary();
			forAllReverse(controlDictFiles, cdfi)
			{
				IFstream ifs(controlDictFiles[cdfi]);

				if (!ifs.good())
				{
					SafeFatalIOErrorInFunction
					(
						ifs,
						"Cannot open controlDict"
					);
				}
				controlDictPtr_->merge(dictionary(ifs));
			}
		}
	}

	return *controlDictPtr_;
}


tnbLib::dictionary& tnbLib::debug::switchSet
(
	const char* subDictName,
	dictionary*& subDictPtr
)
{
	if (!subDictPtr)
	{
		entry* ePtr = controlDict().lookupEntryPtr
		(
			subDictName, false, false
		);

		if (!ePtr || !ePtr->isDict())
		{
			cerr << "debug::switchSet(const char*, dictionary*&):\n"
				<< "    Cannot find " << subDictName << " in dictionary "
				<< controlDict().name().c_str()
				<< std::endl << std::endl;

			::exit(1);
		}

		subDictPtr = &ePtr->dict();
	}

	return *subDictPtr;
}


tnbLib::dictionary& tnbLib::debug::debugSwitches()
{
	return switchSet("DebugSwitches", debugSwitchesPtr_);
}


tnbLib::dictionary& tnbLib::debug::infoSwitches()
{
	return switchSet("InfoSwitches", infoSwitchesPtr_);
}


tnbLib::dictionary& tnbLib::debug::optimisationSwitches()
{
	return switchSet("OptimisationSwitches", optimisationSwitchesPtr_);
}


int tnbLib::debug::debugSwitch(const char* name, const int defaultValue)
{
	return debugSwitches().lookupOrAddDefault
	(
		name, defaultValue, false, false
	);
}


int tnbLib::debug::infoSwitch(const char* name, const int defaultValue)
{
	return infoSwitches().lookupOrAddDefault
	(
		name, defaultValue, false, false
	);
}


int tnbLib::debug::optimisationSwitch(const char* name, const int defaultValue)
{
	return optimisationSwitches().lookupOrAddDefault
	(
		name, defaultValue, false, false
	);
}


float tnbLib::debug::floatOptimisationSwitch
(
	const char* name,
	const float defaultValue
)
{
	return optimisationSwitches().lookupOrAddDefault
	(
		name, defaultValue, false, false
	);
}


void tnbLib::debug::addDebugObject(const char* name, simpleRegIOobject* obj)
{
	simpleObjectRegistryEntry* ptr = debugObjects().lookupPtr(name);
	if (ptr)
	{
		ptr->append(obj);
	}
	else
	{
		debugObjects().append
		(
			name,
			new simpleObjectRegistryEntry
			(
				List<simpleRegIOobject*>(1, obj)
			)
		);
	}
}


void tnbLib::debug::addInfoObject(const char* name, simpleRegIOobject* obj)
{
	simpleObjectRegistryEntry* ptr = infoObjects().lookupPtr(name);
	if (ptr)
	{
		ptr->append(obj);
	}
	else
	{
		infoObjects().append
		(
			name,
			new simpleObjectRegistryEntry
			(
				List<simpleRegIOobject*>(1, obj)
			)
		);
	}
}


void tnbLib::debug::addOptimisationObject
(
	const char* name,
	simpleRegIOobject* obj
)
{
	simpleObjectRegistryEntry* ptr = optimisationObjects().lookupPtr(name);
	if (ptr)
	{
		ptr->append(obj);
	}
	else
	{
		optimisationObjects().append
		(
			name,
			new simpleObjectRegistryEntry
			(
				List<simpleRegIOobject*>(1, obj)
			)
		);
	}
}


void tnbLib::debug::addDimensionSetObject
(
	const char* name,
	simpleRegIOobject* obj
)
{
	simpleObjectRegistryEntry* ptr = dimensionSetObjects().lookupPtr(name);
	if (ptr)
	{
		ptr->append(obj);
	}
	else
	{
		dimensionSetObjects().append
		(
			name,
			new simpleObjectRegistryEntry
			(
				List<simpleRegIOobject*>(1, obj)
			)
		);
	}
}


void tnbLib::debug::addDimensionedConstantObject
(
	const char* name,
	simpleRegIOobject* obj
)
{
	simpleObjectRegistryEntry* ptr = dimensionedConstantObjects().lookupPtr
	(
		name
	);
	if (ptr)
	{
		ptr->append(obj);
	}
	else
	{
		dimensionedConstantObjects().append
		(
			name,
			new simpleObjectRegistryEntry
			(
				List<simpleRegIOobject*>(1, obj)
			)
		);
	}
}


tnbLib::simpleObjectRegistry& tnbLib::debug::debugObjects()
{
	if (!debugObjectsPtr_)
	{
		debugObjectsPtr_ = new simpleObjectRegistry(1000);
	}

	return *debugObjectsPtr_;
}


tnbLib::simpleObjectRegistry& tnbLib::debug::infoObjects()
{
	if (!infoObjectsPtr_)
	{
		infoObjectsPtr_ = new simpleObjectRegistry(100);
	}

	return *infoObjectsPtr_;
}


tnbLib::simpleObjectRegistry& tnbLib::debug::optimisationObjects()
{
	if (!optimisationObjectsPtr_)
	{
		optimisationObjectsPtr_ = new simpleObjectRegistry(100);
	}

	return *optimisationObjectsPtr_;
}


tnbLib::simpleObjectRegistry& tnbLib::debug::dimensionSetObjects()
{
	if (!dimensionSetObjectsPtr_)
	{
		dimensionSetObjectsPtr_ = new simpleObjectRegistry(100);
	}

	return *dimensionSetObjectsPtr_;
}


tnbLib::simpleObjectRegistry& tnbLib::debug::dimensionedConstantObjects()
{
	if (!dimensionedConstantObjectsPtr_)
	{
		dimensionedConstantObjectsPtr_ = new simpleObjectRegistry(100);
	}

	return *dimensionedConstantObjectsPtr_;
}


namespace tnbLib
{

	void listSwitches
	(
		const wordList& debugSwitches,
		const wordList& infoSwitches,
		const wordList& optSwitches,
		const bool unset
	)
	{
		if (unset)
		{
			fileNameList controlDictFiles = findEtcFiles("controlDict", true);
			dictionary controlDict;
			forAllReverse(controlDictFiles, cdfi)
			{
				controlDict.merge(dictionary(IFstream(controlDictFiles[cdfi])()));
			}

			wordHashSet controlDictDebug
			(
				controlDict.subDict("DebugSwitches").sortedToc()
			);

			wordHashSet controlDictInfo
			(
				controlDict.subDict("InfoSwitches").sortedToc()
			);

			wordHashSet controlDictOpt
			(
				controlDict.subDict("OptimisationSwitches").sortedToc()
			);


			IOobject::writeDivider(Info);

			wordHashSet hashset;
			hashset = debugSwitches;
			hashset -= controlDictDebug;
			Info << "Unset DebugSwitches" << hashset.sortedToc() << endl;

			hashset = infoSwitches;
			hashset -= controlDictInfo;
			Info << "Unset InfoSwitches" << hashset.sortedToc() << endl;

			hashset = optSwitches;
			hashset -= controlDictOpt;
			Info << "Unset OptimisationSwitches" << hashset.sortedToc() << endl;
		}
		else
		{
			IOobject::writeDivider(Info);
			Info << "DebugSwitches" << debugSwitches << endl;
			Info << "InfoSwitches" << infoSwitches << endl;
			Info << "OptimisationSwitches" << optSwitches << endl;
		}
	}

}


void tnbLib::debug::listSwitches(const bool unset)
{
	listSwitches
	(
		debug::debugSwitches().sortedToc(),
		debug::infoSwitches().sortedToc(),
		debug::optimisationSwitches().sortedToc(),
		unset
	);
}


void tnbLib::debug::listRegisteredSwitches(const bool unset)
{
	listSwitches
	(
		debug::debugObjects().sortedToc(),
		debug::infoObjects().sortedToc(),
		debug::optimisationObjects().sortedToc(),
		unset
	);
}


// ************************************************************************* //