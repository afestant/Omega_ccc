//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 12:04:24 2019 by ROOT version 6.16/00
// from TTree TreeRecoTracks/TreeRecoTracks
// found on file: signal/AnalysisResults.root
//////////////////////////////////////////////////////////

#ifndef TreeRecoTracks_h
#define TreeRecoTracks_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeRecoTracks {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Float_t         fReco_pt;
   Float_t         fReco_phi;
   Float_t         fReco_eta;
   Float_t         fReco_y;
   Float_t         fGen_pt;
   Float_t         fGen_eta;
   Float_t         fGen_rxy;
   Int_t           fReco_nhits;
   Int_t           fReco_MClabel;
   Int_t           fReco_MClabelMother;
   Float_t         fGen_ptMother;
   Int_t           fReco_pdg;
   Int_t           fReco_pdgMother;
   Int_t           fReco_nReconstructableHits;

   // List of branches
   TBranch        *b_fReco_pt;   //!
   TBranch        *b_fReco_phi;   //!
   TBranch        *b_fReco_eta;   //!
   TBranch        *b_fReco_y;   //!
   TBranch        *b_fGen_pt;   //!
   TBranch        *b_fGen_eta;   //!
   TBranch        *b_fGen_rxy;   //!
   TBranch        *b_fReco_nhits;   //!
   TBranch        *b_fReco_MClabel;   //!
   TBranch        *b_fReco_MClabelMother;   //!
   TBranch        *b_fGen_ptMother;   //!
   TBranch        *b_fReco_pdg;   //!
   TBranch        *b_fReco_pdgMother;   //!
   TBranch        *b_fReco_nReconstructableHits;   //!

   TreeRecoTracks(TTree *tree=0);
   virtual ~TreeRecoTracks();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Int_t    GetEntriesFast();
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   //virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef TreeRecoTracks_cxx
TreeRecoTracks::TreeRecoTracks(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signal/AnalysisResults.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signal/AnalysisResults.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("signal/AnalysisResults.root:/MCanalysis");
      dir->GetObject("TreeRecoTracks",tree);

   }
   Init(tree);
}

TreeRecoTracks::~TreeRecoTracks()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeRecoTracks::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t TreeRecoTracks::GetEntriesFast()
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntriesFast();
}
Long64_t TreeRecoTracks::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!fChain) return -5;
   Long64_t centry = fChain->LoadTree(entry);
   if (centry < 0) return centry;
   if (fChain->GetTreeNumber() != fCurrent) {
      fCurrent = fChain->GetTreeNumber();
      Notify();
   }
   return centry;
}

void TreeRecoTracks::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set branch addresses and branch pointers
   if (!tree) return;
   fChain = tree;
   fCurrent = -1;
   fChain->SetMakeClass(1);

   fChain->SetBranchAddress("fReco_pt", &fReco_pt, &b_fReco_pt);
   fChain->SetBranchAddress("fReco_phi", &fReco_phi, &b_fReco_phi);
   fChain->SetBranchAddress("fReco_eta", &fReco_eta, &b_fReco_eta);
   fChain->SetBranchAddress("fReco_y", &fReco_y, &b_fReco_y);
   fChain->SetBranchAddress("fGen_pt", &fGen_pt, &b_fGen_pt);
   fChain->SetBranchAddress("fGen_eta", &fGen_eta, &b_fGen_eta);
   fChain->SetBranchAddress("fGen_rxy", &fGen_rxy, &b_fGen_rxy);
   fChain->SetBranchAddress("fReco_nhits", &fReco_nhits, &b_fReco_nhits);
   fChain->SetBranchAddress("fReco_MClabel", &fReco_MClabel, &b_fReco_MClabel);
   fChain->SetBranchAddress("fReco_MClabelMother", &fReco_MClabelMother, &b_fReco_MClabelMother);
   fChain->SetBranchAddress("fGen_ptMother", &fGen_ptMother, &b_fGen_ptMother);
   fChain->SetBranchAddress("fReco_pdg", &fReco_pdg, &b_fReco_pdg);
   fChain->SetBranchAddress("fReco_pdgMother", &fReco_pdgMother, &b_fReco_pdgMother);
   fChain->SetBranchAddress("fReco_nReconstructableHits", &fReco_nReconstructableHits, &b_fReco_nReconstructableHits);
   Notify();
}

Bool_t TreeRecoTracks::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeRecoTracks::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeRecoTracks::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeRecoTracks_cxx
