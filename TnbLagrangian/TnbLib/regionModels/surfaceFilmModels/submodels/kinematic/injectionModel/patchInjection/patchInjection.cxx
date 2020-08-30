#include <patchInjection.hxx>

#include <addToRunTimeSelectionTable.hxx>
#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

			defineTypeNameAndDebug(patchInjection, 0);
			addToRunTimeSelectionTable(injectionModel, patchInjection, dictionary);

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			patchInjection::patchInjection
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				injectionModel(type(), film, dict),
				deltaStable_(coeffDict_.lookupOrDefault<scalar>("deltaStable", 0.0))
			{
				const polyBoundaryMesh& pbm = film.regionMesh().boundaryMesh();
				patchIDs_.setSize
				(
					pbm.size() - film.regionMesh().globalData().processorPatches().size()
				);

				if (coeffDict_.found("patches"))
				{
					wordReList patchNames(coeffDict_.lookup("patches"));
					const labelHashSet patchSet = pbm.patchSet(patchNames);

					Info << "        applying to patches:" << nl;

					label pidi = 0;
					forAllConstIter(labelHashSet, patchSet, iter)
					{
						label patchi = iter.key();
						patchIDs_[pidi++] = patchi;
						Info << "            " << pbm[patchi].name() << endl;
					}
					patchIDs_.setSize(pidi);
					patchInjectedMasses_.setSize(pidi, 0);
				}
				else
				{
					Info << "            applying to all patches" << endl;

					forAll(patchIDs_, patchi)
					{
						patchIDs_[patchi] = patchi;
					}

					patchInjectedMasses_.setSize(patchIDs_.size(), 0);
				}

				if (!patchIDs_.size())
				{
					FatalErrorInFunction
						<< "No patches selected"
						<< exit(FatalError);
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			patchInjection::~patchInjection()
			{}


			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			void patchInjection::correct
			(
				scalarField& availableMass,
				scalarField& massToInject,
				scalarField& diameterToInject
			)
			{
				// Do not correct if no patches selected
				if (!patchIDs_.size()) return;

				const scalarField& delta = film().delta();
				const scalarField& rho = film().rho();
				const scalarField& magSf = film().magSf();

				const polyBoundaryMesh& pbm = film().regionMesh().boundaryMesh();

				forAll(patchIDs_, pidi)
				{
					label patchi = patchIDs_[pidi];
					const polyPatch& pp = pbm[patchi];
					const labelList& faceCells = pp.faceCells();

					// Accumulate the total mass removed from patch
					scalar dMassPatch = 0;

					forAll(faceCells, fci)
					{
						label celli = faceCells[fci];

						scalar ddelta = max(0.0, delta[celli] - deltaStable_);
						scalar dMass = ddelta * rho[celli] * magSf[celli];
						massToInject[celli] += dMass;
						availableMass[celli] -= dMass;
						dMassPatch += dMass;
					}

					patchInjectedMasses_[pidi] += dMassPatch;
					addToInjectedMass(dMassPatch);
				}

				injectionModel::correct();

				if (writeTime())
				{
					scalarField patchInjectedMasses0
					(
						getModelProperty<scalarField>
						(
							"patchInjectedMasses",
							scalarField(patchInjectedMasses_.size(), 0)
							)
					);

					scalarField patchInjectedMassTotals(patchInjectedMasses_);
					Pstream::listCombineGather(patchInjectedMassTotals, plusEqOp<scalar>());
					patchInjectedMasses0 += patchInjectedMassTotals;

					setModelProperty<scalarField>
						(
							"patchInjectedMasses",
							patchInjectedMasses0
							);

					patchInjectedMasses_ = 0;
				}
			}


			void patchInjection::patchInjectedMassTotals(scalarField& patchMasses) const
			{
				// Do not correct if no patches selected
				if (!patchIDs_.size()) return;

				scalarField patchInjectedMasses
				(
					getModelProperty<scalarField>
					(
						"patchInjectedMasses",
						scalarField(patchInjectedMasses_.size(), 0)
						)
				);

				scalarField patchInjectedMassTotals(patchInjectedMasses_);
				Pstream::listCombineGather(patchInjectedMassTotals, plusEqOp<scalar>());

				forAll(patchIDs_, pidi)
				{
					label patchi = patchIDs_[pidi];
					patchMasses[patchi] +=
						patchInjectedMasses[pidi] + patchInjectedMassTotals[pidi];
				}
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //