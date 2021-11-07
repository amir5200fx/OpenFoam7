#include <splitCell.hxx>

#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

// Construct from cell number and parent
tnbLib::splitCell::splitCell(const label celli, splitCell* parent)
    :
    celli_(celli),
    parent_(parent),
    master_(nullptr),
    slave_(nullptr)
{}


// * * * * * * * * * * * * * * * * Destructor  * * * * * * * * * * * * * * * //

tnbLib::splitCell::~splitCell()
{
    splitCell* myParent = parent();

    if (myParent)
    {
        // Make sure parent does not refer to me anymore.
        if (myParent->master() == this)
        {
            myParent->master() = nullptr;
        }
        else if (myParent->slave() == this)
        {
            myParent->slave() = nullptr;
        }
        else
        {
            FatalErrorInFunction
                << " parent's master or slave pointer" << endl
                << "Cell:" << cellLabel() << abort(FatalError);
        }
    }
}


// * * * * * * * * * * * * * * * Member Functions  * * * * * * * * * * * * * //

bool tnbLib::splitCell::isMaster() const
{
    splitCell* myParent = parent();

    if (!myParent)
    {
        FatalErrorInFunction
            << "Cell:" << cellLabel() << abort(FatalError);

        return false;
    }
    else if (myParent->master() == this)
    {
        return true;
    }
    else if (myParent->slave() == this)
    {
        return false;
    }
    else
    {
        FatalErrorInFunction
            << " parent's master or slave pointer" << endl
            << "Cell:" << cellLabel() << abort(FatalError);

        return false;
    }
}


bool tnbLib::splitCell::isUnrefined() const
{
    return !master() && !slave();
}


tnbLib::splitCell* tnbLib::splitCell::getOther() const
{
    splitCell* myParent = parent();

    if (!myParent)
    {
        FatalErrorInFunction
            << "Cell:" << cellLabel() << abort(FatalError);

        return nullptr;
    }
    else if (myParent->master() == this)
    {
        return myParent->slave();
    }
    else if (myParent->slave() == this)
    {
        return myParent->master();
    }
    else
    {
        FatalErrorInFunction
            << " parent's master or slave pointer" << endl
            << "Cell:" << cellLabel() << abort(FatalError);

        return nullptr;
    }
}


// ************************************************************************* //