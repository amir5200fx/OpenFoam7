#pragma once
#include <fileOperation.hxx>
#include <Istream.hxx>
#include <IOstreams.hxx>
#include <Pstream.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
bool tnbLib::IOobject::typeHeaderOk(const bool checkType)
{
	bool ok = true;

	// Everyone check or just master
	bool masterOnly =
		typeGlobal<Type>()
		&& (
			IOobject::fileModificationChecking == timeStampMaster
			|| IOobject::fileModificationChecking == inotifyMaster
			);

	const fileOperation& fp = tnbLib::fileHandler();

	// Determine local status
	if (!masterOnly || Pstream::master())
	{
		fileName fName(typeFilePath<Type>(*this));

		ok = fp.readHeader(*this, fName, Type::typeName);
		if (ok && checkType && headerClassName_ != Type::typeName)
		{
			WarningInFunction
				<< "unexpected class name " << headerClassName_
				<< " expected " << Type::typeName
				<< " when reading " << fName << endl;

			ok = false;
		}
	}

	// If masterOnly make sure all processors know about it
	if (masterOnly)
	{
		Pstream::scatter(ok);
	}

	return ok;
}


template<class Type>
void tnbLib::IOobject::warnNoRereading() const
{
	if (readOpt() == IOobject::MUST_READ_IF_MODIFIED)
	{
		WarningInFunction
			<< Type::typeName << ' ' << name()
			<< " constructed with IOobject::MUST_READ_IF_MODIFIED"
			" but " << Type::typeName
			<< " does not support automatic rereading."
			<< endl;
	}
}


// ************************************************************************* //