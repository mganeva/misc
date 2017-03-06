#include <iostream>
#include <yaml-cpp/yaml.h>
#include <fstream>

struct Vec3 { int x; int y; int z;};
YAML::Emitter& operator << (YAML::Emitter& op, const Vec3& v) {
    op << YAML::Flow;
    op << YAML::BeginSeq << v.x << v.y << v.z << YAML::EndSeq;
    return op;
}

int main() {
    YAML::Emitter out;
    out << YAML::BeginSeq;
    out << "eggs";
    out << "bread";
    out << "milk";
    out << YAML::EndSeq;
    std::cout << "Here's the output YAML:\n" << out.c_str() << "\n" << std::endl;

    YAML::Emitter out2;
    out2 << YAML::BeginMap;
    out2 << YAML::Key << "name";
    out2 << YAML::Value << "Ryan Braun";
    out2 << YAML::Key << "position";
    out2 << YAML::Value << "LF";
    out2 << YAML::EndMap;
    std::cout << "Here's the output YAML:\n" << out2.c_str() <<"\n" << std::endl;

    YAML::Emitter out3;
    out3 << YAML::BeginMap;
    out3 << YAML::Key << "name";
    out3 << YAML::Value << "Barack Obama";
    out3 << YAML::Key << "children";
    out3 << YAML::Value << YAML::BeginSeq << "Sasha" << "Malia" << YAML::EndSeq;
    out3 << YAML::EndMap;
    std::cout << "Here's the output YAML:\n" << out3.c_str() << "\n" << std::endl;

    YAML::Emitter manipulations;
    manipulations << YAML::Literal << "A\n B\n  C";
    std::cout << "Here's the output YAML:\n" << manipulations.c_str() << "\n" << std::endl;

    YAML::Emitter manipulations2;
    manipulations2 << YAML::Flow;
    manipulations2 << YAML::BeginSeq << 2 << 3 << 5 << 7 << 11 << YAML::EndSeq;
    std::cout << "Here's the output YAML:\n" << manipulations2.c_str() << "\n" << std::endl;

    YAML::Emitter comments;
    comments << YAML::BeginMap;
    comments << YAML::Key << "method";
    comments << YAML::Value << "least squares";
    comments << YAML::Comment("should we change this method?");
    comments << YAML::EndMap;
    std::cout << "Here's the output YAML:\n" << comments.c_str() << "\n" << std::endl;

    YAML::Emitter anchors;
    anchors << YAML::BeginSeq;
    anchors << YAML::Anchor("fred");
    anchors << YAML::BeginMap;
    anchors << YAML::Key << "name" << YAML::Value << "Fred";
    anchors << YAML::Key << "age" << YAML::Value << "42";
    anchors << YAML::Alias("fred");
    anchors << YAML::EndSeq;
    std::cout << "Here's the output YAML:\n" << anchors.c_str() << "\n" << std::endl;

    std::vector <int> squares;
    squares.push_back(1);
    squares.push_back(4);
    squares.push_back(9);
    squares.push_back(16);

    std::map <std::string, int> ages;
    ages["Daniel"] = 26;
    ages["Jesse"] = 24;



    Vec3 v;
    v.x = 1;
    v.y = 2;
    v.z = 3;

    YAML::Emitter oper;
    oper << v;

    std::cout << "Here's the output YAML:\n" << oper.c_str() << "\n" << std::endl;


    YAML::Emitter manipulator;
    manipulator.SetIndent(4);
    manipulator.SetMapFormat(YAML::Flow);

    std::cout << "Here's the output YAML:\n" << manipulator.c_str() << "\n" << std::endl;

    YAML::Emitter container;
    container << YAML::BeginSeq;
    container << YAML::Flow << squares;
    container << ages;
    container << YAML::EndSeq;

    std::cout << "Here's the output YAML:\n" << container.c_str() << "\n" << std::endl;

    YAML::Emitter exercise;
    exercise << YAML::BeginMap << YAML::Key << "Studenten";
    exercise << YAML::Value << YAML::BeginMap << YAML::Key << "Anna";
    exercise << YAML::Value << YAML::BeginMap << YAML::Key << "Age" << YAML::Value << 18;
    exercise << YAML::Key << "Note" << YAML::Value << 1.2;
    exercise << YAML::EndMap;
    exercise << YAML::Key << "Tobias";
    exercise << YAML::Value << YAML::BeginMap << YAML::Key << "Age" << YAML::Value << 20;
    exercise << YAML::Key << "Note" << YAML::Value << 2.3;
    exercise << YAML::EndMap;
    exercise << YAML::Key << "Pruefungen";
    exercise << YAML::Value << YAML::BeginSeq << "Physik" << "Mathe" << "Bio";
    exercise << YAML::EndSeq << YAML::EndMap << YAML::EndMap;

    std::cout << "Here's the output YAML:\n" << exercise.c_str() << "\n" << std::endl;

    std::ofstream fout("Studenten.yaml");
    fout << exercise.c_str();


    YAML::Node primes = YAML::Load("[2, 3, 5, 7, 11]");
    for(YAML::const_iterator it = primes.begin(); it != primes.end(); ++it) {
        std::cout << it->as<int>() << std::endl;
    }

    primes.push_back(13);
    assert(primes.size() == 6);

    YAML::Node lineup = YAML::Load("{1B: Prince Fieder, 2B: Ricky Weeks, LF: Ryan Braun}");
    for(YAML::const_iterator it = lineup.begin(); it != lineup.end(); ++it) {
        std::cout << "Playing at "  << it->first.as<std::string>() << " is " << it->second.as<std::string>() << std::endl;
    }

    return 0;
}
