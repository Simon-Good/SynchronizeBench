#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <osg/Vec3>
#ifndef Q_MOC_RUN
#include "boost/filesystem.hpp"
#include "boost/foreach.hpp"
#include "boost/program_options.hpp"
#include "owlcpp/io/catalog.hpp"
#include "owlcpp/lib_info.hpp"
#include "owlcpp/rdf/triple_store.hpp"
#include "owlcpp/io/input.hpp"
#endif

using namespace std;
namespace bfs = boost::filesystem;
class OntologyParser
{
public:
	OntologyParser();
	~OntologyParser();
	void mLoadfile();
	void loadNode(string nodeNm);
	string getFromStore(string keyword, vector<string>* vec = NULL);

	void getFeatureParameter(string featureName, float &angle, osg::Vec3 *vec);
	void getConnectedTo(string nodeNm, vector<string> *connect);
	void getDependencies(string nodeNm, vector<string> *dependency);
	void getFeature(string nodeNm, vector<string>* feature);
	string getId(string nodeNm);
	string getFeatureBelong(string featureName);
	string getFeatureLink(string featureName);
private:
	bfs::path in;
	owlcpp::Node_id const* id;
	owlcpp::Triple_store store;
	string iri;
};


