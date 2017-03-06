//**************************************************************************************************
//*  FRIDA: fast reliable interactive data analysis
//*  (C) Joachim Wuttke 1990-, v2(C++) 2001-, this file 2009-
//*  http://apps.jcns.fz-juelich.de/frida
//**************************************************************************************************

//! \file  file_out.cpp
//! \brief NFileOut: write files.

#include "defs.hpp"

#include <fstream>
#include <yaml-cpp/yaml.h>

#include "../readplus/ask.hpp"
#include "../trivia/yaml_out.hpp"

#include "file_out.hpp"
#include "fsel.hpp"
#include "loop.hpp"
#include "obj.hpp"
#include "olf.hpp"
#include "slice.hpp"

namespace NFileOut
{
void save_yda(std::ofstream& ofs, const COlo* f);
void save_y08(FILE* file, const COlo* f);
void save_csv(FILE* file, const COlo* f);
void save_tab(FILE* file, const COlo* f);
}


//! Queries file names, and writes files.

void NFileOut::save(string fmt, bool allow_overwrite)
{ // EMBEDDED_DIALOG
    string outfnam;
    FileIterator fiter(SFSel::instance()->sel());
    while (COlo* f = fiter.next()) {
        // query output file name
        outfnam = wask("Save as (." + fmt + ")", f->name);
        if (outfnam == "")
            return;
        f->name = outfnam;
        outfnam += "." + fmt;
        // document file save
        f->log_action("fs " + outfnam + " # " + triv::time2strg(time(0)));
        // prevent unintended overwriting
        if (!allow_overwrite) {
            FILE* file;
            if ((file = fopen(outfnam.c_str(), "r"))) {
                fclose(file);
                throw "file " + outfnam + " exists, use fso to overwrite";
            }
        }
        // save file
        if (fmt == "yda") {
            std::ofstream ofs;
            ofs.open(outfnam, std::ofstream::out);
            save_yda(ofs, f);
            ofs.close();
        } else {
            FILE* file;
            if (!(file = fopen(outfnam.c_str(), "w")))
                throw "cannot write to file " + outfnam;
            if (fmt == "y08") {
                save_y08(file, f);
            } else if (fmt == "csv") {
                save_csv(file, f);
            } else if (fmt == "tab") {
                save_tab(file, f);
            } else
                throw "BUG: Unknown format " + fmt;
            fclose(file);
        }
        f->as_on_disk = true;
    }
}


//! Writes a file in format y15.

