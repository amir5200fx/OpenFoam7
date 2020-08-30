#include <injectionModelList.hxx>

#include <globalMeshData.hxx>  // added by amir

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			injectionModelList::injectionModelList(surfaceFilmRegionModel& film)
				:
				PtrList<injectionModel>(),
				filmSubModelBase(film)
			{}


			injectionModelList::injectionModelList
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				PtrList<injectionModel>(),
				filmSubModelBase
				(
					"injectionModelList",
					film,
					dict,
					"injectionModelList",
					"injectionModelList"
				),
				massInjected_(film.intCoupledPatchIDs().size(), 0.0)
			{
				const wordList activeModels(dict.lookup("injectionModels"));

				wordHashSet models;
				forAll(activeModels, i)
				{
					models.insert(activeModels[i]);
				}

				Info << "    Selecting film injection models" << endl;
				if (models.size() > 0)
				{
					this->setSize(models.size());

					label i = 0;
					forAllConstIter(wordHashSet, models, iter)
					{
						const word& model = iter.key();
						set(i, injectionModel::New(film, dict, model));
						i++;
					}
				}
				else
				{
					Info << "        none" << endl;
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			injectionModelList::~injectionModelList()
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

			void injectionModelList::correct
			(
				scalarField& availableMass,
				volScalarField& massToInject,
				volScalarField& diameterToInject
			)
			{
				// Correct models that accumulate mass and diameter transfers
				forAll(*this, i)
				{
					injectionModel& im = operator[](i);
					im.correct(availableMass, massToInject, diameterToInject);
				}

				// Push values to boundaries ready for transfer to the primary region
				massToInject.correctBoundaryConditions();
				diameterToInject.correctBoundaryConditions();

				const labelList& patchIDs = film().intCoupledPatchIDs();

				forAll(patchIDs, i)
				{
					label patchi = patchIDs[i];
					massInjected_[i] =
						massInjected_[i] + sum(massToInject.boundaryField()[patchi]);
				}
			}


			void injectionModelList::info(Ostream& os)
			{
				const polyBoundaryMesh& pbm = film().regionMesh().boundaryMesh();

				scalar injectedMass = 0;
				scalarField patchInjectedMasses
				(
					pbm.size() - film().regionMesh().globalData().processorPatches().size(),
					0
				);

				forAll(*this, i)
				{
					const injectionModel& im = operator[](i);
					injectedMass += im.injectedMassTotal();
					im.patchInjectedMassTotals(patchInjectedMasses);
				}

				os << indent << "injected mass      = " << injectedMass << nl;

				forAll(patchInjectedMasses, patchi)
				{
					if (mag(patchInjectedMasses[patchi]) > vSmall)
					{
						os << indent << indent << "from patch " << pbm[patchi].name()
							<< " = " << patchInjectedMasses[patchi] << nl;
					}
				}

				scalarField mass0(massInjected_.size(), 0);
				this->getBaseProperty("massInjected", mass0);

				scalarField mass(massInjected_);
				Pstream::listCombineGather(mass, plusEqOp<scalar>());
				mass += mass0;

				const labelList& patchIDs = film().intCoupledPatchIDs();

				forAll(patchIDs, i)
				{
					label patchi = patchIDs[i];
					Info << indent << "  - patch: " << pbm[patchi].name() << ": "
						<< mass[i] << endl;
				}

				if (film().time().writeTime())
				{
					setBaseProperty("massInjected", mass);
					massInjected_ = 0.0;
				}
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //