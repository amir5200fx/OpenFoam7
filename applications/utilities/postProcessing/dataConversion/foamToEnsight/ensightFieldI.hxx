#pragma once
#include "itoa.hxx"
#include "ensightBinaryStream.hxx"
#include "ensightAsciiStream.hxx"

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <OFstream.hxx>
#include <IOmanip.hxx>
#include <volPointInterpolation.hxx>
#include <globalIndex.hxx>
#include <ensightPTraits.hxx>


namespace tnbLib
{
	// * * * * * * * * * * * * * * * Global Functions  * * * * * * * * * * * * * //

	template<class Type>
	tmp<GeometricField<Type, fvPatchField, volMesh>>
		volField
		(
			const fvMeshSubset& meshSubsetter,
			const GeometricField<Type, fvPatchField, volMesh>& vf
		)
	{
		if (meshSubsetter.hasSubMesh())
		{
			tmp<GeometricField<Type, fvPatchField, volMesh>> tfld
			(
				meshSubsetter.interpolate(vf)
			);
			tfld.ref().checkOut();
			tfld.ref().rename(vf.name());
			return tfld;
		}
		else
		{
			return vf;
		}
	}


	template<class Type>
	Field<Type> map
	(
		const Field<Type>& vf,
		const labelList& map1,
		const labelList& map2
	)
	{
		Field<Type> mf(map1.size() + map2.size());

		forAll(map1, i)
		{
			mf[i] = vf[map1[i]];
		}

		label offset = map1.size();

		forAll(map2, i)
		{
			mf[i + offset] = vf[map2[i]];
		}

		return mf;
	}


	template<class Type>
	void writeField
	(
		const char* key,
		const Field<Type>& vf,
		ensightStream& ensightFile
	)
	{
		if (returnReduce(vf.size(), sumOp<label>()) > 0)
		{
			if (Pstream::master())
			{
				ensightFile.write(key);

				for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
				{
					ensightFile.write(vf.component(cmpt));

					for (int slave = 1; slave < Pstream::nProcs(); slave++)
					{
						IPstream fromSlave(Pstream::commsTypes::scheduled, slave);
						scalarField slaveData(fromSlave);
						ensightFile.write(slaveData);
					}
				}
			}
			else
			{
				for (direction cmpt = 0; cmpt < pTraits<Type>::nComponents; cmpt++)
				{
					OPstream toMaster
					(
						Pstream::commsTypes::scheduled,
						Pstream::masterNo()
					);
					toMaster << vf.component(cmpt);
				}
			}
		}
	}


	template<class Type>
	bool writePatchField
	(
		const Field<Type>& pf,
		const label patchi,
		const label ensightPatchi,
		const faceSets& boundaryFaceSet,
		const ensightMesh::nFacePrimitives& nfp,
		ensightStream& ensightFile
	)
	{
		if (nfp.nTris || nfp.nQuads || nfp.nPolys)
		{
			if (Pstream::master())
			{
				ensightFile.writePartHeader(ensightPatchi);
			}

			writeField
			(
				"tria3",
				Field<Type>(pf, boundaryFaceSet.tris),
				ensightFile
			);

			writeField
			(
				"quad4",
				Field<Type>(pf, boundaryFaceSet.quads),
				ensightFile
			);

			writeField
			(
				"nsided",
				Field<Type>(pf, boundaryFaceSet.polys),
				ensightFile
			);

			return true;
		}
		else
		{
			return false;
		}
	}


