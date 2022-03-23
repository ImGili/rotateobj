#include "cmdline.h"
#include <windows.h>
#include <iostream>
#include <filesystem>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/MatrixTransform>
typedef std::filesystem::path FPath;
typedef std::vector<FPath> FPathVector; 

void GetObjPathFile(const FPath& fpath);
static FPathVector s_ObjPaths;
int main(int argc, char *argv[])
{
    cmdline::parser a;
    a.add<std::string>("input", 'i', "input directory name", true, "");
    a.add<std::string>("output", 'o', "output file name", true, "");
    a.add<int>("angle", 'a', "rotate angle", false, 90, cmdline::range(-90, 90));
    a.add<std::string>("axis", 'ax', "axis", false, "X");
    a.parse_check(argc, argv);
    GetObjPathFile(a.get<std::string>("input"));

    for (auto objpath : s_ObjPaths)
    {
        std::cout << objpath.filename() << std::endl;
        std::cout << objpath.parent_path().filename() << std::endl;
        auto node = osgDB::readNodeFile(objpath.string());
        osg::MatrixTransform* matrixtransform = new osg::MatrixTransform;
        osg::Vec3 Axis = {1, 0, 0};
        if (a.get<std::string>("axis") == "X")
        {
            Axis = {1, 0, 0};
        }
        else if (a.get<std::string>("axis") == "Y")
        {
            Axis = {0, 1, 0};
        }
        else if (a.get<std::string>("axis") == "Z")
        {
            Axis = {0, 0, 1};
        }
        
        matrixtransform->setMatrix(osg::Matrix::rotate(osg::DegreesToRadians(90.0f), Axis));
        matrixtransform->addChild(node);
        std::filesystem::path parentpath = objpath.parent_path().filename();
        std::filesystem::path outpath = a.get<std::string>("output");
        outpath /= parentpath;
        std::cout << outpath << std::endl;
        bool flag = CreateDirectory(outpath.string().c_str(), NULL);
        outpath /= objpath.filename();
        std::cout << outpath << std::endl;
        osgDB::writeNodeFile(*matrixtransform, outpath.string());
    }
    
    return 0;
}

void GetObjPathFile(const FPath& fpath)
{
    for (auto& directoryEntry : std::filesystem::directory_iterator(fpath))
    {
        if (directoryEntry.is_directory())
        {
            GetObjPathFile(directoryEntry);
        }
        else
        {
            if (directoryEntry.path().extension() == ".obj")
            {
                std::cout << directoryEntry.path() << std::endl;
                s_ObjPaths.push_back(directoryEntry.path());
            }
        }
    }
}
