#pragma once
#include <Time.hxx>
#include <PtrList.hxx>
#include <fvPatchFields.hxx>
#include <emptyFvPatch.hxx>
#include <emptyFvPatchField.hxx>
#include <emptyFvsPatchField.hxx>

// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

template<class Type>
tnbLib::tmp<tnbLib::DimensionedField<Type, tnbLib::volMesh>>
tnbLib::fvFieldReconstructor::reconstructFvVolumeInternalField
(
	const IOobject& fieldIoObject,
	const PtrList<DimensionedField<Type, volMesh>>& procFields
) const
{
	// Create the internalField
	Field<Type> internalField(mesh_.nCells());

	forAll(procMeshes_, proci)
	{
		const DimensionedField<Type, volMesh>& procField = procFields[proci];

		// Set the cell values in the reconstructed field
		internalField.rmap
		(
			procField.field(),
			cellProcAddressing_[proci]
		);
	}

	return tmp<DimensionedField<Type, volMesh>>
		(
			new DimensionedField<Type, volMesh>
			(
				fieldIoObject,
				mesh_,
				procFields[0].dimensions(),
				internalField
				)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::DimensionedField<Type, tnbLib::volMesh>>
tnbLib::fvFieldReconstructor::reconstructFvVolumeInternalField
(
	const IOobject& fieldIoObject
) const
{
	// Read the field for all the processors
	PtrList<DimensionedField<Type, volMesh>> procFields
	(
		procMeshes_.size()
	);

	forAll(procMeshes_, proci)
	{
		procFields.set
		(
			proci,
			new DimensionedField<Type, volMesh>
			(
				IOobject
				(
					fieldIoObject.name(),
					procMeshes_[proci].time().timeName(),
					procMeshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				procMeshes_[proci]
				)
		);
	}


	return reconstructFvVolumeInternalField
	(
		IOobject
		(
			fieldIoObject.name(),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		procFields
	);
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::fvFieldReconstructor::reconstructFvVolumeField
(
	const IOobject& fieldIoObject,
	const PtrList<GeometricField<Type, fvPatchField, volMesh>>& procFields
) const
{
	// Create the internalField
	Field<Type> internalField(mesh_.nCells());

	// Create the patch fields
	PtrList<fvPatchField<Type>> patchFields(mesh_.boundary().size());

	forAll(procFields, proci)
	{
		const GeometricField<Type, fvPatchField, volMesh>& procField =
			procFields[proci];

		// Set the cell values in the reconstructed field
		internalField.rmap
		(
			procField.primitiveField(),
			cellProcAddressing_[proci]
		);

		// Set the boundary patch values in the reconstructed field
		forAll(boundaryProcAddressing_[proci], patchi)
		{
			// Get patch index of the original patch
			const label curBPatch = boundaryProcAddressing_[proci][patchi];

			// Get addressing slice for this patch
			const labelList::subList cp =
				procField.mesh().boundary()[patchi].patchSlice
				(
					faceProcAddressing_[proci]
				);

			// check if the boundary patch is not a processor patch
			if (curBPatch >= 0)
			{
				// Regular patch. Fast looping

				if (!patchFields(curBPatch))
				{
					patchFields.set
					(
						curBPatch,
						fvPatchField<Type>::New
						(
							procField.boundaryField()[patchi],
							mesh_.boundary()[curBPatch],
							DimensionedField<Type, volMesh>::null(),
							fvPatchFieldReconstructor
							(
								mesh_.boundary()[curBPatch].size()
							)
						)
					);
				}

				const label curPatchStart =
					mesh_.boundaryMesh()[curBPatch].start();

				labelList reverseAddressing(cp.size());

				forAll(cp, facei)
				{
					// Check
					if (cp[facei] <= 0)
					{
						FatalErrorInFunction
							<< "Processor " << proci
							<< " patch "
							<< procField.mesh().boundary()[patchi].name()
							<< " face " << facei
							<< " originates from reversed face since "
							<< cp[facei]
							<< exit(FatalError);
					}

					// Subtract one to take into account offsets for
					// face direction.
					reverseAddressing[facei] = cp[facei] - 1 - curPatchStart;
				}


				patchFields[curBPatch].rmap
				(
					procField.boundaryField()[patchi],
					reverseAddressing
				);
			}
			else
			{
				const Field<Type>& curProcPatch =
					procField.boundaryField()[patchi];

				// In processor patches, there's a mix of internal faces (some
				// of them turned) and possible cyclics. Slow loop
				forAll(cp, facei)
				{
					// Subtract one to take into account offsets for
					// face direction.
					label curF = cp[facei] - 1;

					// Is the face on the boundary?
					if (curF >= mesh_.nInternalFaces())
					{
						label curBPatch = mesh_.boundaryMesh().whichPatch(curF);

						if (!patchFields(curBPatch))
						{
							patchFields.set
							(
								curBPatch,
								fvPatchField<Type>::New
								(
									mesh_.boundary()[curBPatch].type(),
									mesh_.boundary()[curBPatch],
									DimensionedField<Type, volMesh>::null()
								)
							);
						}

						// add the face
						label curPatchFace =
							mesh_.boundaryMesh()
							[curBPatch].whichFace(curF);

						patchFields[curBPatch][curPatchFace] =
							curProcPatch[facei];
					}
				}
			}
		}
	}

	forAll(mesh_.boundary(), patchi)
	{
		// add empty patches
		if
			(
				isType<emptyFvPatch>(mesh_.boundary()[patchi])
				&& !patchFields(patchi)
				)
		{
			patchFields.set
			(
				patchi,
				fvPatchField<Type>::New
				(
					emptyFvPatchField<Type>::typeName,
					mesh_.boundary()[patchi],
					DimensionedField<Type, volMesh>::null()
				)
			);
		}
	}


	// Now construct and write the field
	// setting the internalField and patchFields
	return tmp<GeometricField<Type, fvPatchField, volMesh>>
		(
			new GeometricField<Type, fvPatchField, volMesh>
			(
				fieldIoObject,
				mesh_,
				procFields[0].dimensions(),
				internalField,
				patchFields
				)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvPatchField, tnbLib::volMesh>>
tnbLib::fvFieldReconstructor::reconstructFvVolumeField
(
	const IOobject& fieldIoObject
) const
{
	// Read the field for all the processors
	PtrList<GeometricField<Type, fvPatchField, volMesh>> procFields
	(
		procMeshes_.size()
	);

	forAll(procMeshes_, proci)
	{
		procFields.set
		(
			proci,
			new GeometricField<Type, fvPatchField, volMesh>
			(
				IOobject
				(
					fieldIoObject.name(),
					procMeshes_[proci].time().timeName(),
					procMeshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				procMeshes_[proci]
				)
		);
	}

	return reconstructFvVolumeField
	(
		IOobject
		(
			fieldIoObject.name(),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		procFields
	);
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::fvFieldReconstructor::reconstructFvSurfaceField
(
	const IOobject& fieldIoObject,
	const PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>>& procFields
) const
{
	// Create the internalField
	Field<Type> internalField(mesh_.nInternalFaces());

	// Create the patch fields
	PtrList<fvsPatchField<Type>> patchFields(mesh_.boundary().size());


	forAll(procMeshes_, proci)
	{
		const GeometricField<Type, fvsPatchField, surfaceMesh>& procField =
			procFields[proci];

		// Set the face values in the reconstructed field

		if (pTraits<Type>::nComponents == 1)
		{
			// Assume all scalar surfaceFields are oriented flux fields
			const labelList& faceMap = faceProcAddressing_[proci];

			// Correctly oriented copy of internal field
			Field<Type> procInternalField(procField.primitiveField());

			// Addressing into original field
			// It is necessary to create a copy of the addressing array to
			// take care of the face direction offset trick.
			labelList curAddr(procInternalField.size());

			forAll(procInternalField, i)
			{
				curAddr[i] = mag(faceMap[i]) - 1;
				if (faceMap[i] < 0)
				{
					procInternalField[i] = -procInternalField[i];
				}
			}

			// Map
			internalField.rmap(procInternalField, curAddr);
		}
		else
		{
			// Map
			internalField.rmap
			(
				procField.primitiveField(),
				mag(labelField(faceProcAddressing_[proci])) - 1
			);
		}

		// Set the boundary patch values in the reconstructed field
		forAll(boundaryProcAddressing_[proci], patchi)
		{
			// Get patch index of the original patch
			const label curBPatch = boundaryProcAddressing_[proci][patchi];

			// Get addressing slice for this patch
			const labelList::subList cp =
				procMeshes_[proci].boundary()[patchi].patchSlice
				(
					faceProcAddressing_[proci]
				);

			// check if the boundary patch is not a processor patch
			if (curBPatch >= 0)
			{
				// Regular patch. Fast looping

				if (!patchFields(curBPatch))
				{
					patchFields.set
					(
						curBPatch,
						fvsPatchField<Type>::New
						(
							procField.boundaryField()[patchi],
							mesh_.boundary()[curBPatch],
							DimensionedField<Type, surfaceMesh>::null(),
							fvPatchFieldReconstructor
							(
								mesh_.boundary()[curBPatch].size()
							)
						)
					);
				}

				const label curPatchStart =
					mesh_.boundaryMesh()[curBPatch].start();

				labelList reverseAddressing(cp.size());

				forAll(cp, facei)
				{
					// Subtract one to take into account offsets for
					// face direction.
					reverseAddressing[facei] = cp[facei] - 1 - curPatchStart;
				}

				patchFields[curBPatch].rmap
				(
					procField.boundaryField()[patchi],
					reverseAddressing
				);
			}
			else
			{
				const Field<Type>& curProcPatch =
					procField.boundaryField()[patchi];

				// In processor patches, there's a mix of internal faces (some
				// of them turned) and possible cyclics. Slow loop
				forAll(cp, facei)
				{
					label curF = cp[facei] - 1;

					// Is the face turned the right side round
					if (curF >= 0)
					{
						// Is the face on the boundary?
						if (curF >= mesh_.nInternalFaces())
						{
							label curBPatch =
								mesh_.boundaryMesh().whichPatch(curF);

							if (!patchFields(curBPatch))
							{
								patchFields.set
								(
									curBPatch,
									fvsPatchField<Type>::New
									(
										mesh_.boundary()[curBPatch].type(),
										mesh_.boundary()[curBPatch],
										DimensionedField<Type, surfaceMesh>
										::null()
									)
								);
							}

							// add the face
							label curPatchFace =
								mesh_.boundaryMesh()
								[curBPatch].whichFace(curF);

							patchFields[curBPatch][curPatchFace] =
								curProcPatch[facei];
						}
						else
						{
							// Internal face
							internalField[curF] = curProcPatch[facei];
						}
					}
				}
			}
		}
	}

	forAll(mesh_.boundary(), patchi)
	{
		// add empty patches
		if
			(
				isType<emptyFvPatch>(mesh_.boundary()[patchi])
				&& !patchFields(patchi)
				)
		{
			patchFields.set
			(
				patchi,
				fvsPatchField<Type>::New
				(
					emptyFvsPatchField<Type>::typeName,
					mesh_.boundary()[patchi],
					DimensionedField<Type, surfaceMesh>::null()
				)
			);
		}
	}


	// Now construct and write the field
	// setting the internalField and patchFields
	return tmp<GeometricField<Type, fvsPatchField, surfaceMesh>>
		(
			new GeometricField<Type, fvsPatchField, surfaceMesh>
			(
				fieldIoObject,
				mesh_,
				procFields[0].dimensions(),
				internalField,
				patchFields
				)
			);
}


template<class Type>
tnbLib::tmp<tnbLib::GeometricField<Type, tnbLib::fvsPatchField, tnbLib::surfaceMesh>>
tnbLib::fvFieldReconstructor::reconstructFvSurfaceField
(
	const IOobject& fieldIoObject
) const
{
	// Read the field for all the processors
	PtrList<GeometricField<Type, fvsPatchField, surfaceMesh>> procFields
	(
		procMeshes_.size()
	);

	forAll(procMeshes_, proci)
	{
		procFields.set
		(
			proci,
			new GeometricField<Type, fvsPatchField, surfaceMesh>
			(
				IOobject
				(
					fieldIoObject.name(),
					procMeshes_[proci].time().timeName(),
					procMeshes_[proci],
					IOobject::MUST_READ,
					IOobject::NO_WRITE
				),
				procMeshes_[proci]
				)
		);
	}

	return reconstructFvSurfaceField
	(
		IOobject
		(
			fieldIoObject.name(),
			mesh_.time().timeName(),
			mesh_,
			IOobject::NO_READ,
			IOobject::NO_WRITE
		),
		procFields
	);
}


template<class Type>
void tnbLib::fvFieldReconstructor::reconstructFvVolumeInternalFields
(
	const IOobjectList& objects,
	const HashSet<word>& selectedFields
)
{
	const word& fieldClassName = DimensionedField<Type, volMesh>::typeName;

	IOobjectList fields = objects.lookupClass(fieldClassName);

	if (fields.size())
	{
		Info << "    Reconstructing " << fieldClassName << "s\n" << endl;

		forAllConstIter(IOobjectList, fields, fieldIter)
		{
			if
				(
					selectedFields.empty()
					|| selectedFields.found(fieldIter()->name())
					)
			{
				Info << "        " << fieldIter()->name() << endl;

				reconstructFvVolumeInternalField<Type>(*fieldIter())().write();

				nReconstructed_++;
			}
		}
		Info << endl;
	}
}


template<class Type>
void tnbLib::fvFieldReconstructor::reconstructFvVolumeFields
(
	const IOobjectList& objects,
	const HashSet<word>& selectedFields
)
{
	const word& fieldClassName =
		GeometricField<Type, fvPatchField, volMesh>::typeName;

	IOobjectList fields = objects.lookupClass(fieldClassName);

	if (fields.size())
	{
		Info << "    Reconstructing " << fieldClassName << "s\n" << endl;

		forAllConstIter(IOobjectList, fields, fieldIter)
		{
			if
				(
					selectedFields.empty()
					|| selectedFields.found(fieldIter()->name())
					)
			{
				Info << "        " << fieldIter()->name() << endl;

				reconstructFvVolumeField<Type>(*fieldIter())().write();

				nReconstructed_++;
			}
		}
		Info << endl;
	}
}


template<class Type>
void tnbLib::fvFieldReconstructor::reconstructFvSurfaceFields
(
	const IOobjectList& objects,
	const HashSet<word>& selectedFields
)
{
	const word& fieldClassName =
		GeometricField<Type, fvsPatchField, surfaceMesh>::typeName;

	IOobjectList fields = objects.lookupClass(fieldClassName);

	if (fields.size())
	{
		Info << "    Reconstructing " << fieldClassName << "s\n" << endl;

		forAllConstIter(IOobjectList, fields, fieldIter)
		{
			if
				(
					selectedFields.empty()
					|| selectedFields.found(fieldIter()->name())
					)
			{
				Info << "        " << fieldIter()->name() << endl;

				reconstructFvSurfaceField<Type>(*fieldIter())().write();

				nReconstructed_++;
			}
		}
		Info << endl;
	}
}


// ************************************************************************* //