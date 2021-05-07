#include <rigidBodySolver.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace RBD
	{

		defineTypeNameAndDebug(rigidBodySolver, 0);
		defineRunTimeSelectionTable(rigidBodySolver, dictionary);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolver::rigidBodySolver(rigidBodyMotion& body)
	:
	model_(body)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::RBD::rigidBodySolver::~rigidBodySolver()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

void tnbLib::RBD::rigidBodySolver::correctQuaternionJoints()
{
	if (model_.unitQuaternions())
	{
		forAll(model_.joints(), i)
		{
			const label qi = model_.joints()[i].qIndex();

			if (model_.joints()[i].unitQuaternion())
			{
				// Calculate the change in the unit quaternion
				vector dv((q().block<vector>(qi) - q0().block<vector>(qi)));
				scalar magDv = mag(dv);

				if (magDv > small)
				{
					// Calculate the unit quaternion corresponding to the change
					quaternion dQuat(dv / magDv, cos(magDv), true);

					// Transform the previous time unit quaternion
					quaternion quat
					(
						normalize(model_.joints()[i].unitQuaternion(q0())*dQuat)
					);

					// Update the joint unit quaternion
					model_.joints()[i].unitQuaternion(quat, q());
				}
			}
		}
	}
}


// ************************************************************************* //