
/** Derived from DTGeometryAnalyzer by Nicola Amapane
 *
 *  \author M. Maggi - INFN Bari
 */

#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/EventSetup.h"
#include "FWCore/Framework/interface/ESHandle.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "Geometry/GEMGeometry/interface/GEMGeometry.h"
#include "Geometry/Records/interface/MuonGeometryRecord.h"
#include "Geometry/GEMGeometry/interface/GEMEtaPartitionSpecs.h"
#include "Geometry/CommonTopologies/interface/StripTopology.h"

#include "Geometry/CSCGeometry/interface/CSCGeometry.h"
#include "L1Trigger/CSCCommonTrigger/interface/CSCTriggerGeometry.h"

#include "DataFormats/Math/interface/deltaPhi.h"

#include <memory>
#include <fstream>
#include <string>
#include <cmath>
#include <vector>
#include <iomanip>
#include <set>

class GEMGeometryAnalyzer : public edm::EDAnalyzer {

public: 
  GEMGeometryAnalyzer( const edm::ParameterSet& pset);

  ~GEMGeometryAnalyzer();

  virtual void analyze( const edm::Event&, const edm::EventSetup& );
  
  const std::string& myName() { return myName_;}
  
private: 

  const int dashedLineWidth_;
  const std::string dashedLine_;
  const std::string myName_;
  std::ofstream ofos;
};

using namespace std;
GEMGeometryAnalyzer::GEMGeometryAnalyzer( const edm::ParameterSet& /*iConfig*/ )
  : dashedLineWidth_(104), dashedLine_( std::string(dashedLineWidth_, '-') ), 
    myName_( "GEMGeometryAnalyzer" ) 
{ 
  ofos.open("MytestOutput.out"); 
  ofos <<"======================== Opening output file"<< std::endl;
}


GEMGeometryAnalyzer::~GEMGeometryAnalyzer() 
{
  ofos.close();
  ofos <<"======================== Closing output file"<< std::endl;
}

void
GEMGeometryAnalyzer::analyze( const edm::Event& /*iEvent*/, const edm::EventSetup& iSetup )
{
  edm::ESHandle<GEMGeometry> gemGeo;
  iSetup.get<MuonGeometryRecord>().get(gemGeo);     
  
  edm::ESHandle<CSCGeometry> cscGeo;
  iSetup.get<MuonGeometryRecord>().get(cscGeo);
  CSCTriggerGeometry::setGeometry(cscGeo);

  ofos << myName() << ": Analyzer..." << std::endl;
  ofos << "start " << dashedLine_ << std::endl;



  cout << "It works!" << endl;

  ofos << dashedLine_ << " end" << std::endl;
}

//define this as a plug-in
#include "FWCore/Framework/interface/MakerMacros.h"
DEFINE_FWK_MODULE(GEMGeometryAnalyzer);