	template<class Type>
	void writePatchField
	(
		const word& fieldName,
		const Field<Type>& pf,
		const word& patchName,
		const ensightMesh& eMesh,
		const fileName& postProcPath,
		const word& prepend,
		const label timeIndex,
		const bool binary,
		Ostream& ensightCaseFile
	)
	{
		const Time& runTime = eMesh.mesh().time();

		const List<faceSets>& boundaryFaceSets = eMesh.boundaryFaceSets();
		const wordList& allPatchNames = eMesh.allPatchNames();
		const HashTable<ensightMesh::nFacePrimitives>&
			nPatchPrims = eMesh.nPatchPrims();

		label ensightPatchi = eMesh.patchPartOffset();

		label patchi = -1;

		forAll(allPatchNames, i)
		{
			if (allPatchNames[i] == patchName)
			{
				patchi = i;
				break;
			}
			ensightPatchi++;
		}


		word pfName = patchName + '.' + fieldName;

		word timeFile = prepend + tnbLib::itoa(timeIndex);

		ensightStream* ensightFilePtr = nullptr;
		if (Pstream::master())
		{
			if (timeIndex == 0)
			{
				ensightCaseFile.setf(ios_base::left);

				ensightCaseFile
					<< ensightPTraits<Type>::typeName
					<< " per element:            1       "
					<< setw(15) << pfName
					<< (' ' + prepend + "****." + pfName).c_str()
					<< nl;
			}

			// set the filename of the ensight file
			fileName ensightFileName(timeFile + "." + pfName);

			if (binary)
			{
				ensightFilePtr = new ensightBinaryStream
				(
					postProcPath / ensightFileName,
					runTime
				);
			}
			else
			{
				ensightFilePtr = new ensightAsciiStream
				(
					postProcPath / ensightFileName,
					runTime
				);
			}
		}

		ensightStream& ensightFile = *ensightFilePtr;

		if (Pstream::master())
		{
			ensightFile.write(ensightPTraits<Type>::typeName);
		}

		if (patchi >= 0)
		{
			writePatchField
			(
				pf,
				patchi,
				ensightPatchi,
				boundaryFaceSets[patchi],
				nPatchPrims.find(patchName)(),
				ensightFile
			);
		}
		else
		{
			faceSets nullFaceSets;

			writePatchField
			(
				Field<Type>(),
				-1,
				ensightPatchi,
				nullFaceSets,
				nPatchPrims.find(patchName)(),
				ensightFile
			);
		}

		if (Pstream::master())
		{
			delete ensightFilePtr;
		}
	}


