#include <sixDoFRigidBodyState.hxx>

#include <dynamicMotionSolverFvMesh.hxx>
#include <sixDoFRigidBodyMotionSolver.hxx>
#include <unitConversion.hxx>
#include <addToRunTimeSelectionTable.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	namespace functionObjects
	{
		defineTypeNameAndDebug(sixDoFRigidBodyState, 0);

		addToRunTimeSelectionTable
		(
			functionObject,
			sixDoFRigidBodyState,
			dictionary
		);
	}
}


// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::functionObjects::sixDoFRigidBodyState::sixDoFRigidBodyState
(
	const word& name,
	const Time& runTime,
	const dictionary& dict
)
	:
	fvMeshFunctionObject(name, runTime, dict),
	logFiles(obr_, name)
{
	read(dict);
	resetName(typeName);
}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::functionObjects::sixDoFRigidBodyState::~sixDoFRigidBodyState()
{}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::functionObjects::sixDoFRigidBodyState::read(const dictionary& dict)
{
	fvMeshFunctionObject::read(dict);
	angleFormat_ = dict.lookupOrDefault<word>("angleFormat", "radians");

	return true;
}


void tnbLib::functionObjects::sixDoFRigidBodyState::writeFileHeader(const label)
{
	OFstream& file = this->file();

	writeHeader(file, "Motion State");
	writeHeaderValue(file, "Angle Units", angleFormat_);
	writeCommented(file, "Time");

	file << tab
		<< "centreOfRotation" << tab
		<< "centreOfMass" << tab
		<< "rotation" << tab
		<< "velocity" << tab
		<< "omega" << endl;
}


bool tnbLib::functionObjects::sixDoFRigidBodyState::execute()
{
	return true;
}


const tnbLib::sixDoFRigidBodyMotion&
tnbLib::functionObjects::sixDoFRigidBodyState::motion() const
{
	const dynamicMotionSolverFvMesh& mesh =
		refCast<const dynamicMotionSolverFvMesh>(obr_);

	const sixDoFRigidBodyMotionSolver& motionSolver_ =
		refCast<const sixDoFRigidBodyMotionSolver>(mesh.motion());

	return motionSolver_.motion();
}


tnbLib::vector
tnbLib::functionObjects::sixDoFRigidBodyState::velocity() const
{
	return motion().v();
}


tnbLib::vector
tnbLib::functionObjects::sixDoFRigidBodyState::angularVelocity() const
{
	vector angularVelocity(motion().omega());

	if (angleFormat_ == "degrees")
	{
		angularVelocity.x() = radToDeg(angularVelocity.x());
		angularVelocity.y() = radToDeg(angularVelocity.y());
		angularVelocity.z() = radToDeg(angularVelocity.z());
	}

	return angularVelocity;
}


bool tnbLib::functionObjects::sixDoFRigidBodyState::write()
{
	logFiles::write();

	if (Pstream::master())
	{
		const sixDoFRigidBodyMotion& motion = this->motion();

		vector rotationAngle
		(
			quaternion(motion.orientation()).eulerAngles(quaternion::XYZ)
		);

		vector angularVelocity(motion.omega());

		if (angleFormat_ == "degrees")
		{
			rotationAngle.x() = radToDeg(rotationAngle.x());
			rotationAngle.y() = radToDeg(rotationAngle.y());
			rotationAngle.z() = radToDeg(rotationAngle.z());

			angularVelocity.x() = radToDeg(angularVelocity.x());
			angularVelocity.y() = radToDeg(angularVelocity.y());
			angularVelocity.z() = radToDeg(angularVelocity.z());
		}

		writeTime(file());
		file()
			<< tab
			<< motion.centreOfRotation() << tab
			<< motion.centreOfMass() << tab
			<< rotationAngle << tab
			<< motion.v() << tab
			<< angularVelocity << endl;
	}

	return true;
}


// ************************************************************************* //