// Written by David Sheets
// TaxiVis product for analyzing trends in taxi trajectories.
// Copyright (C) 2012  David Sheets (dsheets4@kent.edu)
//
// This is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
#ifndef TAXISVISGUICONSTANTS_H
#define TAXISVISGUICONSTANTS_H

${CMAKE_AUTOGEN_MESSAGE_CXX}


#include <QtCore/QSize>

namespace TaxiVisGuiConstants
{
    const QSize MainWindowSizeDefault(${TAXIVIS_MAIN_DEFAULT_WIDTH},${TAXIVIS_MAIN_DEFAULT_HEIGHT});
    const QSize ChildWindowSizeDefault(${TAXIVIS_CHILD_DEFAULT_WIDTH},${TAXIVIS_CHILD_DEFAULT_HEIGHT});
};

#endif // TAXISVISGUICONSTANTS_H
