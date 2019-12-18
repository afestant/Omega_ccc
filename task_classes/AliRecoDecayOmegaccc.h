#ifndef ALICERECODECAYOMEGACCC_H
#define ALICERECODECAYOMEGACCC_H

/* Copyright(c) 1998-2009, ALICE Experiment at CERN, All rights reserved. *
 * See cxx source for full Copyright notice                               */

/* $Id$ */
#include "AliGenParam.h"
#include "AliGenerator.h"
#include "AliRunLoader.h"
#include "AliRun.h"
#include "AliMCEvent.h"
#include "AliStack.h"
#include "AliESDEvent.h"
#include "AliESDUtils.h"
#include "AliESDcascade.h"
#include "AliESDVertex.h"
#include "AliExternalTrackParam.h"
#include "AliRecoDecayOmegac.h"
#include "AliRecoDecayOmegacc.h"

class AliKalmanTrack;
class AliVTrack;
class AliESDtrack;


class AliRecoDecayOmegaccc {
    
public:
    AliRecoDecayOmegaccc();
    AliRecoDecayOmegaccc(const AliRecoDecayOmegaccc& omegaccc);
    AliRecoDecayOmegaccc(const AliRecoDecayOmegacc &omegacc, const AliESDtrack &t, const AliESDVertex &vtx);
    virtual ~AliRecoDecayOmegaccc(){}
    AliRecoDecayOmegaccc& operator=(const AliRecoDecayOmegaccc& omegaccc);
    
    void FillCand(const AliESDVertex &primvtx);
    float DecayLength(AliESDVertex *primV, AliESDVertex *secV);
    float DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV);
    float DecayLengthError(AliESDVertex *primV, AliESDVertex *secV);
    float DecayLengthErrorXY(AliESDVertex *primV, AliESDVertex *secV);
    float NormalizedDecayLength(AliESDVertex *primV, AliESDVertex *secV) {return DecayLength(primV, secV)/DecayLengthError(primV, secV);}
    float NormalizedDecayLengthXY(AliESDVertex *primV, AliESDVertex *secV) {return DecayLengthXY(primV, secV)/DecayLengthErrorXY(primV, secV);}
    float CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]);
    float CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]);
    bool CheckIsSignal(AliESDEvent *evt, AliMCEvent *mcevt);
    bool IsSelected(double *cuts);
    
    template <class T, class P> void PhiAndThetaToVertex(AliESDVertex *primV, AliESDVertex *secV, P &phi, T &theta) const;
    Double_t RotatedCovMatrixXX(AliESDVertex *vtx, Double_t phi = 0., Double_t theta = 0.) const;
    
    float EtaCand(float p, float pz)  const {return 0.5*TMath::Log((p+pz)/(p-pz+1.e-13));}
    float YCand(float e, float pz)    const {return 0.5*TMath::Log((e+pz)/(e-pz+1.e-13));}
    float PhiCand(float px, float py) const {return TMath::Pi()+TMath::ATan2(-py,-px);}
    
    //getters
    AliExternalTrackParam GetTrackParamForCand()  {return fCandTrackParam;}
    float GetInvMass()           {return fInvMass;}
    float GetPt()                {return fPt;}
    float GetPx()                {return fPx;}
    float GetPy()                {return fPy;}
    float GetPz()                {return fPz;}
    float GetImpParRPhiCand()    {return fImpParRPhi;}
    float GetImpParRPhiBach()    {return fBachImpParRPhi;}
    float GetImpParZCand()    {return fImpParZ;}
    float GetImpParZBach()    {return fBachImpParZ;}
    float GetDecVtxChi2()        {return fChi2NdfVtx;}
    float GetRap() {return fRap;}
    float GetPhi() {return fPhi;}
    float GetEta() {return fEta;}
    bool  GetIsTrueSignal() {return fIsTrueSignal;}
    int   GetCandMCLabel()  {return fLblCand;}
    
    //setters
    void SetTrackParamForCand();
    void SetMagneticField(float val) {fBzkG=val;}
    
protected:
    AliESDVertex fDecayVtx;
    float fChi2NdfVtx;
    float fPx;
    float fPy;
    float fPz;
    float fPt;
    float fP;
    float fE;
    float fInvMass;
    float fEta;
    float fRap;
    float fPhi;
    float fImpParRPhi;
    float fImpParZ;
    float fWeakDauImpParRPhi;
    float fWeakDauImpParZ;
    float fBachImpParRPhi;
    float fBachImpParZ;
    float fDecayLength;
    float fDecayLengthXY;
    float fDecayLengthError;
    float fDecayLengthXYError;
    float fNormDecayLength;
    float fNormDecayLengthXY;
    float fCosThetaP;
    float fCosThetaPXY;
    AliExternalTrackParam fCandTrackParam;
    AliExternalTrackParam fWeakDauTrackParam;
    AliRecoDecayOmegacc fWeakDau;
    AliESDtrack fBachelor;
    float fBzkG;
    int fLblCand;
    bool fIsTrueSignal;
    
    /// \cond CLASSIMP
    ClassDef(AliRecoDecayOmegaccc,1)
    /// \endcond
};
#endif
