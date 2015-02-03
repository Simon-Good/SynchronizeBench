#include "OntologyParser.h"

OntologyParser::~OntologyParser(void)
{
}

OntologyParser::OntologyParser(){
	in = bfs::path("demo_ontology.owl");
	mLoadfile();
}

void OntologyParser::getDependencies(string nodeNm, vector<string> *dependency){
	this->loadNode(nodeNm);
	getFromStore("dependOn", dependency);
}

void OntologyParser::getConnectedTo(string nodeNm, vector<string>* connect){
	this->loadNode(nodeNm);
	getFromStore("connectedTo", connect);
}

void OntologyParser::getFeature(string nodeNm, vector<string>* feature){
	this->loadNode(nodeNm);
	getFromStore("hasFeature", feature);
}

string OntologyParser::getFeatureLink(string featureName){
	this->loadNode(featureName);
	return this->getFromStore("featureLink");
}

string OntologyParser::getId(string nodeNm){
	this->loadNode(nodeNm);
	string idName = getFromStore("ID");
	smatch m;
	regex reg("\"(\\d*)\"");
	regex_match(idName, m, reg);
	string ret = m[1];
	return ret;
}

string OntologyParser::getFromStore(string keyword, vector<string>* vec){
	string pred, obj;
	BOOST_FOREACH(
		owlcpp::Triple const&t, 
		store.find_triple(*id, owlcpp::any(), owlcpp::any(),  owlcpp::any())){
			pred = to_string(t.pred_, store);
			obj = to_string(t.obj_, store);
			size_t pos = pred.find("#" + keyword);
			if(pos != string::npos){
				pred = pred.substr(pos, pred.length());
				pos = obj.find("#");
				if(vec != NULL){
					vec->push_back(obj.substr(pos +1, obj.length()));
				}else if(pos != string::npos){
					return obj.substr(pos +1, obj.length());
				}else{
					return obj;
				}
			}
	}
	return "";
}

string OntologyParser::getFeatureBelong(string featureName){
	this->loadNode(featureName);
	return getFromStore("featureBelong");
}

void OntologyParser::getFeatureParameter(string featureName, float &angle, osg::Vec3 *vec){
	this->loadNode(featureName);
	string obj = this->getFromStore("AxisDirection");
	regex reg("\"(.*) (.*) (.*) (.*)\"");
	smatch m;
	regex_match(obj, m, reg);
	angle = stof(m[1]);
	vec->set(stof(m[2]), stof(m[3]), stof(m[4]));
}



void OntologyParser::loadNode(string nodeNm){
	string indie = iri + "#" + nodeNm;
	id = store.find_node_iri(indie);
}

void OntologyParser::mLoadfile(){
	try {
		owlcpp::Catalog cat;
		add(cat, in);
		load_file(in, store);
		BOOST_FOREACH(owlcpp::Doc_id id, cat){
			iri = cat.ontology_iri_str(id);
			break;
		}
	} catch(...) {
		std::cerr << boost::current_exception_diagnostic_information() << std::endl;
	}
}