void NFileOut::save_yda(std::ofstream& ofs, const COlo* f)
{
    const COld* fd = dynamic_cast<const COld*>(f);
    const COlc* fc = dynamic_cast<const COlc*>(f);

    YAML::Emitter out;
    out << YAML::BeginMap;

    out << YAML::Key << "Meta" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "format" << YAML::Value << "yaml/frida 2.0";
    out << YAML::Key << "type" << YAML::Value << (fd ? "generic tabular data" : "frida2 curve");
    out << YAML::EndMap;

    out << YAML::Key << "History" << YAML::Value << YAML::BeginSeq;
    for (string lin : f->lDoc)
        out << lin;
    out << YAML::EndSeq;

    out << YAML::Key << "Coord" << YAML::Value << YAML::BeginMap;
    out << YAML::Key << "x" << YAML::Value << YAML::Flow << YAML::BeginMap << YAML::Key << "name"
        << YAML::Value << f->xco.name << YAML::Key << "unit" << YAML::Value << f->xco.unit
        << YAML::EndMap;
    out << YAML::Key << "y" << YAML::Value << YAML::Flow << YAML::BeginMap << YAML::Key << "name"
        << YAML::Value << f->yco.name << YAML::Key << "unit" << YAML::Value << f->yco.unit
        << YAML::EndMap;
    out << YAML::Key << "z" << YAML::Value << YAML::Flow << YAML::BeginSeq;
    for (auto& zco : f->ZCo)
        out << YAML::BeginMap << YAML::Key << "name" << YAML::Value << zco.name << YAML::Key
            << "unit" << YAML::Value << zco.unit << YAML::EndMap;
    out << YAML::EndSeq;
    out << YAML::EndMap;

    out << YAML::Key << "RPar" << YAML::Value << YAML::BeginSeq;
    for (auto& rpar : f->RPar)
        out << YAML::BeginMap << YAML::Key << "name" << YAML::Value << rpar.Co.name << YAML::Key
            << "unit" << YAML::Value << rpar.Co.unit << YAML::Key << "val" << YAML::Value
            << rpar.val << YAML::Key << "stdv" << YAML::Value << rpar.dval << YAML::EndMap;
    out << YAML::EndSeq;

    if (fc) {
        out << YAML::Key << "Curve" << YAML::Value << YAML::BeginMap;
        out << YAML::Key << "expr" << YAML::Value << fc->expr;
        out << YAML::Key << "nPar" << YAML::Value << fc->nP;
        out << YAML::Key << "weighing" << YAML::Value << COlc::wgtNames[fc->weighing];
        out << YAML::Key << "chi2" << YAML::Value << fc->chi2;
        out << YAML::EndMap;
    }

    out << YAML::Key << "Slices" << YAML::Value << YAML::BeginSeq;
    for (size_t j = 0; j < f->V.size(); ++j) {
        out << YAML::BeginMap;
        out << YAML::Key << "j" << YAML::Value << j;
        const CSlice* s = f->V[j].get();
        out << YAML::Key << "z" << YAML::Value << YAML::Flow << YAML::BeginSeq;
        for (auto& z : s->z) {
            out << YAML::BeginMap;
            if (auto pz = PCAST<const CObjNum>(z)) {
                out << YAML::Key << "val" << YAML::Value << pz->to_r();
                if (auto pdz = PCAST<const CObjEnu>(z))
                    out << YAML::Key << "stdv" << YAML::Value << pdz->to_dr();
            } else
                out << YAML::Key << "string" << YAML::Value << z->to_s();
            out << YAML::EndMap;
        }
        out << YAML::EndSeq;
        if (fd) {
            const CSpec* sd = fd->VS(j);
            out << YAML::Key << "x" << YAML::Value << YAML::Flow << sd->x;
            out << YAML::Key << "y" << YAML::Value << YAML::Flow << sd->y;
            if (sd->has_dy())
                out << YAML::Key << "dy" << YAML::Value << YAML::Flow << sd->dy;
        } else {
            const CCurve* sc = fc->VC(j);
            out << YAML::Key << "p" << YAML::Value << YAML::Flow << sc->P;
            out << YAML::Key << "attr" << YAML::Value << YAML::Flow << sc->ParAttr;
            out << YAML::Key << "fitOutcome" << YAML::Value << sc->fitOutcome;
            out << YAML::Key << "fitChi2" << YAML::Value << sc->fitChi2;
            out << YAML::Key << "fitR2" << YAML::Value << sc->fitR2;
        }
        out << YAML::EndMap;
    }
    ofs << out.c_str(); // https://github.com/jbeder/yaml-cpp/issues/337
}


//! Writes a file in format y08.

