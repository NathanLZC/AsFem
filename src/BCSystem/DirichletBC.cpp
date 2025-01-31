//****************************************************************
//* This file is part of the AsFem framework
//* A Simple Finite Element Method program (AsFem)
//* All rights reserved, Yang Bai/M3 Group@CopyRight 2020-present
//* https://github.com/M3Group/AsFem
//* Licensed under GNU GPLv3, please see LICENSE for details
//* https://www.gnu.org/licenses/gpl-3.0.en.html
//****************************************************************
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//+++ Author : Yang Bai
//+++ Date   : 2021.10.06
//+++ Purpose: implement the dirichlet boundary condition
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "BCSystem/DirichletBC.h"

DirichletBC::DirichletBC(){
    m_localU.resize(11,0.0);// the maximum dofs of each bc block is 10!
}

void DirichletBC::computeBCValue(const FECalcType &calctype,const double &penalty,const double &bcvalue,const nlohmann::json &json,
                                const LocalElmtInfo &elmtinfo,
                                const LocalElmtSolution &elmtsoln,
                                const vector<int> &dofids,
                                Vector &U,
                                SparseMatrix &K,
                                Vector &RHS){
    if(calctype==FECalcType::COMPUTERESIDUAL){
        for(int i=0;i<static_cast<int>(dofids.size());i++){
            RHS.insertValue(dofids[i],0.0);
        }
    }
    else if(calctype==FECalcType::COMPUTEJACOBIAN){
        for(int i=0;i<static_cast<int>(dofids.size());i++){
            K.insertValue(dofids[i],dofids[i],penalty);
        }
    }

    computeU(bcvalue,json,dofids,elmtinfo,elmtsoln,m_localU);
    for(int i=0;i<static_cast<int>(dofids.size());i++){
        U.insertValue(dofids[i],m_localU(i+1));
    }

}

void DirichletBC::computeU(const double &bcvalue,const nlohmann::json &json,const vector<int> &dofids,
                          const LocalElmtInfo &elmtinfo,
                          const LocalElmtSolution &elmtsoln,
                          VectorXd &localU){
    if(json.size()||elmtinfo.m_t||elmtsoln.m_gpU.size()){}
    for(int i=1;i<=static_cast<int>(dofids.size());i++){
        localU(i)=bcvalue;
    }
}