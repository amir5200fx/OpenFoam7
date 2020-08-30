#include <thermalBaffleFvPatchScalarField.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <emptyPolyPatch.hxx>
#include <mappedWallPointPatch.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace compressible
	{

		// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

		thermalBaffleFvPatchScalarField::
			thermalBaffleFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			turbulentTemperatureRadCoupledMixedFvPatchScalarField(p, iF),
			owner_(false),
			baffle_(),
			dict_(dictionary::null),
			extrudeMeshPtr_()
		{}


		thermalBaffleFvPatchScalarField::
			thermalBaffleFvPatchScalarField
			(
				const thermalBaffleFvPatchScalarField& ptf,
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const fvPatchFieldMapper& mapper
			)
			:
			turbulentTemperatureRadCoupledMixedFvPatchScalarField
			(
				ptf,
				p,
				iF,
				mapper
			),
			owner_(ptf.owner_),
			baffle_(),
			dict_(ptf.dict_),
			extrudeMeshPtr_()
		{}


		thermalBaffleFvPatchScalarField::
			thermalBaffleFvPatchScalarField
			(
				const fvPatch& p,
				const DimensionedField<scalar, volMesh>& iF,
				const dictionary& dict
			)
			:
			turbulentTemperatureRadCoupledMixedFvPatchScalarField(p, iF, dict),
			owner_(false),
			baffle_(),
			dict_(dict),
			extrudeMeshPtr_()
		{

			const fvMesh& thisMesh = patch().boundaryMesh().mesh();

			typedef regionModels::thermalBaffleModels::thermalBaffleModel baffle;

			if (thisMesh.name() == polyMesh::defaultRegion)
			{
				const word regionName =
					dict_.lookupOrDefault<word>("regionName", "none");

				const word baffleName("3DBaffle" + regionName);

				if
					(
						!thisMesh.time().foundObject<fvMesh>(regionName)
						&& regionName != "none"
						)
				{
					if (extrudeMeshPtr_.empty())
					{
						createPatchMesh();
					}

					baffle_.reset(baffle::New(thisMesh, dict).ptr());
					owner_ = true;
					baffle_->rename(baffleName);
				}
			}
		}


		thermalBaffleFvPatchScalarField::
			thermalBaffleFvPatchScalarField
			(
				const thermalBaffleFvPatchScalarField& ptf,
				const DimensionedField<scalar, volMesh>& iF
			)
			:
			turbulentTemperatureRadCoupledMixedFvPatchScalarField(ptf, iF),
			owner_(ptf.owner_),
			baffle_(),
			dict_(ptf.dict_),
			extrudeMeshPtr_()
		{}


		// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


		void thermalBaffleFvPatchScalarField::autoMap
		(
			const fvPatchFieldMapper& m
		)
		{
			mixedFvPatchScalarField::autoMap(m);
		}


		void thermalBaffleFvPatchScalarField::rmap
		(
			const fvPatchScalarField& ptf,
			const labelList& addr
		)
		{
			mixedFvPatchScalarField::rmap(ptf, addr);
		}


		void thermalBaffleFvPatchScalarField::createPatchMesh()
		{

			const fvMesh& thisMesh = patch().boundaryMesh().mesh();

			word regionName = dict_.lookup("regionName");

			List<polyPatch*> regionPatches(3);
			List<word> patchNames(regionPatches.size());
			List<word> patchTypes(regionPatches.size());
			List<dictionary> dicts(regionPatches.size());

			patchNames[bottomPatchID] = word("bottom");
			patchNames[sidePatchID] = word("side");
			patchNames[topPatchID] = word("top");

			patchTypes[bottomPatchID] = mappedWallPolyPatch::typeName;
			patchTypes[topPatchID] = mappedWallPolyPatch::typeName;

			if (readBool(dict_.lookup("columnCells")))
			{
				patchTypes[sidePatchID] = emptyPolyPatch::typeName;
			}
			else
			{
				patchTypes[sidePatchID] = polyPatch::typeName;
			}

			const mappedPatchBase& mpp =
				refCast<const mappedPatchBase>(patch().patch());

			const word coupleGroup(mpp.coupleGroup());

			wordList inGroups(1);
			inGroups[0] = coupleGroup;

			dicts[bottomPatchID].add("coupleGroup", coupleGroup);
			dicts[bottomPatchID].add("inGroups", inGroups);
			dicts[bottomPatchID].add("sampleMode", mpp.sampleModeNames_[mpp.mode()]);

			const label sepPos = coupleGroup.find('_');

			const word coupleGroupSlave = coupleGroup(0, sepPos) + "_slave";

			inGroups[0] = coupleGroupSlave;
			dicts[topPatchID].add("coupleGroup", coupleGroupSlave);
			dicts[topPatchID].add("inGroups", inGroups);
			dicts[topPatchID].add("sampleMode", mpp.sampleModeNames_[mpp.mode()]);


			forAll(regionPatches, patchi)
			{
				dictionary&  patchDict = dicts[patchi];
				patchDict.set("nFaces", 0);
				patchDict.set("startFace", 0);

				regionPatches[patchi] = polyPatch::New
				(
					patchTypes[patchi],
					patchNames[patchi],
					dicts[patchi],
					patchi,
					thisMesh.boundaryMesh()
				).ptr();
			}

			extrudeMeshPtr_.reset
			(
				new extrudePatchMesh
				(
					thisMesh,
					patch(),
					dict_,
					regionName,
					regionPatches
				)
			);

			if (extrudeMeshPtr_.empty())
			{
				WarningInFunction
					<< "Specified IOobject::MUST_READ_IF_MODIFIED but class"
					<< " patchMeshPtr not set."
					<< endl;
			}
		}


		void thermalBaffleFvPatchScalarField::updateCoeffs()
		{
			if (this->updated())
			{
				return;
			}

			const fvMesh& thisMesh = patch().boundaryMesh().mesh();

			if (owner_ && thisMesh.name() == polyMesh::defaultRegion)
			{
				baffle_->evolve();
			}

			turbulentTemperatureRadCoupledMixedFvPatchScalarField::updateCoeffs();
		}


		void thermalBaffleFvPatchScalarField::write(Ostream& os) const
		{
			turbulentTemperatureRadCoupledMixedFvPatchScalarField::write(os);

			const fvMesh& thisMesh = patch().boundaryMesh().mesh();

			if (thisMesh.name() == polyMesh::defaultRegion && owner_)
			{

				os.writeKeyword("extrudeModel");
				os << word(dict_.lookup("extrudeModel"))
					<< token::END_STATEMENT << nl;

				os.writeKeyword("nLayers");
				os << readLabel(dict_.lookup("nLayers"))
					<< token::END_STATEMENT << nl;

				os.writeKeyword("expansionRatio");
				os << readScalar(dict_.lookup("expansionRatio"))
					<< token::END_STATEMENT << nl;

				os.writeKeyword("columnCells");
				os << readBool(dict_.lookup("columnCells"))
					<< token::END_STATEMENT << nl;

				word extrudeModel(word(dict_.lookup("extrudeModel")) + "Coeffs");
				os.writeKeyword(extrudeModel);
				os << dict_.subDict(extrudeModel) << nl;

				word regionName = dict_.lookup("regionName");
				os.writeKeyword("regionName") << regionName
					<< token::END_STATEMENT << nl;

				bool active = readBool(dict_.lookup("active"));
				os.writeKeyword("active") << active
					<< token::END_STATEMENT << nl;

				os.writeKeyword("thermoType");
				os << dict_.subDict("thermoType") << nl;

				os.writeKeyword("mixture");
				os << dict_.subDict("mixture") << nl;

				os.writeKeyword("radiation");
				os << dict_.subDict("radiation") << nl;
			}
		}


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		makePatchTypeField
		(
			fvPatchScalarField,
			thermalBaffleFvPatchScalarField
		);


		// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

	} // End namespace compressible
} // End namespace tnbLib


// ************************************************************************* //