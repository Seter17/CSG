#include "FileManager.h"
#include "Object.h"
#include <fstream>
#include <string>


using namespace std;

FileManager::FileManager(void) {}


FileManager::~FileManager(void) {}

const string headerDelimeter = ": ";
const string metaDelimeter = ", ";
const string coordDelimeter = "; ";
const string defaultColor = "0xD99308";

void FileManager::ReadTestFile(const string& path, vector<enterprise_manager::Object<Odouble>*>& objects) {
	ifstream file;
	file.open(path.c_str(), std::ifstream::in);

	if (!file.is_open()) {
		cout << " Failed to open" << endl;
		return;
	}

	string buffer;

	std::vector<enterprise_manager::Vec3<Odouble>> coord;
	std::vector<Oint> coordIndex;

	std::vector<std::pair<Transformation, enterprise_manager::Vec3d>> transformations;

	int index = -1;
	while (getline(file, buffer)) {
		if (buffer.empty())
			continue;

		size_t headerPos = buffer.find(headerDelimeter);
		string header = buffer.substr(0, headerPos);

		if (header == "Object") {

			if (coord.size() > 0) {
				coordIndex.push_back(-1);
				//this mean we end parsing previous object data so we can push it inside our list of objects
				objects.push_back(enterprise_manager::Object<Odouble>::CreateFromIndexedFaceSet(coord, coordIndex, false, false));

				//time to start from the beginning for new object
				index = -1;
				transformations.clear();
				coord.clear();
				coordIndex.clear();
			}

			string objectData = buffer.substr(headerPos + headerDelimeter.size());
			_ParseObjectHeader(objectData);
		}

		else if (header == "Facet") {
			if (coord.size() > 0) { // we already parse few coordinates and this is not the first facet
				coordIndex.push_back(-1);
			}

			string facetData = buffer.substr(headerPos + headerDelimeter.size());
			_ParseFacetHeader(facetData);
		}
		else if (header == "Translation") {
			enterprise_manager::Vec3d vector;
			string vectorData = buffer.substr(headerPos + headerDelimeter.size());
			_ParsePoint(vectorData, vector);
			cout << "Translation will be made along vector: (" << vector[0] << "; " << vector[1] << "; " << vector[2] << ")" << endl;
			transformations.push_back(std::make_pair(Translation, vector));
		}
		else if (header == "Scale") {
			enterprise_manager::Vec3d vector;
			string vectorData = buffer.substr(headerPos + headerDelimeter.size());
			enterprise_manager::Vec3d scale(stod(vectorData), 0, 0);
			cout << "Scale will be made in: (" << scale[0] << " units." << endl;
			transformations.push_back(std::make_pair(Scale, scale));
		}
		else {
			++index;
			enterprise_manager::Vec3d vertex;
			_ParsePoint(buffer, vertex);
			_Transform(vertex, transformations);
			coord.push_back(vertex);
			coordIndex.push_back(index);
		}
	}

	//init last object
	if (coord.size() > 0) {
		coordIndex.push_back(-1);//close last polygon
		objects.push_back(enterprise_manager::Object<Odouble>::CreateFromIndexedFaceSet(coord, coordIndex, false, false));
	}
}

void FileManager::WriteTestFile(vector<enterprise_manager::Object<Odouble>*>& objects, const std::string& fileName) {
	ofstream file;
	file.open(fileName.c_str());

	for (Oint i = 0; i < objects.size(); ++i) {
		file << "Object" << headerDelimeter << objects[i]->polygon().size() << metaDelimeter << "Object" << i << metaDelimeter << defaultColor << endl;
		for (Oint j = 0; j < objects[i]->polygon().size(); ++j) {
			file << "Facet" << headerDelimeter << objects[i]->polygon()[j]->vertex().size() << metaDelimeter << "Facet" << j << endl;
			for (Oint k = 0; k < objects[i]->polygon()[j]->vertex().size(); ++k) {
				file << objects[i]->polygon()[j]->vertex()[k]->point()[0] << coordDelimeter
					<< objects[i]->polygon()[j]->vertex()[k]->point()[1]
					<< coordDelimeter << objects[i]->polygon()[j]->vertex()[k]->point()[2] << endl;
			}
		}
	}
}

void FileManager::_ParseObjectHeader(string& headerString) {
	size_t amountPos = headerString.find_first_of(metaDelimeter);

	int amounOfFacets;
	string id, color;

	if (amountPos != string::npos) {
		string test = headerString.substr(0, amountPos);
		amounOfFacets = stoi(headerString.substr(0, amountPos));

		headerString = headerString.substr(amountPos + metaDelimeter.size());

		size_t colorPos = headerString.find(metaDelimeter);

		if (colorPos != string::npos) {
			id = headerString.substr(0, colorPos);
			color = headerString.substr(colorPos + metaDelimeter.size());
		}
		else
			id = headerString; //no color data
	}
	else
		amounOfFacets = stoi(headerString); //only amount of facets specified

	cout << "Object " << id << " was created with " << amounOfFacets << " facets of color " << color << endl;
}

void FileManager::_ParseFacetHeader(string& facetString) {
	size_t amountPos = facetString.find_first_of(metaDelimeter);

	int amounOfPoints;
	string id;

	if (amountPos != string::npos) {
		string test = facetString.substr(0, amountPos);
		amounOfPoints = stoi(facetString.substr(0, amountPos));
		id = facetString.substr(amountPos + metaDelimeter.size());
	}
	else
		amounOfPoints = stoi(facetString); //only amount of points specified

	cout << "\tFacet " << id << " is existing with " << amounOfPoints << " points" << endl;

}

void FileManager::_ParsePoint(std::string& point, enterprise_manager::Vec3d& vertex) {
	if (point[point.length() - 1] == ';')
		point.erase(point.length() - 1);

	size_t xPos = point.find(coordDelimeter);
	size_t yPos = point.find_last_of(coordDelimeter);

	vertex[0] = stod(point.substr(0, xPos));
	vertex[1] = stod(point.substr(xPos + 1, yPos));
	vertex[2] = stod(point.substr(yPos + 1));

	cout << "\t\tX:" << vertex[0] << " Y:" << vertex[1] << " Z:" << vertex[2] << endl;
}

void FileManager::ClearObjects(vector<enterprise_manager::Object<Odouble>*>& objects) {
	if (objects.size() == 0)
		return;
	for (size_t i = 0; i < objects.size(); ++i) {
		delete objects[i];
	}
	objects.clear();
}

void FileManager::_Transform(enterprise_manager::Vec3d& point, const vector<std::pair<Transformation, enterprise_manager::Vec3d>>& transformations) {
	for (Oint i = 0; i < transformations.size(); ++i) {
		if (transformations[i].first == Translation) {
			point += transformations[i].second;
		}
		else if (transformations[i].first == Scale) {
			point *= transformations[i].second[0];
		}
	}
}
