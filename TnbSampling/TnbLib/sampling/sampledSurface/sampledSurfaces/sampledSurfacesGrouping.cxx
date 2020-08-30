#include <sampledSurfaces.hxx>

#include <Time.hxx>  // added by amir
#include <stringListOps.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

tnbLib::label tnbLib::sampledSurfaces::classifyFields()
{
	label nFields = 0;

	if (loadFromFiles_)
	{
		// Check files for a particular time
		IOobjectList objects(mesh_, mesh_.time().timeName());
		wordList allFields = objects.sortedNames();

		forAll(fieldSelection_, i)
		{
			labelList indices = findStrings(fieldSelection_[i], allFields);

			if (indices.size())
			{
				nFields += indices.size();
			}
			else
			{
				WarningInFunction
					<< "Cannot find field file matching "
					<< fieldSelection_[i] << endl;
			}
		}
	}
	else
	{
		// Check currently available fields
		wordList allFields = mesh_.sortedNames();
		labelList indices = findStrings(fieldSelection_, allFields);

		forAll(fieldSelection_, i)
		{
			labelList indices = findStrings(fieldSelection_[i], allFields);

			if (indices.size())
			{
				nFields += indices.size();
			}
			else
			{
				WarningInFunction
					<< "Cannot find registered field matching "
					<< fieldSelection_[i] << endl;
			}
		}
	}

	return nFields;
}


// ************************************************************************* //