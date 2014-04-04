


void plotROC(TString sigFileName = "T1tttt_mLSP-200_mGo-1000_condorSub/T1tttt_mG1000_mLSP200_LPCSUSYPAT_SumJetMass_AnalysisTree.root", 
	     //TString bkgFileName = "QCD_condorSub/QCDsample_LPCSUSYPAT_ALL_SumJetMass_AnalysisTree.root"
	     TString bkgFileName = "TTJet_SemiLept_condorSub/TTJets_SemiLept_LPCSUSYPAT_ALL_SumJetMass_AnalysisTree.root"
	     //TString bkgFileName = "WJetsToLNu_400HTinf_condorSub/WJetsToLNu_400HTinf_LPCSUSYPAT_ALL_SumJetMass_AnalysisTree.root"
	     //TString bkgFileName = "ZJetsToNuNu_400HTinf_condorSub/ZJetsToNuNu_400HTinf_LPCSUSYPAT_ALL_SumJetMass_AnalysisTree.root"
	     ){

  gROOT->ProcessLine(".L ~/tdrstyle.C");
  setTDRStyle();

  gROOT->ProcessLine(".L rocCurve.C++");

  TFile* sigFile = new TFile(sigFileName);  
  TFile* bkgFile = new TFile(bkgFileName);

  ROCplotter* myROC = new ROCplotter((TTree*)sigFile->Get("TreeFiller/AnalysisTree"),(TTree*)bkgFile->Get("TreeFiller/AnalysisTree"));

  TGraph* sjm = myROC.make("sumJetMass_pt50",
			   500,0.,2500.,
			   2,1,2,
			   "(nJets_pt50>3&&Ht_pt50>500&&met_pt30>200)*eventWeight");

  TGraph* ht = myROC.make("Ht_pt50",
			  500,0.,2500.,
			  4,2,2,
			  "(nJets_pt50>3&&Ht_pt50>500&&met_pt30>200)*eventWeight");

  TCanvas* can = new TCanvas("can","can",500,500);

  ht->GetXaxis()->SetTitle("#epsilon_{sig}");
  ht->GetYaxis()->SetTitle("#epsilon_{bkg}");

  ht->Draw("AC");
  sjm->Draw("same");    
  
}
