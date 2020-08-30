#include <pyrolysisModelCollection.hxx>

#include <volFields.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{
			defineTypeNameAndDebug(pyrolysisModelCollection, 0);
		}
	}
}

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace pyrolysisModels
		{

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			pyrolysisModelCollection::pyrolysisModelCollection(const fvMesh& mesh)
				:
				PtrList<pyrolysisModel>()

			{
				IOdictionary pyrolysisZonesDict
				(
					IOobject
					(
						"pyrolysisZones",
						mesh.time().constant(),
						mesh,
						IOobject::MUST_READ,
						IOobject::NO_WRITE
					)
				);

				const wordList regions(pyrolysisZonesDict.toc());

				setSize(regions.size());

				for (label i = 0; i < regions.size(); i++)
				{
					set
					(
						i,
						pyrolysisModel::New
						(
							mesh,
							pyrolysisZonesDict.subDict(regions[i]),
							regions[i]
						)
					);
				}
			}


			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			pyrolysisModelCollection::~pyrolysisModelCollection()
			{}


			// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //


			void pyrolysisModelCollection::preEvolveRegion()
			{
				forAll(*this, i)
				{
					this->operator[](i).preEvolveRegion();
				}
			}


			void pyrolysisModelCollection::evolveRegion()
			{
				forAll(*this, i)
				{
					this->operator[](i).evolveRegion();
				}
			}


			void pyrolysisModelCollection::evolve()
			{
				forAll(*this, i)
				{
					pyrolysisModel& pyrolysis = this->operator[](i);

					if (pyrolysis.active())
					{
						if (pyrolysis.primaryMesh().changing())
						{
							FatalErrorInFunction
								<< "Currently not possible to apply "
								<< pyrolysis.modelName()
								<< " model to moving mesh cases" << nl << abort(FatalError);
						}

						// Pre-evolve
						pyrolysis.preEvolveRegion();

						// Increment the region equations up to the new time level
						pyrolysis.evolveRegion();

						// Provide some feedback
						if (pyrolysis.infoOutput())
						{
							Info << incrIndent;
							pyrolysis.info();
							Info << endl << decrIndent;
						}
					}
				}
			}


			void pyrolysisModelCollection::info()
			{
				forAll(*this, i)
				{
					this->operator[](i).info();
				}
			}


			scalar pyrolysisModelCollection::maxDiff() const
			{
				scalar maxDiff = 0.0;
				forAll(*this, i)
				{
					if (maxDiff < this->operator[](i).maxDiff())
					{
						maxDiff = this->operator[](i).maxDiff();
					}

				}
				return maxDiff;
			}


			scalar pyrolysisModelCollection::solidRegionDiffNo() const
			{
				scalar totalDiNum = great;

				forAll(*this, i)
				{
					if
						(
							totalDiNum > this->operator[](i).solidRegionDiffNo()
							)
					{
						totalDiNum = this->operator[](i).solidRegionDiffNo();
					}
				}

				return totalDiNum;
			}


		} // End namespace pyrolysisModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //