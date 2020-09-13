#include <PatchPostProcessing.hxx>

#include <Pstream.hxx>
#include <stringListOps.hxx>
#include <ListOps.hxx>
#include <ListListOps.hxx>

#include <OFstream.hxx>  // added by amir
#include <fvMesh.hxx>  // added by amir
#include <OStringStream.hxx>  // added by amir

// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

template<class CloudType>
tnbLib::label tnbLib::PatchPostProcessing<CloudType>::applyToPatch
(
	const label globalPatchi
) const
{
	forAll(patchIDs_, i)
	{
		if (patchIDs_[i] == globalPatchi)
		{
			return i;
		}
	}

	return -1;
}


// * * * * * * * * * * * * * protected Member Functions  * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchPostProcessing<CloudType>::write()
{
	forAll(patchData_, i)
	{
		List<List<scalar>> procTimes(Pstream::nProcs());
		procTimes[Pstream::myProcNo()] = times_[i];
		Pstream::gatherList(procTimes);

		List<List<string>> procData(Pstream::nProcs());
		procData[Pstream::myProcNo()] = patchData_[i];
		Pstream::gatherList(procData);

		if (Pstream::master())
		{
			const fvMesh& mesh = this->owner().mesh();

			// Create directory if it doesn't exist
			mkDir(this->writeTimeDir());

			const word& patchName = mesh.boundaryMesh()[patchIDs_[i]].name();

			OFstream patchOutFile
			(
				this->writeTimeDir() / patchName + ".post",
				IOstream::ASCII,
				IOstream::currentVersion,
				mesh.time().writeCompression()
			);

			List<string> globalData;
			globalData = ListListOps::combine<List<string>>
				(
					procData,
					accessOp<List<string>>()
					);

			List<scalar> globalTimes;
			globalTimes = ListListOps::combine<List<scalar>>
				(
					procTimes,
					accessOp<List<scalar>>()
					);

			labelList indices;
			sortedOrder(globalTimes, indices);

			string header("# Time currentProc " + parcelType::propertyList_);
			patchOutFile << header.c_str() << nl;

			forAll(globalTimes, i)
			{
				label dataI = indices[i];

				patchOutFile
					<< globalTimes[dataI] << ' '
					<< globalData[dataI].c_str()
					<< nl;
			}
		}

		patchData_[i].clearStorage();
		times_[i].clearStorage();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchPostProcessing<CloudType>::PatchPostProcessing
(
	const dictionary& dict,
	CloudType& owner,
	const word& modelName
)
	:
	CloudFunctionObject<CloudType>(dict, owner, modelName, typeName),
	maxStoredParcels_(readScalar(this->coeffDict().lookup("maxStoredParcels"))),
	patchIDs_(),
	times_(),
	patchData_()
{
	const wordList allPatchNames = owner.mesh().boundaryMesh().names();
	wordList patchName(this->coeffDict().lookup("patches"));

	labelHashSet uniquePatchIDs;
	forAllReverse(patchName, i)
	{
		labelList patchIDs = findStrings(patchName[i], allPatchNames);

		if (patchIDs.empty())
		{
			WarningInFunction
				<< "Cannot find any patch names matching " << patchName[i]
				<< endl;
		}

		uniquePatchIDs.insert(patchIDs);
	}

	patchIDs_ = uniquePatchIDs.toc();

	if (debug)
	{
		forAll(patchIDs_, i)
		{
			const label patchi = patchIDs_[i];
			const word& patchName = owner.mesh().boundaryMesh()[patchi].name();
			Info << "Post-process patch " << patchName << endl;
		}
	}

	patchData_.setSize(patchIDs_.size());
	times_.setSize(patchIDs_.size());
}


template<class CloudType>
tnbLib::PatchPostProcessing<CloudType>::PatchPostProcessing
(
	const PatchPostProcessing<CloudType>& ppm
)
	:
	CloudFunctionObject<CloudType>(ppm),
	maxStoredParcels_(ppm.maxStoredParcels_),
	patchIDs_(ppm.patchIDs_),
	times_(ppm.times_),
	patchData_(ppm.patchData_)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

template<class CloudType>
tnbLib::PatchPostProcessing<CloudType>::~PatchPostProcessing()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class CloudType>
void tnbLib::PatchPostProcessing<CloudType>::postPatch
(
	const parcelType& p,
	const polyPatch& pp,
	bool&
)
{
	const label patchi = pp.index();
	const label localPatchi = applyToPatch(patchi);

	if (localPatchi != -1 && patchData_[localPatchi].size() < maxStoredParcels_)
	{
		times_[localPatchi].append(this->owner().time().value());

		OStringStream data;
		data << Pstream::myProcNo() << ' ' << p;

		patchData_[localPatchi].append(data.str());
	}
}


// ************************************************************************* //