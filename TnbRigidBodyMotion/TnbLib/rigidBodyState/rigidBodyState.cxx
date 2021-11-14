#include <rigidBodyState.hxx>

#include <dynamicMotionSolverFvMesh.hxx>
#include <motionSolver.hxx>
#include <unitConversion.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(rigidBodyState, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			rigidBodyState,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::rigidBodyState::rigidBodyState
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name),
	names_(motion().movingBodyNames())
{
	read(dict);
	resetNames(names_);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::rigidBodyState::~rigidBodyState()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

const tnbLib::RBD::rigidBodyMotion&
tnbLib::functionObjects::rigidBodyState::motion() const
{
	const dynamicMotionSolverFvMesh& mesh =
		refCast<const dynamicMotionSolverFvMesh>(obr_);

	return (refCast<const RBD::rigidBodyMotion>(mesh.motion()));
}


bool tnbLib::functionObjects::rigidBodyState::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);
	angleFormat_ = dict.lookupOrDefault<word>("angleFormat", "radians");

	return true;
}


void tnbLib::functionObjects::rigidBodyState::writeFileHeader(const label i)
{
	writeHeader(this->files()[i], "Motion State");
	writeHeaderValue(this->files()[i], "Angle Units", angleFormat_);
	writeCommented(this->files()[i], "Time");

	this->files()[i] << tab
		<< "Centre of rotation" << tab
		<< "Orientation" << tab
		<< "Linear velocity" << tab
		<< "Angular velocity" << endl;

}


bool tnbLib::functionObjects::rigidBodyState::execute()
{
	return true;
}


bool tnbLib::functionObjects::rigidBodyState::write()
{
	logFiles::write();

	if (Pstream::master())
	{
		const RBD::rigidBodyMotion& motion = this->motion();

		forAll(names_, i)
		{
			const label bodyID = motion.bodyID(names_[i]);

			const spatialTransform CofR(motion.X0(bodyID));
			const spatialVector vCofR(motion.v(bodyID, Zero));

			vector rotationAngle
			(
				quaternion(CofR.E()).eulerAngles(quaternion::XYZ)
			);

			vector angularVelocity(vCofR.w());

			if (angleFormat_ == "degrees")
			{
				rotationAngle.x() = radToDeg(rotationAngle.x());
				rotationAngle.y() = radToDeg(rotationAngle.y());
				rotationAngle.z() = radToDeg(rotationAngle.z());

				angularVelocity.x() = radToDeg(angularVelocity.x());
				angularVelocity.y() = radToDeg(angularVelocity.y());
				angularVelocity.z() = radToDeg(angularVelocity.z());
			}

			writeTime(files()[i]);
			files()[i]
				<< tab
				<< CofR.r() << tab
				<< rotationAngle << tab
				<< vCofR.l() << tab
				<< angularVelocity << endl;
		}
	}

	return true;
}


// ************************************************************************* //