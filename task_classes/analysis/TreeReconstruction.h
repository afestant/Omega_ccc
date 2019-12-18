//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Thu Jun 27 12:04:24 2019 by ROOT version 6.16/00
// from TTree TreeReconstruction/TreeReconstruction
// found on file: signal/AnalysisResults.root
//////////////////////////////////////////////////////////

#ifndef TreeReconstruction_h
#define TreeReconstruction_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.

class TreeReconstruction {
public :
   TTree          *fChain;   //!pointer to the analyzed TTree or TChain
   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.

   // Declaration of leaf types
   Int_t           fParticle_pdg;
   Int_t           fParticle_pdgMoth;
   Float_t         fParticle_pt;
   Float_t         fParticle_p;
   Float_t         fParticle_eta;
   Float_t         fParticle_rap;
   Float_t         fParticle_phi;
   Float_t         fParticle_x;
   Float_t         fParticle_y;
   Float_t         fParticle_z;
   Float_t         fParticle_rxy;
   Int_t           fParticle_NhitsAss;
   Int_t           fParticle_NhitsReco;
   Bool_t          fParticle_isReco;

   // List of branches
   TBranch        *b_fParticle_pdg;   //!
   TBranch        *b_fParticle_pdgMoth;   //!
   TBranch        *b_fParticle_pt;   //!
   TBranch        *b_fParticle_p;   //!
   TBranch        *b_fParticle_eta;   //!
   TBranch        *b_fParticle_Rap;   //!
   TBranch        *b_fParticle_phi;   //!
   TBranch        *b_fParticle_x;   //!
   TBranch        *b_fParticle_y;   //!
   TBranch        *b_fParticle_z;   //!
   TBranch        *b_fParticle_rxy;   //!
   TBranch        *b_fParticle_NhitsAss;   //!
   TBranch        *b_fParticle_NhitsReco;   //!
   TBranch        *b_fParticle_isReco;   //!

   TreeReconstruction(TTree *tree=0);
   virtual ~TreeReconstruction();
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

#ifdef TreeReconstruction_cxx
TreeReconstruction::TreeReconstruction(TTree *tree) : fChain(0) 
{
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
   if (tree == 0) {
      TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("signal/AnalysisResults.root");
      if (!f || !f->IsOpen()) {
         f = new TFile("signal/AnalysisResults.root");
      }
      TDirectory * dir = (TDirectory*)f->Get("signal/AnalysisResults.root:/MCanalysis");
      dir->GetObject("TreeReconstruction",tree);

   }
   Init(tree);
}

TreeReconstruction::~TreeReconstruction()
{
   if (!fChain) return;
   delete fChain->GetCurrentFile();
}

Int_t TreeReconstruction::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!fChain) return 0;
   return fChain->GetEntry(entry);
}
Int_t TreeReconstruction::GetEntriesFast()
{
    // Read contents of entry.
    if (!fChain) return 0;
    return fChain->GetEntriesFast();
}
Long64_t TreeReconstruction::LoadTree(Long64_t entry)
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

void TreeReconstruction::Init(TTree *tree)
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

   fChain->SetBranchAddress("fParticle_pdg", &fParticle_pdg, &b_fParticle_pdg);
   fChain->SetBranchAddress("fParticle_pdgMoth", &fParticle_pdgMoth, &b_fParticle_pdgMoth);
   fChain->SetBranchAddress("fParticle_pt", &fParticle_pt, &b_fParticle_pt);
   fChain->SetBranchAddress("fParticle_p", &fParticle_p, &b_fParticle_p);
   fChain->SetBranchAddress("fParticle_eta", &fParticle_eta, &b_fParticle_eta);
   fChain->SetBranchAddress("fParticle_rap", &fParticle_rap, &b_fParticle_Rap);
   fChain->SetBranchAddress("fParticle_phi", &fParticle_phi, &b_fParticle_phi);
   fChain->SetBranchAddress("fParticle_x", &fParticle_x, &b_fParticle_x);
   fChain->SetBranchAddress("fParticle_y", &fParticle_y, &b_fParticle_y);
   fChain->SetBranchAddress("fParticle_z", &fParticle_z, &b_fParticle_z);
   fChain->SetBranchAddress("fParticle_rxy", &fParticle_rxy, &b_fParticle_rxy);
   fChain->SetBranchAddress("fParticle_NhitsAss", &fParticle_NhitsAss, &b_fParticle_NhitsAss);
   fChain->SetBranchAddress("fParticle_NhitsReco", &fParticle_NhitsReco, &b_fParticle_NhitsReco);
   fChain->SetBranchAddress("fParticle_isReco", &fParticle_isReco, &b_fParticle_isReco);
   Notify();
}

Bool_t TreeReconstruction::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void TreeReconstruction::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!fChain) return;
   fChain->Show(entry);
}
Int_t TreeReconstruction::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef TreeReconstruction_cxx
