#include <MRFZone.hxx>

#include <fvMesh.hxx>
#include <volFields.hxx>
#include <surfaceFields.hxx>
#include <fvMatrices.hxx>
#include <faceSet.hxx>
#include <geometricOneField.hxx>
#include <syncTools.hxx>

#include <PstreamReduceOps.hxx>  // added by amir
#include <emptyPolyPatch.hxx>  // added by amir
#include <Time.hxx>  // added by amir

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(MRFZone, 0);
}


// * * * * * * * * * * * * * Private Member Functions  * * * * * * * * * * * //

void tnbLib::MRFZone::setMRFFaces()
{
	const polyBoundaryMesh& patches = mesh_.boundaryMesh();

	// Type per face:
	//  0:not in zone
	//  1:moving with frame
	//  2:other
	labelList faceType(mesh_.nFaces(), 0);

	// Determine faces in cell zone
	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	// (without constructing cells)

	const labelList& own = mesh_.faceOwner();
	const labelList& nei = mesh_.faceNeighbour();

	// Cells in zone
	boolList zoneCell(mesh_.nCells(), false);

	if (cellZoneID_ != -1)
	{
		const labelList& cellLabels = mesh_.cellZones()[cellZoneID_];
		forAll(cellLabels, i)
		{
			zoneCell[cellLabels[i]] = true;
		}
	}


	label nZoneFaces = 0;

	for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
	{
		if (zoneCell[own[facei]] || zoneCell[nei[facei]])
		{
			faceType[facei] = 1;
			nZoneFaces++;
		}
	}


	labelHashSet excludedPatches(excludedPatchLabels_);

	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		if (pp.coupled() || excludedPatches.found(patchi))
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;

				if (zoneCell[own[facei]])
				{
					faceType[facei] = 2;
					nZoneFaces++;
				}
			}
		}
		else if (!isA<emptyPolyPatch>(pp))
		{
			forAll(pp, i)
			{
				label facei = pp.start() + i;

				if (zoneCell[own[facei]])
				{
					faceType[facei] = 1;
					nZoneFaces++;
				}
			}
		}
	}

	// Synchronize the faceType across processor patches
	syncTools::syncFaceList(mesh_, faceType, maxEqOp<label>());

	// Now we have for faceType:
	//  0   : face not in cellZone
	//  1   : internal face or normal patch face
	//  2   : coupled patch face or excluded patch face

	// Sort into lists per patch.

	internalFaces_.setSize(mesh_.nFaces());
	label nInternal = 0;

	for (label facei = 0; facei < mesh_.nInternalFaces(); facei++)
	{
		if (faceType[facei] == 1)
		{
			internalFaces_[nInternal++] = facei;
		}
	}
	internalFaces_.setSize(nInternal);

	labelList nIncludedFaces(patches.size(), 0);
	labelList nExcludedFaces(patches.size(), 0);

	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		forAll(pp, patchFacei)
		{
			label facei = pp.start() + patchFacei;

			if (faceType[facei] == 1)
			{
				nIncludedFaces[patchi]++;
			}
			else if (faceType[facei] == 2)
			{
				nExcludedFaces[patchi]++;
			}
		}
	}

	includedFaces_.setSize(patches.size());
	excludedFaces_.setSize(patches.size());
	forAll(nIncludedFaces, patchi)
	{
		includedFaces_[patchi].setSize(nIncludedFaces[patchi]);
		excludedFaces_[patchi].setSize(nExcludedFaces[patchi]);
	}
	nIncludedFaces = 0;
	nExcludedFaces = 0;

	forAll(patches, patchi)
	{
		const polyPatch& pp = patches[patchi];

		forAll(pp, patchFacei)
		{
			label facei = pp.start() + patchFacei;

			if (faceType[facei] == 1)
			{
				includedFaces_[patchi][nIncludedFaces[patchi]++] = patchFacei;
			}
			else if (faceType[facei] == 2)
			{
				excludedFaces_[patchi][nExcludedFaces[patchi]++] = patchFacei;
			}
		}
	}


	if (debug)
	{
		faceSet internalFaces(mesh_, "internalFaces", internalFaces_);
		Pout << "Writing " << internalFaces.size()
			<< " internal faces in MRF zone to faceSet "
			<< internalFaces.name() << endl;
		internalFaces.write();

		faceSet MRFFaces(mesh_, "includedFaces", 100);
		forAll(includedFaces_, patchi)
		{
			forAll(includedFaces_[patchi], i)
			{
				label patchFacei = includedFaces_[patchi][i];
				MRFFaces.insert(patches[patchi].start() + patchFacei);
			}
		}
		Pout << "Writing " << MRFFaces.size()
			<< " patch faces in MRF zone to faceSet "
			<< MRFFaces.name() << endl;
		MRFFaces.write();

		faceSet excludedFaces(mesh_, "excludedFaces", 100);
		forAll(excludedFaces_, patchi)
		{
			forAll(excludedFaces_[patchi], i)
			{
				label patchFacei = excludedFaces_[patchi][i];
				excludedFaces.insert(patches[patchi].start() + patchFacei);
			}
		}
		Pout << "Writing " << excludedFaces.size()
			<< " faces in MRF zone with special handling to faceSet "
			<< excludedFaces.name() << endl;
		excludedFaces.write();
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::MRFZone::MRFZone
(
	const word& name,
	const fvMesh& mesh,
	const dictionary& dict,
	const word& cellZoneName
)
	:
	mesh_(mesh),
	name_(name),
	coeffs_(dict),
	active_(coeffs_.lookupOrDefault("active", true)),
	cellZoneName_(cellZoneName),
	cellZoneID_(),
	excludedPatchNames_
	(
		wordReList(coeffs_.lookupOrDefault("nonRotatingPatches", wordReList()))
	),
	origin_(coeffs_.lookup("origin")),
	axis_(coeffs_.lookup("axis")),
	omega_(Function1<scalar>::New("omega", coeffs_))
{
	if (cellZoneName_ == word::null)
	{
		coeffs_.lookup("cellZone") >> cellZoneName_;
	}

	if (!active_)
	{
		cellZoneID_ = -1;
	}
	else
	{
		cellZoneID_ = mesh_.cellZones().findZoneID(cellZoneName_);

		axis_ = axis_ / mag(axis_);

		const labelHashSet excludedPatchSet
		(
			mesh_.boundaryMesh().patchSet(excludedPatchNames_)
		);

		excludedPatchLabels_.setSize(excludedPatchSet.size());

		label i = 0;
		forAllConstIter(labelHashSet, excludedPatchSet, iter)
		{
			excludedPatchLabels_[i++] = iter.key();
		}

		bool cellZoneFound = (cellZoneID_ != -1);

		reduce(cellZoneFound, orOp<bool>());

		if (!cellZoneFound)
		{
			FatalErrorInFunction
				<< "cannot find MRF cellZone " << cellZoneName_
				<< exit(FatalError);
		}

		setMRFFaces();
	}
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

tnbLib::vector tnbLib::MRFZone::Omega() const
{
	return omega_->value(mesh_.time().timeOutputValue())*axis_;
}


void tnbLib::MRFZone::addCoriolis
(
	const volVectorField& U,
	volVectorField& ddtU
) const
{
	if (cellZoneID_ == -1)
	{
		return;
	}

	const labelList& cells = mesh_.cellZones()[cellZoneID_];
	vectorField& ddtUc = ddtU.primitiveFieldRef();
	const vectorField& Uc = U;

	const vector Omega = this->Omega();

	forAll(cells, i)
	{
		label celli = cells[i];
		ddtUc[celli] += (Omega ^ Uc[celli]);
	}
}


void tnbLib::MRFZone::addCoriolis(fvVectorMatrix& UEqn, const bool rhs) const
{
	if (cellZoneID_ == -1)
	{
		return;
	}

	const labelList& cells = mesh_.cellZones()[cellZoneID_];
	const scalarField& V = mesh_.V();
	vectorField& Usource = UEqn.source();
	const vectorField& U = UEqn.psi();

	const vector Omega = this->Omega();

	if (rhs)
	{
		forAll(cells, i)
		{
			label celli = cells[i];
			Usource[celli] += V[celli] * (Omega ^ U[celli]);
		}
	}
	else
	{
		forAll(cells, i)
		{
			label celli = cells[i];
			Usource[celli] -= V[celli] * (Omega ^ U[celli]);
		}
	}
}


void tnbLib::MRFZone::addCoriolis
(
	const volScalarField& rho,
	fvVectorMatrix& UEqn,
	const bool rhs
) const
{
	if (cellZoneID_ == -1)
	{
		return;
	}

	const labelList& cells = mesh_.cellZones()[cellZoneID_];
	const scalarField& V = mesh_.V();
	vectorField& Usource = UEqn.source();
	const vectorField& U = UEqn.psi();

	const vector Omega = this->Omega();

	if (rhs)
	{
		forAll(cells, i)
		{
			label celli = cells[i];
			Usource[celli] += V[celli] * rho[celli] * (Omega ^ U[celli]);
		}
	}
	else
	{
		forAll(cells, i)
		{
			label celli = cells[i];
			Usource[celli] -= V[celli] * rho[celli] * (Omega ^ U[celli]);
		}
	}
}


void tnbLib::MRFZone::makeRelative(volVectorField& U) const
{
	if (cellZoneID_ == -1)
	{
		return;
	}

	const volVectorField& C = mesh_.C();

	const vector Omega = this->Omega();

	const labelList& cells = mesh_.cellZones()[cellZoneID_];

	forAll(cells, i)
	{
		label celli = cells[i];
		U[celli] -= (Omega ^ (C[celli] - origin_));
	}

	// Included patches

	volVectorField::Boundary& Ubf = U.boundaryFieldRef();

	forAll(includedFaces_, patchi)
	{
		forAll(includedFaces_[patchi], i)
		{
			label patchFacei = includedFaces_[patchi][i];
			Ubf[patchi][patchFacei] = Zero;
		}
	}

	// Excluded patches
	forAll(excludedFaces_, patchi)
	{
		forAll(excludedFaces_[patchi], i)
		{
			label patchFacei = excludedFaces_[patchi][i];
			Ubf[patchi][patchFacei] -=
				(Omega
					^ (C.boundaryField()[patchi][patchFacei] - origin_));
		}
	}
}


void tnbLib::MRFZone::makeRelative(surfaceScalarField& phi) const
{
	makeRelativeRhoFlux(geometricOneField(), phi);
}


void tnbLib::MRFZone::makeRelative(FieldField<fvsPatchField, scalar>& phi) const
{
	makeRelativeRhoFlux(oneFieldField(), phi);
}


void tnbLib::MRFZone::makeRelative(Field<scalar>& phi, const label patchi) const
{
	makeRelativeRhoFlux(oneField(), phi, patchi);
}


void tnbLib::MRFZone::makeRelative
(
	const surfaceScalarField& rho,
	surfaceScalarField& phi
) const
{
	makeRelativeRhoFlux(rho, phi);
}


void tnbLib::MRFZone::makeAbsolute(volVectorField& U) const
{
	if (cellZoneID_ == -1)
	{
		return;
	}

	const volVectorField& C = mesh_.C();

	const vector Omega = this->Omega();

	const labelList& cells = mesh_.cellZones()[cellZoneID_];

	forAll(cells, i)
	{
		label celli = cells[i];
		U[celli] += (Omega ^ (C[celli] - origin_));
	}

	// Included patches
	volVectorField::Boundary& Ubf = U.boundaryFieldRef();

	forAll(includedFaces_, patchi)
	{
		forAll(includedFaces_[patchi], i)
		{
			label patchFacei = includedFaces_[patchi][i];
			Ubf[patchi][patchFacei] =
				(Omega ^ (C.boundaryField()[patchi][patchFacei] - origin_));
		}
	}

	// Excluded patches
	forAll(excludedFaces_, patchi)
	{
		forAll(excludedFaces_[patchi], i)
		{
			label patchFacei = excludedFaces_[patchi][i];
			Ubf[patchi][patchFacei] +=
				(Omega ^ (C.boundaryField()[patchi][patchFacei] - origin_));
		}
	}
}


void tnbLib::MRFZone::makeAbsolute(surfaceScalarField& phi) const
{
	makeAbsoluteRhoFlux(geometricOneField(), phi);
}


void tnbLib::MRFZone::makeAbsolute
(
	const surfaceScalarField& rho,
	surfaceScalarField& phi
) const
{
	makeAbsoluteRhoFlux(rho, phi);
}


void tnbLib::MRFZone::correctBoundaryVelocity(volVectorField& U) const
{
	if (!active_)
	{
		return;
	}

	const vector Omega = this->Omega();

	// Included patches
	volVectorField::Boundary& Ubf = U.boundaryFieldRef();

	forAll(includedFaces_, patchi)
	{
		const vectorField& patchC = mesh_.Cf().boundaryField()[patchi];

		vectorField pfld(Ubf[patchi]);

		forAll(includedFaces_[patchi], i)
		{
			label patchFacei = includedFaces_[patchi][i];

			pfld[patchFacei] = (Omega ^ (patchC[patchFacei] - origin_));
		}

		Ubf[patchi] == pfld;
	}
}


void tnbLib::MRFZone::writeData(Ostream& os) const
{
	os << nl;
	os.write(name_) << nl;
	os << token::BEGIN_BLOCK << incrIndent << nl;
	writeEntry(os, "active", active_);
	writeEntry(os, "cellZone", cellZoneName_);
	writeEntry(os, "origin", origin_);
	writeEntry(os, "axis", axis_);
	omega_->writeData(os);

	if (excludedPatchNames_.size())
	{
		writeEntry(os, "nonRotatingPatches", excludedPatchNames_);
	}

	os << decrIndent << token::END_BLOCK << nl;
}


bool tnbLib::MRFZone::read(const dictionary& dict)
{
	coeffs_ = dict;

	active_ = coeffs_.lookupOrDefault("active", true);
	coeffs_.lookup("cellZone") >> cellZoneName_;
	cellZoneID_ = mesh_.cellZones().findZoneID(cellZoneName_);

	return true;
}


void tnbLib::MRFZone::update()
{
	if (mesh_.topoChanging())
	{
		setMRFFaces();
	}
}


// ************************************************************************* //