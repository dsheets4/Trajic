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
#ifndef COMMON_DEFINITIONS_H
#define COMMON_DEFINITIONS_H

${CMAKE_AUTOGEN_MESSAGE_CXX}


#include <string>

namespace CommonDefinitions
{
   // =========================================================================
   // Application information.

   //! Provides a centralizing name for the application so that it can be 
   //! modified more easily later (e.g. for translation).
   const std::string sAppName   = "${PROJECT_NAME}";

   //! Application version number.
   const std::string sVersion   = "${VER_MAJOR}.${VER_MINOR}.${VER_PATCH}";


   // =========================================================================
   // Common directories

   //! Directory containing the HTML and other related www material
   const std::string sWwwDir          = "${WWW_DIR}";

   //! Directory containing input and output data files.
   const std::string sDataDir         = "${DATA_DIR}";

   //! Directory containing example scripts for the application.
   const std::string sScriptDir       = "${SCRIPT_DIR}";

   //! Directory the Stanford Topic Modeling toolbox materials.
   const std::string sTmtDir          = "${TMT_DIR}";

   //! Directory the Stanford Topic Modeling toolbox materials.
   const std::string sImageCaptureDir = "${IMGCAP_DIR}";
};

#endif // COMMON_DEFINITIONS_H

