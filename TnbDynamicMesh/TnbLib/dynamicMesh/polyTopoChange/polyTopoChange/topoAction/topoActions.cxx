#include <topoAction.hxx>

#include <polyAddPoint.hxx>
#include <polyAddFace.hxx>
#include <polyAddCell.hxx>
#include <polyModifyPoint.hxx>
#include <polyModifyFace.hxx>
#include <polyModifyCell.hxx>
#include <polyRemovePoint.hxx>
#include <polyRemoveFace.hxx>
#include <polyRemoveCell.hxx>

// * * * * * * * * * * * * * * Static Data Members * * * * * * * * * * * * * //

namespace tnbLib
{
	defineTypeNameAndDebug(topoAction, 0);

	defineTypeNameAndDebug(polyAddPoint, 0);
	defineTypeNameAndDebug(polyModifyPoint, 0);
	defineTypeNameAndDebug(polyRemovePoint, 0);

	defineTypeNameAndDebug(polyAddFace, 0);
	defineTypeNameAndDebug(polyModifyFace, 0);
	defineTypeNameAndDebug(polyRemoveFace, 0);

	defineTypeNameAndDebug(polyAddCell, 0);
	defineTypeNameAndDebug(polyModifyCell, 0);
	defineTypeNameAndDebug(polyRemoveCell, 0);
}


// ************************************************************************* //