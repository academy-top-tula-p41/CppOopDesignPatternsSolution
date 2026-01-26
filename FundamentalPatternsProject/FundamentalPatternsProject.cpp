#include <iostream>

#include "PropertyContainerPattern.h"

#include "Examples.h"

int main()
{
    Movie warAndPiece("War and Piece");

    warAndPiece.SetProperty("country", "USSR");
    warAndPiece.SetProperty("year", "1975");
    warAndPiece.SetProperty("director", "S. Bondarchuk");
    warAndPiece.SetProperty("year", "1965");

    auto propertyNames = warAndPiece.GetPropertyNames();

    std::cout << "Movie name: " << warAndPiece.Title()
              << " (" << warAndPiece.Id() << ")\n";

    for (auto it{ propertyNames.begin() }; it != propertyNames.end(); it++)
        std::cout << "\t" << *it << ": " << warAndPiece.GetProperty(*it) << "\n";

    Movie ironia("Ironia sudby");
    std::cout << "Movie name: " << ironia.Title()
        << " (" << ironia.Id() << ")\n";
}
