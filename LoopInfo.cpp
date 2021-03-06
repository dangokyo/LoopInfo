//===- Hello.cpp - Example code from "Writing an LLVM Pass" ---------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements a version of the LLVM pass to record the information 
// of loop in each module
//
//===----------------------------------------------------------------------===//

#include "llvm/ADT/Statistic.h"
#include "llvm/IR/Function.h"
#include "llvm/Pass.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/IR/DebugInfo.h"
using namespace llvm;

#define DEBUG_TYPE "loop"


StringRef *LoopBody = new StringRef("for.body");
STATISTIC(LoopCounter, "Counts number of loops greeted");

namespace {
  struct LoopInfo : public FunctionPass {
    static char ID; // Pass identification, replacement for typeid
    LoopInfo() : FunctionPass(ID) {}

    bool runOnFunction(Function &F) override {
      errs().write_escaped(F.getName()) << '\n';
      for(Function::iterator i=F.begin(), end = F.end(); i!=end; ++i)
      {
      		//errs()<<"Opcode:"<<i->getOpcode()) << '\n';
		if(!(i->getName().find(*LoopBody, 0)))
		{
			LoopCounter++;
			errs()<<i->getName()<<" "<<LoopCounter<< '\n';
			for(BasicBlock::const_iterator bb = i->begin(), End = i->end(); bb!=End;++bb)
			{
			int iOperand=0;
			int numOperand = int(bb->getNumOperands());
			//errs()<<"Numoperands:"<<int(bb->getNumOperands())<<'\n';
			errs()<<"Block info:"<<" "<<bb->getOpcodeName()<<'\n';
			//errs()<<"Operand info:"<<"\n";
				for(iOperand=0; iOperand < numOperand; iOperand++ )			
				{
					errs()<<"Operand "<<iOperand<<" info:"<<bb->getOperand(iOperand)->getValueID()<<' '<<bb->getOperand(iOperand)->getType()->getTypeID()<<'\n';
				}	
				/*if(MDNode *node = bb->getMetadata("dbg"))
				{
				DILocation Loc(node);
				unsigned line = Loc.getLineNumber();
				StringRef file = Loc.getFilename();
				StringRef Dir = Loc.getDirectory();
				//node->getOperand()->getName();
				errs()<<LoopCounter<<" "<<line<<" "<<file<<" "<<Dir<<"\n";
				}
				else
				{
					errs()<<"No metadata for current node"<<'\n';
				}*/	
			}
			errs()<<'\n';
		}
		else
		{	
			continue;
			//errs()<<i->getName()<< '\n'<<'\n';
		}
			
      }
      return false;
    }

    // We don't modify the program, so we preserve all analyses.
    void getAnalysisUsage(AnalysisUsage &AU) const override {
      AU.setPreservesAll();
    }
  };
}

char LoopInfo::ID = 0;
static RegisterPass<LoopInfo>
Y("LoopInfo", "Loop info analysis Pass (with getAnalysisUsage implemented)");
