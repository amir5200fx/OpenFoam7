#include <fvOptionList.hxx>

#include <surfaceFields.hxx>

#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace fv
	{
		defineTypeNameAndDebug(optionList, 0);
	}
}


// * * * * * * * * * * * * Protected Member Functions  * * * * * * * * * * * //

const tnbLib::dictionary& tnbLib::fv::optionList::optionsDict
(
	const dictionary& dict
) const
{
	if (dict.found("options"))
	{
		return dict.subDict("options");
	}
	else
	{
		return dict;
	}
}


bool tnbLib::fv::optionList::readOptions(const dictionary& dict)
{
	checkTimeIndex_ = mesh_.time().timeIndex() + 2;

	bool allOk = true;
	forAll(*this, i)
	{
		option& bs = this->operator[](i);
		bool ok = bs.read(dict.subDict(bs.name()));
		allOk = (allOk && ok);
	}
	return allOk;
}


void tnbLib::fv::optionList::checkApplied() const
{
	if (mesh_.time().timeIndex() == checkTimeIndex_)
	{
		forAll(*this, i)
		{
			const option& bs = this->operator[](i);
			bs.checkApplied();
		}
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::fv::optionList::optionList(const fvMesh& mesh, const dictionary& dict)
	:
	PtrList<option>(),
	mesh_(mesh),
	checkTimeIndex_(mesh_.time().startTimeIndex() + 2)
{
	reset(optionsDict(dict));
}


tnbLib::fv::optionList::optionList(const fvMesh& mesh)
	:
	PtrList<option>(),
	mesh_(mesh),
	checkTimeIndex_(mesh_.time().startTimeIndex() + 2)
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::fv::optionList::reset(const dictionary& dict)
{
	// Count number of active fvOptions
	label count = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isDict())
		{
			count++;
		}
	}

	this->setSize(count);
	label i = 0;
	forAllConstIter(dictionary, dict, iter)
	{
		if (iter().isDict())
		{
			const word& name = iter().keyword();
			const dictionary& sourceDict = iter().dict();

			this->set
			(
				i++,
				option::New(name, sourceDict, mesh_)
			);
		}
	}
}


bool tnbLib::fv::optionList::appliesToField(const word& fieldName) const
{
	forAll(*this, i)
	{
		const option& source = this->operator[](i);

		label fieldi = source.applyToField(fieldName);

		if (fieldi != -1)
		{
			return true;
		}
	}

	return false;
}


bool tnbLib::fv::optionList::read(const dictionary& dict)
{
	return readOptions(optionsDict(dict));
}


bool tnbLib::fv::optionList::writeData(Ostream& os) const
{
	// Write list contents
	forAll(*this, i)
	{
		os << nl;
		this->operator[](i).writeHeader(os);
		this->operator[](i).writeData(os);
		this->operator[](i).writeFooter(os);
	}

	// Check state of IOstream
	return os.good();
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const fv::optionList& options)
{
	options.writeData(os);
	return os;
}


// ************************************************************************* //