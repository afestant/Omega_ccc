#ifndef ALIRECODECAYOMEGAC_H
#define ALIRECODECAYOMEGAC_H

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

class AliKalmanTrack;
class AliVTrack;
class AliESDtrack;


class AliRecoDecayOmegac {
    
public:
    AliRecoDecayOmegac();
    AliRecoDecayOmegac(const AliRecoDecayOmegac& omegac);
    AliRecoDecayOmegac(const AliESDcascade &casc, const AliESDtrack &t, const AliESDVertex &vtx, const AliESDv0 &v, const AliESDtrack &tBachCasc);
    virtual ~AliRecoDecayOmegac(){}
    AliRecoDecayOmegac& operator=(const AliRecoDecayOmegac& omegac);
    
    void FillCand(const AliESDVertex &primvtx);
    float DecayLength(AliESDVertex *primV, AliESDVertex *secV);
    float DecayLengthXY(AliESDVertex *primV, AliESDVertex *secV);
    float CosPointingAngle(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]);
    float CosPointingAngleXY(AliESDVertex *primV, AliESDVertex *secV, Double_t p[3]);
    bool CheckIsSignal(AliESDEvent *evt, AliMCEvent *mcevt);
    bool IsSelected(double *cuts);
    
    float EtaCand(float p, float pz)  const {return 0.5*TMath::Log((p+pz)/(p-pz+1.e-13));}
    float YCand(float e, float pz)    const {return 0.5*TMath::Log((e+pz)/(e-pz+1.e-13));}
    float PhiCand(float px, float py) const {return TMath::Pi()+TMath::ATan2(-py,-px);}
    
    //getters
    AliExternalTrackParam GetTrackParamForCascade() {return fCascTrackParam;}
    AliExternalTrackParam GetTrackParamForCand()    {return fCandTrackParam;}
    float GetInvMass()        {return fInvMass;}
    float GetPt()             {return fPt;}
    float GetPx()                {return fPx;}
    float GetPy()                {return fPy;}
    float GetPz()                {return fPz;}
    float GetImpParRPhiCand() {return fImpParRPhi;}
    float GetImpParRPhiCasc() {return fCascImpParRPhi;}
    float GetImpParRPhiBach() {return fBachImpParRPhi;}
    float GetImpParZCand() {return fImpParZ;}
    float GetImpParZCasc() {return fCascImpParZ;}
    float GetImpParZBach() {return fBachImpParZ;}
    float GetDecVtxChi2()     {return fChi2NdfVtx;}
    float GetRap() {return fRap;}
    float GetPhi() {return fPhi;}
    float GetEta() {return fEta;}
    bool  GetIsTrueSignal() {return fIsTrueSignal;}
    int   GetCandMCLabel()  {return fLblCand;}
    
    //setters
    void SetTrackParamForCascade();
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
    float fCascImpParRPhi;
    float fCascImpParZ;
    float fBachImpParRPhi;
    float fBachImpParZ;
    float fDecayLength;
    float fDecayLengthXY;
    float fCosThetaP;
    float fCosThetaPXY;
    AliExternalTrackParam fCandTrackParam;
    AliExternalTrackParam fCascTrackParam;
    AliESDcascade fCasc;
    AliExternalTrackParam fV0TrackParam;
    AliESDtrack fCascBachelor;
    AliESDv0 fV0;
    AliESDtrack fBachelor;
    float fBzkG;
    int fLblCand;
    bool fIsTrueSignal;
    
    /// \cond CLASSIMP
    ClassDef(AliRecoDecayOmegac,1)
    /// \endcond
};
#endif
