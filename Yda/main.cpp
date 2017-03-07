#include "SaveYda.h"
#include <iostream>

int main(int argc, char* argv []) {

    SaveYda test;

    std::map<std::string,std::string> meta;
    meta["format"] = "yaml/frida 2.0";
    meta["type"] = "generic tabular data";
    test.setMetadata(meta);
    std::map<std::string,std::string> testGet = test.getMetadata();
    for(std::map<std::string,std::string>::iterator it = testGet.begin(); it != testGet.end(); ++it) {
        std::cout << it->first << "=>" << it->second << std::endl;
    }

    ParStruct par;
    par.name = "T";
    par.stdv = 0;
    par.unit = "K";
    par.value = 273.15;

    ParStruct par2;
    par2.name = "E";
    par2.stdv = 0;
    par2.unit = "mV";
    par2.value = 277.15;

    std::vector<ParStruct> parv;

    parv.push_back(par);
    parv.push_back(par2);

    test.setRpar(parv);

    Coordinate xcoo;
    xcoo.designation = "x";
    xcoo.name = "w";
    xcoo.unit = "meV";

    Coordinate ycoo;
    ycoo.designation = "y";
    ycoo.name = "S(q,w)";
    ycoo.unit = "meV-1";

    Coordinate zcoo;
    zcoo.designation = "z";
    zcoo.name = "2th";
    zcoo.unit = "deg";

    std::vector<Coordinate> coov;

    coov.push_back(xcoo);
    coov.push_back(ycoo);
    coov.push_back(zcoo);
    test.setCoord(coov);

    std::vector<std::string> his;
    his.push_back("<propsal number> <proposal title> <proposal authors>");
    his.push_back("<raw spectra> <Mandit algorithm, parameters>");
    test.setHistory(his);

    std::vector<double> xv;
    xv.push_back(0);
    xv.push_back(1);
    xv.push_back(2);
    xv.push_back(3);

    std::vector<double> yv;
    yv.push_back(10);
    yv.push_back(10.3);
    yv.push_back(10.6);
    yv.push_back(11);

    Spectrum sl1;
    sl1.j = 0;
    sl1.z = 0;
    sl1.x = xv;
    sl1.y = yv;

    std::vector<double> xv2;
    xv2.push_back(0);
    xv2.push_back(1);
    xv2.push_back(2);
    xv2.push_back(3);

    std::vector<double> yv2;
    yv2.push_back(11);
    yv2.push_back(11.3);
    yv2.push_back(11.6);
    yv2.push_back(12);

    Spectrum sl2;
    sl2.j = 1;
    sl2.z = 1;
    sl2.x = xv2;
    sl2.y = yv2;

    std::vector<Spectrum> spe;
    spe.push_back(sl1);
    spe.push_back(sl2);

    test.setSlices(spe);

    YAML::Emitter out;

    test.writeHeader(out);

    std::cout << "Here's the output YAML:\n" << out.c_str() << "\n" << std::endl;

    return 0;
}
