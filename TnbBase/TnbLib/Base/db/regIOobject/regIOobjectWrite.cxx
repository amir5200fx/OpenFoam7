#include <regIOobject.hxx>

#include <Time.hxx>
#include <OSspecific.hxx>
#include <OFstream.hxx>

//- added by amir
#include <IOstreams.hxx>
#include <Pstream.hxx>
#include <fileOperation.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

bool tnbLib::regIOobject::writeObject
(
	IOstream::streamFormat fmt,
	IOstream::versionNumber ver,
	IOstream::compressionType cmp,
	const bool write
) const
{
	if (!good())
	{
		SeriousErrorInFunction
			<< "bad object " << name()
			<< endl;

		return false;
	}

	if (instance().empty())
	{
		SeriousErrorInFunction
			<< "instance undefined for object " << name()
			<< endl;

		return false;
	}



	//- uncomment this if you want to write global objects on master only
	// bool isGlobal = global();
	bool isGlobal = false;

	if (instance() == time().timeName())
	{
		// Mark as written to local directory
		isGlobal = false;
	}
	else if
		(
			instance() != time().system()
			&& instance() != time().caseSystem()
			&& instance() != time().constant()
			&& instance() != time().caseConstant()
			)
	{
		// Update instance
		const_cast<regIOobject&>(*this).instance() = time().timeName();

		// Mark as written to local directory
		isGlobal = false;
	}

	if (OFstream::debug)
	{
		if (isGlobal)
		{
			Pout << "regIOobject::write() : "
				<< "writing (global) file " << objectPath();
		}
		else
		{
			Pout << "regIOobject::write() : "
				<< "writing (local) file " << objectPath();
		}
	}


	bool osGood = false;


	// Everyone check or just master
	bool masterOnly =
		isGlobal
		&& (
			regIOobject::fileModificationChecking == timeStampMaster
			|| regIOobject::fileModificationChecking == inotifyMaster
			);


	if (Pstream::master() || !masterOnly)
	{
		// if (mkDir(path()))
		//{
		//    // Try opening an OFstream for object
		//    OFstream os(objectPath(), fmt, ver, cmp);
		//
		//    // If any of these fail, return (leave error handling to Ostream
		//    // class)
		//    if (!os.good())
		//    {
		//        return false;
		//    }
		//
		//    if (!writeHeader(os))
		//    {
		//        return false;
		//    }
		//
		//    // Write the data to the Ostream
		//    if (!writeData(os))
		//    {
		//        return false;
		//    }
		//
		//    writeEndDivider(os);
		//
		//    osGood = os.good();
		//}
		osGood = fileHandler().writeObject(*this, fmt, ver, cmp, write);
	}
	else
	{
		// Or scatter the master osGood?
		osGood = true;
	}

	if (OFstream::debug)
	{
		Pout << " .... written" << endl;
	}

	// Only update the lastModified_ time if this object is re-readable,
	// i.e. lastModified_ is already set
	if (watchIndices_.size())
	{
		fileHandler().setUnmodified(watchIndices_.last());
	}

	return osGood;
}


bool tnbLib::regIOobject::write(const bool write) const
{
	return writeObject
	(
		time().writeFormat(),
		IOstream::currentVersion,
		time().writeCompression(),
		write
	);
}

// ************************************************************************* //