	template<class Type>
	void ensightField
	(
		const GeometricField<Type, fvPatchField, volMesh>& vf,
		const ensightMesh& eMesh,
		const fileName& postProcPath,
		const word& prepend,
		const label timeIndex,
		const bool binary,
		Ostream& ensightCaseFile
	)
	{
		Info << "Converting field " << vf.name() << endl;

		word timeFile = prepend + tnbLib::itoa(timeIndex);

		const fvMesh& mesh = eMesh.mesh();
		const Time& runTime = mesh.time();

		const cellSets& meshCellSets = eMesh.meshCellSets();
		const List<faceSets>& boundaryFaceSets = eMesh.boundaryFaceSets();
		const wordList& allPatchNames = eMesh.allPatchNames();
		const wordHashSet& patchNames = eMesh.patchNames();
		const HashTable<ensightMesh::nFacePrimitives>&
			nPatchPrims = eMesh.nPatchPrims();
		const List<faceSets>& faceZoneFaceSets = eMesh.faceZoneFaceSets();
		const wordHashSet& faceZoneNames = eMesh.faceZoneNames();
		const HashTable<ensightMesh::nFacePrimitives>&
			nFaceZonePrims = eMesh.nFaceZonePrims();

		const labelList& tets = meshCellSets.tets;
		const labelList& pyrs = meshCellSets.pyrs;
		const labelList& prisms = meshCellSets.prisms;
		const labelList& wedges = meshCellSets.wedges;
		const labelList& hexes = meshCellSets.hexes;
		const labelList& polys = meshCellSets.polys;

		ensightStream* ensightFilePtr = nullptr;
		if (Pstream::master())
		{
			// set the filename of the ensight file
			fileName ensightFileName(timeFile + "." + vf.name());

			if (binary)
			{
				ensightFilePtr = new ensightBinaryStream
				(
					postProcPath / ensightFileName,
					runTime
				);
			}
			else
			{
				ensightFilePtr = new ensightAsciiStream
				(
					postProcPath / ensightFileName,
					runTime
				);
			}
		}

		ensightStream& ensightFile = *ensightFilePtr;

		if (Pstream::master())
		{
			if (timeIndex == 0)
			{
				ensightCaseFile.setf(ios_base::left);

				ensightCaseFile
					<< ensightPTraits<Type>::typeName
					<< " per element:            1       "
					<< setw(15) << vf.name()
					<< (' ' + prepend + "****." + vf.name()).c_str()
					<< nl;
			}

			ensightFile.write(ensightPTraits<Type>::typeName);
		}

		if (patchNames.empty())
		{
			eMesh.barrier();

			if (Pstream::master())
			{
				ensightFile.writePartHeader(1);
			}

			writeField
			(
				"hexa8",
				map(vf, hexes, wedges),
				ensightFile
			);

			writeField
			(
				"penta6",
				Field<Type>(vf, prisms),
				ensightFile
			);

			writeField
			(
				"pyramid5",
				Field<Type>(vf, pyrs),
				ensightFile
			);

			writeField
			(
				"tetra4",
				Field<Type>(vf, tets),
				ensightFile
			);

			writeField
			(
				"nfaced",
				Field<Type>(vf, polys),
				ensightFile
			);
		}

		label ensightPatchi = eMesh.patchPartOffset();

		forAll(allPatchNames, patchi)
		{
			const word& patchName = allPatchNames[patchi];

			eMesh.barrier();

			if (patchNames.empty() || patchNames.found(patchName))
			{
				if
					(
						writePatchField
						(
							vf.boundaryField()[patchi],
							patchi,
							ensightPatchi,
							boundaryFaceSets[patchi],
							nPatchPrims.find(patchName)(),
							ensightFile
						)
						)
				{
					ensightPatchi++;
				}
			}
		}

		// write faceZones, if requested
		if (faceZoneNames.size())
		{
			// Interpolates cell values to faces - needed only when exporting
			// faceZones...
			GeometricField<Type, fvsPatchField, surfaceMesh> sf
			(
				linearInterpolate(vf)
			);

			forAllConstIter(wordHashSet, faceZoneNames, iter)
			{
				const word& faceZoneName = iter.key();

				eMesh.barrier();

				label zoneID = mesh.faceZones().findZoneID(faceZoneName);

				const faceZone& fz = mesh.faceZones()[zoneID];

				// Prepare data to write
				label nIncluded = 0;
				forAll(fz, i)
				{
					if (eMesh.faceToBeIncluded(fz[i]))
					{
						++nIncluded;
					}
				}

				Field<Type> values(nIncluded);

				// Loop on the faceZone and store the needed field values
				label j = 0;
				forAll(fz, i)
				{
					label facei = fz[i];
					if (mesh.isInternalFace(facei))
					{
						values[j] = sf[facei];
						++j;
					}
					else
					{
						if (eMesh.faceToBeIncluded(facei))
						{
							label patchi = mesh.boundaryMesh().whichPatch(facei);
							const polyPatch& pp = mesh.boundaryMesh()[patchi];
							label patchFacei = pp.whichFace(facei);
							Type value = sf.boundaryField()[patchi][patchFacei];
							values[j] = value;
							++j;
						}
					}
				}

				if
					(
						writePatchField
						(
							values,
							zoneID,
							ensightPatchi,
							faceZoneFaceSets[zoneID],
							nFaceZonePrims.find(faceZoneName)(),
							ensightFile
						)
						)
				{
					ensightPatchi++;
				}
			}
		}
		if (Pstream::master())
		{
			delete ensightFilePtr;
		}
	}


