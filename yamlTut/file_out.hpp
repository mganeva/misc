//**************************************************************************************************
//*  FRIDA: fast reliable interactive data analysis
//*  (C) Joachim Wuttke 1990-, v2(C++) 2001-, this file 2009-
//*  http://apps.jcns.fz-juelich.de/frida
//**************************************************************************************************

//! \file  file_out.hpp
//! \brief NFileOut: write files.

#ifndef FILE_OUT_H
#define FILE_OUT_H


//! Method to save files.

namespace NFileOut
{
void save(string fmt, bool allow_overwrite = false);
}
#endif // FILE_OUT_H
