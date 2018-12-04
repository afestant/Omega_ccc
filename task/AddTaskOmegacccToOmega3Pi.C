AliAnalysisTaskSEOmegacccToOmega3Pi *AddTaskOmegacccToOmega3Pi()
{
    //
    //
    
    AliAnalysisTaskSEOmegacccToOmega3Pi *task = new AliAnalysisTaskSEOmegacccToOmega3Pi("MCanalysis");
    
    // Get the pointer to the existing analysis manager via the static access method.
    //==============================================================================
    AliAnalysisManager *mgr = AliAnalysisManager::GetAnalysisManager();
    if (!mgr) {
        ::Error("AddTaskD0Distr", "No analysis manager to connect to.");
        return NULL;
    }
    
    
    if(!mgr->GetMCtruthEventHandler()){
     Printf("AliAnalysisHFCorrOnFlySim; This task requires an input MC event handler");
     return NULL;
}
    
    mgr->AddTask(task);
    
    // Create containers for input/output
    
    TString inname = "cinput";
    TString histoname = "coutputEntries";
    TString listnamegen = "coutputListGen";
    TString listnamereco = "coutputListReco";

   
    
    
    AliAnalysisDataContainer *cinput = mgr->CreateContainer(inname,TChain::Class(),AliAnalysisManager::kInputContainer);
    TString outputfile = AliAnalysisManager::GetCommonFileName();
    outputfile += ":MCanalysis";
    
    AliAnalysisDataContainer *coutputEntries = mgr->CreateContainer(histoname,TH1F::Class(),AliAnalysisManager::kOutputContainer,outputfile.Data());
    AliAnalysisDataContainer *coutputListGen = mgr->CreateContainer(listnamegen,TList::Class(),AliAnalysisManager::kOutputContainer,outputfile.Data());
    AliAnalysisDataContainer *coutputListReco = mgr->CreateContainer(listnamereco,TList::Class(),AliAnalysisManager::kOutputContainer,outputfile.Data());
    

    
    mgr->ConnectInput(task,0,cinput);
    mgr->ConnectOutput(task,1,coutputEntries);
    mgr->ConnectOutput(task,2,coutputListGen);
    mgr->ConnectOutput(task,3,coutputListReco);
   
       
    return task;
    
    
    
}

