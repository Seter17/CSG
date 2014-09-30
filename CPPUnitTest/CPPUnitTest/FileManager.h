#pragma once
#include "Object.h"
#include <vector>
#include "config.h"

class FileManager
{
public:
    FileManager(void);
    ~FileManager(void);

    void ReadTestFile(const std::string& path, vector<enterprise_manager::Object<Odouble>*>& objects);
    void WriteTestFile(vector<enterprise_manager::Object<Odouble>*>& objects, const std::string& fileName);
    void ClearObjects(vector<enterprise_manager::Object<Odouble>*>& objects);
    
private:
    enum Transformation {Translation, Scale};

    void _ParseObjectHeader(std::string& headerString);
    void _ParseFacetHeader(std::string& facetString);
    void _ParsePoint(std::string& point, enterprise_manager::Vec3d& vertex);

    void _Transform(enterprise_manager::Vec3d& point, const vector<std::pair<Transformation, enterprise_manager::Vec3d>>& transformations);
};

