#include <forceList.hxx>

// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace regionModels
	{
		namespace surfaceFilmModels
		{

			// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

			forceList::forceList(surfaceFilmRegionModel& film)
				:
				PtrList<force>()
			{}


			forceList::forceList
			(
				surfaceFilmRegionModel& film,
				const dictionary& dict
			)
				:
				PtrList<force>()
			{
				const wordList models(dict.lookup("forces"));

				Info << "    Selecting film force models" << endl;
				if (models.size() > 0)
				{
					this->setSize(models.size());

					forAll(models, i)
					{
						set(i, force::New(film, dict, models[i]));
					}
				}
				else
				{
					Info << "        none" << endl;
				}
			}

			// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

			forceList::~forceList()
			{}

			// * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * * //

			tmp<fvVectorMatrix> forceList::correct(volVectorField& U)
			{
				tmp<fvVectorMatrix> tResult
				(
					new fvVectorMatrix(U, dimForce / dimArea * dimVolume)
				);
				fvVectorMatrix& result = tResult.ref();

				forAll(*this, i)
				{
					result += this->operator[](i).correct(U);
				}

				return tResult;
			}


			// * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * //

		} // End namespace surfaceFilmModels
	} // End namespace regionModels
} // End namespace tnbLib

// ************************************************************************* //