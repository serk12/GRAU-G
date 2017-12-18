#include "modelInfo01.h"

void ModelInfo01::onPluginLoad()
{

}

void ModelInfo01::preFrame() 
{
	
}

void ModelInfo01::postFrame() 
{
	const vector<Object>& obj = this->scene()->objects();
	cout << "#objects: " << obj.size() << endl;
	float qttyFaces = 0;
	float qttyVert  = 0;
	float qttyTri   = 0;	
	for(int i = 0; i < obj.size(); ++i){
		qttyFaces += obj[i].faces().size();
		for(int j = 0; j < obj[i].faces().size(); ++j){
			qttyTri += (obj[i].faces()[j].numVertices() == 3) ? 1 : 0;		
		}		
		qttyVert  += obj[i].vertices().size();
	}
	cout << "#poligons: " << qttyFaces << endl;
	cout << "#vertices: " << qttyVert  << endl;
	cout << "#perTrian: " << (qttyTri/qttyFaces)*100 << "%" << endl; 
}

#if QT_VERSION < 0x050000
Q_EXPORT_PLUGIN2(modelInfo01, ModelInfo01)   // plugin name, plugin class
#endif

