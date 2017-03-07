#include "SaveYda.h"

YAML::Emitter& operator << (YAML::Emitter& em,const ParStruct p) {
    em << YAML::BeginMap << YAML::Key << "name" << YAML::Value << p.name
        << YAML::Key << "unit" << YAML::Key << p.unit << YAML::Key << "val"
        << YAML::Value << p.value << YAML::Key << "stdv" << YAML::Value << p.stdv
        << YAML::EndMap;
    return em;
}

YAML::Emitter& operator << (YAML::Emitter& em,const Coordinate c) {
    em << YAML::BeginMap << YAML::Key << c.designation << YAML::Flow << YAML::BeginMap
       << YAML::Key << "name" << YAML::Value << c.name << YAML::Key << "unit"
       << YAML::Value << c.unit << YAML::EndMap << YAML::EndMap;
    return em;
}

YAML::Emitter& operator << (YAML::Emitter& em,const Spectrum s) {
    em << YAML::BeginMap << YAML::Key << "j" << YAML::Value << s.j
       << YAML::Key << "z" << YAML::Value << YAML::Flow << YAML::BeginSeq
       << YAML::Flow << YAML::BeginMap << YAML::Key << "val"
       << YAML::Value << s.z << YAML::EndMap << YAML::EndSeq
       << YAML::Key << "x" << YAML::Value << YAML::Flow << s.x
       << YAML::Key << "y" << YAML::Value << YAML::Flow << s.y
       << YAML::EndMap;
}

void SaveYda::writeHistory(YAML::Emitter &em) {
    em << history;
}

void SaveYda::writeHeader(YAML::Emitter& em) {
    em << YAML::BeginMap << YAML::Key << "Meta";
    em << YAML::Value << metadata;
    em << YAML::Key << "History" << YAML::Value;
    writeHistory(em);
    em << YAML::Key << "Coord" << coord;
    em << YAML::Key << "RPar" << rpar; //<< YAML::EndSeq;
    em << YAML::Key << "Slices" << slices;


}