	template<class Type>
	void ensightPointField
	(
		const GeometricField<Type, pointPatchField, pointMesh>& pf,
		const ensightMesh& eMesh,
		const fileName& postProcPath,
		const word& prepend,
		const label timeIndex,
		const bool binary,
		Ostream& ensightCaseFile
	)
	{
		Info << "Converting field " << pf.name() << endl;

		word timeFile = prepend + tnbLib::itoa(timeIndex);

		const fvMesh& mesh = eMesh.mesh();
		const wordList& allPatchNames = eMesh.allPatchNames();
		const wordHashSet& patchNames = eMesh.patchNames();
		const wordHashSet& faceZoneNames = eMesh.faceZoneNames();


		ensightStream* ensightFilePtr = nullptr;
		if (Pstream::master())
		{
			// set the filename of the ensight file
			fileName ensightFileName(timeFile + "." + pf.name());

			if (binary)
			{
				ensightFilePtr = new ensightBinaryStream
				(
					postProcPath / ensightFileName,
					mesh.time()
				);
			}
			else
			{
				ensightFilePtr = new ensightAsciiStream
				(
					postProcPath / ensightFileName,
					mesh.time()
				);
			}
		}

		ensightStream& ensightFile = *ensightFilePtr;

		if (Pstream::master())
		{
			if (timeIndex == 0)
			{
				ensightCaseFile.setf(ios_base::left);

				ensightCaseFile
					<< ensightPTraits<Type>::typeName
					<< " per node:            1       "
					<< setw(15) << pf.name()
					<< (' ' + prepend + "****." + pf.name()).c_str()
					<< nl;
			}

			ensightFile.write(ensightPTraits<Type>::typeName);
		}

		if (eMesh.patchNames().empty())
		{
			eMesh.barrier();

			if (Pstream::master())
			{
				ensightFile.writePartHeader(1);
			}

			writeField
			(
				"coordinates",
				Field<Type>(pf.primitiveField(), eMesh.uniquePointMap()),
				ensightFile
			);
		}


		label ensightPatchi = eMesh.patchPartOffset();

		forAll(allPatchNames, patchi)
		{
			const word& patchName = allPatchNames[patchi];

			eMesh.barrier();

			if (patchNames.empty() || patchNames.found(patchName))
			{
				const fvPatch& p = mesh.boundary()[patchi];
				if
					(
						returnReduce(p.size(), sumOp<label>())
				> 0
						)
				{
					// Renumber the patch points/faces into unique points
					labelList pointToGlobal;
					labelList uniqueMeshPointLabels;
					autoPtr<globalIndex> globalPointsPtr =
						mesh.globalData().mergePoints
						(
							p.patch().meshPoints(),
							p.patch().meshPointMap(),
							pointToGlobal,
							uniqueMeshPointLabels
						);

					if (Pstream::master())
					{
						ensightFile.writePartHeader(ensightPatchi);
					}

					writeField
					(
						"coordinates",
						Field<Type>(pf.primitiveField(), uniqueMeshPointLabels),
						ensightFile
					);

					ensightPatchi++;
				}
			}
		}

		// write faceZones, if requested
		if (faceZoneNames.size())
		{
			forAllConstIter(wordHashSet, faceZoneNames, iter)
			{
				const word& faceZoneName = iter.key();

				eMesh.barrier();

				label zoneID = mesh.faceZones().findZoneID(faceZoneName);

				const faceZone& fz = mesh.faceZones()[zoneID];

				if (returnReduce(fz().nPoints(), sumOp<label>()) > 0)
				{
					// Renumber the faceZone points/faces into unique points
					labelList pointToGlobal;
					labelList uniqueMeshPointLabels;
					autoPtr<globalIndex> globalPointsPtr =
						mesh.globalData().mergePoints
						(
							fz().meshPoints(),
							fz().meshPointMap(),
							pointToGlobal,
							uniqueMeshPointLabels
						);

					if (Pstream::master())
					{
						ensightFile.writePartHeader(ensightPatchi);
					}

					writeField
					(
						"coordinates",
						Field<Type>
						(
							pf.primitiveField(),
							uniqueMeshPointLabels
							),
						ensightFile
					);

					ensightPatchi++;
				}
			}
		}

		if (Pstream::master())
		{
			delete ensightFilePtr;
		}
	}


	template<class Type>
	void ensightField
	(
		const GeometricField<Type, fvPatchField, volMesh>& vf,
		const ensightMesh& eMesh,
		const fileName& postProcPath,
		const word& prepend,
		const label timeIndex,
		const bool binary,
		const bool nodeValues,
		Ostream& ensightCaseFile
	)
	{
		if (nodeValues)
		{
			tmp<GeometricField<Type, pointPatchField, pointMesh>> pfld
			(
				volPointInterpolation::New(vf.mesh()).interpolate(vf)
			);
			pfld.ref().rename(vf.name());

			ensightPointField<Type>
				(
					pfld,
					eMesh,
					postProcPath,
					prepend,
					timeIndex,
					binary,
					ensightCaseFile
					);
		}
		else
		{
			ensightField<Type>
				(
					vf,
					eMesh,
					postProcPath,
					prepend,
					timeIndex,
					binary,
					ensightCaseFile
					);
		}
	}


	// ************************************************************************* //
}