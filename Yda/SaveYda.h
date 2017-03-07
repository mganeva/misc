#include <yaml-cpp/yaml.h>

struct ParStruct {
    std::string name;
    std::string unit;
    double value;
    double stdv;
};

struct Coordinate {
    std::string name;
    std::string unit;
    std::string designation;
};

struct Spectrum {
    int j;
    double z;
    std::vector<double> x;
    std::vector<double> y;
};

YAML::Emitter& operator << (YAML::Emitter& em,const ParStruct p);
YAML::Emitter& operator << (YAML::Emitter& em,const Coordinate c);
YAML::Emitter& operator << (YAML::Emitter& em,const Spectrum s);

class SaveYda {
public:

    std::map<std::string, std::string> metadata;
    std::vector<ParStruct> rpar;
    std::vector<std::string> history;
    std::string m_filename;
    std::vector<Coordinate> coord;
    std::vector<Spectrum> slices;


    std::map<std::string, std::string> getMetadata() {return metadata;}
    std::vector<ParStruct>  getRpar() {return rpar;}
    std::vector<std::string> getHistory() { return history; }
    std::string getM_filename() { return m_filename;}
    std::vector<Coordinate> getCoords() { return coord;}
    std::vector<Spectrum> getSlices() { return slices; }

    void setMetadata(std::map<std::string, std::string> nMetadata) { metadata = nMetadata;}
    void setRpar(std::vector<ParStruct>  nRpar) { rpar = nRpar;}
    void setHistory(std::vector<std::string> nHistory) { history = nHistory; }
    void setM_filename(std::string  filename) { m_filename = filename;}
    void setCoord(std::vector<Coordinate>  nCoord) { coord = nCoord;}
    void setSlices(std::vector<Spectrum> nSlices) { slices = nSlices; }

    void writeHeader(YAML::Emitter& em);
    void writeHistory(YAML::Emitter& em);


 };



