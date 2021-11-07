#include <refineCell.hxx>

#include <error.hxx>
#include <OSstream.hxx>

// * * * * * * * * * * * * * * * * Constructors  * * * * * * * * * * * * * * //

tnbLib::refineCell::refineCell()
    :
    cellNo_(-1),
    direction_(Zero)
{}


tnbLib::refineCell::refineCell(const label celli, const vector& direction)
    :
    cellNo_(celli),
    direction_(direction)
{
    scalar magDir = mag(direction_);

    if (magDir < small)
    {
        FatalErrorInFunction
            << "(almost)zero vector as direction for cell " << cellNo_
            << abort(FatalError);
    }
    else if (mag(magDir - 1) > small)
    {
        // Normalize
        direction_ /= mag(direction_);
    }
}


tnbLib::refineCell::refineCell(Istream& is)
    :
    cellNo_(readLabel(is)),
    direction_(is)
{
    scalar magDir = mag(direction_);

    if (magDir < small)
    {
        FatalErrorInFunction
            << "(almost)zero vector as direction for cell " << cellNo_
            << abort(FatalError);
    }
    else if (mag(magDir - 1) > small)
    {
        // Normalize
        direction_ /= mag(direction_);
    }
}


// * * * * * * * * * * * * * * * IOstream Operators  * * * * * * * * * * * * //

tnbLib::Ostream& tnbLib::operator<<(Ostream& os, const refineCell& r)
{
    if (os.format() == IOstream::ASCII)
    {
        os << r.cellNo() << token::SPACE << r.direction();
    }
    else
    {
        os << r.cellNo() << r.direction();
    }
    return os;
}


// ************************************************************************* //