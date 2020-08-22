#include <polyTopoChanger.hxx>

#include <polyMesh.hxx>
#include <polyTopoChange.hxx>
#include <Time.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(polyTopoChanger, 0);
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

void tnbLib::polyTopoChanger::readModifiers()
{
	if
		(
			readOpt() == IOobject::MUST_READ
			|| readOpt() == IOobject::MUST_READ_IF_MODIFIED
			|| (readOpt() == IOobject::READ_IF_PRESENT && headerOk())
			)
	{
		if (readOpt() == IOobject::MUST_READ_IF_MODIFIED)
		{
			WarningInFunction
				<< "Specified IOobject::MUST_READ_IF_MODIFIED but class"
				<< " does not support automatic re-reading."
				<< endl;
		}


		PtrList<polyMeshModifier>& modifiers = *this;

		// Read modifiers
		Istream& is = readStream(typeName);

		PtrList<entry> patchEntries(is);
		modifiers.setSize(patchEntries.size());

		forAll(modifiers, modifierI)
		{
			modifiers.set
			(
				modifierI,
				polyMeshModifier::New
				(
					patchEntries[modifierI].keyword(),
					patchEntries[modifierI].dict(),
					modifierI,
					*this
				)
			);
		}

		// Check state of IOstream
		is.check("polyTopoChanger::readModifiers()");

		close();
	}
}


tnbLib::polyTopoChanger::polyTopoChanger
(
	const IOobject& io,
	polyMesh& mesh
)
	:
	PtrList<polyMeshModifier>(),
	regIOobject(io),
	mesh_(mesh)
{
	readModifiers();
}


tnbLib::polyTopoChanger::polyTopoChanger(polyMesh& mesh)
	:
	PtrList<polyMeshModifier>(),
	regIOobject
	(
		IOobject
		(
			"meshModifiers",
			mesh.time().findInstance
			(
				mesh.meshDir(),
				"meshModifiers",
				IOobject::READ_IF_PRESENT
			),
			mesh.meshSubDir,
			mesh,
			IOobject::READ_IF_PRESENT,
			IOobject::NO_WRITE
		)
	),
	mesh_(mesh)
{
	readModifiers();
}


tnbLib::wordList tnbLib::polyTopoChanger::types() const
{
	const PtrList<polyMeshModifier>& modifiers = *this;

	wordList t(modifiers.size());

	forAll(modifiers, modifierI)
	{
		t[modifierI] = modifiers[modifierI].type();
	}

	return t;
}


tnbLib::wordList tnbLib::polyTopoChanger::names() const
{
	const PtrList<polyMeshModifier>& modifiers = *this;

	wordList t(modifiers.size());

	forAll(modifiers, modifierI)
	{
		t[modifierI] = modifiers[modifierI].name();
	}

	return t;
}


bool tnbLib::polyTopoChanger::changeTopology() const
{
	// Go through all mesh modifiers and accumulate the morphing information
	const PtrList<polyMeshModifier>& topoChanges = *this;

	bool triggerChange = false;

	forAll(topoChanges, morphI)
	{
		if (topoChanges[morphI].active())
		{
			bool curTriggerChange = topoChanges[morphI].changeTopology();

			if (debug)
			{
				Info << "Modifier " << morphI << " named "
					<< topoChanges[morphI].name();

				if (curTriggerChange)
				{
					Info << " morphing" << endl;
				}
				else
				{
					Info << " unchanged" << endl;
				}
			}

			triggerChange = triggerChange || curTriggerChange;
		}
		else
		{
			if (debug)
			{
				Info << "Modifier " << morphI << " named "
					<< topoChanges[morphI].name() << " inactive" << endl;
			}
		}

	}

	return triggerChange;
}


tnbLib::autoPtr<tnbLib::polyTopoChange>
tnbLib::polyTopoChanger::topoChangeRequest() const
{
	// Collect changes from all modifiers
	const PtrList<polyMeshModifier>& topoChanges = *this;

	polyTopoChange* refPtr(new polyTopoChange(mesh()));
	polyTopoChange& ref = *refPtr;

	forAll(topoChanges, morphI)
	{
		if (topoChanges[morphI].active())
		{
			topoChanges[morphI].setRefinement(ref);
		}
	}

	return autoPtr<polyTopoChange>(refPtr);
}


void tnbLib::polyTopoChanger::modifyMotionPoints(pointField& p) const
{
	const PtrList<polyMeshModifier>& topoChanges = *this;

	forAll(topoChanges, morphI)
	{
		if (topoChanges[morphI].active())
		{
			topoChanges[morphI].modifyMotionPoints(p);
		}
	}
}


void tnbLib::polyTopoChanger::update(const mapPolyMesh& m)
{
	// Go through all mesh modifiers and accumulate the morphing information
	PtrList<polyMeshModifier>& topoChanges = *this;

	forAll(topoChanges, morphI)
	{
		topoChanges[morphI].updateMesh(m);
	}

	// Force the mesh modifiers to auto-write.  This allows us to
	// preserve the current state of modifiers corresponding with
	// the mesh.
	writeOpt() = IOobject::AUTO_WRITE;
	instance() = mesh_.time().timeName();
}


tnbLib::autoPtr<tnbLib::mapPolyMesh> tnbLib::polyTopoChanger::changeMesh
(
	const bool inflate,
	const bool syncParallel,
	const bool orderCells,
	const bool orderPoints
)
{
	if (changeTopology())
	{
		autoPtr<polyTopoChange> ref = topoChangeRequest();

		autoPtr<mapPolyMesh> topoChangeMap = ref().changeMesh
		(
			mesh_,
			inflate,
			syncParallel,
			orderCells,
			orderPoints
		);

		update(topoChangeMap());
		mesh_.updateMesh(topoChangeMap());
		return topoChangeMap;
	}
	else
	{
		return autoPtr<mapPolyMesh>(nullptr);
	}
}


void tnbLib::polyTopoChanger::addTopologyModifiers
(
	const List<polyMeshModifier*>& tm
)
{
	setSize(tm.size());

	// Copy the patch pointers
	forAll(tm, tmI)
	{
		if (tm[tmI]->topoChanger() != *this)
		{
			FatalErrorInFunction
				<< "Mesh modifier created with different mesh reference."
				<< abort(FatalError);
		}
		set(tmI, tm[tmI]);
	}

	writeOpt() = IOobject::AUTO_WRITE;
}


tnbLib::label tnbLib::polyTopoChanger::findModifierID
(
	const word& modName
) const
{
	const PtrList<polyMeshModifier>& topoChanges = *this;

	forAll(topoChanges, morphI)
	{
		if (topoChanges[morphI].name() == modName)
		{
			return morphI;
		}
	}

	// Modifier not found
	if (debug)
	{
		WarningInFunction
			<< "List of available modifier names: " << names() << endl;
	}

	// Not found, return -1
	return -1;
}


bool tnbLib::polyTopoChanger::writeData(Ostream& os) const
{
	os << *this;
	return os.good();
}


// * * * * * * * * * * * * * * * Member Operators  * * * * * * * * * * * * * //

bool tnbLib::polyTopoChanger::operator!=(const polyTopoChanger& me) const
{
	return &me != this;
}


bool tnbLib::polyTopoChanger::operator==(const polyTopoChanger& me) const
{
	return &me == this;
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const polyTopoChanger& mme)
{
	os << mme.size() << nl << token::BEGIN_LIST;

	forAll(mme, mmeI)
	{
		mme[mmeI].writeDict(os);
	}

	os << token::END_LIST;

	return os;
}


// ************************************************************************* //