void NFileOut::save_y08(FILE* file, const COlo* f)
{
    const COld* fd = dynamic_cast<const COld*>(f);
    const COlc* fc = dynamic_cast<const COlc*>(f);

    fprintf(
        file, "Meta:\n"
              "  format:  frida/y08 for yaml1\n"
              "  type:    %s\n",
        fd ? "generic tabular data" : "frida2 curve");

    fprintf(file, "History:\n");
    for (string lin : f->lDoc)
        fprintf(file, "- %s\n", triv::yaml(lin).c_str());

    fprintf(file, "Coord:\n");
    fprintf(
        file, "  x:\n    name: %s\n    unit: %s\n", triv::yaml(f->xco.name).c_str(),
        triv::yaml(f->xco.unit).c_str());
    fprintf(
        file, "  y:\n    name: %s\n    unit: %s\n", triv::yaml(f->yco.name).c_str(),
        triv::yaml(f->yco.unit).c_str());
    for (int i = 0; i < f->ZCo.size(); i++)
        fprintf(
            file, "  z%i:\n    name: %s\n    unit: %s\n", i, triv::yaml(f->ZCo[i].name).c_str(),
            triv::yaml(f->ZCo[i].unit).c_str());

    fprintf(file, "Param:\n");
    for (int i = 0; i < f->RPar.size(); i++)
        fprintf(
            file, "  -\n    name:  %s\n    unit:  %s\n    value: %20.15g\n",
            triv::yaml(f->RPar[i].Co.name).c_str(), triv::yaml(f->RPar[i].Co.unit).c_str(),
            f->RPar[i].val);

    if (fc) {
        fprintf(file, "Formula: %s\n", fc->expr.c_str());
    }

    fprintf(file, "Tables: # %i tables follow\n", f->nJ());

    for (int j = 0; j < f->nJ(); j++) {
        fprintf(file, "  - # table %i\n", j);
        CSlice* s = f->V[j].get();
        for (int i = 0; i < f->nZ(); i++) {
            if (RObjNum pz = PCAST<const CObjNum>(s->z[i])) {
                fprintf(file, "    z%i: %18.10g\n", i, pz->to_r());
                if (RObjNum pdz = PCAST<const CObjEnu>(s->z[i]))
                    fprintf(file, "    dz%i: %18.10g\n", i, pdz->to_dr());
            } else
                fprintf(file, "    z%i: %s\n", i, s->z[i]->to_s().c_str());
        }
        if (fd) {
            const CSpec* s = fd->VS(j);
            if (s->dy.size()) {
                fprintf(file, "    xyd: |2 # %i entries\n", (int)s->size());
                for (int i = 0; i < s->size(); i++)
                    fprintf(file, "      %20.15g %20.15g %20.15g\n", s->x[i], s->y[i], s->dy[i]);
            } else {
                fprintf(file, "    xy: |2 # %i entries\n", (int)s->size());
                for (int i = 0; i < s->size(); i++)
                    fprintf(file, "      %20.15g %20.15g\n", s->x[i], s->y[i]);
            }
        } else {
            CCurve* s = fc->VC(j);
            for (int i = 0; i < fc->nP; i++)
                fprintf(file, "    p%i: %18.10g\n", i, s->P[i]);
        }
    }
}


//! Writes y as tab-separated table.

void NFileOut::save_csv(FILE* file, const COlo* f)
{
    const COld* fd = dynamic_cast<const COld*>(f);
    if (!fd)
        throw S("csv save not implemented for non-data files");
    for (int j = 0; j < f->nJ(); j++) {
        for (int i = 0; i < fd->VS(j)->size(); ++i) {
            fprintf(file, "%g\t", fd->VS(j)->y[i]);
        }
        fprintf(file, "\n");
    }
}


//! Writes data as x-y columns with z header lines.

void NFileOut::save_tab(FILE* file, const COlo* f)
{
    const COld* fd = dynamic_cast<const COld*>(f);
    if (!fd)
        throw S("tab save not implemented for non-data files");
    for (int j = 0; j < f->nJ(); j++) {
        for (int iz = 0; iz < f->ZCo.size(); ++iz) {
            if (iz > 0)
                fprintf(file, "\t");
            fprintf(file, "%g", PCAST<const CObjNum>(fd->VS(j)->z[iz])->to_r());
        }
        fprintf(file, "\n");
        for (int i = 0; i < fd->VS(j)->size(); ++i) {
            fprintf(file, "%g\t%g\n", fd->VS(j)->x[i], fd->VS(j)->y[i]);
        }
        fprintf(file, "\n");
    }
}
